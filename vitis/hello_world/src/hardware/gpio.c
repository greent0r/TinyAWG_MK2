#include "gpio.h"

XGpio xgpio;

uint8_t buzz_enable = 0;         // 按键声音开关（默认关闭，系统界面可切换）

// 蜂鸣器触发：GPIO输出一个短脉冲，PL侧蜂鸣器模块检测到脉冲后自行驱动发声
// （不占用PS定时器资源；脉冲宽度约1us，远小于UI调度周期，非阻塞）
void buzz_beep(void)
{
    if (!buzz_enable) return;
    BUZZ_SET;
    for (volatile uint32_t i = 0; i < 200; i++);   // ~1us 脉冲宽度
    BUZZ_CLR;
}

void gpio_init()
{
    XGpio_Initialize(&xgpio, XPAR_XGPIO_0_BASEADDR);
    XGpio_SetDataDirection(&xgpio, 1, 0);

    // XGpio_DiscreteClear(&xgpio,1,K1);
    // XGpio_DiscreteClear(&xgpio,1,K2);
    // XGpio_DiscreteSet(&xgpio,1,K3);
    // XGpio_DiscreteClear(&xgpio,1,K4);
    // XGpio_DiscreteSet(&xgpio,1,K5);
}
