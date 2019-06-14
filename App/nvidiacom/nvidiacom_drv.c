/**
  ******************************************************************************
  * @文件名     ： canopen_drv.c
  * @作者       ： FelixWu
  * @版本       ： V1.0.0
  * @日期       ： 2019年03月01日
  * @摘要       ： nvidia com with arm驱动源文件
  ******************************************************************************/
/*----------------------------------------------------------------------------
  更新日志:
  2019-03-01 V1.0.0:初始版本
  ----------------------------------------------------------------------------*/
/* 包含的头文件 --------------------------------------------------------------*/
#include "nvidiacom_drv.h"


	  	


/* 定时器TIM相关变量 */

/* 静态申明 ------------------------------------------------------------------*/



/************************************************
函数名称 ： UART_Nvidiacom_Configuration
功    能 ： Nvidiacom 串口配置
参    数 ： 无
返 回 值 ： 无
作    者 ： FelixWu
*************************************************/
void UART_Nvidiacom_Configuration(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef  NVIC_InitStructure;

  /* 时钟配置 */
  RCC_APB2PeriphClockCmd(NVIDIA_COM_TX_GPIO_CLK | NVIDIA_COM_RX_GPIO_CLK , ENABLE);

  if(USART1 == NVIDIA_COM)
    RCC_APB2PeriphClockCmd(NVIDIA_COM_CLK, ENABLE);
  else
    RCC_APB1PeriphClockCmd(NVIDIA_COM_CLK, ENABLE);

  /* 引脚配置 */
  GPIO_InitStructure.GPIO_Pin = NVIDIA_COM_TX_PIN;                    //UART Tx
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(NVIDIA_COM_TX_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = NVIDIA_COM_RX_PIN;                    //UART Rx
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(NVIDIA_COM_RX_GPIO_PORT, &GPIO_InitStructure);

  /* NVIC配置 */
  NVIC_InitStructure.NVIC_IRQChannel = NVIDIA_COM_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIDIA_COM_Priority;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* UART配置 */
  USART_InitStructure.USART_BaudRate = NVIDIA_COM_BaudRate;           //波特率
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;        //传输位数
  USART_InitStructure.USART_StopBits = USART_StopBits_1;             //停止位
  USART_InitStructure.USART_Parity = USART_Parity_No ;               //校验位
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;    //收发功能 USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(NVIDIA_COM, &USART_InitStructure);

  USART_ClearFlag(NVIDIA_COM, USART_FLAG_RXNE | USART_FLAG_TC);
  USART_ITConfig(NVIDIA_COM, USART_IT_RXNE, ENABLE);                  //接收中断
  USART_ITConfig(NVIDIA_COM, USART_IT_IDLE, ENABLE);                  //接收中断

  //USART_Cmd(NVIDIA_COM, ENABLE);                                      //使能UART
  USART_Cmd(NVIDIA_COM, DISABLE);                                      //使能UART
}

/************************************************
函数名称 ： NVIDIA_SendByte
功    能 ： 调试串口发送一个字节
参    数 ： Data --- 数据
返 回 值 ： 无
作    者 ： FelixWu
*************************************************/
void NVIDIA_SendByte(uint8_t Data)
{
  /* 等待发送为空 */
  while(RESET == USART_GetFlagStatus(NVIDIA_COM, USART_FLAG_TXE));
  USART_SendData(NVIDIA_COM, Data);
}

/************************************************
函数名称 ： NVIDIA_SendNByte
功    能 ： 调试串口发送N个字节
参    数 ： pData ---- 数据
            Length --- 长度
返 回 值 ： 无
作    者 ： FelixWu
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
函数名称 ： Nvidiacom_Driver_Init
功    能 ： Nvidiacom驱动初始化
参    数 ： 无
返 回 值 ： 无
作    者 ： FelixWu
*************************************************/
void Nvidiacom_Driver_Init(void)
{
	
	UART_Nvidiacom_Configuration();
}




/**** Copyright (C)2019 FelixWu. All Rights Reserved **** END OF FILE ****/
