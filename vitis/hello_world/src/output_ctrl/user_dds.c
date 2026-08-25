#include "user_dds.h"
#include "output_ctrl.h"
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "xil_cache.h"
#include "xil_io.h"

static int16_t *rom_ptr(uint8_t dds);
static uint32_t rom_len(void);
static void rom_done(uint8_t dds, int16_t *rom);

uint8_t max_rom_bits = 17; //初始值对应128K（表示点数，每点两个字节）
uint8_t dds_sel = 0;      //0=bram_dds(小存储) 1=ddr_dds(大存储), 双通道同时控制

uint8_t user_wave_sel = 0;
uint8_t user_wave_en[2] = {0, 0};

// 用户波形输出: 把选中组的1M点(user_buf, int16满幅有符号)按当前存储深度重采样写入ROM
// (最近邻抽取), 存储深度≤1M时均为整比例缩放; 之后由 samples_play 负责 bram/ddr 二次重采样播放。
void generate_user_wave(uint8_t dds)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    const int16_t *src = (const int16_t *)user_buf[user_wave_sel];
    if (len == USER_WAVE_POINTS) {
        memcpy(rom, src, len * sizeof(int16_t));
    } else {
        for (uint32_t i = 0; i < len; i++)
            rom[i] = src[(uint32_t)(((uint64_t)i * USER_WAVE_POINTS) / len)];
    }
    rom_done(dds, rom);
}

// 开启用户波形输出(存储深度≤1M); 超限返回-1
int user_wave_start(uint8_t dds)
{
    if (max_rom_bits > USER_WAVE_MAX_BITS) return -1;
    user_wave_en[dds] = 1;
    wave_update(dds);
    return 0;
}

// 关闭用户波形输出, 恢复标准波形
void user_wave_stop(uint8_t dds)
{
    if (!user_wave_en[dds]) return;
    user_wave_en[dds] = 0;
    wave_update(dds);
}

uint8_t user_buf[GROUP_COUNT][GROUP_SIZE];

// GUI波形预览缓冲：每段取min/max，保留边沿与尖峰
int16_t wave_preview_min[2][WAVE_PREVIEW_POINTS];
int16_t wave_preview_max[2][WAVE_PREVIEW_POINTS];

// PL最小播放点数（4字节对齐后）
#define MIN_PLAY_POINTS 100

// ============================================================================
// 波形生成公共辅助
// ============================================================================
static int16_t *rom_ptr(uint8_t dds)
{
    return dds ? (int16_t *)ROM1_BASE : (int16_t *)ROM0_BASE;
}

static uint32_t rom_len(void)
{
    return 1U << max_rom_bits;
}

static void rom_done(uint8_t dds, int16_t *rom)
{
    Xil_DCacheFlushRange((UINTPTR)rom, rom_len() * sizeof(int16_t));
    wave_preview_update(dds);
}

// ============================================================================
// 波形预览抽取：将ROM降采样为GUI画布点数，存min/max供GUI满幅归一化显示
// ============================================================================
void wave_preview_update(uint8_t dds)
{
    volatile int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    uint32_t seg = len / WAVE_PREVIEW_POINTS;
    if (seg == 0) seg = 1;

    for (uint32_t p = 0; p < WAVE_PREVIEW_POINTS; p++) {
        uint32_t start = p * seg;
        uint32_t end = (p == WAVE_PREVIEW_POINTS - 1) ? len : start + seg;
        int16_t mn = rom[start], mx = rom[start];
        for (uint32_t i = start + 1; i < end; i++) {
            int16_t v = rom[i];
            if (v < mn) mn = v;
            if (v > mx) mx = v;
        }
        wave_preview_min[dds][p] = mx;  // 输出级反向放大器，预览取反（保持min<max）
        wave_preview_max[dds][p] = mn;
    }
}

// 调制载波窗口预览：从ROM中部截取最多10个载波周期直接采样
static void wave_preview_mod_carrier(uint8_t dds, int16_t *rom, uint32_t len, uint32_t carrier_cycles)
{
    uint32_t dc = (carrier_cycles > 10) ? 10 : carrier_cycles;
    if (dc < 1) dc = 1;
    uint32_t win = dc * (len / carrier_cycles);
    if (win > len) win = len;
    uint32_t st = (len - win) / 2;
    for (int p = 0; p < WAVE_PREVIEW_POINTS; p++) {
        uint32_t idx = st + p * win / WAVE_PREVIEW_POINTS;
        if (idx >= len) idx = len - 1;
        wave_preview_min[dds][p] = -rom[idx];  // 输出级反向放大器，预览取反
        wave_preview_max[dds][p] = -rom[idx];
    }
}

// ============================================================================
// 多周期闭合算法：寻找最接近整数的总点数
// ============================================================================
uint32_t calculate_closure_points(double f_target)
{
    double points_per_cycle = SYSTEM_CLOCK_HZ / f_target;
    uint32_t max_M = (uint32_t)((double)MAX_WAVE_POINTS / points_per_cycle);
    uint32_t best_points = (uint32_t)(points_per_cycle + 0.5);
    double   min_df      = 1e30;

    for (uint32_t M = 1; M <= max_M; M++) {
        double   N_ideal = (double)M * points_per_cycle;
        uint32_t N       = (uint32_t)(N_ideal + 0.5);
        if (N < 4)              continue;   // 每周期至少 4 个点
        if (N > MAX_WAVE_POINTS) break;
        double f_actual = (double)M * SYSTEM_CLOCK_HZ / (double)N;
        double df       = fabs(f_actual - f_target);

        if (df < min_df) {
            min_df      = df;
            best_points = N;
            if (df <= 0.1) break;           // 满足 0.1 Hz 精度立即退出
        }
    }
    return best_points;
}

