#ifndef USER_DDS_H
#define USER_DDS_H

#include <stdint.h>
#include "xil_io.h"
#include "xparameters.h"


// BRAM配置宏
#define BRAM_SIZE       65536           // 每通道 BRAM 65536 字节
#define SAMPLE_COUNT    (BRAM_SIZE / 2) // 每周期样本数 32768 (bram_dds 表周期)
#define BRAM_WORD_COUNT (BRAM_SIZE / 4) // 32-bit words (每 word 交织存 2 个样本)

#define BRAM0_BASE      XPAR_XBRAM_0_BASEADDR      // axi_bram_ctrl_0 (blk_mem_gen_0) 通道0波形表
#define BRAM1_BASE      XPAR_XBRAM_1_BASEADDR      // axi_bram_ctrl_1 (blk_mem_gen_1) 通道1波形表

#define SYSTEM_CLOCK_HZ     200000000    // 200 MHz
#define DDS0_BASE           0x18000000   // DDS0波形缓存基地址
#define DDS1_BASE           0x1C000000   // DDS1波形缓存基地址
#define ROM0_BASE           0x08000000   // DDS0波形存储基地址
#define ROM1_BASE           0x0C000000   // DDS1波形存储基地址
#define SAMPLE_MAX          32767.0      // 16-bit有符号数最大值
#define MAX_WAVE_POINTS     (1 << 25)    // 允许的最大波形缓存点数，对应32M个点，64MB的空间

//用户波形：每组1MB，512K(2^19)个int16点，32组
#define GROUP_COUNT     32
#define GROUP_SIZE      (1024*1024U)   //1048576字节 = 1MB
extern uint8_t user_buf[GROUP_COUNT][GROUP_SIZE];

// 波形预览（GUI画布 220x120，每段取min/max保留边沿与尖峰）
#define WAVE_PREVIEW_POINTS 220

extern int16_t wave_preview_min[2][WAVE_PREVIEW_POINTS];
extern int16_t wave_preview_max[2][WAVE_PREVIEW_POINTS];
void wave_preview_update(uint8_t dds);

// 寄存器偏移量定义
#define REG_CTRL_BASEADDR        XPAR_REG_CTRL_0_BASEADDR
#define DDS0_TOTAL_POINTS_OFFSET 0x000  // DDR_DDS0循环的总点数
#define DDS1_TOTAL_POINTS_OFFSET 0x004  // DDR_DDS1循环的总点数
#define DDS_CONTROL_OFFSET       0x008  // bit 0: DDS0 play_en  bit 1: DDS1 play_en
                                        // bit 2: DDS0 sel 置0则选择bram_dds，置1选择ddr_dds 
                                        // bit 3: DDS1 sel 置0则选择bram_dds，置1选择ddr_dds 
#define DDS0_PINC_OFFSET         0x00C  // BRAM_DDS0 PINC寄存器
#define DDS0_POFF_OFFSET         0x010  // BRAM_DDS0 POFF寄存器
#define DDS1_PINC_OFFSET         0x014  // BRAM_DDS1 PINC寄存器
#define DDS1_POFF_OFFSET         0x018  // BRAM_DDS1 POFF寄存器

#define DDS0_EN_BIT   (1u << 0)         // ddr_dds0 play_en
#define DDS1_EN_BIT   (1u << 1)         // ddr_dds1 play_en
#define DDS0_SEL_BIT  (1u << 2)         // mux0: 0=bram_dds_0  1=ddr_dds_0
#define DDS1_SEL_BIT  (1u << 3)         // mux1: 0=bram_dds_1  1=ddr_dds_1

#define REG_WRITE(base, offset, data) Xil_Out32((base) + (offset), (data))
#define REG_READ(base, offset)        Xil_In32((base) + (offset))

#define BURST_MARGIN_SAMPLES 2000   // 脉冲串内容后的零值裕量(≥200样本=1个tick误差), 停止动作落在其内

