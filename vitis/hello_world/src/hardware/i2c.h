#ifndef I2C_H
#define I2C_H

#include "xparameters.h"
#include "xiicps.h"
#include "xil_printf.h"
#include "sleep.h"
#include "gpio.h"
#include "xgpio.h"

// I2C 配置参数
#define I2C0_BASE_ADDR         XPAR_XIICPS_0_BASEADDR
#define I2C1_BASE_ADDR         XPAR_XIICPS_1_BASEADDR  
#define I2C_DEFAULT_BAUD_RATE  100000

// I2C 实例
extern XIicPs i2c0;
extern XIicPs i2c1;

// 函数声明
int i2c0_init(void);
int i2c1_init(void);
int i2c0_write_data(u16 slave_addr, u8 *data, u16 len);
int i2c1_write_data(u16 slave_addr, u8 *data, u16 len);
int i2c0_read_data(u16 slave_addr, u8 reg ,u8 *data, u16 len);
int i2c1_read_data(u16 slave_addr, u8 reg, u8 *data, u16 len);

//GPIO IIC
// void MyI2C_Start(void);
// void MyI2C_Stop(void);
// void MyI2C_SendByte(uint8_t Byte);
// uint8_t MyI2C_ReceiveByte(void);
// void MyI2C_SendAck(uint8_t AckBit);
// uint8_t MyI2C_ReceiveAck(void);

#endif /* I2C_H */