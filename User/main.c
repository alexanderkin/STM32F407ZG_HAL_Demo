#include "main.h"
#include "clock_init.h"
#include "bsp_init.h"
#include "rtos_task.h"

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    bsp_Init();
	
		lv_init();
    lv_port_disp_init();
		lv_demo_widgets();

    for (;;)
    {
        lv_task_handler();
    }
	
//    if (start_Task_Init() == pdPASS)
//    {
//        vTaskStartScheduler();
//    }
//    
//    for (;;) { };
}

HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
  return HAL_OK;
}
