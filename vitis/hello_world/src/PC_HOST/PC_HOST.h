#ifndef PC_HOST
#define PC_HOST

#include "stdio.h"
#include "output_ctrl.h"
#include "user_dds.h"
#include "xuartps.h"
#include <stdio.h>
#include "xil_printf.h"
#include <sys/_intsup.h>
#include "xparameters.h"
#include "xparameters_ps.h"
#include "sleep.h"
#include "xgpio.h"
#include "xscutimer.h"
#include "sleep.h"


// ============================================================================
// 上位机协议 v2（文本行 + 原始流式上传，波特率 2000000）
// ----------------------------------------------------------------------------
// 请求:  G                      查询全部参数 -> STATUS 行
//        S key=val key=val..    设置参数（可多个，空格分隔）-> OK / ERR
//        D v0,..,v5             设置DAC 6通道电压(0~5V) -> OK / ERR
//        U<g>\n                 开始向组 g(0~31) 上传用户波形 -> READY
//        数字开头的旧格式        兼容：同 D
// 用户波形上传（无确认/无校验的原始流式）:
//        PC: "U<g>\n" -> 设备回 "READY\n" -> PC直接连发 1MB 原始int16小端数据
//        -> 设备收满1MB回 "DONE\n"。无帧头/CRC/逐包ACK，速率即串口数据率。
// 键名:  ch wave freq vpp offset phase duty sym rising zc decay hr steps cycles damp
//        trise rcw gaussw dpw erise lw rpulses ssteep sna qna ewave rsq rtr rw uduty prbs
//        m_en m_mode m_base m_carr m_depth m_dev m_index
//        s_start s_end s_points s_intv s_mode s_loop s_run
//        h_en h_count h_idx h_amp1..16 h_ph1..16 h_apply
//        b_en b_cycles b_phase b_delay b_trig
//        u_sel u_en depth buzz sync out out0 out1
// ============================================================================

// 用户波形上传大小（1MB = 512K int16）
#define UPLOAD_TOTAL_BYTES (USER_WAVE_POINTS * 2)

// 兼容旧宏（保留，未使用）
#define HEAD1 0xAA
#define HEAD2 0xBB
#define TAIL1 0xCC
#define TAIL2 0xDD


extern XUartPs Uart_Ps;
extern volatile uint8_t uart_rx_pending;



void uart_init();
void uart_intr_handler(void *call_back_ref);
void uart_rx_process(void);
void pc_cmd_process(void);
void pc_upload_tick(void);   // 上传超时看门狗，由SCU定时器ISR调用
int Uart_Send(u8 *sendbuf, int length);



#endif

