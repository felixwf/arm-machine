/**
  ******************************************************************************
  * @�ļ���     �� bsp_timer.c
  * @����       �� Felix Wu
  * @�汾       �� V1.0.0
  * @����       �� 2018��11��14��
  * @ժҪ       �� TIM�ײ�Դ�ļ�
  ******************************************************************************/
/*----------------------------------------------------------------------------
  ������־:
  2018-11-14 V1.0.0:��ʼ�汾
  ----------------------------------------------------------------------------*/
/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "bsp_timer.h"


//FreeRTOSʱ��ͳ�����õĽ��ļ�����
volatile unsigned long long FreeRTOSRunTimeTicks;


/****************************************** CANOpen��ʱ ******************************************/
/************************************************
�������� �� CANOpen_TIM_Configuration
��    �� �� CANOpen��ʱ����
��    �� �� ��
�� �� ֵ �� ��
��    �� �� Felix Wu
*************************************************/
void CANOpen_TIM_Configuration(void)
{
  NVIC_InitTypeDef        NVIC_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

  /* ʱ������ */
  RCC_APB1PeriphClockCmd(CANOPEN_TIM_CLK, ENABLE);

  /* NVIC���� */
  NVIC_InitStructure.NVIC_IRQChannel = CANOPEN_TIM_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = CANOPEN_TIM_Priority;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* ʱ������ */
  TIM_TimeBaseStructure.TIM_Prescaler = CANOPEN_TIM_PRESCALER_VALUE; //Ԥ��Ƶֵ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;        //���ϼ���ģʽ
  TIM_TimeBaseStructure.TIM_Period = CANOPEN_TIM_PERIOD;             //������ֵ(����)
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;            //ʱ�ӷ�Ƶ����
  TIM_TimeBaseInit(CANOPEN_TIMx, &TIM_TimeBaseStructure);

  /* ʹ���ж� */
  TIM_ClearFlag(CANOPEN_TIMx, TIM_IT_Update);                        //�����־
  TIM_ITConfig(CANOPEN_TIMx, TIM_IT_Update, ENABLE);                 //ʹ�� TIMx �����ж�

  /* ��ʼ�� */
  TIM_SetCounter(CANOPEN_TIMx, 0);
  TIM_Cmd(CANOPEN_TIMx, ENABLE);
}

/************************************************
�������� �� TIM_Initializes
��    �� �� TIM��ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� Felix Wu
*************************************************/
void TIM_Initializes(void)
{
  CANOpen_TIM_Configuration();
}

//��ʼ��TIM3ʹ��ΪFreeRTOS��ʱ��ͳ���ṩʱ��
void ConfigureTimeForRunTimeStats(void)
{
	//��ʱ��3��ʼ������ʱ��ʱ��Ϊ72M����Ƶϵ��Ϊ72-1�����Զ�ʱ��3��Ƶ��
	//Ϊ72M/72=1M���Զ���װ��Ϊ50-1����ô��ʱ�����ھ���50us
	FreeRTOSRunTimeTicks=0;
	TIM3_Int_Init(50-1,72-1);	//��ʼ��TIM3
}

//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�4��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���

	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx					 
}

//��ʱ��3�жϷ�����
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //����ж�
	{
		FreeRTOSRunTimeTicks++;
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //����жϱ�־λ
}

/**** Copyright (C)2018 Felix Wu. All Rights Reserved **** END OF FILE ****/