// ============================================================================
// 播放点数计算：闭点 + 放大到最小点数 + 4字节对齐
// ============================================================================
uint32_t calc_play_points(double f_target)
{
    uint32_t total_points = calculate_closure_points(f_target);
    while(total_points < MIN_PLAY_POINTS) total_points *= 10;
    return (total_points + 3u) & ~3u;
}

// ============================================================================
// 写入波形数据到缓存（仅生成+flush，不启停PL；返回生成点数）
// ============================================================================
uint32_t wave_gen_to_ddr(uint8_t dds, double f_target, double phase_offset)
{
    int16_t *rom = rom_ptr(dds);
    volatile int16_t *ddr_ptr = dds ? (int16_t *)DDS1_BASE : (int16_t *)DDS0_BASE;
    uint32_t total_points = calc_play_points(f_target);
    uint32_t rom_mask = (1U << max_rom_bits) - 1;
    uint64_t pinc = (uint64_t)round(f_target * (1ULL << 32) / (double)SYSTEM_CLOCK_HZ);

    // 软件 DDS 相位累加与重采样（%2^k 优化为按位与）
    uint64_t phase_acc = (uint64_t)(phase_offset / 360.0 * (1ULL << 32));
    for (uint32_t i = 0; i < total_points; i++) {
        uint32_t rom_idx = (uint32_t)(phase_acc >> (32 - max_rom_bits)) & rom_mask;
        ddr_ptr[i] = (int16_t)-rom[rom_idx];  // 输出级反向放大器，输出取反
        phase_acc += pinc;
    }
    Xil_DCacheFlushRange((UINTPTR)ddr_ptr, total_points * sizeof(int16_t));
    return total_points;
}

// ============================================================================
// bram_dds: 将 ROM 单周期波形重采样为 BRAM 交织表
//   BRAM word w = {sample[2w+1], sample[2w]}（高16位=奇数样本，低16位=偶数样本）
//   表周期 = SAMPLE_COUNT(32K) 个样本；ROM 与表不等长时按相位等比例抽取，
//   以保留完整一个周期。输出级为反向放大器，与 wave_gen_to_ddr 一致取反后再入表。
// ============================================================================
void wave_gen_to_bram(uint8_t dds)
{
    uint32_t base = dds ? BRAM1_BASE : BRAM0_BASE;
    const int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();

    for (uint32_t i = 0; i < SAMPLE_COUNT; i += 2) {
        int32_t s0 = -(int32_t)rom[(uint32_t)(((uint64_t)i * len) / SAMPLE_COUNT)];
        int32_t s1 = -(int32_t)rom[(uint32_t)(((uint64_t)(i + 1) * len) / SAMPLE_COUNT)];
        uint32_t packed = ((uint32_t)(uint16_t)s1 << 16) | (uint16_t)s0;
        Xil_Out32(base + (i >> 1) * 4u, packed);
    }
}

// ============================================================================
// bram_dds 频率字：pinc = f * 2^31 / 200M（表周期32K样本占相位空间 2^31）
// ============================================================================
void dds_set_pinc(uint8_t dds, double f)
{
    uint32_t pinc = (uint32_t)llround(f * (double)(1ULL << 31) / (double)SYSTEM_CLOCK_HZ);
    REG_WRITE(REG_CTRL_BASEADDR, dds ? DDS1_PINC_OFFSET : DDS0_PINC_OFFSET, pinc);
}

// ============================================================================
// 生成并启动播放（dds_sel 自动区分 bram_dds / ddr_dds）
//   bram_dds: 相位累加器32位，表周期32K样本占相位空间 2^32*32K/64K = 2^31，
//             故 pinc = f * 2^31 / 200M；同时切换mux并停止 ddr_dds
// ============================================================================
int samples_play(uint8_t dds, double f_target, double phase_offset)
{
    if (dds_sel == 0) {
        wave_gen_to_bram(dds);
        dds_set_pinc(dds, f_target);

        uint32_t poff = (uint32_t)llround(phase_offset / 360.0 * (double)(1ULL << 32));
        REG_WRITE(REG_CTRL_BASEADDR, dds ? DDS1_POFF_OFFSET : DDS0_POFF_OFFSET, poff);

        uint32_t ctrl = REG_READ(REG_CTRL_BASEADDR, DDS_CONTROL_OFFSET);
        ctrl &= 0xFFFFFFF3;                        // 双通道 sel=0 → bram_dds
        ctrl |= (dds ? DDS1_EN_BIT : DDS0_EN_BIT); // 本通道 en=1: bram_dds 使能(bram/ddr 共用使能线)
        REG_WRITE(REG_CTRL_BASEADDR, DDS_CONTROL_OFFSET, ctrl);
    } else {
        uint32_t ctrl = REG_READ(REG_CTRL_BASEADDR, DDS_CONTROL_OFFSET);
        ctrl |= 0xC;   // sel=1 → ddr_dds;
        REG_WRITE(REG_CTRL_BASEADDR, DDS_CONTROL_OFFSET, ctrl);
        uint32_t total_points = wave_gen_to_ddr(dds, f_target, phase_offset);
        DDS_config_and_play(dds, total_points);
    }
    return 0;
}

