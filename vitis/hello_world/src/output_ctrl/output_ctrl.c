#include "output_ctrl.h"
#include <math.h>
#include "user_dds.h"
#include "DAC8568.h"

uint8_t dds_ch = 0;
wave_t *p_wave = &wave[0];
mod_t *p_mod = &mod[0];
scan_t *p_scan = &scan[0];

static void burst_abort(uint8_t dds);   // 前置声明: wave_update 中调用

// wave_t[2] 命名初始化
wave_t wave[2] = {
    [0] = {
        .freq = 1000.0,
        .vpp = 1.0,
        .offset = 0.0,
        .phase = 0.0,
        .wave_sel = 0,
        .duty_cycle = 0.5,
        .symmetry = 0.5,
        .rising = 0,
        .zero_crossings = 7,
        .decay_factor = 0.5f,
        .heart_rate = 90,
        .steps = 25,
        .cycles = 5,
        .damping = 2.0,
        .trap_rise = 0.25,
        .rc_width = 0.5,
        .gauss_width = 0.15,
        .dp_width = 0.08,
        .exp_rise_rate = 0.5,
        .lorentz_width = 0.05,
        .rand_pulses = 20,
        .smooth_steep = 0.5,
        .sine_noise_amp = 0.3,
        .square_noise_amp = 0.3,
        .exp_wave_rate = 0.5,
        .round_sq = 0.25,
        .round_tr = 0.25,
        .rect_width = 0.25,
        .uni_duty = 0.5,
        .prbs_order = 7
    },
    [1] = {
        .freq = 1000.0,
        .vpp = 1.0,
        .offset = 0.0,
        .phase = 0.0,
        .wave_sel = 0,
        .duty_cycle = 0.5,
        .symmetry = 0.5,
        .rising = 0,
        .zero_crossings = 7,
        .decay_factor = 0.5f,
        .heart_rate = 90,
        .steps = 25,
        .cycles = 5,
        .damping = 2.0,
        .trap_rise = 0.25,
        .rc_width = 0.5,
        .gauss_width = 0.15,
        .dp_width = 0.08,
        .exp_rise_rate = 0.5,
        .lorentz_width = 0.05,
        .rand_pulses = 20,
        .smooth_steep = 0.5,
        .sine_noise_amp = 0.3,
        .square_noise_amp = 0.3,
        .exp_wave_rate = 0.5,
        .round_sq = 0.25,
        .round_tr = 0.25,
        .rect_width = 0.25,
        .uni_duty = 0.5,
        .prbs_order = 7
    }
};

// mod_t[2] 命名初始化
mod_t mod[2] = {
    [0] = {
        .is_modding = 0,
        .mode = 0,
        .wave_sel = 0,
        .car_wave_sel = 0,
        .carriar = 1000000.0,
        .base = 1000.0,
        .base_phase = 0.0,
        .depth = 0.5,
        .delta_f = 10000.0,
        .pm_index = 1.0
    },
    [1] = {
        .is_modding = 0,
        .mode = 0,
        .wave_sel = 0,
        .car_wave_sel = 0,
        .carriar = 1000000.0,
        .base = 1000.0,
        .base_phase = 0.0,
        .depth = 0.5,
        .delta_f = 10000.0,
        .pm_index = 1.0
    }
};

// scan_t[2] 命名初始化
scan_t scan[2] = {
    [0] = {
        .start = 0.0,
        .end = 10000000.0,
        .point = 1001,
        .time_interval_ns = 10000000,
        .scan_mode = 0,
        .is_loop = 0,
        .is_running = 0
    },
    [1] = {
        .start = 0.0,
        .end = 10000000.0,
        .point = 1001,
        .time_interval_ns = 10000000,
        .scan_mode = 0,
        .is_loop = 0,
        .is_running = 0
    }
};

// harmonic_t[2] 命名初始化: 默认2次谐波, 基波满幅, 二次50%
harmonic_t harmonic[2] = {
    [0] = {
        .enable = 0,
        .count = 2,
        .idx = 1,
        .amp = {100.0, 50.0},
        .phase = {0},
        .vpp_comp = 1.0
    },
    [1] = {
        .enable = 0,
        .count = 2,
        .idx = 1,
        .amp = {100.0, 50.0},
        .phase = {0},
        .vpp_comp = 1.0
    }
};