// ============================================================================
// 用户波形: 32组 × 512K点(GROUP_COUNT组, 每组GROUP_SIZE=1MB=512K个int16样本),
// 作为标准波形的扩展输出。数据源为用户数组 user_buf。
//   输出时按当前存储深度(rom_len = 1<<max_rom_bits)重采样到ROM;
//   存储深度超过512K(2^19)时禁止开启用户波形输出(与扫频的存储限制策略一致)。
// ============================================================================
#define USER_WAVE_GROUPS    GROUP_COUNT
#define USER_WAVE_POINTS    (GROUP_SIZE / 2)   // 每组固定 512K 个波形点(int16)
#define USER_WAVE_MAX_BITS  19                 // 允许输出用户波形的最大存储深度(≤512K)

extern uint8_t user_wave_sel;   // 当前选中的用户波形组 0~31 (双通道共享)
extern uint8_t user_wave_en[2]; // 各通道用户波形输出开关

void generate_user_wave(uint8_t dds); // 将选中组的1M点重采样写入ROM
int  user_wave_start(uint8_t dds);    // 开启用户波形输出, 返回0成功/-1存储深度超限
void user_wave_stop(uint8_t dds);     // 关闭并恢复标准波形输出


extern uint8_t max_rom_bits;
extern uint8_t dds_sel;   // 0=bram_dds(小存储) 1=ddr_dds(大存储), 双通道同时控制

// 函数声明
int samples_play(uint8_t dds, double f_target, double phase_offset);
void wave_gen_to_bram(uint8_t dds);
void dds_set_pinc(uint8_t dds, double f);
uint32_t calc_play_points(double f_target);
uint32_t wave_gen_to_ddr(uint8_t dds, double f_target, double phase_offset);
uint32_t calculate_closure_points(double f_target);
void DDS_config_and_play(uint8_t dds, uint32_t total_points);
void generate_sine(uint8_t dds);
void generate_dc(uint8_t dds);
void generate_square(uint8_t dds, double duty);
void generate_triangle(uint8_t dds, double symmetry);
void generate_sawtooth(uint8_t dds, uint8_t rising);
void generate_noise(uint8_t dds, double freq_seed);
void generate_impulse(uint8_t dds);
void generate_sinc(uint8_t dds, uint32_t zero_crossings);
void generate_exp_decay(uint8_t dds, double decay_factor);
void generate_damped_sine(uint8_t dds, uint32_t cycles, double damping);
void generate_ecg(uint8_t dds, uint32_t heart_rate);
void generate_full_wave(uint8_t dds);
void generate_half_wave(uint8_t dds);
void generate_staircase(uint8_t dds, uint32_t steps, uint8_t rising);
void generate_trapezoid(uint8_t dds, double duty);
void generate_raised_cosine(uint8_t dds, double duty);
void generate_gauss_pulse(uint8_t dds, double duty);
void generate_double_pulse(uint8_t dds, double duty);
void generate_exp_rise(uint8_t dds, float decay);
void generate_lorentz_pulse(uint8_t dds, double duty);
void generate_rand_pulses(uint8_t dds, uint32_t steps);
void generate_smooth_step(uint8_t dds, float decay);
void generate_sine_noise(uint8_t dds, double noise_amp);
void generate_square_noise(uint8_t dds, double noise_amp);
void generate_parabola(uint8_t dds);
void generate_cubic(uint8_t dds);
void generate_exp_wave(uint8_t dds, float decay);
void generate_round_square(uint8_t dds, double duty);
void generate_round_triangle(uint8_t dds, double duty);
void generate_rect_pulse(uint8_t dds, double duty);
void generate_uni_square(uint8_t dds, double duty);
void generate_prbs(uint8_t dds, uint32_t steps);
void generate_barker13(uint8_t dds);
void generate_manchester(uint8_t dds);
void generate_am_mod(uint8_t dds, double base, double carriar, double mod_depth);
void generate_fm_mod(uint8_t dds, double mod_freq, double carrier_freq, double delta_f);
void generate_pm_mod(uint8_t dds, double base, double carrier, double pm_index);
void generate_harmonic(uint8_t dds);
uint32_t generate_burst(uint8_t dds);   // 生成脉冲内容(含裕量0)并配置引擎, 返回内容长度



#endif // USER_DDS_H