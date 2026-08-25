#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include <sys/_intsup.h>
#include <xil_types.h>
#include "xparameters.h"
#include "xparameters_ps.h"
#include "sleep.h"
#include "xgpio.h"
#include "xscutimer.h"
#include "sleep.h"

#include "user_dds.h"
#include "output_ctrl.h"
#include "DAC8568.h"
#include "MAX17048.h"
#include "touch.h"
#include "PC_HOST.h"
#include "lcd.h"
#include "i2c.h"
#include "spi.h"
#include "intc_timer.h"
#include "gpio.h"

#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "gui_guider.h"
#include "events_init.h"

lv_ui guider_ui;

int main()
{
    init_platform();
    uart_init();
    printf("Hello World Begin\n\r");
    gpio_init();
    spi_init();
    i2c0_init();
    i2c1_init();
    timer_init();
    ttc0_init();
    Setup_Intr_System();

    DAC8568_Init();
    max17048_init();
    LCD_Init();
    TP_Init();
    lv_init();
	lv_port_disp_init();
	lv_port_indev_init();
    setup_ui(&guider_ui);
    
    DDS0_OFF;
    DDS1_OFF;
    wave_update(0);
    wave_update(1);

    printf("Hello World End\n\r");

    while (1) 
    {
        uart_rx_process();
        scan_process();
        burst_process();
        lv_task_handler();
    }

    cleanup_platform();
    return 0;
}
