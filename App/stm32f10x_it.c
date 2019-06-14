/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "bsp_can.h"
#include "bsp_usart.h"
#include "bsp_timer.h"
#include "pccom_drv.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t count = 0;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
//void SVC_Handler(void)
//{
//}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
//void PendSV_Handler(void)
//{
//}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
//void SysTick_Handler(void)
//{
//}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/************************************************
�������� �� DEBUG_COM_IRQHandler
��    �� �� USARTx�ж�(����)
��    �� �� ��
�� �� ֵ �� ��
��    �� �� FelixWu
*************************************************/
void DEBUG_COM_IRQHandler(void)
{
    static uint8_t Data;

    if(USART_GetITStatus(DEBUG_COM, USART_IT_RXNE) != RESET)
    {
        Data = USART_ReceiveData(DEBUG_COM);

//  CLI_RcvDateFromISR(Data);
        USART_SendData(DEBUG_COM, Data);             //��δʹ�ý���
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
//	u8 Res;
//    BaseType_t xHigherPriorityTaskWoken = pdTRUE;


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

		printf("pccom received");
        /* Notify battery����task */
        uint8_t command_code = PC_COM_RX_BUF[2];
        for(int i = 0 ; i < PC_COM_REC_LEN; i ++)
            PC_COM_RX_BUF_BACKUP[i] = PC_COM_RX_BUF[i];
        switch(command_code)// ���ݴ����յ��Ĳ�ͬ��ָ����룬���в�ͬ�Ĳ�����
        {
        case 0x00:
//            if(CANOpen_App_Task_Handler!=NULL) {
//                xTaskNotifyFromISR(CANOpen_App_Task_Handler, 0, (eNotifyAction) eSetValueWithOverwrite,&xHigherPriorityTaskWoken);//��������֪ͨ
//                portYIELD_FROM_ISR(xHigherPriorityTaskWoken);//�����Ҫ�Ļ�����һ�������л�
//            }
            break;
        case 0x01:
            break;
        case 0x02:
            break;
        case 0x03:
            break;
        case 0x04:
            break;
        case 0x05:
            break;

        default:
            break;
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




/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