// ============================================================================
// 配置 PL 侧寄存器并启动 ddr_dds 播放（仅操作本通道的 en/sel 位）
// ============================================================================
void DDS_config_and_play(uint8_t dds, uint32_t total_points)
{
    uint32_t en_bit  = dds ? DDS1_EN_BIT  : DDS0_EN_BIT;
    uint32_t sel_bit = dds ? DDS1_SEL_BIT : DDS0_SEL_BIT;
    uint32_t ctrl = REG_READ(REG_CTRL_BASEADDR, DDS_CONTROL_OFFSET);

    ctrl &= ~en_bit;    // 先停 ddr_dds（total_points 需在 play_en 低电平时锁存）
    REG_WRITE(REG_CTRL_BASEADDR, DDS_CONTROL_OFFSET, ctrl);

    REG_WRITE(REG_CTRL_BASEADDR,
              dds ? DDS1_TOTAL_POINTS_OFFSET : DDS0_TOTAL_POINTS_OFFSET,
              total_points);

    ctrl |= sel_bit | en_bit;   // mux 切到 ddr_dds 并启动
    REG_WRITE(REG_CTRL_BASEADDR, DDS_CONTROL_OFFSET, ctrl);
}

// ============================================================================
// 波形生成函数（写入ROM一个完整周期，结尾统一flush+更新预览）
// ============================================================================

void generate_sine(uint8_t dds)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    double scale = 2.0 * M_PI / len;
    for (uint32_t i = 0; i < len; i++)
    {
        rom[i] = (int16_t)(SAMPLE_MAX * sin(i * scale));
    }
    rom_done(dds, rom);
}

//直流输出
void generate_dc(uint8_t dds)
{
    int16_t *rom = rom_ptr(dds);
    memset(rom, 0, rom_len() * sizeof(int16_t));
    rom_done(dds, rom);
}

//方波
void generate_square(uint8_t dds, double duty)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    duty = (duty > 1.0f) ? 1.0f : ((duty < 0.0f) ? 0.0f : duty);
    uint32_t split = (uint32_t)(len * duty);
    for (uint32_t i = 0; i < len; i++)
    {
        rom[i] = (i < split) ? (int16_t)SAMPLE_MAX : -(int16_t)SAMPLE_MAX;
    }
    rom_done(dds, rom);
}

//三角波
void generate_triangle(uint8_t dds, double symmetry)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    symmetry = (symmetry > 1.0f) ? 1.0f : ((symmetry < 0.0f) ? 0.0f : symmetry);
    uint32_t split = (uint32_t)(len * symmetry);
    double k1 = 2.0 * SAMPLE_MAX / split;
    double k2 = -2.0 * SAMPLE_MAX / (len - split);
    for (uint32_t i = 0; i < len; i++)
    {
        if (i < split)
            rom[i] = (int16_t)(k1 * i - SAMPLE_MAX);
        else
            rom[i] = (int16_t)(SAMPLE_MAX + k2 * (i - split));
    }
    rom_done(dds, rom);
}

//锯齿波
void generate_sawtooth(uint8_t dds, uint8_t rising)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    double step = 2.0 * SAMPLE_MAX / len;
    for (uint32_t i = 0; i < len; i++)
    {
        rom[i] = rising ? (int16_t)(step * i - SAMPLE_MAX)
                        : (int16_t)(SAMPLE_MAX - step * i);
    }
    rom_done(dds, rom);
}

//噪声
void generate_noise(uint8_t dds, double freq_seed)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    srand((uint32_t)freq_seed);
    const double gain = 2.0 / RAND_MAX;
    for (uint32_t i = 0; i < len; i++)
    {
        rom[i] = (int16_t)((gain * rand() - 1.0) * SAMPLE_MAX);
    }
    rom_done(dds, rom);
}

//阶跃信号
void generate_impulse(uint8_t dds)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    rom[0] = (int16_t)SAMPLE_MAX;
    for (uint32_t i = 1; i < len; i++){
        rom[i] = 0;
    }
    rom_done(dds, rom);
}

//Sinc函数
void generate_sinc(uint8_t dds, uint32_t zero_crossings)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    zero_crossings = zero_crossings < 1 ? 1 : (zero_crossings > 100 ? 100 : zero_crossings);
    double time_range = 2 * zero_crossings + 1;
    double scale = time_range / len;
    const double half_range = time_range / 2.0;
    for (uint32_t i = 0; i < len; i++)
    {
        double t = i * scale - half_range;
        double val;
        if (fabs(t) < 1e-10)
            val = 1.0;
        else
        {
            double x = M_PI * t;
            val = sin(x) / x;
        }
        rom[i] = (int16_t)(val * SAMPLE_MAX);
    }
    rom_done(dds, rom);
}

//指数衰减
void generate_exp_decay(uint8_t dds, double decay_factor)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    decay_factor = decay_factor < 0 ? 0.0 : (decay_factor > 1.0 ? 1.0 : decay_factor);
    double coeff = decay_factor * 10.0;
    double inv_len = 1.0 / len;
    for (uint32_t i = 0; i < len; i++)
    {
        double t = i * inv_len;
        rom[i] = (int16_t)(exp(-coeff * t) * SAMPLE_MAX);
    }
    rom_done(dds, rom);
}

