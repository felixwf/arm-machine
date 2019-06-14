/**
  ******************************************************************************
  * @文件名     ： button_app.c
  * @作者       ： FelixWu
  * @版本       ： V1.0.0
  * @日期       ： 2019年03月07日
  * @摘要       ： button_app
  ******************************************************************************/
/*----------------------------------------------------------------------------
  更新日志:
  2019-03-01 V1.0.0:初始版本
  ----------------------------------------------------------------------------*/
#include "global_var.h"



/* Battery status */
uint8_t SOC_battery = 20;

uint8_t sysCurt_battery = 0;
uint8_t sysCurt_battery_H = 0;
uint8_t sysCurt_battery_L = 0;

uint8_t sysVol_battery = 0;
uint8_t sysVol_battery_H = 0;
uint8_t sysVol_battery_L = 0;

uint8_t alarmBits_battery = 0;


/*
 * ########################################
 * ########################################
 * ########################################
 * ########################################
 * ########################################
*/


/* Battery serial msg */
u8 BATTERY_COM_RX_BUF[BATTERY_COM_RX_LEN];
u16 BATTERY_COM_RX_CNT = 0;
uint16_t BATTERY_COM_RX_STA=0;       //接收状态标记


/*
 * ########################################
 * ########################################
 * ########################################
 * ########################################
 * ########################################
*/


/* Lifter status */
uint8_t LIFTER_TARGET_STATUS = 0x22;
uint8_t LIFTER_CURRENT_STATUS = 0x00;
uint8_t IS_LIFTER_RUNNING_DOWN = 0;
uint8_t IS_LIFTER_RUNNING_UP = 0;


/*
 * ########################################
 * ########################################
 * ########################################
 * ########################################
 * ########################################
*/


/* AGV status */
/* example:
 * red button pressed --> emergency_mode --> 0xF0
 * green button pressed --> normal_mode --> 0x0F
 */
uint8_t AGV_STATUS = AGV_STATUS_NORMAL;

uint8_t RED_BUTTON_TRIGGER = 0x00;
uint8_t GREEN_BUTTON_TRIGGER = 0x00;
uint8_t EMERGENCY_BUTTON_TRIGGER = 0x00;

/*
 * ########################################
 * ########################################
 * ########################################
 * ########################################
 * ########################################
*/


/* AGV Servo */
#ifdef AGV_VERSION_1
uint32_t wheel_servo_node_id[4] = {0x01, 0x02, 0x03, 0x05};
#endif

#ifdef AGV_VERSION_2
uint32_t wheel_servo_node_id[4] = {0x01, 0x02, 0x03, 0x04};
#endif

uint8_t wheel_servo_total_numbers = sizeof(wheel_servo_node_id)/sizeof(wheel_servo_node_id[0]);
//int32_t wheel_encoder_fl, wheel_encoder_fr, wheel_encoder_bl, wheel_encoder_br;
//int16_t servo_status_code_fl, servo_status_code_fr, servo_status_code_bl, servo_status_code_br;
motor_encoder_type motor_encoder;
servo_status_type servo_status_code;
/*
 * ########################################
 * ########################################
 * ########################################
 * ########################################
 * ########################################
*/


/* Nvidia status */
/* msg from Nvidia is delayed or not
 * value should be : 'NVIDIA_TIMEOUT_TRUE' or 'NVIDIA_TIMEOUT_FALSE'
 */
uint8_t IS_NVIDIA_TIMEOUT = NVIDIA_TIMEOUT_FALSE;


/*
 * ########################################
 * ########################################
 * ########################################
 * ########################################
 * ########################################
*/


/* Nvidia serial msg */
uint8_t  NVIDIA_COM_RX_BUF[NVIDIA_COM_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
uint16_t NVIDIA_COM_RX_STA=0;       			//接收状态标记
uint8_t  NVIDIA_COM_RX_BUF_BACKUP[NVIDIA_COM_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符


/**** Copyright (C)2019 FelixWu. All Rights Reserved **** END OF FILE ****/