// ============================================================================
// 输出幅度/偏置设置 —— 三档增益校准点标定
// ----------------------------------------------------------------------------
// 校准过程（每通道、每挡位各做一次，共6组）：
//   ① 把VG_in设为该挡位的增益电压（如0.93V），输出波形设置为直流
//   ② 设OFFSET_in=1.65V，测输出直流电压 → dc_165
//   ③ 设OFFSET_in=1.66V，测输出直流电压 → dc_166
//      ②③两个点确定偏置直线: Vout = k_off*OFFSET_in + b_off
//   ④ 输出波形设置为正弦，设REFIO=0.25V，
//      用示波器测输出交流峰峰值 → ac_025
//   ⑤ 设REFIO=0.75V，测输出交流峰峰值 → ac_075
//      ④⑤两个点确定增益直线: Vpp = k_ac*REFIO + b_ac
// ============================================================================

// 校准点数据（由实测换算，格式: {增益, dc@1.65V, dc@1.66V, ac@0.25V, ac@0.75V}）
static const calib_t calib[2][3] = {
    { // 通道0
        {0.94,  -0.0192, 0.3, 0.048, 0.132},
        {0.96,  -0.0164, 0.304, 0.148, 0.428},
        {1.27,  0.0416, 0.36, 1.88, 5.40},
    },
    { // 通道1
        {0.94, -0.069300, 0.245700, 0.045600, 0.165953},
        {0.96,  -0.069300, 0.245700, 0.203000, 0.780059},
        {1.27,  -0.054455, 0.247898, 1.820000, 6.920000},
    }
};