//衰减正弦波
void generate_damped_sine(uint8_t dds, uint32_t cycles, double damping)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    cycles = cycles < 1 ? 1 : (cycles > 200 ? 200 : cycles);
    damping = damping < 0 ? 0.0 : (damping > 10.0 ? 10.0 : damping);
    double scale = 2.0 * M_PI * cycles / len;
    double inv_len = 1.0 / len;
    for (uint32_t i = 0; i < len; i++)
    {
        rom[i] = (int16_t)(exp(-damping * i * inv_len) * sin(i * scale) * SAMPLE_MAX);
    }
    rom_done(dds, rom);
}

//ECG波形
// 一个波形周期内画整数个完整心跳，保证ROM首尾相位闭合（循环播放不跳变）
// 实际心率 = beats * freq * 60 (freq为波形频率Hz，beats为周期内心跳数)
void generate_ecg(uint8_t dds, uint32_t heart_rate)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    heart_rate = heart_rate < 40 ? 40 : (heart_rate > 180 ? 180 : heart_rate);
    uint32_t beats = (uint32_t)(heart_rate / 60.0 + 0.5);   // 周期内心跳数（四舍五入）
    if (beats < 1) beats = 1;
    double period_samples = (double)len / beats;            // 每个心跳占用的采样数
    double inv_period = 1.0 / period_samples;
    for (uint32_t i = 0; i < len; i++)
    {
        double phase = fmod(i, period_samples) * inv_period;
        double ecg_value = 0.0;
        //P波
        if (phase >= 0.05 && phase < 0.15)
        {
            double p_phase = (phase - 0.05) / 0.1 - 0.5;
            ecg_value += 0.25 * exp(-50.0 * p_phase * p_phase);
        }
        //QRS波
        if (phase >= 0.2 && phase < 0.3)
        {
            double qrs_phase = (phase - 0.2) / 0.1 - 0.5;
            ecg_value += exp(-100.0 * qrs_phase * qrs_phase);
            if (phase < 0.225) ecg_value -= 0.2;
            if (phase > 0.275) ecg_value -= 0.2;
        }
        //T波
        if (phase >= 0.4 && phase < 0.6)
        {
            double t_phase = (phase - 0.4) / 0.2 - 0.5;
            ecg_value += 0.3 * exp(-25.0 * t_phase * t_phase);
        }
        //基线压低
        if ((phase >= 0.15 && phase < 0.2) || (phase >= 0.3 && phase < 0.4))
            ecg_value -= 0.05;
        //噪声
        ecg_value += ((rand() % 100) / 5000.0) - 0.01;
        rom[i] = (int16_t)(ecg_value * SAMPLE_MAX);
    }
    rom_done(dds, rom);
}

//全波整流
void generate_full_wave(uint8_t dds)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    double scale = 2.0 * M_PI / len;
    for (uint32_t i = 0; i < len; i++)
    {
        rom[i] = (int16_t)(fabs(sin(i * scale)) * SAMPLE_MAX);
    }
    rom_done(dds, rom);
}

//半波整流
void generate_half_wave(uint8_t dds)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    double scale = 2.0 * M_PI / len;
    for (uint32_t i = 0; i < len; i++)
    {
        double sine_value = sin(i * scale);
        rom[i] = (int16_t)((sine_value > 0.0) ? (sine_value * SAMPLE_MAX) : 0);
    }
    rom_done(dds, rom);
}

//阶梯波
void generate_staircase(uint8_t dds, uint32_t steps, uint8_t rising)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    steps = steps < 2 ? 2 : (steps > 1000 ? 1000 : steps);
    uint32_t samples_per_step = len / steps;
    double step_gain = 2.0 * SAMPLE_MAX / (steps - 1);
    for (uint32_t i = 0; i < len; i++)
    {
        uint32_t step_index = i / samples_per_step;
        if (step_index >= steps) step_index = steps - 1;
        double val = rising ? (-SAMPLE_MAX + step_index * step_gain)
                            : (SAMPLE_MAX - step_index * step_gain);
        rom[i] = (int16_t)val;
    }
    rom_done(dds, rom);
}

//梯形波（duty控制上升沿占周期比例，默认0.25）
void generate_trapezoid(uint8_t dds, double duty)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    duty = (duty > 0.45) ? 0.45 : ((duty < 0.05) ? 0.05 : duty);
    double rise = duty;
    double fall = 1.0 - duty;
    for (uint32_t i = 0; i < len; i++)
    {
        double p = (double)i / len;
        double v;
        if (p < rise)       v = -1.0 + 2.0 * p / rise;
        else if (p < fall)  v = 1.0;
        else                v = 1.0 - 2.0 * (p - fall) / duty;
        rom[i] = (int16_t)(v * SAMPLE_MAX);
    }
    rom_done(dds, rom);
}

//升余弦脉冲（duty控制脉宽，0->1->0光滑过渡，默认0.5）
void generate_raised_cosine(uint8_t dds, double duty)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    duty = (duty > 0.95) ? 0.95 : ((duty < 0.05) ? 0.05 : duty);
    double scale = 2.0 * M_PI / len;
    double w = duty * 2.0 * M_PI;
    for (uint32_t i = 0; i < len; i++)
    {
        double t = i * scale;
        double v = (t < w) ? (0.5 * (1.0 - cos(2.0 * M_PI * t / w))) : 0.0;
        rom[i] = (int16_t)(v * SAMPLE_MAX);
    }
    rom_done(dds, rom);
}

