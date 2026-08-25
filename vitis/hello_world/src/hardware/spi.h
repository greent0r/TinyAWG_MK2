#ifndef SPI
#define SPI


#include <stdio.h>
#include "xil_printf.h"
#include "xparameters.h"
#include "xparameters_ps.h"
#include "xspips.h"
#include "xdmaps.h"

#define SPI_BASE_ADDR       XPS_SPI0_BASEADDR

// 从设备片选（0, 1, or 2）
#define SPI_SELECT_SLAVE    0

// 输入时钟频率
#define SPI_INPUT_CLK_HZ    XPAR_SPI0_SPI_CLK_FREQ_HZ

extern XSpiPs SpiInstance;


// 函数声明
int spi_init(void);
int spi_send_receive(u8 *tx_buffer, u8 *rx_buffer, u32 length);
int spi_send_only(u8 *tx_buffer, u32 length);
int spi_receive_only(u8 *rx_buffer, u32 length);

#endif /* SPI_H_ */


