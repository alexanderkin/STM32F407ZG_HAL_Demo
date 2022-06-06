#include "bsp_init.h"

void bsp_Init(void)
{
    bsp_led_init();
    bsp_usart_init();
    bsp_lcd_init();
		bsp_Tim7_Init(1000);
}
