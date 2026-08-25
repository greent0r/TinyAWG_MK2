#include "max17048.h"
#include "i2c.h"
#include "xil_printf.h"

uint16_t Battery_Soc = 0;        /**< 电池电量百分比*/
uint16_t Battery_Voltage = 0;    /**< 电池电压*/

void max17048_WriteReg(uint8_t reg, uint16_t data)
{
    // MyI2C_Start();
    // MyI2C_SendByte(DEV_ADDR_WRITE);
    // if(MyI2C_ReceiveAck()!=0) printf("no ack\n");
    // MyI2C_SendByte(reg);
    // if(MyI2C_ReceiveAck()!=0) printf("no ack\n");
    // MyI2C_SendByte(data>>8);
    // if(MyI2C_ReceiveAck()!=0) printf("no ack\n");
    // MyI2C_SendByte(data&0xff);
    // if(MyI2C_ReceiveAck()!=0) printf("no ack\n");
    // MyI2C_Stop();
    uint8_t write_buffer[3];
    write_buffer[0] = reg;
    write_buffer[1] = (data>>8)&0XFF;
    write_buffer[2] = data&0XFF;
    i2c1_write_data(DEV_ADDR, write_buffer, 3);

}

void max17048_ReadReg(uint8_t reg, uint16_t* data){
    // MyI2C_Start();
    // MyI2C_SendByte(DEV_ADDR_WRITE);
    // if(MyI2C_ReceiveAck()!=0) printf("no ack\n");
    // MyI2C_SendByte(reg);
    // if(MyI2C_ReceiveAck()!=0) printf("no ack\n");
    // MyI2C_Start();
    // MyI2C_SendByte(DEV_ADDR_READ);
    // if(MyI2C_ReceiveAck()!=0) printf("no ack\n");
    // *data = MyI2C_ReceiveByte()<<8;
    // MyI2C_SendAck(1);
    // *data |= MyI2C_ReceiveByte();
    // MyI2C_SendAck(0);
    // MyI2C_Stop();
    uint8_t buf[2];
    i2c1_read_data(DEV_ADDR, reg, buf, 2);
    *data = (buf[0]<<8) | buf[1];
}

void max17048_init(){
    uint16_t data=0;
    max17048_ReadReg(REG_STATUS, &data);
    data &= ~((0x01 & 0x3F) << 8);
    max17048_WriteReg(REG_STATUS, data);
    max17048_ReadReg(REG_VERSION, &data);
    printf("max17048 version=%x\n",data);
}

void max17048_update(){
    uint16_t data=0;
    max17048_ReadReg(REG_V_CELL, &data);
    Battery_Voltage = (data*10)>>7;
    // Battery_Soc = (Battery_Voltage >= 4160) ? 100 :
    //             (Battery_Voltage >= 4150) ? 99 :
    //             (Battery_Voltage >= 4140) ? 97 :
    //             (Battery_Voltage >= 4120) ? 95 :
    //             (Battery_Voltage >= 4100) ? 92 :
    //             (Battery_Voltage >= 4080) ? 90 :
    //             (Battery_Voltage >= 4050) ? 87 :
    //             (Battery_Voltage >= 4030) ? 85 :
    //             (Battery_Voltage >= 3970) ? 80 :
    //             (Battery_Voltage >= 3930) ? 75 :
    //             (Battery_Voltage >= 3900) ? 70 :
    //             (Battery_Voltage >= 3870) ? 65 :
    //             (Battery_Voltage >= 3840) ? 60 :
    //             (Battery_Voltage >= 3810) ? 55 :
    //             (Battery_Voltage >= 3790) ? 50 :
    //             (Battery_Voltage >= 3770) ? 45 :
    //             (Battery_Voltage >= 3760) ? 40 :
    //             (Battery_Voltage >= 3740) ? 35 :
    //             (Battery_Voltage >= 3730) ? 30 :
    //             (Battery_Voltage >= 3720) ? 25 :
    //             (Battery_Voltage >= 3710) ? 20 :
    //             (Battery_Voltage >= 3690) ? 15 :
    //             (Battery_Voltage >= 3660) ? 12 :
    //             (Battery_Voltage >= 3650) ? 10 :
    //             (Battery_Voltage >= 3640) ? 8 :
    //             (Battery_Voltage >= 3630) ? 5 :
    //             (Battery_Voltage >= 3610) ? 3 : 1;
    max17048_ReadReg(REG_SOC, &data);
    Battery_Soc = data>>8;
    if(Battery_Soc < 1) Battery_Soc = 1;
    //max17048_ReadReg(REG_STATUS, &data);
    //uint16_t status = (data>>8) & 0x3F;
    //printf("status=%x,vcell=%.0fmV,soc=%d\%\n",status,vcell,soc);
}

