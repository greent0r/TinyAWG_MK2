// ============================================================================
// 蜂鸣器控制模块 (无源蜂鸣器)
// ----------------------------------------------------------------------------
// 协议: PS 通过 AXI GPIO 输出位(bit10=BUZZ)发送一个正脉冲(平时低, 拉高~1us)
//       本模块检测上升沿后, 输出 4kHz 50%占空比 PWM 驱动蜂鸣器发声 100ms。
//       蜂鸣期间再次触发则重新计时(连按连续响)。
// 参数: SYS_CLK_HZ  系统时钟频率
//       BEEP_FREQ   蜂鸣频率(默认4kHz)
//       BEEP_MS     蜂鸣时长(默认100ms)
// ============================================================================
module buzz#(
    parameter SYS_CLK_HZ = 200_000_000,   // 系统时钟 (Hz)
    parameter BEEP_FREQ  = 4_000,         // 蜂鸣频率 (Hz)
    parameter BEEP_MS    = 100            // 蜂鸣时长 (ms)
)(
    input  wire       clk,          // 系统时钟
    input  wire       rst_n,        // 复位, 低有效
    input  wire       buzz_trig,    // 触发脉冲输入 (AXI GPIO bit10)
    output reg        buzz_out      // 蜂鸣器驱动 (平时低, 触发后PWM)
);

    localparam HALF_PERIOD = SYS_CLK_HZ / (BEEP_FREQ * 2);        // 半周期计数
    localparam BEEP_CYCLES = SYS_CLK_HZ / 1000 * BEEP_MS;         // 总时长计数

    // ---- 触发脉冲边沿检测 (两级同步防亚稳态) ----
    reg trig_d1, trig_d2;
    wire trig_rise = trig_d1 & ~trig_d2;

    // ---- 蜂鸣状态 ----
    reg        active;               // 1=蜂鸣中
    reg [31:0] time_cnt;             // 总时长计数
    reg [31:0] half_cnt;             // 半周期计数

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            trig_d1  <= 1'b0;
            trig_d2  <= 1'b0;
            active   <= 1'b0;
            time_cnt <= 32'd0;
            half_cnt <= 32'd0;
            buzz_out <= 1'b0;
        end else begin
            trig_d1 <= buzz_trig;
            trig_d2 <= trig_d1;

            if (trig_rise) begin
                // 检测到触发: 启动/重新计时
                active   <= 1'b1;
                time_cnt <= 32'd0;
                half_cnt <= 32'd0;
                buzz_out <= 1'b1;
            end else if (active) begin
                time_cnt <= time_cnt + 32'd1;
                half_cnt <= half_cnt + 32'd1;

                // 半周期到达: 翻转输出, 形成方波
                if (half_cnt >= HALF_PERIOD - 1) begin
                    half_cnt <= 32'd0;
                    buzz_out <= ~buzz_out;
                end
                // 总时长到达: 停止并保持低
                if (time_cnt >= BEEP_CYCLES - 1) begin
                    active   <= 1'b0;
                    buzz_out <= 1'b0;
                end
            end
        end
    end

endmodule