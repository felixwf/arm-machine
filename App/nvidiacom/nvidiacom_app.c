/**
  ******************************************************************************
  * @�ļ���     �� nvidiacom.c
  * @����       �� FelixWu
  * @�汾       �� V1.0.0
  * @����       �� 2019��03��01��
  * @ժҪ       �� arm board communication with nvidia board
  ******************************************************************************/
/*----------------------------------------------------------------------------
  ������־:
  2019-03-01 V1.0.0:��ʼ�汾
  ----------------------------------------------------------------------------*/
#include "nvidiacom_app.h"
#include "nvidiacom_drv.h"


/* ��̬���� ------------------------------------------------------------------*/
static void Nvidiacom_App_Task(void *pvParameters);


/************************************************
�������� �� Nvidiacom_App_Init
��    �� �� NvidiacomӦ�ó����ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� FelixWu
*************************************************/
void Nvidiacom_App_Init(void)
{
    BaseType_t xReturn;

    Nvidiacom_Driver_Init();

    xReturn = xTaskCreate(Nvidiacom_App_Task, "Nvidiacom_App_Task", NVIDIACOM_STACK_SIZE, NULL, NVIDIACOM_TASK_PRIORITY, NULL);
    if(pdPASS != xReturn)
    {
        return;                                      //������������ʧ��
    }
}

/************************************************
�������� �� Nvidiacom_App_Task
��    �� �� NvidiacomӦ���������
��    �� �� pvParameters --- ��ѡ����
�� �� ֵ �� ��
��    �� �� FelixWu
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
        /* Ӧ�ô��� */
    }
}


/**** Copyright (C)2019 FelixWu. All Rights Reserved **** END OF FILE ****/
