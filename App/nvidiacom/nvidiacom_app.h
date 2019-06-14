/**
  ******************************************************************************
  * @�ļ���     �� nvidia_drv.h
  * @����       �� FelixWu
  * @�汾       �� V1.0.0
  * @����       �� 2019��03��01��
  * @ժҪ       �� Nvidia com with armӦ�ó���ͷ�ļ�
  ******************************************************************************/

/* �����ֹ�ݹ���� ----------------------------------------------------------*/
#ifndef _NVIDIACOM_APP_H
#define _NVIDIACOM_APP_H

/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "bsp_usart.h"


/* �궨�� --------------------------------------------------------------------*/
#define NVIDIACOM_STACK_SIZE        128                      //CANOPEN�����ջ��С
#define NVIDIACOM_TASK_PRIORITY     3                        //CANOPEN�������ȼ�




/* �������� ------------------------------------------------------------------*/
void Nvidiacom_App_Init(void);



#endif /* _NVIDIACOM_APP_H */

/**** Copyright (C)2019 FelixWu. All Rights Reserved **** END OF FILE ****/
