// ============================================================================
// 文件：user_dds_opt.v
// 描述：高性能DDS播放器 (时序优化版，适用于 BRAM Latency = 1)
// 优化点：
// 1. 移除数据通路复位，强制使用DSP和Carry Chain。
// 2. 流水线深度调整为 5 拍延迟 (Stage 3 -> Stage 7)
// ============================================================================

module bram_dds (
    // 系统接口
    input  wire        clk,        // 系统时钟
    input  wire        rstn_in,    // 外部异步低有效复位
    input  wire        en,         // 使能(与 ddr_dds 的 play_en 共用一条线)
                                    //   en=0: 相位累加器清零、输出0(空闲/等待触发)
                                    //   en=1: 从 poff 起步累加播放
                                    //   两通道同时拉高即相位同步输出
    
    // 相位控制接口
    input  wire [31:0] pinc,       // 相位增量 (频率控制字)
    input  wire [31:0] poff,       // 相位偏移
    
    // BRAM B端口接口
    output reg  [31:0] addrb,      // BRAM字节地址
    input  wire [31:0] doutb,      // BRAM输出数据
    output wire        enb,        // BRAM使能 (常高)
    output wire        rstb,       // BRAM复位 (与系统复位同步)
    output wire [3:0]  web,        // BRAM写使能 (常低)
    
    // DDS输出
    output reg  [15:0] dds_out     // 16位波形数据输出 (带缓冲)
);

// ============================================================================
// 参数与属性
// ============================================================================
// BRAM延迟为 1 周期时，is_odd 控制信号需要 5 拍延迟 (T0->T5)
localparam CONTROL_DELAY = 5; 

// ============================================================================
// 1. 异步复位同步释放电路
// ============================================================================
reg rstn_sync1, rstn_sync;
always @(posedge clk or negedge rstn_in) begin
    if (!rstn_in) begin
        rstn_sync1 <= 1'b0;
        rstn_sync  <= 1'b0;
    end else begin
        rstn_sync1 <= 1'b1;
        rstn_sync  <= rstn_sync1;
    end
end

// ============================================================================
// 2. 输入接口寄存 (Stage 0)
// ============================================================================
reg [31:0] pinc_r1, pinc_r2;
reg [31:0] poff_r1, poff_r2;
reg [31:0] doutb_r; // Stage 6 数据锁存

always @(posedge clk) begin
    // 移除复位以优化时序路径
    pinc_r1 <= pinc;    pinc_r2 <= pinc_r1;
    poff_r1 <= poff;    poff_r2 <= poff_r1;
    doutb_r <= doutb; // 锁存 BRAM 输出数据 (Stage 6)
end

// ============================================================================
// Stage 1 & 2: 相位累加与偏移 (DSP优化)
// ============================================================================
// 强制使用 DSP 硬核资源进行高速累加
(* use_dsp = "yes" *) reg [31:0] phase_acc_r;
(* use_dsp = "yes" *) reg [31:0] phase_sum_r;

// Stage 1: 相位累加器
// 使能用同步复位实现(FF的R端口, 不增加D路径逻辑): en=0 清零, en上升沿从 poff 起步,
// 两通道同沿使能即相位同步。不改动 acc+pinc 累加回路, 保持 DSP 映射与流水线时序。
always @(posedge clk) begin
    if (!en)
        phase_acc_r <= 32'd0;
    else
        phase_acc_r <= phase_acc_r + pinc_r2;
end

// Stage 2: 相位偏移加法 (利用 Carry Chain)
always @(posedge clk) begin
    phase_sum_r <= phase_acc_r + poff_r2;
end

// ============================================================================
// Stage 3-5: 地址生成流水线
// ============================================================================
reg [15:0] sample_idx_r;    // Stage 3: 样本索引 (高16位)
reg [14:0] word_addr_r;     // Stage 4: 字地址

// Stage 3: 计算样本索引
always @(posedge clk) begin
    sample_idx_r <= phase_sum_r[31:16];
end

// Stage 4: 字地址计算 (除以 2)
always @(posedge clk) begin
    word_addr_r <= sample_idx_r[15:1];
end

// Stage 5: BRAM物理地址输出 (乘以 4)
always @(posedge clk) begin
    addrb <= { {15{1'b0}}, word_addr_r, 2'b00 };
end

// ============================================================================
// 控制信号对齐流水线 (Stage 3 -> Stage 7)
// ============================================================================
// 移位寄存器深度 = 5 (CONTROL_DELAY)
reg [CONTROL_DELAY-1:0] odd_shift_reg; // reg [4:0]

always @(posedge clk) begin
    // 将 Stage 3 产出的奇偶位 (sample_idx_r[0]) 推入移位链
    odd_shift_reg <= {odd_shift_reg[CONTROL_DELAY-2:0], sample_idx_r[0]};
end

// 读取移位链的最高位，它与 Stage 6 的数据 doutb_r 严格对齐
wire is_odd_final = odd_shift_reg[CONTROL_DELAY-1]; // odd_shift_reg[4]

// ============================================================================
// Stage 7: Mux 选择 (en=0 时输出0, 用于脉冲串空闲/等待触发)
// ============================================================================
reg [15:0] dds_out_internal;

always @(posedge clk) begin
    // is_odd_final = 0 (偶数索引，取低位)
    // is_odd_final = 1 (奇数索引，取高位)
    dds_out_internal <= en ? (is_odd_final ? doutb_r[31:16] : doutb_r[15:0])
                           : 16'd0;
end

// ============================================================================
// Stage 8: 输出缓冲级
// ============================================================================
always @(posedge clk) begin
    dds_out <= dds_out_internal;
end

// ============================================================================
// 常量BRAM控制信号
// ============================================================================
assign enb  = 1'b1;         // 始终使能读
assign web  = 4'b0000;      // 禁止写
assign rstb = ~rstn_sync;   // BRAM复位与内部复位同步

endmodule