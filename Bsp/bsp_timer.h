/**
  ******************************************************************************
  * @�ļ���     �� bsp_timer.h
  * @����       �� Felix Wu
  * @�汾       �� V1.0.0
  * @����       �� 2018��11��14��
  * @ժҪ       �� TIM�ײ�ͷ�ļ�
  ******************************************************************************/

/* �����ֹ�ݹ���� ----------------------------------------------------------*/
#ifndef _BSP_TIMER_H
#define _BSP_TIMER_H


/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "stm32f10x.h"


/* �궨�� --------------------------------------------------------------------*/
/* CANOpen��ʱ */
#define CANOPEN_TIMx              TIM2
#define CANOPEN_TIM_CLK           RCC_APB1Periph_TIM2
#define CANOPEN_TIM_IRQn          TIM2_IRQn
#define CANOPEN_TIM_Priority      12
#define CANOPEN_TIM_IRQ_Handler   TIM2_IRQHandler

#define CANOPEN_TIM_COUNTER_CLOCK           1000000         //����ʱ��(1000K��/��)
                                                           //Ԥ��Ƶֵ
#define CANOPEN_TIM_PRESCALER_VALUE         (SystemCoreClock/CANOPEN_TIM_COUNTER_CLOCK - 1)
#define CANOPEN_TIM_PERIOD                  65535          //��ʱ����
//#define CANOPEN_TIM_PERIOD                  6554          //��ʱ����

void TIM3_Int_Init(u16 arr,u16 psc);

extern volatile unsigned long long FreeRTOSRunTimeTicks;
void ConfigureTimeForRunTimeStats(void);

/* �������� ------------------------------------------------------------------*/
void TIM_Initializes(void);


#endif /* _BSP_TIMER_H */

/**** Copyright (C)2018 Felix Wu. All Rights Reserved **** END OF FILE ****/
