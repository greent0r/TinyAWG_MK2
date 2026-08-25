
#ifndef MAX17048_MAX17048_H_
#define MAX17048_MAX17048_H_

#include <stdio.h>
#include "stdlib.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xparameters_ps.h"
#include "sleep.h"
#include "gpio.h"
#include "i2c.h"
#include "stdbool.h"

/*MAX17048设备I2C地址*/
#define DEV_ADDR                0x36
/*MAX17048设备I2C写操作地址*/
#define DEV_ADDR_WRITE          0x6C
/*MAX17048设备I2C读操作地址*/
#define DEV_ADDR_READ           0x6D

/*MAX17048寄存器地址*/
#define REG_V_CELL              0x02
#define REG_SOC                 0x04
#define REG_MODE                0x06
#define REG_VERSION             0x08
#define REG_HIBRT               0x0A
#define REG_CONFIG              0x0C
#define REG_VALRT               0x14
#define REG_CRATE               0x16
#define REG_V_RESET             0x18
#define REG_STATUS              0x1A

#define REG_TABLE               0x40/**< REG RANGE:0x40 to 0x70*/
#define REG_TABLE_END           0x70

#define REG_CMD                 0xFE

/*16BIT位*/
#define REG_BIT0                (1U<<0)
#define REG_BIT1                (1U<<1)
#define REG_BIT2                (1U<<2)
#define REG_BIT3                (1U<<3)
#define REG_BIT4                (1U<<4)
#define REG_BIT5                (1U<<5)
#define REG_BIT6                (1U<<6)
#define REG_BIT7                (1U<<7)
#define REG_BIT8                (1U<<8)
#define REG_BIT9                (1U<<9)
#define REG_BIT10               (1U<<10)
#define REG_BIT11               (1U<<11)
#define REG_BIT12               (1U<<12)
#define REG_BIT13               (1U<<13)
#define REG_BIT14               (1U<<14)
#define REG_BIT15               (1U<<15)

// 全局变量声明
extern uint16_t Battery_Soc;
extern uint16_t Battery_Voltage;

// 函数声明
void max17048_init(void);
void max17048_update(void);


#endif /* MAX17048_MAX17048_H_ */