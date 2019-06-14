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
#include "nvidiacom_drv.h"
#include "global_var.h"
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
函数名称 ： DEBUG_COM_IRQHandler
功    能 ： USARTx中断(调试)
参    数 ： 无
返 回 值 ： 无
作    者 ： FelixWu
*************************************************/
void DEBUG_COM_IRQHandler(void)
{
    static uint8_t Data;

    if(USART_GetITStatus(DEBUG_COM, USART_IT_RXNE) != RESET)
    {
        Data = USART_ReceiveData(DEBUG_COM);

//  CLI_RcvDateFromISR(Data);
        USART_SendData(DEBUG_COM, Data);             //暂未使用接收
    }
}

/************************************************
函数名称 ： NVIDIA_COM_IRQHandler
功    能 ： USARTx中断(通讯)
参    数 ： 无
返 回 值 ： 无
作    者 ： FelixWu
*************************************************/
void NVIDIA_COM_IRQHandler(void)
{
//	u8 Res;
    BaseType_t xHigherPriorityTaskWoken = pdTRUE;


    if(USART_GetITStatus(NVIDIA_COM, USART_IT_RXNE) != RESET)
    {
        /* START --- 添加在这里的内容，是为了保证清除了标志 */
        USART_ClearITPendingBit(NVIDIA_COM, USART_IT_RXNE);
        /* END ---- 添加在这里的内容，是为了保证清除了标志 */

        NVIDIA_COM_RX_BUF[NVIDIA_COM_RX_STA++] = USART_ReceiveData(NVIDIA_COM);
    }
    else if(USART_GetITStatus(NVIDIA_COM, USART_IT_IDLE) != RESET)	// 如果接收到完整的一帧数据
    {
        USART_ReceiveData(NVIDIA_COM);
        NVIDIA_COM_RX_STA=0;
        USART_ClearITPendingBit(NVIDIA_COM,USART_IT_IDLE);

        /* Notify battery更新task */
        uint8_t command_code = NVIDIA_COM_RX_BUF[2];
        for(int i = 0 ; i < NVIDIA_COM_REC_LEN; i ++)
            NVIDIA_COM_RX_BUF_BACKUP[i] = NVIDIA_COM_RX_BUF[i];
        switch(command_code)// 根据串口收到的不同的指令代码，进行不同的操作。
        {
        case 0x00:
//            if(CANOpen_App_Task_Handler!=NULL) {
//                xTaskNotifyFromISR(CANOpen_App_Task_Handler, 0, (eNotifyAction) eSetValueWithOverwrite,&xHigherPriorityTaskWoken);//发送任务通知
//                portYIELD_FROM_ISR(xHigherPriorityTaskWoken);//如果需要的话进行一次任务切换
//            }
            break;
        case 0x01:
            /* 接收速度指令，解析，并发送《速度控制》任务通知 */
//				printf("0x01\r\n");
//								printf("count = %d\r\n", count++);
//            if(CANOpen_App_Task_Handler!=NULL) {
//                xTaskNotifyFromISR(CANOpen_App_Task_Handler, 1, (eNotifyAction) eSetValueWithOverwrite,&xHigherPriorityTaskWoken);//发送任务通知
//                /* 接收到速度指令，发出通知后，立刻清除定时器，否则定时器会发送停止命令 */
//                xTimerResetFromISR(AutoReloadTimer_Handle, &xHigherPriorityTaskWoken);
//                portYIELD_FROM_ISR(xHigherPriorityTaskWoken);//如果需要的话进行一次任务切换
//            }
            break;
        case 0x02:
            /* 接收升降电机控制指令，解析，并发送《升降电机控制》任务通知 */
//				printf("0x02\r\n");
            switch(NVIDIA_COM_RX_BUF[3])
            {
            case 0x00:
                LIFTER_TARGET_STATUS = 0x00;
                break;

            case 0x10:
                LIFTER_TARGET_STATUS = 0x10;
                break;

            case 0x01:
                LIFTER_TARGET_STATUS = 0x01;
                break;

            case 0x11:
                LIFTER_TARGET_STATUS = 0x11;
                break;

            }
//					if(CANOpen_App_Task_Handler!=NULL){
//						xTaskNotifyFromISR(CANOpen_App_Task_Handler, 2, (eNotifyAction) eSetValueWithOverwrite,&xHigherPriorityTaskWoken);//发送任务通知
//						portYIELD_FROM_ISR(xHigherPriorityTaskWoken);//如果需要的话进行一次任务切换
//					}
            break;
        case 0x03:
//            if(CANOpen_App_Task_Handler!=NULL) {
//                xTaskNotifyFromISR(CANOpen_App_Task_Handler, 3, (eNotifyAction) eSetValueWithOverwrite,&xHigherPriorityTaskWoken);//发送任务通知
//                portYIELD_FROM_ISR(xHigherPriorityTaskWoken);//如果需要的话进行一次任务切换
//            }
            break;
        case 0x04:
            /* 接收驱动器出错清零指令，解析，并发送《驱动器复位》任务通知 */
//            if(CANOpen_App_Task_Handler!=NULL) {
//                xTaskNotifyFromISR(CANOpen_App_Task_Handler, 4, (eNotifyAction) eSetValueWithOverwrite,&xHigherPriorityTaskWoken);//发送任务通知
//                portYIELD_FROM_ISR(xHigherPriorityTaskWoken);//如果需要的话进行一次任务切换
//            }
            break;
        case 0x05:
            /* 接收上传AGV状态指令，解析，并发送《驱动器复位》任务通知 */
//					printf("nvidia com reveived 0x05\r\n");
//					if(StatusManager_App_Task_Handler!=NULL){
//						xTaskNotifyFromISR(StatusManager_App_Task_Handler, 1, (eNotifyAction) eSetValueWithOverwrite,&xHigherPriorityTaskWoken);//发送任务通知
//						portYIELD_FROM_ISR(xHigherPriorityTaskWoken);//如果需要的话进行一次任务切换
//					}
            break;

        default:
            break;
        }

//		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);//如果需要的话进行一次任务切换

    }

    /* START --- 添加在这里的内容，是为了保证清除了标志 */
    //发的地方清标志
    if(USART_GetFlagStatus(NVIDIA_COM,USART_FLAG_ORE) == SET)
    {
        USART_ClearFlag(NVIDIA_COM,USART_FLAG_ORE);
        USART_ReceiveData(NVIDIA_COM);
    }
    /* END ---- 添加在这里的内容，是为了保证清除了标志 */
}




/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
