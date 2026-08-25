#ifndef INTC
#define INTC

#include "xparameters.h"
#include "xparameters_ps.h"
#include "sleep.h"
#include "xgpio.h"
#include "xil_exception.h"
#include "xscugic.h"
#include "xscutimer.h"
#include "xttcps.h"

#define TIMER_LOAD_1MS      333333


extern XScuGic intc;
extern XScuTimer timer;
extern XTtcPs ttc0;

void timer_init(void);
void ttc0_init(void);
void Setup_Intr_System();

#endif