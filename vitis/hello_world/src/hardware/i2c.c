#include "i2c.h"

XIicPs i2c0;
XIicPs i2c1;

/**
 * @brief 初始化 i2c0
 */
int i2c0_init(void)
{
    int status;
    XIicPs_Config* i2c_config = XIicPs_LookupConfig(I2C0_BASE_ADDR);

    status = XIicPs_CfgInitialize(&i2c0, i2c_config, i2c_config->BaseAddress);
    if (status != XST_SUCCESS) {
        xil_printf("i2c0: CfgInitialize failed.\r\n");
        return XST_FAILURE;
    }

    status = XIicPs_SetSClk(&i2c0, I2C_DEFAULT_BAUD_RATE);
    if (status != XST_SUCCESS) {
        xil_printf("i2c0: SetSClk failed.\r\n");
        return XST_FAILURE;
    }

    xil_printf("i2c0: Initialized\r\n");
    return XST_SUCCESS;
}

/**
 * @brief 初始化 i2c1
 */
int i2c1_init(void)
{
    int status;
    XIicPs_Config* i2c_config = XIicPs_LookupConfig(I2C1_BASE_ADDR);

    status = XIicPs_CfgInitialize(&i2c1, i2c_config, i2c_config->BaseAddress);
    if (status != XST_SUCCESS) {
        xil_printf("i2c1: CfgInitialize failed.\r\n");
        return XST_FAILURE;
    }

    status = XIicPs_SetSClk(&i2c1, I2C_DEFAULT_BAUD_RATE);
    if (status != XST_SUCCESS) {
        xil_printf("i2c1: SetSClk failed.\r\n");
        return XST_FAILURE;
    }

    xil_printf("i2c1: Initialized\r\n");
    return XST_SUCCESS;
}

/**
 * @brief i2c0 写入数据
 */
int i2c0_write_data(u16 slave_addr, u8 *data, u16 len)
{
    int status = XIicPs_MasterSendPolled(&i2c0, data, len, slave_addr);
    if (status != XST_SUCCESS) {
        xil_printf("i2c0: Write failed (len=%u, addr=0x%02X).\r\n", len, slave_addr);
        return XST_FAILURE;
    }
    while (XIicPs_BusIsBusy(&i2c0));
    return XST_SUCCESS;
}

/**
 * @brief i2c1 写入数据
 */
int i2c1_write_data(u16 slave_addr, u8 *data, u16 len)
{
    int status = XIicPs_MasterSendPolled(&i2c1, data, len, slave_addr);
    if (status != XST_SUCCESS) {
        xil_printf("i2c1: Write failed: %d (len=%u, addr=0x%02X).\r\n", status, len, slave_addr);
        return XST_FAILURE;
    }
    while (XIicPs_BusIsBusy(&i2c1));
    return XST_SUCCESS;
}

/**
 * @brief i2c0 读取数据
 */
int i2c0_read_data(u16 slave_addr, u8 reg ,u8 *data, u16 len)
{
    int status = XIicPs_MasterSendPolled(&i2c0, &reg, 1, slave_addr);
    if (status != XST_SUCCESS) {
        xil_printf("i2c0: Read address setup failed.\r\n");
        return XST_FAILURE;
    }
    while (XIicPs_BusIsBusy(&i2c0));

    status = XIicPs_MasterRecvPolled(&i2c0, data, len, slave_addr);
    if (status != XST_SUCCESS) {
        xil_printf("i2c0: Read data failed (len=%u, addr=0x%02X).\r\n", len, slave_addr);
        return XST_FAILURE;
    }
    while (XIicPs_BusIsBusy(&i2c0));
    return XST_SUCCESS;
}

/**
 * @brief i2c1 读取数据
 */