//高斯脉冲（duty控制脉冲宽度，默认0.15）
void generate_gauss_pulse(uint8_t dds, double duty)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    duty = (duty > 0.5) ? 0.5 : ((duty < 0.02) ? 0.02 : duty);
    for (uint32_t i = 0; i < len; i++)
    {
        double t = (double)i / len - 0.5;
        double v = exp(-(t * t) / (duty * duty));
        rom[i] = (int16_t)(v * SAMPLE_MAX);
    }
    rom_done(dds, rom);
}

//双脉冲（duty控制脉宽，一正一负，默认0.08）
void generate_double_pulse(uint8_t dds, double duty)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    duty = (duty > 0.2) ? 0.2 : ((duty < 0.01) ? 0.01 : duty);
    for (uint32_t i = 0; i < len; i++)
    {
        double p = (double)i / len;
        double v = 0.0;
        if (p < duty) v = 1.0;
        else if (p >= 0.25 && p < 0.25 + duty) v = -1.0;
        rom[i] = (int16_t)(v * SAMPLE_MAX);
    }
    rom_done(dds, rom);
}

//指数上升（decay控制上升速率，0->1渐近，默认0.5）
void generate_exp_rise(uint8_t dds, float decay)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    decay = decay < 0 ? 0.0f : (decay > 1.0f ? 1.0f : decay);
    double coeff = decay * 10.0;
    for (uint32_t i = 0; i < len; i++)
    {
        double t = (double)i / len;
        double v = 1.0 - exp(-coeff * t);
        rom[i] = (int16_t)(v * SAMPLE_MAX);
    }
    rom_done(dds, rom);
}

//洛伦兹脉冲（duty控制半宽，窄峰，默认0.05）
void generate_lorentz_pulse(uint8_t dds, double duty)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    duty = (duty > 0.2) ? 0.2 : ((duty < 0.005) ? 0.005 : duty);
    for (uint32_t i = 0; i < len; i++)
    {
        double t = (double)i / len - 0.5;
        double v = 1.0 / (1.0 + (t / duty) * (t / duty));
        rom[i] = (int16_t)(v * SAMPLE_MAX);
    }
    rom_done(dds, rom);
}

//随机脉冲（steps控制脉冲个数，随机位置正负脉冲，默认20）
void generate_rand_pulses(uint8_t dds, uint32_t steps)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    steps = steps < 1 ? 1 : (steps > 200 ? 200 : steps);
    srand(2026);
    for (uint32_t i = 0; i < len; i++) rom[i] = 0;
    for (uint32_t k = 0; k < steps; k++) {
        uint32_t pos = (uint32_t)(((double)rand() / RAND_MAX) * len);
        if (pos >= len) pos = len - 1;
        int16_t amp = (rand() & 1) ? (int16_t)SAMPLE_MAX : -(int16_t)SAMPLE_MAX;
        rom[pos] = amp;
    }
    rom_done(dds, rom);
}

//平滑阶跃（decay控制过渡陡度，0->1，默认0.5）
void generate_smooth_step(uint8_t dds, float decay)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    decay = decay < 0 ? 0.0f : (decay > 1.0f ? 1.0f : decay);
    double steep = decay * 60.0;
    for (uint32_t i = 0; i < len; i++)
    {
        double t = (double)i / len - 0.5;
        double v = 0.5 + atan(steep * t) / M_PI;
        rom[i] = (int16_t)(v * SAMPLE_MAX);
    }
    rom_done(dds, rom);
}

//正弦加噪（正弦叠加白噪声，噪声幅度可调）
void generate_sine_noise(uint8_t dds, double noise_amp)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    noise_amp = (noise_amp > 1.0) ? 1.0 : ((noise_amp < 0.0) ? 0.0 : noise_amp);
    double scale = 2.0 * M_PI / len;
    const double gain = 2.0 / RAND_MAX;
    srand(100);
    const double norm = 1.0 / (1.0 + noise_amp);
    for (uint32_t i = 0; i < len; i++)
    {
        double v = sin(i * scale) + noise_amp * (gain * rand() - 1.0);
        rom[i] = (int16_t)(v * norm * SAMPLE_MAX);
    }
    rom_done(dds, rom);
}

//方波加噪（方波叠加白噪声，噪声幅度可调）
void generate_square_noise(uint8_t dds, double noise_amp)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    noise_amp = (noise_amp > 1.0) ? 1.0 : ((noise_amp < 0.0) ? 0.0 : noise_amp);
    const double gain = 2.0 / RAND_MAX;
    srand(100);
    const double norm = 1.0 / (1.0 + noise_amp);
    for (uint32_t i = 0; i < len; i++)
    {
        double s = (i < len / 2) ? 1.0 : -1.0;
        double v = s + noise_amp * (gain * rand() - 1.0);
        rom[i] = (int16_t)(v * norm * SAMPLE_MAX);
    }
    rom_done(dds, rom);
}

//抛物波（周期抛物线，顶点圆滑）
void generate_parabola(uint8_t dds)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    for (uint32_t i = 0; i < len; i++)
    {
        double p = (double)i / len;
        double v = 8.0 * (p - 0.5) * (p - 0.5) - 1.0;
        rom[i] = (int16_t)(v * SAMPLE_MAX);
    }
    rom_done(dds, rom);
}

