/**
  ******************************************************************************
  * @文件名     ： nvidiacom.c
  * @作者       ： FelixWu
  * @版本       ： V1.0.0
  * @日期       ： 2019年03月01日
  * @摘要       ： arm board communication with nvidia board
  ******************************************************************************/
/*----------------------------------------------------------------------------
  更新日志:
  2019-03-01 V1.0.0:初始版本
  ----------------------------------------------------------------------------*/
#include "nvidiacom_app.h"
#include "nvidiacom_drv.h"


/* 静态申明 ------------------------------------------------------------------*/
static void Nvidiacom_App_Task(void *pvParameters);


/************************************************
函数名称 ： Nvidiacom_App_Init
功    能 ： Nvidiacom应用程序初始化
参    数 ： 无
返 回 值 ： 无
作    者 ： FelixWu
*************************************************/
void Nvidiacom_App_Init(void)
{
    BaseType_t xReturn;

    Nvidiacom_Driver_Init();

    xReturn = xTaskCreate(Nvidiacom_App_Task, "Nvidiacom_App_Task", NVIDIACOM_STACK_SIZE, NULL, NVIDIACOM_TASK_PRIORITY, NULL);
    if(pdPASS != xReturn)
    {
        return;                                      //创建接收任务失败
    }
}

/************************************************
函数名称 ： Nvidiacom_App_Task
功    能 ： Nvidiacom应用任务程序
参    数 ： pvParameters --- 可选参数
返 回 值 ： 无
作    者 ： FelixWu
*************************************************/
static void Nvidiacom_App_Task(void *pvParameters)
{
	CanRxMsg RxMsg;
    for(;;)
    {
        vTaskDelay(1000);
//			CANRcv_DateFromISR(&RxMsg);
//	    printf("id = %d\r\n", RxMsg.DLC);
//	    printf("AGV_STATUS = 0x%x\tAGV_BATTERY = 0x%x\r\n", AGV_STATUS, SOC_battery);
        /* 应用代码 */
    }
}


/**** Copyright (C)2019 FelixWu. All Rights Reserved **** END OF FILE ****/
