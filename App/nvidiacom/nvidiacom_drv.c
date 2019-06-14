/**
  ******************************************************************************
  * @�ļ���     �� canopen_drv.c
  * @����       �� FelixWu
  * @�汾       �� V1.0.0
  * @����       �� 2019��03��01��
  * @ժҪ       �� nvidia com with arm����Դ�ļ�
  ******************************************************************************/
/*----------------------------------------------------------------------------
  ������־:
  2019-03-01 V1.0.0:��ʼ�汾
  ----------------------------------------------------------------------------*/
/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "nvidiacom_drv.h"


	  	


/* ��ʱ��TIM��ر��� */

/* ��̬���� ------------------------------------------------------------------*/



/************************************************
�������� �� UART_Nvidiacom_Configuration
��    �� �� Nvidiacom ��������
��    �� �� ��
�� �� ֵ �� ��
��    �� �� FelixWu
*************************************************/
void UART_Nvidiacom_Configuration(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef  NVIC_InitStructure;

  /* ʱ������ */
  RCC_APB2PeriphClockCmd(NVIDIA_COM_TX_GPIO_CLK | NVIDIA_COM_RX_GPIO_CLK , ENABLE);

  if(USART1 == NVIDIA_COM)
    RCC_APB2PeriphClockCmd(NVIDIA_COM_CLK, ENABLE);
  else
    RCC_APB1PeriphClockCmd(NVIDIA_COM_CLK, ENABLE);

  /* �������� */
  GPIO_InitStructure.GPIO_Pin = NVIDIA_COM_TX_PIN;                    //UART Tx
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(NVIDIA_COM_TX_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = NVIDIA_COM_RX_PIN;                    //UART Rx
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(NVIDIA_COM_RX_GPIO_PORT, &GPIO_InitStructure);

  /* NVIC���� */
  NVIC_InitStructure.NVIC_IRQChannel = NVIDIA_COM_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIDIA_COM_Priority;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* UART���� */
  USART_InitStructure.USART_BaudRate = NVIDIA_COM_BaudRate;           //������
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;        //����λ��
  USART_InitStructure.USART_StopBits = USART_StopBits_1;             //ֹͣλ
  USART_InitStructure.USART_Parity = USART_Parity_No ;               //У��λ
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;    //�շ����� USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(NVIDIA_COM, &USART_InitStructure);

  USART_ClearFlag(NVIDIA_COM, USART_FLAG_RXNE | USART_FLAG_TC);
  USART_ITConfig(NVIDIA_COM, USART_IT_RXNE, ENABLE);                  //�����ж�
  USART_ITConfig(NVIDIA_COM, USART_IT_IDLE, ENABLE);                  //�����ж�

  //USART_Cmd(NVIDIA_COM, ENABLE);                                      //ʹ��UART
  USART_Cmd(NVIDIA_COM, DISABLE);                                      //ʹ��UART
}

/************************************************
�������� �� NVIDIA_SendByte
��    �� �� ���Դ��ڷ���һ���ֽ�
��    �� �� Data --- ����
�� �� ֵ �� ��
��    �� �� FelixWu
*************************************************/
void NVIDIA_SendByte(uint8_t Data)
{
  /* �ȴ�����Ϊ�� */
  while(RESET == USART_GetFlagStatus(NVIDIA_COM, USART_FLAG_TXE));
  USART_SendData(NVIDIA_COM, Data);
}

/************************************************
�������� �� NVIDIA_SendNByte
��    �� �� ���Դ��ڷ���N���ֽ�
��    �� �� pData ---- ����
            Length --- ����
�� �� ֵ �� ��
��    �� �� FelixWu
*************************************************/
void NVIDIA_SendNByte(uint8_t *pData, uint16_t Length)
{
//  taskENTER_CRITICAL();
  while(Length--)
  {
    NVIDIA_SendByte(*pData);
    pData++;
  }
//  taskEXIT_CRITICAL();
}

/************************************************
�������� �� Nvidiacom_Driver_Init
��    �� �� Nvidiacom������ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� FelixWu
*************************************************/
void Nvidiacom_Driver_Init(void)
{
	
	UART_Nvidiacom_Configuration();
}




/**** Copyright (C)2019 FelixWu. All Rights Reserved **** END OF FILE ****/