//三次波（三角波的立方，顶点更陡）
void generate_cubic(uint8_t dds)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    for (uint32_t i = 0; i < len; i++)
    {
        double p = (double)i / len;
        double t = (p < 0.5) ? (2.0 * p) : (2.0 - 2.0 * p);   // 0..1 三角
        double v = (2.0 * t - 1.0);
        rom[i] = (int16_t)(v * v * v * SAMPLE_MAX);
    }
    rom_done(dds, rom);
}

//指数波（指数增长周期波形，速率可调）
void generate_exp_wave(uint8_t dds, float decay)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    decay = decay < 0 ? 0.0f : (decay > 1.0f ? 1.0f : decay);
    double coeff = 1.0 + decay * 9.0;
    double denom = exp(coeff) - 1.0;
    for (uint32_t i = 0; i < len; i++)
    {
        double p = (double)i / len;
        double v = (exp(coeff * p) - 1.0) / denom * 2.0 - 1.0;
        rom[i] = (int16_t)(v * SAMPLE_MAX);
    }
    rom_done(dds, rom);
}

//升余弦方波（圆角方波，边沿余弦过渡，圆滑度可调）
void generate_round_square(uint8_t dds, double duty)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    duty = (duty > 0.5) ? 0.5 : ((duty < 0.02) ? 0.02 : duty);
    double edge = duty * 0.5;   // 单边沿占周期比例
    for (uint32_t i = 0; i < len; i++)
    {
        double q = fmod((double)i / len * 2.0, 2.0);   // 0..2
        double v;
        if (q < edge)           v = -cos(q / edge * M_PI);
        else if (q < 0.5)       v = 1.0;
        else if (q < 0.5 + edge) v = cos((q - 0.5) / edge * M_PI);
        else if (q < 1.5)       v = -1.0;
        else if (q < 1.5 + edge) v = -cos((q - 1.5) / edge * M_PI);
        else                    v = 1.0;
        rom[i] = (int16_t)(v * SAMPLE_MAX);
    }
    rom_done(dds, rom);
}

//圆角三角波（顶点用tanh圆滑，圆滑度可调）
void generate_round_triangle(uint8_t dds, double duty)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    duty = (duty > 0.5) ? 0.5 : ((duty < 0.02) ? 0.02 : duty);
    double k = 1.0 / (duty * 2.0);
    double norm = tanh(k);
    for (uint32_t i = 0; i < len; i++)
    {
        double p = (double)i / len;
        double t = (p < 0.5) ? (2.0 * p) : (2.0 - 2.0 * p);
        double v = tanh(k * (2.0 * t - 1.0)) / norm;
        rom[i] = (int16_t)(v * SAMPLE_MAX);
    }
    rom_done(dds, rom);
}

//矩形脉冲（平顶窄脉冲，脉宽可调）
void generate_rect_pulse(uint8_t dds, double duty)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    duty = (duty > 0.5) ? 0.5 : ((duty < 0.02) ? 0.02 : duty);
    for (uint32_t i = 0; i < len; i++)
    {
        double p = (double)i / len;
        rom[i] = (p < duty) ? (int16_t)SAMPLE_MAX : 0;
    }
    rom_done(dds, rom);
}

//单极性方波（0~+1，占空比可调）
void generate_uni_square(uint8_t dds, double duty)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    duty = (duty > 1.0) ? 1.0 : ((duty < 0.0) ? 0.0 : duty);
    uint32_t split = (uint32_t)(len * duty);
    for (uint32_t i = 0; i < len; i++)
    {
        rom[i] = (i < split) ? (int16_t)SAMPLE_MAX : 0;
    }
    rom_done(dds, rom);
}

//PRBS伪随机序列（LFSR，阶数可调，序列周期=2^n-1）
void generate_prbs(uint8_t dds, uint32_t steps)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    steps = steps < 3 ? 3 : (steps > 16 ? 16 : steps);
    // 常用本原多项式抽头
    static const uint16_t taps[] = {0x5, 0x9, 0x12, 0x21, 0x41, 0x8E, 0x108, 0x204,
                                    0x402, 0x829, 0x100D, 0x2015, 0x4022, 0xB400};
    uint16_t mask = taps[steps - 3];
    uint16_t lfsr = 1;
    for (uint32_t i = 0; i < len; i++)
    {
        uint16_t bit = lfsr & 1;
        rom[i] = bit ? (int16_t)SAMPLE_MAX : -(int16_t)SAMPLE_MAX;
        if (bit) lfsr = (lfsr >> 1) ^ mask;
        else     lfsr >>= 1;
    }
    rom_done(dds, rom);
}

//巴克码（13位，雷达/同步测试）
void generate_barker13(uint8_t dds)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    static const int8_t barker[] = {1, 1, 1, 1, 1, -1, -1, 1, 1, -1, 1, -1, 1};
    for (uint32_t i = 0; i < len; i++)
    {
        uint32_t idx = i * 13 / len;
        rom[i] = (int16_t)(barker[idx] * SAMPLE_MAX);
    }
    rom_done(dds, rom);
}

