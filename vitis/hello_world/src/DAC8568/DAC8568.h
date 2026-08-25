#ifndef DAC8568
#define DAC8568

#include <stdio.h>
#include "stdlib.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xparameters_ps.h"
#include "sleep.h"
#include "gpio.h"


//GPIO置位（拉高）
#define	LDAC_SET	XGpio_DiscreteSet(&xgpio,1,LDAC)    	  
#define	CLR_SET	    XGpio_DiscreteSet(&xgpio,1,CLR)   
#define	SYNC_SET	XGpio_DiscreteSet(&xgpio,1,SYNC)  	  
#define	SCLK_SET	XGpio_DiscreteSet(&xgpio,1,SCLK)   	
#define	DIN_SET	    XGpio_DiscreteSet(&xgpio,1,DIN)    

//GPIO复位（拉低）							    
#define	LDAC_CLR	XGpio_DiscreteClear(&xgpio,1,LDAC)     
#define	CLR_CLR	    XGpio_DiscreteClear(&xgpio,1,CLR)     
#define	SYNC_CLR	XGpio_DiscreteClear(&xgpio,1,SYNC) 
#define	SCLK_CLR	XGpio_DiscreteClear(&xgpio,1,SCLK)   	  
#define	DIN_CLR	    XGpio_DiscreteClear(&xgpio,1,DIN)    

#define PrefixControlbyte 0x03
#define AddressOutA 0x0 //OFFSET_in0
#define AddressOutB 0x1 //REFIO1
#define AddressOutC 0x2 //VG_in0
#define AddressOutD 0x3 //VG_in1
#define AddressOutE 0x4 //REFIO0
#define AddressOutF 0x5 //OFFSET_in1
#define AddressOutG 0x6 //
#define AddressOutH 0x7 //
#define Featurebyte 0x0 //

#define OFFSET_in0 AddressOutA
#define REFIO1     AddressOutB
#define VG_in0     AddressOutC
#define VG_in1     AddressOutD
#define REFIO0     AddressOutE
#define OFFSET_in1 AddressOutF
 
/****************************DAC8568命令************************/
#define SETUP_INTERNAL_REGISTER 0
#define POWER_UP 1
#define RESET 2
 

void DAC8568_Init(void);
void DAC8568_SetVolt(unsigned char Ch, float Vol);


#endif