static double cal_clamp(double v, double lo, double hi)
{
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

// 挡位按输出峰峰值划分（由各挡交流增益曲线可得，此处直接用固定阈值）
// 通道0: 挡1≤0.09V(VG0.94)  挡2≤0.84V(VG0.96)  挡3>0.84V(VG1.27)
// 通道1: 挡1≤0.21V(VG0.94) 挡2≤1.01V(VG0.96)  挡3>1.01V(VG1.27)
static const double stage_th[2][2] = {
    {0.09, 0.84},
    {0.21, 1.01},
};

// 由校准点推导直线系数（每个挡位调用一次，结果缓存避免重复计算）
typedef struct {
    double k_ac, b_ac;   // Vpp = k_ac*REFIO + b_ac
    double k_off, b_off; // Vout = k_off*OFFSET_in + b_off
} calib_line_t;

// 由两个校准点求直线斜率与截距
static double line_slope(double x1, double y1, double x2, double y2)
{
    return (y2 - y1) / (x2 - x1);
}

static void calib_derive(uint8_t dds, int stage, calib_line_t *l)
{
    const calib_t *c = &calib[dds][stage];
    // 交流: (0.25V, ac_025) 与 (0.75V, ac_100) 两点
    l->k_ac  = line_slope(0.25, c->ac_025, 0.75, c->ac_075);
    l->b_ac  = c->ac_025 - l->k_ac * 0.25;
    // 直流: (1.65V, dc_165) 与 (1.66V, dc_166) 两点
    l->k_off = line_slope(1.65, c->dc_165, 1.66, c->dc_166);
    l->b_off = c->dc_165 - l->k_off * 1.65;
}

void DDS_set_vpp_offset(u8 dds, double vpp, double offset)
{
    // ① 按峰峰值选挡位
    int sel = 2;
    if (vpp <= stage_th[dds][0])       sel = 0;
    else if (vpp <= stage_th[dds][1])  sel = 1;

    // ② 由该挡位校准点推导直线，反推REFIO
    calib_line_t line;
    calib_derive(dds, sel, &line);
    double refio = cal_clamp((vpp - line.b_ac) / line.k_ac, 0.01, 1.3);

    // ③ 最后用同一挡位直流校准点反推偏置OFFSET_in
    double off   = cal_clamp((offset - line.b_off) / line.k_off, 0.0, 3.3);

    if (!dds){
        DAC8568_SetVolt(VG_in0, calib[dds][sel].vg);
        DAC8568_SetVolt(REFIO0, refio);
        DAC8568_SetVolt(OFFSET_in0, off);
    }else{
        DAC8568_SetVolt(VG_in1, calib[dds][sel].vg);
        DAC8568_SetVolt(REFIO1, refio);
        DAC8568_SetVolt(OFFSET_in1, off);
    }
}

void wave_update(u8 dds)
{
    wave_t *w = &wave[dds];
    burst_abort(dds);   // 波形参数变化中止脉冲串状态机

    // 用户波形开启时优先输出用户波形(标准波形的扩展), 谐波/调制不叠加
    if (user_wave_en[dds]) {
        generate_user_wave(dds);
        samples_play(dds, w->freq, w->phase);
        DDS_set_vpp_offset(dds, w->vpp, w->offset);
        return;
    }

    // 谐波开启时基础波恒为正弦, 覆盖 normal 页 wave_sel
    if (harmonic[dds].enable) {
        generate_harmonic(dds);
        samples_play(dds, w->freq, w->phase);
        // vpp_comp: 谐波叠加被缩小后, 输出级增益按因子放大, 使基波幅度=设定vpp
        DDS_set_vpp_offset(dds, w->vpp * harmonic[dds].vpp_comp, w->offset);
        return;
    }

    switch(w->wave_sel){
        case 0: generate_sine(dds); break;
        case 1: generate_square(dds, w->duty_cycle); break;
        case 2: generate_triangle(dds, w->symmetry); break;
        case 3: generate_dc(dds); break;
        case 4: generate_sawtooth(dds, w->rising); break;
        case 5: generate_noise(dds, w->freq); break;
        case 6: generate_impulse(dds); break;
        case 7: generate_full_wave(dds); break;
        case 8: generate_half_wave(dds); break;
        case 9: generate_damped_sine(dds, w->cycles, w->damping); break;
        case 10: generate_ecg(dds, w->heart_rate); break;
        case 11: generate_sinc(dds, w->zero_crossings); break;
        case 12: generate_exp_decay(dds, w->decay_factor); break;
        case 13: generate_staircase(dds, w->steps, w->rising); break;
        case 14: generate_trapezoid(dds, w->trap_rise); break;
        case 15: generate_raised_cosine(dds, w->rc_width); break;
        case 16: generate_gauss_pulse(dds, w->gauss_width); break;
        case 17: generate_double_pulse(dds, w->dp_width); break;
        case 18: generate_exp_rise(dds, w->exp_rise_rate); break;
        case 19: generate_lorentz_pulse(dds, w->lorentz_width); break;
        case 20: generate_rand_pulses(dds, w->rand_pulses); break;
        case 21: generate_smooth_step(dds, w->smooth_steep); break;
        case 22: generate_sine_noise(dds, w->sine_noise_amp); break;
        case 23: generate_square_noise(dds, w->square_noise_amp); break;
        case 24: generate_parabola(dds); break;
        case 25: generate_cubic(dds); break;
        case 26: generate_exp_wave(dds, w->exp_wave_rate); break;
        case 27: generate_round_square(dds, w->round_sq); break;
        case 28: generate_round_triangle(dds, w->round_tr); break;
        case 29: generate_rect_pulse(dds, w->rect_width); break;
        case 30: generate_uni_square(dds, w->uni_duty); break;
        case 31: generate_prbs(dds, w->prbs_order); break;
        case 32: generate_barker13(dds); break;
        case 33: generate_manchester(dds); break;
        default: break;
    }
    samples_play(dds, w->freq, w->phase);
    DDS_set_vpp_offset(dds, w->vpp, w->offset);
}

void mod_update(uint8_t dds)
{
    mod_t *m = &mod[dds];
    wave_t *w = &wave[dds];

    // 用户波形输出时不做调制, 直接走标准波形输出路径
    if (user_wave_en[dds]) {
        wave_update(dds);
        return;
    }
    if (!m->is_modding){
        wave_update(dds);
        return;
    }
    switch (m->mode){
        case 0:
            generate_am_mod(dds, m->base, m->carriar, m->depth);
            break;
        case 1:
            generate_fm_mod(dds, m->base, m->carriar, m->delta_f);
            break;
        case 2:
            generate_pm_mod(dds, m->base, m->carriar, m->pm_index);
            break;
        default:
            break;
    }

    if (m->mode == 0)
        DDS_set_vpp_offset(dds, 2 * w->vpp, w->offset); // AM包络峰值为两倍
    else
        DDS_set_vpp_offset(dds, w->vpp, w->offset);
    samples_play(dds, m->base, m->base_phase);
}

// 双通道同步：同时停→启，两通道从各自buffer起点重新播放，实现相位对齐
void DDS_sync_channels(void)
{
    REG_WRITE(REG_CTRL_BASEADDR, DDS_CONTROL_OFFSET, 0x00);
    REG_WRITE(REG_CTRL_BASEADDR, DDS_CONTROL_OFFSET, 0x03);
}

// burst_t[2] 命名初始化: 默认3个循环, 相位0, 无延迟, 关闭
burst_t burst[2] = {
    [0] = { .enable = 0, .cycles = 3, .phase = 0.0, .delay_us = 0, .is_running = 0 },
    [1] = { .enable = 0, .cycles = 3, .phase = 0.0, .delay_us = 0, .is_running = 0 }
};

// ============================================================================
// 脉冲串(手动触发N循环, 0=无限)
//   有限N: 触发 → (延迟) → en=1 输出内容 → 计时到(内容+裕量中段) → en=0 回空闲
//   无限:  触发 → en=1 连续输出, 再触发 → en=0
//   缓冲 = 内容(从 wave.phase+burst.phase 起步的 (N−φ/360) 个周期) + 裕量0
//   停止目标取裕量中段: tick粒度100样本, 停止位置误差 ≤100样本, 前后余量充足,
//   保证落在0区(bram 表余段清零 / ddr 缓冲裕量段), 无尾沿毛刺
// ============================================================================
static uint8_t  burst_state[2];     // 0=空闲 1=延迟中 2=播放中
static uint32_t burst_tick[2];      // ISR递增
static uint32_t burst_delay_ticks[2];
static uint32_t burst_play_ticks[2];

static void burst_en(uint8_t dds, uint8_t on)
{
    uint32_t en_bit = dds ? DDS1_EN_BIT : DDS0_EN_BIT;
    uint32_t ctrl = REG_READ(REG_CTRL_BASEADDR, DDS_CONTROL_OFFSET);
    if (on) ctrl |= en_bit; else ctrl &= ~en_bit;
    REG_WRITE(REG_CTRL_BASEADDR, DDS_CONTROL_OFFSET, ctrl);
}

// 波形参数变化时中止burst状态机, 避免与正常播放的使能控制冲突
static void burst_abort(uint8_t dds)
{
    burst_state[dds] = 0;
    burst[dds].is_running = 0;
}

// 开关关闭/外部调用: 停止输出并回空闲
void burst_stop(uint8_t dds)
{
    burst_abort(dds);
    burst_en(dds, 0);
}

// ISR中调用: 仅计时
void burst_update(uint8_t dds)
{
    if (burst_state[dds] != 0) burst_tick[dds]++;
}

// 主循环中调用: 延迟/播放到期处理
void burst_process(void)
{
    for (uint8_t dds = 0; dds < 2; dds++) {
        if (burst_state[dds] == 1) {                    // 延迟中
            if (burst_tick[dds] >= burst_delay_ticks[dds]) {
                burst_tick[dds] = 0;
                burst_state[dds] = 2;
                burst_en(dds, 1);                        // 开始输出
            }
        } else if (burst_state[dds] == 2) {             // 播放中
            if (burst_tick[dds] >= burst_play_ticks[dds]) {
                burst_en(dds, 0);                        // 停止, 输出归0
                burst_state[dds] = 0;
                burst[dds].is_running = 0;
            }
        }
    }
}

// 手动触发(需脉冲开关已开启)
void burst_trigger(uint8_t dds)
{
    burst_t *b = &burst[dds];
    if (!b->enable) return;

    if (b->cycles == 0) {
        // 无限: 触发启动连续输出, 再触发停止
        uint32_t en_bit = dds ? DDS1_EN_BIT : DDS0_EN_BIT;
        uint32_t ctrl = REG_READ(REG_CTRL_BASEADDR, DDS_CONTROL_OFFSET);
        if (ctrl & en_bit) {
            ctrl &= ~en_bit;
            REG_WRITE(REG_CTRL_BASEADDR, DDS_CONTROL_OFFSET, ctrl);
            b->is_running = 0;
        } else {
            wave_update(dds);                            // 装载并播放当前波形(en=1)
            b->is_running = 1;
        }
        return;
    }

    // 有限N: 播放中忽略重复触发
    if (burst_state[dds] != 0) return;

    uint32_t content = generate_burst(dds);              // 生成内容+裕量并配置引擎(不置en)
    burst_tick[dds] = 0;
    burst_delay_ticks[dds] = b->delay_us * 2;  // 500ns tick
    burst_play_ticks[dds] = (content + BURST_MARGIN_SAMPLES / 2 + 99) / 100;  // 停止在裕量中段
    burst_state[dds] = 1;
    b->is_running = 1;
}
// ============================================================================
// 扫频（仅 bram_dds / 32K 模式）
//   bram_dds 表固定，每个步进只更新 pinc 寄存器 → 相位连续、无需重载表。
//   ddr_dds 模式由 GUI 禁止启动扫频。
// ============================================================================
static uint32_t current_step[2];
static uint32_t scan_tick[2];           // 从当前步进开始计数的500ns tick数（ISR递增）
static volatile uint8_t scan_step_pending[2];  // ISR置位：dwell时间已到，待主循环处理
static uint32_t intervals_needed[2];
static double current_freq[2];
static double freq_increment[2];
static double log_base[2];

// ISR中调用：仅计时+置标志，不做任何重活
void scan_update(uint8_t dds)
{
    scan_t *s = &scan[dds];
    if (!s->is_running) return;

    scan_tick[dds]++;
    if (scan_tick[dds] < intervals_needed[dds]) return;
    scan_step_pending[dds] = 1;
}

// 主循环中调用：dwell到期后更新 pinc 实现相位连续的步进扫频
void scan_process(void)
{
    for (uint8_t dds = 0; dds < 2; dds++) {
        scan_t *s = &scan[dds];
        if (!s->is_running) continue;
        if (!scan_step_pending[dds]) continue;

        // 结束/回绕判定
        if (current_step[dds] >= s->point){
            if (s->is_loop){
                current_step[dds] = 0;
                current_freq[dds] = s->start;
            }
            else{
                s->is_running = 0;
                dds_set_pinc(dds, wave[dds].freq);   // 恢复基础频率
                continue;
            }
        }

        scan_step_pending[dds] = 0;

        switch (s->scan_mode){
            case 0:
                current_freq[dds] = s->start + freq_increment[dds] * current_step[dds];
                break;
            case 1:
                current_freq[dds] = s->start * pow(log_base[dds], current_step[dds]);
                break;
        }

        dds_set_pinc(dds, current_freq[dds]);
        current_step[dds]++;
        scan_tick[dds] = 0;
    }
}

// 返回 0 启动成功；返回 -1 拒绝启动（非 bram_dds 模式或参数非法）
int scan_start(uint8_t dds)
{
    scan_t *s = &scan[dds];
    if (dds_sel != 0) return -1;   // 扫频仅支持 32K(bram_dds) 模式
    if (s->time_interval_ns < 500) return -1;
    if (s->point < 2) return -1;
    if (s->start >= s->end) return -1;
    if (s->scan_mode == 1 && s->start <= 0.0) return -1;

    current_step[dds] = 0;
    scan_tick[dds] = 0;
    scan_step_pending[dds] = 0;
    current_freq[dds] = s->start;
    intervals_needed[dds] = s->time_interval_ns / 500;

    switch (s->scan_mode){
        case 0:
            freq_increment[dds] = (s->end - s->start) / (s->point - 1);
            break;
        case 1:
            log_base[dds] = pow(s->end / s->start, 1.0 / (s->point - 1));
            break;
        default:
            return -1;
    }

    s->is_running = 1;
    dds_set_pinc(dds, current_freq[dds]);   // 第一步频率（表由GUI侧 samples_play 已装载）
    return 0;
}


