/**
  ******************************************************************************
  * @文件名     ： nvidia_drv.h
  * @作者       ： FelixWu
  * @版本       ： V1.0.0
  * @日期       ： 2019年03月01日
  * @摘要       ： CANOpen驱动头文件
  ******************************************************************************/

/* 定义防止递归包含 ----------------------------------------------------------*/
#ifndef _NVIDIACOM_DRV_H
#define _NVIDIACOM_DRV_H

/* 包含的头文件 --------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "bsp_usart.h"
#include "global_var.h"


/* 静态变量 ------------------------------------------------------------------*/
static xQueueHandle xNVIDIARcvQueue = NULL;        //UART接收队列

/* 宏定义 --------------------------------------------------------------------*/
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
#define NVIDIA_COM_Priority        7                       //优先级
#define NVIDIA_COM_BaudRate        115200                   //波特率
#define NVIDIA_COM_IRQHandler      USART3_IRQHandler        //中断函数接口(见stm32f10x_it.c)

	  	
#define NVIDIA_COM_RX_QUEUE_LEN           10                       //Nvidia_com接收队列长度(队列的数量)(发送)
#define NVIDIA_COM_RX_QUEUE_SIZE          19                       //Nvidia_com接收队列大小(一个队列长度) - sizeof(CanTxMsg)


/* 函数申明 ------------------------------------------------------------------*/
void Nvidiacom_Driver_Init(void);
void NVIDIA_SendNByte(uint8_t *pData, uint16_t Length);
void NVIDIA_SendByte(uint8_t Data);

#endif /* _NVIDIACOM_DRV_H */

/**** Copyright (C)2019 FelixWu. All Rights Reserved **** END OF FILE ****/
