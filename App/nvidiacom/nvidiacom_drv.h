/**
  ******************************************************************************
  * @�ļ���     �� nvidia_drv.h
  * @����       �� FelixWu
  * @�汾       �� V1.0.0
  * @����       �� 2019��03��01��
  * @ժҪ       �� CANOpen����ͷ�ļ�
  ******************************************************************************/

/* �����ֹ�ݹ���� ----------------------------------------------------------*/
#ifndef _NVIDIACOM_DRV_H
#define _NVIDIACOM_DRV_H

/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "bsp_usart.h"
#include "global_var.h"


/* ��̬���� ------------------------------------------------------------------*/
static xQueueHandle xNVIDIARcvQueue = NULL;        //UART���ն���

/* �궨�� --------------------------------------------------------------------*/
/* Nvidia */
#define NVIDIA_COM                 USART3
#define NVIDIA_COM_CLK             RCC_APB1Periph_USART3
#define NVIDIA_COM_TX_GPIO_CLK     RCC_APB2Periph_GPIOB     //UART TX
#define NVIDIA_COM_TX_PIN          GPIO_Pin_10
#define NVIDIA_COM_TX_GPIO_PORT    GPIOB
#define NVIDIA_COM_RX_GPIO_CLK     RCC_APB2Periph_GPIOB     //UART RX
#define NVIDIA_COM_RX_PIN          GPIO_Pin_11
#define NVIDIA_COM_RX_GPIO_PORT    GPIOB
#define NVIDIA_COM_IRQn            USART3_IRQn
#define NVIDIA_COM_Priority        7                       //���ȼ�
#define NVIDIA_COM_BaudRate        115200                   //������
#define NVIDIA_COM_IRQHandler      USART3_IRQHandler        //�жϺ����ӿ�(��stm32f10x_it.c)

	  	
#define NVIDIA_COM_RX_QUEUE_LEN           10                       //Nvidia_com���ն��г���(���е�����)(����)
#define NVIDIA_COM_RX_QUEUE_SIZE          19                       //Nvidia_com���ն��д�С(һ�����г���) - sizeof(CanTxMsg)


/* �������� ------------------------------------------------------------------*/
void Nvidiacom_Driver_Init(void);
void NVIDIA_SendNByte(uint8_t *pData, uint16_t Length);
void NVIDIA_SendByte(uint8_t Data);

#endif /* _NVIDIACOM_DRV_H */

/**** Copyright (C)2019 FelixWu. All Rights Reserved **** END OF FILE ****/