//曼彻斯特码（8位数据0xA5编码，每bit中间跳变）
void generate_manchester(uint8_t dds)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    const uint8_t data = 0xA5;
    for (uint32_t i = 0; i < len; i++)
    {
        double pos = (double)i / len * 8.0;           // 0..8 对应8个bit
        uint32_t bit_idx = (uint32_t)pos;
        if (bit_idx > 7) bit_idx = 7;
        uint8_t bit = (data >> (7 - bit_idx)) & 1;
        double sub = pos - bit_idx;                    // 0..1 位内位置
        int16_t v = (sub < 0.5) ? (bit ? -(int16_t)SAMPLE_MAX : (int16_t)SAMPLE_MAX)
                                : (bit ? (int16_t)SAMPLE_MAX : -(int16_t)SAMPLE_MAX);
        rom[i] = v;
    }
    rom_done(dds, rom);
}

//AM调制
void generate_am_mod(uint8_t dds, double base, double carriar, double mod_depth)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    double carrier_cycles_per_mod = carriar / base;
    double scale = 2.0 * M_PI / len;
    const double amp_scale = 0.5 * SAMPLE_MAX;
    for (uint32_t i = 0; i < len; i++)
    {
        double t = i * scale;
        double envelope = 1.0 + mod_depth * cos(t);
        rom[i] = (int16_t)(cos(carrier_cycles_per_mod * t) * envelope * amp_scale);
    }
    Xil_DCacheFlushRange((UINTPTR)rom, len * sizeof(int16_t));
    // AM预览：解析包络 ±(1+depth*cos(t))*amp（调制波形不走ROM降采样）
    {
        double scl = 2.0 * M_PI / WAVE_PREVIEW_POINTS;
        for (int p = 0; p < WAVE_PREVIEW_POINTS; p++) {
            int16_t v = (int16_t)((1.0 + mod_depth * cos(p * scl)) * amp_scale);
            wave_preview_max[dds][p] = v;
            wave_preview_min[dds][p] = -v;
        }
    }
}

//FM调制
void generate_fm_mod(uint8_t dds, double mod_freq, double carrier_freq, double delta_f)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    double mod_index = delta_f / mod_freq;
    double carrier_cycles_per_mod = carrier_freq / mod_freq;
    uint32_t int_carrier_cycles = (uint32_t)round(carrier_cycles_per_mod);
    if (int_carrier_cycles == 0) int_carrier_cycles = 1;
    double scale = 2.0 * M_PI / len;
    for (uint32_t i = 0; i < len; i++)
    {
        double t = i * scale;
        double phase = int_carrier_cycles * t + mod_index * sin(t);
        rom[i] = (int16_t)(cos(phase) * SAMPLE_MAX);
    }
    Xil_DCacheFlushRange((UINTPTR)rom, len * sizeof(int16_t));
    wave_preview_mod_carrier(dds, rom, len, int_carrier_cycles);
}

//PM调制
void generate_pm_mod(uint8_t dds, double base, double carrier, double pm_index)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    double carrier_cycles_per_mod = carrier / base;
    uint32_t int_carrier_cycles = (uint32_t)round(carrier_cycles_per_mod);
    if (int_carrier_cycles == 0) int_carrier_cycles = 1;
    double scale = 2.0 * M_PI / len;
    for (uint32_t i = 0; i < len; i++)
    {
        double t = i * scale;
        double phase = carrier_cycles_per_mod * t + pm_index * cos(t);
        rom[i] = (int16_t)(cos(phase) * SAMPLE_MAX);
    }
    Xil_DCacheFlushRange((UINTPTR)rom, len * sizeof(int16_t));
    wave_preview_mod_carrier(dds, rom, len, int_carrier_cycles);
}

// ============================================================================
// 谐波合成: 直接合成 y[i] = Σk amp[k-1]% × sin(k·θi + phase[k-1])
//   在 rom 循环中对每个样本累加各次谐波(递推 sin/cos(kθ) 避免逐次 sin 调用),
//   一次合成直接写入 rom, 不再先生成基波表再叠加。
//   归一化: 峰值理论上限 = Σ|amp%|, 按此缩放保证合成波形幅度不超过满幅;
//   vpp_comp = Σ|amp%| / 基波% 供输出级补偿, 使最终输出基波幅度=设定vpp。
//   全局相位(wave.phase)由播放层 poff 统一施加(各次谐波按 k×φ 平移)。
// ============================================================================
void generate_harmonic(uint8_t dds)
{
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    harmonic_t *h = &harmonic[dds];
    uint8_t count = h->count;
    if (count == 0) count = 1;
    if (count > HARM_MAX) count = HARM_MAX;

    // 每谐波: 幅值比 + 相位展开系数(cos/sin 预计算)
    double ratio[HARM_MAX], cph[HARM_MAX], sph[HARM_MAX];
    double sum_ratio = 0.0;
    for (uint8_t k = 0; k < count; k++) {
        ratio[k] = h->amp[k] / 100.0;
        double p = h->phase[k] * (M_PI / 180.0);
        cph[k] = cos(p);
        sph[k] = sin(p);
        sum_ratio += fabs(ratio[k]);
    }

    double gain = (sum_ratio > 0.0) ? (SAMPLE_MAX / sum_ratio) : 0.0;
    double scale = 2.0 * M_PI / len;

    for (uint32_t i = 0; i < len; i++) {
        double th = i * scale;
        double sn = sin(th), cs = cos(th);
        double sk = sn, ck = cs;   // sin(1θ), cos(1θ)
        double y = 0.0;
        for (uint8_t k = 0; k < count; k++) {
            if (k > 0) {
                double skn = sk * cs + ck * sn;   // sin((k+1)θ)
                double ckn = ck * cs - sk * sn;   // cos((k+1)θ)
                sk = skn;
                ck = ckn;
            }
            y += ratio[k] * (sk * cph[k] + ck * sph[k]);
        }
        rom[i] = (int16_t)(y * gain);
    }

    h->vpp_comp = (ratio[0] > 0.0) ? (sum_ratio / ratio[0]) : 1.0;
    rom_done(dds, rom);
}

