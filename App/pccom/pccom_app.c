/**
  ******************************************************************************
  * @文件名     ： pccom.c
  * @作者       ： FelixWu
  * @版本       ： V1.0.0
  * @日期       ： 2019年03月01日
  * @摘要       ： arm board communication with nvidia board
  ******************************************************************************/
/*----------------------------------------------------------------------------
  更新日志:
  2019-03-01 V1.0.0:初始版本
  ----------------------------------------------------------------------------*/
#include "pccom_app.h"
#include "pccom_drv.h"


/* 静态申明 ------------------------------------------------------------------*/
static void PCcom_App_Task(void *pvParameters);


/************************************************
函数名称 ： PCcom_App_Init
功    能 ： PCcom应用程序初始化
参    数 ： 无
返 回 值 ： 无
作    者 ： FelixWu
*************************************************/
void PCcom_App_Init(void)
{
    BaseType_t xReturn;

    PCcom_Driver_Init();

    xReturn = xTaskCreate(PCcom_App_Task, "PCcom_App_Task", PCCOM_STACK_SIZE, NULL, PCCOM_TASK_PRIORITY, NULL);
    if(pdPASS != xReturn)
    {
        return;                                      //创建接收任务失败
    }
}

/************************************************
函数名称 ： PCcom_App_Task
功    能 ： PCcom应用任务程序
参    数 ： pvParameters --- 可选参数
返 回 值 ： 无
作    者 ： FelixWu
*************************************************/
static void PCcom_App_Task(void *pvParameters)
{
    for(;;)
    {
        vTaskDelay(1000);
        /* 应用代码 */
    }
}


/**** Copyright (C)2019 FelixWu. All Rights Reserved **** END OF FILE ****/
