#ifndef OUTPUT_CTRL_H
#define OUTPUT_CTRL_H

#include <stdio.h>
#include <stdint.h>
#include "xil_printf.h"
#include "xil_types.h"
#include "xil_io.h"
#include "xparameters.h"
#include "gpio.h"


typedef struct {
    double freq;
    double vpp;
    double offset;
    double phase;
    uint32_t wave_sel; //波形选择
    // 各波形独立参数：每个波形只使用自己的字段，不做跨波形复用
    double duty_cycle;      // 方波: 占空比 (0~1)
    double symmetry;        // 三角波: 对称性 (0~1)
    uint8_t rising;         // 锯齿波/阶梯波: 上升或下降 (0/1)
    uint32_t zero_crossings;// Sinc: 零点数 (1~100)
    double decay_factor;    // 指数衰减: 衰减速率 (0~1)
    uint32_t heart_rate;    // ECG: 心跳 (40~180)
    uint32_t steps;         // 阶梯波: 阶数 (2~1000)
    uint32_t cycles;        // 衰减正弦: 周期数 (1~200)
    double damping;         // 衰减正弦: 阻尼系数 (0~10)
    double trap_rise;       // 梯形波: 升沿占周期比例 (0.05~0.45)
    double rc_width;        // 升余弦脉冲: 脉宽 (0.05~0.95)
    double gauss_width;     // 高斯脉冲: 宽度 (0.02~0.5)
    double dp_width;        // 双脉冲: 脉宽 (0.01~0.2)
    double exp_rise_rate;   // 指数上升: 上升速率 (0~1)
    double lorentz_width;   // 洛伦兹脉冲: 宽度 (0.005~0.2)
    uint32_t rand_pulses;   // 随机脉冲: 脉冲个数 (1~200)
    double smooth_steep;    // 平滑阶跃: 过渡陡度 (0~1)
    double sine_noise_amp;  // 正弦加噪: 噪声幅度 (0~1)
    double square_noise_amp;// 方波加噪: 噪声幅度 (0~1)
    double exp_wave_rate;   // 指数波: 速率 (0~1)
    double round_sq;        // 升余弦方波: 圆滑度 (0.02~0.5)
    double round_tr;        // 圆角三角波: 圆滑度 (0.02~0.5)
    double rect_width;      // 矩形脉冲: 脉宽 (0.02~0.5)
    double uni_duty;        // 单极性方波: 占空比 (0~1)
    uint32_t prbs_order;    // PRBS: 阶数 (3~16)
}wave_t;

typedef struct {
    uint8_t is_modding;
    uint8_t mode;//调制类型
    uint32_t wave_sel;//调制波形
    uint32_t car_wave_sel;//载波波形
    double carriar;//载波频率
    double base;//调制频率
    double base_phase;//调制相位
    double depth;//AM调制深度
    double delta_f;//FM最大频偏
    double pm_index;//PM相偏
}mod_t;

typedef struct {
    double start;
    double end;
    uint32_t point;
    uint32_t time_interval_ns;
    uint32_t scan_mode;
    uint8_t is_loop;
    uint8_t is_running;
}scan_t;

typedef struct {
    double vg;      // 该挡位的增益电压(VG_in)
    double dc_165;  // 校准点: OFFSET_in=1.65V时的直流输出电压(V)
    double dc_166;  // 校准点: OFFSET_in=1.66V时的直流输出电压(V)
    double ac_025;  // 校准点: REFIO=0.25V时的交流峰峰值(V)
    double ac_075;  // 校准点: REFIO=0.75V时的交流峰峰值(V)
} calib_t;

#define HARM_MAX 16  // 谐波个数上限

typedef struct {
    uint8_t enable;    // 谐波开关
    uint8_t count;     // 谐波个数 1~16
    uint8_t idx;       // 当前编辑的谐波序号(UI)
    double  amp[16];   // 各次谐波幅值: 相对基波百分比, 100=与基波同幅
    double  phase[16]; // 各次谐波相位: 度, 全0即同相
    double  vpp_comp;  // 输出补偿因子(运行期计算): 使基波幅度恒等于设定vpp
} harmonic_t;

typedef struct {
    uint8_t  enable;     // 脉冲功能开关
    uint32_t cycles;     // 0=无限(手动触发启停连续输出), 1~999999=每触发输出N个循环
    double   phase;      // 第一个脉冲相位(度) -180~+180, 与 wave.phase 相加生效, 实现小数周期
    uint32_t delay_us;   // 触发延迟(µs)
    uint8_t  is_running; // 0=空闲 1=延迟中/播放中
} burst_t;

#define	K0_SET	XGpio_DiscreteSet(&xgpio,1,K0)   	
#define	K1_SET	XGpio_DiscreteSet(&xgpio,1,K1)    							    
#define	K0_CLR	XGpio_DiscreteClear(&xgpio,1,K0)     
#define	K1_CLR	XGpio_DiscreteClear(&xgpio,1,K1)   

#define DDS0_ON  K0_CLR
#define DDS0_OFF K0_SET
#define DDS1_ON  K1_CLR
#define DDS1_OFF K1_SET

extern uint8_t dds_ch;
extern wave_t *p_wave;
extern mod_t *p_mod;
extern scan_t *p_scan;
extern scan_t scan[2];
extern wave_t wave[2];
extern mod_t mod[2];
extern harmonic_t harmonic[2];
extern burst_t burst[2];

void DDS_set_vpp_offset(u8 dds, double vpp, double offset);
void DDS_sync_channels(void);
void wave_update(u8 dds);
void mod_update(uint8_t dds);
int scan_start(uint8_t dds);   // 仅32K(bram_dds)模式可用, 返回0成功/-1拒绝
void scan_update(uint8_t dds);
void scan_process(void);
void burst_trigger(uint8_t dds);   // 手动触发: 有限N=发一次, 无限=启停连续输出
void burst_stop(uint8_t dds);      // 停止并回空闲(开关关闭时调用)
void burst_update(uint8_t dds);    // ISR中调用: 计时
void burst_process(void);          // 主循环中调用: 延迟/播放到期处理


#endif // OUTPUT_CTRL_H