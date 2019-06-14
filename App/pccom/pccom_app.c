/**
  ******************************************************************************
  * @�ļ���     �� pccom.c
  * @����       �� FelixWu
  * @�汾       �� V1.0.0
  * @����       �� 2019��03��01��
  * @ժҪ       �� arm board communication with nvidia board
  ******************************************************************************/
/*----------------------------------------------------------------------------
  ������־:
  2019-03-01 V1.0.0:��ʼ�汾
  ----------------------------------------------------------------------------*/
#include "pccom_app.h"
#include "pccom_drv.h"


/* ��̬���� ------------------------------------------------------------------*/
static void PCcom_App_Task(void *pvParameters);


/************************************************
�������� �� PCcom_App_Init
��    �� �� PCcomӦ�ó����ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� FelixWu
*************************************************/
void PCcom_App_Init(void)
{
    BaseType_t xReturn;

    PCcom_Driver_Init();

    xReturn = xTaskCreate(PCcom_App_Task, "PCcom_App_Task", PCCOM_STACK_SIZE, NULL, PCCOM_TASK_PRIORITY, NULL);
    if(pdPASS != xReturn)
    {
        return;                                      //������������ʧ��
    }
}

/************************************************
�������� �� PCcom_App_Task
��    �� �� PCcomӦ���������
��    �� �� pvParameters --- ��ѡ����
�� �� ֵ �� ��
��    �� �� FelixWu
*************************************************/
static void PCcom_App_Task(void *pvParameters)
{
    for(;;)
    {
        vTaskDelay(1000);
        /* Ӧ�ô��� */
    }
}


/**** Copyright (C)2019 FelixWu. All Rights Reserved **** END OF FILE ****/
