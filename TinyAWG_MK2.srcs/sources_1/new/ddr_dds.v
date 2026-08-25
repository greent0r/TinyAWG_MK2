`timescale 1 ns / 1 ps

module ddr_dds #
(
    parameter integer C_M_AXI_BURST_LEN    = 256,
    parameter integer C_M_AXI_ID_WIDTH     = 1,
    parameter integer C_M_AXI_ADDR_WIDTH   = 32,
    parameter integer C_M_AXI_DATA_WIDTH   = 64,
    parameter integer C_M_AXI_ARUSER_WIDTH = 0,
    parameter integer C_M_AXI_RUSER_WIDTH  = 0,
    parameter [31:0]  BASE_ADDR            = 32'h10000000,
    parameter integer FIFO_DEPTH           = 2048
)
(
    input  wire                                  clk,
    input  wire                                  rstn,
    input  wire                                  play_en,
    input  wire [31:0]                           total_points,

    output wire [C_M_AXI_ID_WIDTH-1:0]           M_AXI_ARID,
    output wire [C_M_AXI_ADDR_WIDTH-1:0]         M_AXI_ARADDR,
    output wire [7:0]                            M_AXI_ARLEN,
    output wire [2:0]                            M_AXI_ARSIZE,
    output wire [1:0]                            M_AXI_ARBURST,
    output wire                                  M_AXI_ARLOCK,
    output wire [3:0]                            M_AXI_ARCACHE,
    output wire [2:0]                            M_AXI_ARPROT,
    output wire [3:0]                            M_AXI_ARQOS,
    output wire [C_M_AXI_ARUSER_WIDTH-1:0]       M_AXI_ARUSER,
    output wire                                  M_AXI_ARVALID,
    input  wire                                  M_AXI_ARREADY,

    input  wire [C_M_AXI_ID_WIDTH-1:0]           M_AXI_RID,
    input  wire [C_M_AXI_DATA_WIDTH-1:0]         M_AXI_RDATA,
    input  wire [1:0]                            M_AXI_RRESP,
    input  wire                                  M_AXI_RLAST,
    input  wire [C_M_AXI_RUSER_WIDTH-1:0]        M_AXI_RUSER,
    input  wire                                  M_AXI_RVALID,
    output wire                                  M_AXI_RREADY,

    output wire [15:0]                           dds_out,
    output wire                                  dds_valid
);

    localparam integer FIFO_AW = $clog2(FIFO_DEPTH);

    // ========================================================================
    // play_en edge detect
    // ========================================================================
    reg play_en_d;
    always @(posedge clk) play_en_d <= play_en;

    wire play_en_fall = play_en_d && !play_en;

    reg discard_r;
    reg need_reset_r;

    // ========================================================================
    // total_points latch
    //
    // 只在 play_en 低电平期间更新内部 total_points_r。
    // 这样 PS 可以先 stop，再写 total_points，再 start，
    // PL 启动时使用的就是新值。
    // ========================================================================
    reg [31:0] total_points_r;

    always @(posedge clk) begin
        if (!rstn)
            total_points_r <= 32'd0;
        else if (!play_en)
            total_points_r <= total_points;
    end

    // ========================================================================
    // 本版本强制假设 total_points 是 4 的倍数。
    // 一个 64-bit word = 4 个 16-bit sample。
    // ========================================================================
    wire [31:0] total_words_w = total_points_r >> 2;

    // ========================================================================
    // 64-bit FIFO
    // ========================================================================
    (* ram_style = "block" *) reg [63:0] fifo_mem [0:FIFO_DEPTH-1];

    reg [FIFO_AW:0] wr_ptr;
    reg [FIFO_AW:0] rd_ptr;
    reg [FIFO_AW:0] fifo_cnt_r;
    reg             fifo_full_r;

    wire wen_fifo_w;
    wire rd_advance_w;

    // ========================================================================
    // AXI read state machine
    // ========================================================================
    localparam [1:0] ST_IDLE  = 2'd0,
                     ST_RADDR = 2'd1,
                     ST_RDATA = 2'd2;

    reg [1:0]  axi_state;
    reg        axi_arvalid;
    reg [7:0]  axi_arlen_r;

    reg [31:0] cur_addr;
    reg [31:0] words_to_end_r;

    // ========================================================================
    // AXI R channel
    //
    // 这里修正：RLAST 必须等 RREADY，真正收下 last beat 才回 IDLE。
    // ========================================================================
    assign M_AXI_RREADY = (axi_state == ST_RDATA) && !fifo_full_r;

    wire axi_wen_w = M_AXI_RVALID && M_AXI_RREADY;

    // discard_r 期间仍然接收 AXI 数据，但不写 FIFO
    assign wen_fifo_w = axi_wen_w && !discard_r;

    // ========================================================================
    // FIFO write pointer / count
    // ========================================================================
    always @(posedge clk) begin
        if (!rstn || play_en_fall) begin
            wr_ptr       <= 0;
            fifo_cnt_r   <= 0;
            fifo_full_r  <= 1'b0;
        end else begin
            if (wen_fifo_w)
                fifo_mem[wr_ptr[FIFO_AW-1:0]] <= M_AXI_RDATA;

            wr_ptr <= wen_fifo_w ? (wr_ptr + 1'b1) : wr_ptr;

            fifo_cnt_r <= fifo_cnt_r
                        + {{FIFO_AW{1'b0}}, wen_fifo_w}
                        - {{FIFO_AW{1'b0}}, rd_advance_w};

            fifo_full_r <= (fifo_cnt_r >= FIFO_DEPTH[FIFO_AW:0] - 3);
        end
    end

    // ========================================================================
    // need_reset_r
    //
    // play_en 下降后，必须等 AXI 当前事务回到 IDLE，
    // 才允许复位地址/长度并重新启动。
    // ========================================================================
    always @(posedge clk) begin
        if (!rstn)
            need_reset_r <= 1'b1;
        else if (play_en_fall)
            need_reset_r <= 1'b1;
        else if (need_reset_r && (axi_state == ST_IDLE))
            need_reset_r <= 1'b0;
    end

    // ========================================================================
    // Address / words remaining
    //
    // 不再使用 bytes_to_end / samples_remaining。
    // 直接使用 64-bit word 计数。
    // ========================================================================
    always @(posedge clk) begin
        if (!rstn) begin
            cur_addr        <= BASE_ADDR;
            words_to_end_r  <= 32'd0;
        end else if ((need_reset_r || !play_en) && (axi_state == ST_IDLE)) begin
            cur_addr        <= BASE_ADDR;
            words_to_end_r  <= total_words_w;
        end else if (play_en && axi_wen_w && !discard_r && (words_to_end_r != 32'd0)) begin
            if (words_to_end_r == 32'd1) begin
                cur_addr        <= BASE_ADDR;
                words_to_end_r  <= total_words_w;
            end else begin
                cur_addr        <= cur_addr + 32'd8;
                words_to_end_r  <= words_to_end_r - 32'd1;
            end
        end
    end

    // ========================================================================
    // ARLEN calculation
    //
    // words_to_end_r 是当前周期还剩多少个 64-bit word。
    // ========================================================================
    always @(posedge clk) begin
        if (!rstn) begin
            axi_arlen_r <= 8'd0;
        end else if ((axi_state == ST_IDLE) &&
                     play_en &&
                     !need_reset_r &&
                     !discard_r &&
                     !fifo_full_r &&
                     (words_to_end_r != 32'd0)) begin
            if (words_to_end_r >= C_M_AXI_BURST_LEN)
                axi_arlen_r <= C_M_AXI_BURST_LEN - 1;
            else
                axi_arlen_r <= words_to_end_r[7:0] - 8'd1;
        end
    end

    // ========================================================================
    // AXI AR channel constant outputs
    // ========================================================================
    assign M_AXI_ARID    = {C_M_AXI_ID_WIDTH{1'b0}};
    assign M_AXI_ARADDR  = cur_addr;
    assign M_AXI_ARLEN   = axi_arlen_r;
    assign M_AXI_ARSIZE  = 3'd3;
    assign M_AXI_ARBURST = 2'b01;
    assign M_AXI_ARLOCK  = 1'b0;
    assign M_AXI_ARCACHE = 4'b0010;
    assign M_AXI_ARPROT  = 3'h0;
    assign M_AXI_ARQOS   = 4'hF;
    assign M_AXI_ARUSER  = {C_M_AXI_ARUSER_WIDTH{1'b0}};
    assign M_AXI_ARVALID = axi_arvalid;

    // ========================================================================
    // AXI state machine
    // ========================================================================
    always @(posedge clk) begin
        if (!rstn) begin
            axi_state   <= ST_IDLE;
            axi_arvalid <= 1'b0;
        end else begin
            axi_arvalid <= 1'b0;

            case (axi_state)
                ST_IDLE: begin
                    if (play_en &&
                        !need_reset_r &&
                        !discard_r &&
                        !fifo_full_r &&
                        (words_to_end_r != 32'd0)) begin
                        axi_arvalid <= 1'b1;
                        axi_state   <= ST_RADDR;
                    end
                end

                ST_RADDR: begin
                    axi_arvalid <= 1'b1;

                    if (M_AXI_ARREADY) begin
                        axi_arvalid <= 1'b0;
                        axi_state   <= ST_RDATA;
                    end
                end

                ST_RDATA: begin
                    if (M_AXI_RVALID && M_AXI_RREADY && M_AXI_RLAST)
                        axi_state <= ST_IDLE;
                end

                default: begin
                    axi_state <= ST_IDLE;
                end
            endcase
        end
    end

    // ========================================================================
    // discard control
    //
    // play_en 下降时，当前 AXI burst 残余数据丢弃。
    // ========================================================================
    always @(posedge clk) begin
        if (!rstn)
            discard_r <= 1'b0;
        else if (play_en_fall)
            discard_r <= 1'b1;
        else if (axi_state == ST_IDLE)
            discard_r <= 1'b0;
    end

    // ========================================================================
    // DDS read side
    //
    // 固定每个 64-bit word 出 4 个 16-bit sample。
    // 不再判断 vcnt。
    // ========================================================================
    reg [63:0] ram_rd_data_r;

    always @(posedge clk) begin
        ram_rd_data_r <= fifo_mem[rd_ptr[FIFO_AW-1:0]];
    end

    localparam [1:0] RD_WAIT = 2'd0,
                     RD_LOAD = 2'd1,
                     RD_RUN  = 2'd2;

    reg [1:0]  rd_state;
    reg [1:0]  lane;
    reg [63:0] rd_word_reg;
    reg [15:0] dds_out_r;
    reg        dds_valid_r;

    wire fifo_has_data_w = (fifo_cnt_r != 0);

    assign rd_advance_w = (rd_state == RD_LOAD) ||
                          (rd_state == RD_RUN && lane == 2'd3 && fifo_has_data_w);

    always @(posedge clk) begin
        if (!rstn || !play_en) begin
            rd_state    <= RD_WAIT;
            rd_ptr      <= 0;
            lane        <= 2'd0;
            rd_word_reg <= 64'd0;
            dds_out_r   <= 16'd0;
            dds_valid_r <= 1'b0;
        end else begin
            case (rd_state)
                RD_WAIT: begin
                    dds_valid_r <= 1'b0;

                    if (fifo_has_data_w)
                        rd_state <= RD_LOAD;
                end

                RD_LOAD: begin
                    rd_word_reg <= ram_rd_data_r;
                    rd_ptr      <= rd_ptr + 1'b1;
                    lane        <= 2'd0;
                    rd_state    <= RD_RUN;
                    dds_valid_r <= 1'b0;
                end

                RD_RUN: begin
                    case (lane)
                        2'd0: dds_out_r <= rd_word_reg[15:0];
                        2'd1: dds_out_r <= rd_word_reg[31:16];
                        2'd2: dds_out_r <= rd_word_reg[47:32];
                        2'd3: dds_out_r <= rd_word_reg[63:48];
                    endcase

                    dds_valid_r <= 1'b1;

                    if (lane == 2'd3) begin
                        if (fifo_has_data_w) begin
                            rd_word_reg <= ram_rd_data_r;
                            rd_ptr      <= rd_ptr + 1'b1;
                            lane        <= 2'd0;
                        end else begin
                            rd_state <= RD_WAIT;
                            lane     <= 2'd0;
                        end
                    end else begin
                        lane <= lane + 1'b1;
                    end
                end

                default: begin
                    rd_state <= RD_WAIT;
                end
            endcase
        end
    end

    assign dds_out   = dds_out_r;
    assign dds_valid = dds_valid_r;

endmodule