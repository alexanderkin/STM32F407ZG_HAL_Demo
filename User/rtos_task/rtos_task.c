#include "rtos_task.h"

#define TASK1_PRIORITY 1
#define TASK1_STACK_SIZE 512
TaskHandle_t Task1_Handler;

#define TASK2_PRIORITY 2
#define TASK2_STACK_SIZE 512
TaskHandle_t Task2_Handler;

#define TASK3_PRIORITY 3
#define TASK3_STACK_SIZE 512
TaskHandle_t Task3_Handler;

static void task1(void)
{
    GPIO_PinState state;
    for (;;)
    {
        LED3_Toggle();
        state = HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_8);
        if (state == GPIO_PIN_RESET)
            printf("Task1 : LED is = ON\r\n");
        else if (state == GPIO_PIN_SET)
            printf("Task1 : LED is = OFF\r\n");
        vTaskDelay(500);
    }
}

static void task2(void)
{
    int i = 0;
    for (;;)
    {
        i++;
        printf("Task2 : i = %d\r\n", i);
        vTaskDelay(1000);
    }  
}

static void task3(void)
{
    int Battery = 0;
    int Hour = 21, Minute = 35, Second = 00;
    int Year = 2022, Month = 1, Day = 8;
    char timeBuff[100];
    char dataBuff[100];
    NT35510_Clear(0, 0, 800, 480, WHITE);
    NT35510_Clear(0, 0, 800, 60, BLUE);

    NT35510_Clear(730, 19, 40, 20, WHITE);
    NT35510_Clear(770, 25, 4, 8, WHITE);
    NT35510_Clear(733, 22, 32, 14, BLUE);
    NT35510_Clear(734, 23, 10, 12, WHITE);

    NT35510_Clear(136, 150, 480, 240, BLACK);
    NT35510_Clear(616, 222, 48, 96, BLACK);
    NT35510_Clear(172, 186, 408, 168, WHITE);
    NT35510_Clear(184, 198, 128, 144, BLACK);

    for (;;)
    {
        Battery++;
        Second++;
        if (Second == 60)
        {
            Minute++;
            Second = 0;
        }
        if (Minute == 60)
        {
            Hour++;
            Minute = 0;
        }
        if (Hour == 24)
        {
            Day++;
            Hour = 0;
        }
        if (Day == 31)
        {
            Month++;
            Day = 1;
        }
        if (Month == 13)
        {
            Year++;
            Month = 1;
        }
        LCD_SetColors(WHITE, BLUE);
        sprintf(timeBuff, "%02d:%02d:%02d ", Hour, Minute, Second);
        NT35510_DispString_EN(10, 12, timeBuff);
        sprintf(dataBuff, "%d/%02d/%02d ", Year, Month, Day);
        NT35510_DispString_EN(320, 12, dataBuff);
        
        if (Battery < 3)
        {
            NT35510_Clear(744, 23, 10 * Battery, 12, WHITE);
            NT35510_Clear(312, 198, 128 * Battery, 144, BLACK);
        }
        else
        {
            Battery = 0;
            NT35510_DispString_EN(10, 12, timeBuff);
            NT35510_DispString_EN(320, 12, dataBuff);
            NT35510_Clear(744, 22, 20, 14, BLUE);
            NT35510_Clear(312, 186, 268, 168, WHITE);
        }
        vTaskDelay(1000);
    }
}

int start_Task_Init(void)
{
    BaseType_t xReturn = pdPASS;

    xReturn = xTaskCreate((TaskFunction_t) task1,
                          (const char *  ) "task1",
                          (uint16_t      ) TASK1_STACK_SIZE,
                          (void *        ) NULL,
                          (UBaseType_t   ) TASK1_PRIORITY,
                          (TaskHandle_t* ) &Task1_Handler);
    if (xReturn == pdPASS)
        printf("task1 Create Success!\r\n");
    else
        printf("task1 Create Error!\r\n");

    xReturn = xTaskCreate((TaskFunction_t) task2,
                          (const char *  ) "task2",
                          (uint16_t      ) TASK2_STACK_SIZE,
                          (void *        ) NULL,
                          (UBaseType_t   ) TASK2_PRIORITY,
                          (TaskHandle_t* ) &Task2_Handler);
    if (xReturn == pdPASS)
        printf("task2 Create Success!\r\n");
    else
        printf("task2 Create Error!\r\n");

    xReturn = xTaskCreate((TaskFunction_t) task3,
                          (const char *  ) "task3",
                          (uint16_t      ) TASK3_STACK_SIZE,
                          (void *        ) NULL,
                          (UBaseType_t   ) TASK3_PRIORITY,
                          (TaskHandle_t* ) &Task3_Handler);
    if (xReturn == pdPASS)
        printf("task2 Create Success!\r\n");
    else
        printf("task2 Create Error!\r\n");
    
    return xReturn;
}
