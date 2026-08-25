#include "spi.h"

XSpiPs SpiInstance;

/**
 * @brief 使用基地址初始化 SPI0（Master 模式）
 * 手动构造 XSpiPs_Config 结构体，避免使用 DeviceId
 * @return XST_SUCCESS on success
 */
int spi_init(void)
{
    int status;
    XSpiPs_Config spi_config;

    spi_config.BaseAddress = SPI_BASE_ADDR;
    spi_config.InputClockHz = SPI_INPUT_CLK_HZ;
    // 其他字段（如 DeviceId、IntrId）在非中断模式下可忽略

    // 使用 CfgInitialize 初始化（这是官方唯一初始化入口）
    status = XSpiPs_CfgInitialize(&SpiInstance, &spi_config, spi_config.BaseAddress);
    if (status != XST_SUCCESS) {
        xil_printf("SPI: CfgInitialize failed.\r\n");
        return XST_FAILURE;
    }

    // 设置选项：Master + Force SS（推荐）
    u32 options = XSPIPS_MASTER_OPTION |
                  XSPIPS_FORCE_SSELECT_OPTION;
    // 若需 Mode 2（CPOL=1），加上 XSPIPS_CLK_ACTIVE_LOW_OPTION
    // 注意：Zynq PS SPI 不支持 CPHA=1（即 XSPIPS_CLK_PHASE_1_OPTION 无效！）
    // 官方文档明确说明：Zynq-7000 PS SPI 仅支持 CPHA=0

    status = XSpiPs_SetOptions(&SpiInstance, options);
    if (status != XST_SUCCESS) {
        xil_printf("SPI: SetOptions failed.\r\n");
        return XST_FAILURE;
    }

    // 设置时钟分频（驱动内部根据 InputClockHz 和目标频率计算 Prescaler）
    status = XSpiPs_SetClkPrescaler(&SpiInstance, XSPIPS_CLK_PRESCALE_4);
    if (status != XST_SUCCESS) {
        xil_printf("SPI: SetClkPrescaler failed for %d.\r\n", XSPIPS_CLK_PRESCALE_256);
        return XST_FAILURE;
    }

    XSpiPs_SetSlaveSelect(&SpiInstance, 0x00);

    xil_printf("SPI: Initialized\r\n");

    return XST_SUCCESS;
}

/**
 * @brief 全双工 SPI 传输（轮询）
 */
int spi_send_receive(u8 *tx_buf, u8 *rx_buf, u32 len)
{
    if (len == 0) return XST_SUCCESS;

    int status = XSpiPs_PolledTransfer(&SpiInstance, tx_buf, rx_buf, len);
    if (status != XST_SUCCESS) {
        xil_printf("SPI: Transfer failed (len=%lu).\r\n", len);
        return XST_FAILURE;
    }
    return XST_SUCCESS;
}

int spi_send_only(u8 *tx_buf, u32 len)
{
    return spi_send_receive(tx_buf, NULL, len);
}

int spi_receive_only(u8 *rx_buf, u32 len)
{
    return spi_send_receive(NULL, rx_buf, len);
}