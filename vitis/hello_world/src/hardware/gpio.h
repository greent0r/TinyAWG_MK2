#ifndef GPIO
#define GPIO

#include <stdio.h>
#include "stdlib.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xparameters_ps.h"
#include "xgpio.h"

#define LCD_RST 0x1
#define LCD_DC 0x2
#define LCD_CS 0x4
#define K0 0x8
#define K1 0x10 
#define DIN 0x20 
#define LDAC 0x40 
#define CLR 0x80 
#define SCLK 0x100 
#define SYNC 0x200 
#define BUZZ 0x400 
#define TF_CD 0x800 
#define LCD_BLK 0x1000 


extern XGpio xgpio;

#define BUZZ_SET	XGpio_DiscreteSet(&xgpio,1,BUZZ)
#define BUZZ_CLR	XGpio_DiscreteClear(&xgpio,1,BUZZ)

extern uint8_t buzz_enable;

void buzz_beep(void);



void gpio_init();






#endif
