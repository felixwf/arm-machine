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


/* ��̬���� ------------------------------------------------------------------*/
static void PCcom_Rec_App_Task(void *pvParameters);
TaskHandle_t PCcom_Rec_App_Task_Handler;
static void PCcom_Send_App_Task(void *pvParameters);
TaskHandle_t PCcom_Send_App_Task_Handler;


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

    xReturn = xTaskCreate(PCcom_Rec_App_Task, "PCcom_Rec_App_Task", PCCOM_STACK_SIZE, NULL, PCCOM_TASK_PRIORITY, &PCcom_Rec_App_Task_Handler);
    if(pdPASS != xReturn)
    {
        return;                                      //������������ʧ��
    }
    xReturn = xTaskCreate(PCcom_Send_App_Task, "PCcom_Send_App_Task", PCCOM_STACK_SIZE, NULL, PCCOM_TASK_PRIORITY, &PCcom_Rec_App_Task_Handler);
    if(pdPASS != xReturn)
    {
        return;                                      //����Send����ʧ��
    }
}


/************************************************
�������� �� PCcom_Rec_App_Task
��    �� �� PCcomӦ���������
��    �� �� pvParameters --- ��ѡ����
�� �� ֵ �� ��
��    �� �� FelixWu
*************************************************/
static void PCcom_Rec_App_Task(void *pvParameters)
{
	u32 NotifyValue = 0;
	BaseType_t err;
    for(;;)
    {
		err = xTaskNotifyWait(0x00, 0xffffffff, &NotifyValue, portMAX_DELAY);
		if(err == pdPASS)
		{
			switch(NotifyValue)// ���ݴ����յ��Ĳ�ͬ��ָ����룬���в�ͬ�Ĳ�����
			{
                case 0x00:
                    // (x, y)
                    target_cartesian.x = ((uint32_t)(PC_COM_RX_BUF_BACKUP[3] << 24) + (uint32_t)(PC_COM_RX_BUF_BACKUP[4] << 16) + (uint32_t)(PC_COM_RX_BUF_BACKUP[5] << 8) + PC_COM_RX_BUF_BACKUP[6]) / 1000.0;
                    target_cartesian.y = ((uint32_t)(PC_COM_RX_BUF_BACKUP[7] << 24) + (uint32_t)(PC_COM_RX_BUF_BACKUP[8] << 16) + (uint32_t)(PC_COM_RX_BUF_BACKUP[9] << 8) + PC_COM_RX_BUF_BACKUP[10]) / 1000.0;
                    printf("x = %.3fmm\ty = %.3fmm\r\n", target_cartesian.x, target_cartesian.y);
                    break;
                case 0x01:
                    // (theta, distance)
                    target_polar.distance = ((uint32_t)(PC_COM_RX_BUF_BACKUP[3] << 24) + (uint32_t)(PC_COM_RX_BUF_BACKUP[4] << 16) + (uint32_t)(PC_COM_RX_BUF_BACKUP[5] << 8) + PC_COM_RX_BUF_BACKUP[6]) / 1000.0;
                    target_polar.theta = ((uint32_t)(PC_COM_RX_BUF_BACKUP[7] << 24) + (uint32_t)(PC_COM_RX_BUF_BACKUP[8] << 16) + (uint32_t)(PC_COM_RX_BUF_BACKUP[9] << 8) + PC_COM_RX_BUF_BACKUP[10]) / 1000.0;
                    printf("d = %.3fmm\ttheta = %.3fdeg\r\n", target_polar.distance, target_polar.theta);
                    break;
                case 0x02:
                    // (lift up and drop down)
                    if(PC_COM_RX_BUF_BACKUP[3] == 0x01)
                    {
                        // lift up
                        
                    }
                    else
                    {
                        // drop down
                    }
                    break;
                case 0x03:
                    // (activate and deactivate sucker)
                    if(PC_COM_RX_BUF_BACKUP[3] == 0x01)
                    {
                        // activate
                    }
                    else
                    {
                        // deactivate
                    }
                    
                    printf("0x03");
                    break;
                default:
                    break;
			}		
		}
        vTaskDelay(1);
        /* Ӧ�ô��� */
    }
}

/************************************************
�������� �� PCcom_Send_App_Task
��    �� �� PCcomӦ���������
��    �� �� pvParameters --- ��ѡ����
�� �� ֵ �� ��
��    �� �� FelixWu
*************************************************/
static void PCcom_Send_App_Task(void *pvParameters)
{
	u32 NotifyValue = 0;
	BaseType_t err;
    for(;;)
    {
		err = xTaskNotifyWait(0x00, 0xffffffff, &NotifyValue, portMAX_DELAY);
		if(err == pdPASS)
		{
            printf("update the status");
            // send the status to PC
        }
    }

}
/************************************************
�������� �� PC_COM_IRQHandler
��    �� �� USARTx�ж�(ͨѶ)
��    �� �� ��
�� �� ֵ �� ��
��    �� �� FelixWu
*************************************************/
void PC_COM_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdTRUE;

    if(USART_GetITStatus(PC_COM, USART_IT_RXNE) != RESET)
    {
        /* START --- �������������ݣ���Ϊ�˱�֤����˱�־ */
        USART_ClearITPendingBit(PC_COM, USART_IT_RXNE);
        /* END ---- �������������ݣ���Ϊ�˱�֤����˱�־ */

        PC_COM_RX_BUF[PC_COM_RX_STA++] = USART_ReceiveData(PC_COM);
    }
    else if(USART_GetITStatus(PC_COM, USART_IT_IDLE) != RESET)	// ������յ�������һ֡����
    {
        USART_ReceiveData(PC_COM);
        PC_COM_RX_STA=0;
        USART_ClearITPendingBit(PC_COM,USART_IT_IDLE);

        /* Notify battery����task */
        for(int i = 0 ; i < PC_COM_REC_LEN; i ++)
            PC_COM_RX_BUF_BACKUP[i] = PC_COM_RX_BUF[i];
		
		if(PCcom_Rec_App_Task_Handler!=NULL) {
			xTaskNotifyFromISR(PCcom_Rec_App_Task_Handler, PC_COM_RX_BUF[2], (eNotifyAction) eSetValueWithOverwrite,&xHigherPriorityTaskWoken);//��������֪ͨ
			portYIELD_FROM_ISR(PCcom_Rec_App_Task_Handler);//�����Ҫ�Ļ�����һ�������л�
		}

    }

    /* START --- �������������ݣ���Ϊ�˱�֤����˱�־ */
    //���ĵط����־
    if(USART_GetFlagStatus(PC_COM,USART_FLAG_ORE) == SET)
    {
        USART_ClearFlag(PC_COM,USART_FLAG_ORE);
        USART_ReceiveData(PC_COM);
    }
    /* END ---- �������������ݣ���Ϊ�˱�֤����˱�־ */
}


/**** Copyright (C)2019 FelixWu. All Rights Reserved **** END OF FILE ****/