// ============================================================================
// 脉冲串内容生成
//   内容 = 从 (wave.phase + burst.phase) 起步、共 (N − φ/360) 个周期的波形,
//          重采样写入目标引擎, 后接 BURST_MARGIN_SAMPLES 个0(停止容差窗口);
//   自动路由: 内容+裕量 ≤ 32K 且 bram 模式 → bram_dds(表补零到整表, pinc=2^16
//          自然速率); 否则 → ddr_dds(total_points=内容+裕量)。
//   配置引擎但不置 en, 由 burst 状态机在延迟结束后拉高。
// ============================================================================
uint32_t generate_burst(uint8_t dds)
{
    burst_t *b = &burst[dds];
    int16_t *rom = rom_ptr(dds);
    uint32_t len = rom_len();
    uint32_t mask = len - 1;
    double f = wave[dds].freq;
    if (f < 1.0) f = 1000.0;

    double ph_eff = wave[dds].phase + b->phase;
    double cycles_eff = (double)b->cycles - b->phase / 360.0;   // 小数周期
    uint32_t C = (uint32_t)llround(cycles_eff * SYSTEM_CLOCK_HZ / f);
    uint32_t total = C + BURST_MARGIN_SAMPLES;
    if (total > MAX_WAVE_POINTS) { total = MAX_WAVE_POINTS; C = total - BURST_MARGIN_SAMPLES; }

    uint64_t pinc64 = (uint64_t)round(f * (double)(1ULL << 32) / (double)SYSTEM_CLOCK_HZ);
    uint64_t acc = (uint64_t)(ph_eff / 360.0 * (double)(1ULL << 32));

    uint32_t en_bit  = dds ? DDS1_EN_BIT  : DDS0_EN_BIT;
    uint32_t sel_bit = dds ? DDS1_SEL_BIT : DDS0_SEL_BIT;
    uint32_t ctrl = REG_READ(REG_CTRL_BASEADDR, DDS_CONTROL_OFFSET);
    ctrl &= ~en_bit;                        // 保持停止
    REG_WRITE(REG_CTRL_BASEADDR, DDS_CONTROL_OFFSET, ctrl);

    if (dds_sel == 0 && total <= SAMPLE_COUNT) {
        // bram 表: 交织写入内容, 余下补0, pinc=2^16 线性逐点播放
        uint32_t base = dds ? BRAM1_BASE : BRAM0_BASE;
        uint32_t word = 0;
        for (uint32_t i = 0; i < C; i++) {
            int16_t v = (int16_t)-rom[(uint32_t)(acc >> (32 - max_rom_bits)) & mask];
            acc += pinc64;
            if (i & 1) Xil_Out32(base + (i >> 1) * 4u, word | ((uint32_t)(uint16_t)v << 16));
            else       word = (uint32_t)(uint16_t)v;
        }
        if (C & 1) Xil_Out32(base + (C >> 1) * 4u, word);   // 奇数尾: 低=内容 高=0
        for (uint32_t w = (C + 1) >> 1; w < SAMPLE_COUNT >> 1; w++)
            Xil_Out32(base + w * 4u, 0);                    // 裕量+余表清零

        REG_WRITE(REG_CTRL_BASEADDR, dds ? DDS1_PINC_OFFSET : DDS0_PINC_OFFSET, (uint32_t)(1u << 16));
        REG_WRITE(REG_CTRL_BASEADDR, dds ? DDS1_POFF_OFFSET : DDS0_POFF_OFFSET, 0);  // 相位已烘焙
        ctrl &= ~sel_bit;                                   // sel=0 → bram_dds
        REG_WRITE(REG_CTRL_BASEADDR, DDS_CONTROL_OFFSET, ctrl);
    } else {
        // ddr 缓冲: 内容 + 裕量0, total_points = total
        volatile int16_t *ddr_ptr = dds ? (int16_t *)DDS1_BASE : (int16_t *)DDS0_BASE;
        for (uint32_t i = 0; i < C; i++) {
            ddr_ptr[i] = (int16_t)-rom[(uint32_t)(acc >> (32 - max_rom_bits)) & mask];
            acc += pinc64;
        }
        for (uint32_t i = C; i < total; i++) ddr_ptr[i] = 0;
        Xil_DCacheFlushRange((UINTPTR)ddr_ptr, total * sizeof(int16_t));

        REG_WRITE(REG_CTRL_BASEADDR,
                  dds ? DDS1_TOTAL_POINTS_OFFSET : DDS0_TOTAL_POINTS_OFFSET, total);
        ctrl |= sel_bit;                                    // sel=1 → ddr_dds
        REG_WRITE(REG_CTRL_BASEADDR, DDS_CONTROL_OFFSET, ctrl);
    }
    return C;
}