int i2c1_read_data(u16 slave_addr, u8 reg, u8 *data, u16 len)
{
    int status = XIicPs_MasterSendPolled(&i2c1, &reg, 1, slave_addr);
    if (status != XST_SUCCESS) {
        xil_printf("i2c1: Read address setup failed.\r\n");
        return XST_FAILURE;
    }
    while (XIicPs_BusIsBusy(&i2c1));

    status = XIicPs_MasterRecvPolled(&i2c1, data, len, slave_addr);
    if (status != XST_SUCCESS) {
        xil_printf("i2c1: Read data failed (len=%u, addr=0x%02X).\r\n", len, slave_addr);
        return XST_FAILURE;
    }
    while (XIicPs_BusIsBusy(&i2c1));
    return XST_SUCCESS;
}




// void MyI2C_W_SCL(uint8_t BitValue)
// {
//     if(BitValue)
//         XGpio_DiscreteSet(&xgpio, 1, SCL);
//     else
//         XGpio_DiscreteClear(&xgpio, 1, SCL);
// }

// void MyI2C_W_SDA(uint8_t BitValue)
// {
//     // 设置SDA位为输出模式（清除SDA位，0表示输出）
//     uint32_t current_dir = XGpio_GetDataDirection(&xgpio, 1);
//     current_dir &= ~SDA;  // 清除SDA位，设为输出
//     XGpio_SetDataDirection(&xgpio, 1, current_dir);
    
//     if(BitValue)
//         XGpio_DiscreteSet(&xgpio, 1, SDA);
//     else
//         XGpio_DiscreteClear(&xgpio, 1, SDA);
// }

// uint8_t MyI2C_R_SDA(void)
// {
//     // 设置SDA位为输入模式（设置SDA位，1表示输入）
//     uint32_t current_dir = XGpio_GetDataDirection(&xgpio, 1);
//     current_dir |= SDA;   // 设置SDA位，设为输入
//     XGpio_SetDataDirection(&xgpio, 1, current_dir);
    
//     // 读取SDA位的状态
//     uint32_t gpio_value = XGpio_DiscreteRead(&xgpio, 1);
//     return (gpio_value & SDA) ? 1 : 0;
// }

// void MyI2C_Start(void)
// {
//     MyI2C_W_SDA(1);
//     MyI2C_W_SCL(1);
//     usleep(2);
//     MyI2C_W_SDA(0);
//     usleep(2);
//     MyI2C_W_SCL(0);
// }

// void MyI2C_Stop(void)
// {
//     MyI2C_W_SDA(0);
//     MyI2C_W_SCL(0);
//     usleep(2);
//     MyI2C_W_SCL(1);
//     usleep(2);
//     MyI2C_W_SDA(1);
//     usleep(2);
// }

// void MyI2C_SendByte(uint8_t Byte)
// {
//     uint8_t i;
//     MyI2C_W_SCL(0);
//     for (i = 0; i < 8; i ++){
//         MyI2C_W_SDA(Byte & (0x80 >> i));
//         usleep(2);
//         MyI2C_W_SCL(1);
//         usleep(2);
//         MyI2C_W_SCL(0);
//         usleep(2);
//     }
// }

// uint8_t MyI2C_ReceiveByte(void)
// {
//     uint8_t i, Byte = 0x00;
//     for (i = 0x80; i != 0; i >>= 1)
//     {
//         MyI2C_W_SCL(0);
//         usleep(2);
//         MyI2C_W_SCL(1);
//         if (MyI2C_R_SDA())  Byte |= i;
//         else                Byte &= ~i;
//         usleep(2);
//     }
//     return Byte;
// }

// void MyI2C_SendAck(uint8_t AckBit)
// {
//     if(AckBit){
//         MyI2C_W_SCL(0);
//         MyI2C_W_SDA(0);
//         usleep(2);
//         MyI2C_W_SCL(1);
//         usleep(2);
//         MyI2C_W_SCL(0);
//     }
//     else{
//         MyI2C_W_SCL(0);
//         MyI2C_W_SDA(1);
//         usleep(2);
//         MyI2C_W_SCL(1);
//         usleep(2);
//         MyI2C_W_SCL(0);
//     }
// }

// uint8_t MyI2C_ReceiveAck(void)
// {
//     uint8_t AckBit;
//     usleep(2);
//     MyI2C_W_SCL(1);
//     usleep(2);
//     AckBit = MyI2C_R_SDA();
//     MyI2C_W_SCL(0);
//     return AckBit;
// }