#ifndef __ROTS_TASK_H__
#define __ROTS_TASK_H__

#include "main.h"
#include "bsp_init.h"
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"
#include "lvgl.h"

extern TaskHandle_t Task1_Handler;

int start_Task_Init(void);

#endif /* __ROTS_TASK_H__ */
