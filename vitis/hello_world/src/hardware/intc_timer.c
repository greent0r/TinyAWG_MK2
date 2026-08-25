#include "lvgl.h"
#include "intc_timer.h"
#include "xscugic.h"
#include "xscutimer.h"
#include "xttcps.h"
#include "output_ctrl.h"
#include "gui_guider.h"
#include "MAX17048.h"
#include "PC_HOST.h"
#include "xuartps.h"


XScuGic intc;
XScuTimer timer;
XTtcPs ttc0;

//500ns
static void Timer_IntrHandler(void *CallBackRef)
{
    if(scan[0].is_running) {
        scan_update(0);
    }
    if(scan[1].is_running) {
        scan_update(1);
    }
    if(burst[0].is_running) {
        burst_update(0);
    }
    if(burst[1].is_running) {
        burst_update(1);
    }
    pc_upload_tick();   // 用户波形上传超时看门狗（防止断开后残留RXFULL模式）
    XScuTimer_ClearInterruptStatus(&timer);
}

static void TTC0_IntrHandler(void *CallBackRef, u32 StatusEvent)
{
	lv_tick_inc(1);
}


void Setup_Intr_System()
{
	XScuGic_Config * IntcConfig;
	IntcConfig = XScuGic_LookupConfig(XPAR_INTC_BASEADDR);
	XScuGic_CfgInitialize(&intc, IntcConfig, IntcConfig->CpuBaseAddress);
	Xil_ExceptionInit();
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, (void *) &intc);

	XScuGic_Connect(&intc, XPAR_PS7_SCUTIMER_0_INTR, (Xil_ExceptionHandler)Timer_IntrHandler, (void *) &timer);
	XScuGic_Enable(&intc, XPAR_PS7_SCUTIMER_0_INTR);
	XScuTimer_EnableInterrupt(&timer);
    XScuTimer_Start(&timer);

	XScuGic_Connect(&intc, XPAR_PS7_TTC_0_INTR,(Xil_ExceptionHandler)XTtcPs_InterruptHandler, (void *)&ttc0);
	XTtcPs_SetStatusHandler(&ttc0, &ttc0, (XTtcPs_StatusHandler)TTC0_IntrHandler);
    XScuGic_Enable(&intc, XPAR_PS7_TTC_0_INTR);
	XTtcPs_EnableInterrupts(&ttc0, XTTCPS_IXR_INTERVAL_MASK);
	XTtcPs_Start(&ttc0);

    // 为指定的中断注册自定义的中断处理函数
    XScuGic_Connect(&intc, XPAR_PS7_UART_0_INTR, (Xil_ExceptionHandler)uart_intr_handler, (void *)&Uart_Ps);
    // 中断掩码在 uart_init() 中已配置(RXFULL排空累积 + TOUT空闲定包边界)
    XScuGic_Enable(&intc, XPAR_PS7_UART_0_INTR);

    Xil_ExceptionEnableMask(XIL_EXCEPTION_IRQ);
}

void timer_init(void)
{
	XScuTimer_Config *ConfigPtr;
	ConfigPtr = XScuTimer_LookupConfig(XPAR_XSCUTIMER_0_BASEADDR);
	XScuTimer_CfgInitialize(&timer, ConfigPtr, ConfigPtr->BaseAddr);
	XScuTimer_LoadTimer(&timer, 166);
	XScuTimer_EnableAutoReload(&timer);
}

void ttc0_init(void)
{
    s32 state;
	XTtcPs_Config *Config;
	Config = XTtcPs_LookupConfig(XPAR_XTTCPS_0_BASEADDR);
	state = XTtcPs_CfgInitialize(&ttc0, Config, Config->BaseAddress);
	state = XTtcPs_SetOptions(&ttc0, (XTTCPS_OPTION_INTERVAL_MODE | XTTCPS_OPTION_WAVE_DISABLE));

	u16 Interval;
	u8 Prescaler;
	XTtcPs_CalcIntervalFromFreq(&ttc0, 1000, &Interval, &Prescaler);
	XTtcPs_SetInterval(&ttc0, Interval);
	XTtcPs_SetPrescaler(&ttc0, Prescaler);

}

