/**
  ******************************************************************************
  * @文件名     ： global_bar.h
  * @作者       ： FelixWu
  * @版本       ： V1.0.0
  * @日期       ： 2019年03月01日
  * @摘要       ： 全局变量定义
  ******************************************************************************/

#ifndef _GLOBAL_VAR_H
#define _GLOBAL_VAR_H

#include "FreeRTOS.h"
/*
 * ########################################
 * ########################################
 * ########################################
 * ########################################
 * ########################################
*/


/** 定义AGV的型号 **/
//#define AGV_VERSION_1 1
#define AGV_VERSION_2 1

/* unit convert: m/s(agv) --> rpm(motor) */
#ifdef AGV_VERSION_2
#define MPS2RPM 2981.24381206
#endif

#ifdef AGV_VERSION_1
#define MPS2RPM 3162.018737
#endif


/*
 * ########################################
 * ########################################
 * ########################################
 * ########################################
 * ########################################
*/


/* Battery status */
extern uint8_t SOC_battery;
extern uint8_t sysCurt_battery_H;
extern uint8_t sysCurt_battery_L;
extern uint8_t sysCurt_battery;
extern uint8_t sysVol_battery_H;
extern uint8_t sysVol_battery_L;
extern uint8_t sysVol_battery;
extern uint8_t alarmBits_battery;


/*
 * ########################################
 * ########################################
 * ########################################
 * ########################################
 * ########################################
*/


/* Battery serial msg */
#define BATTERY_COM_RX_LEN 255
extern u8 BATTERY_COM_RX_BUF[BATTERY_COM_RX_LEN];
extern u16 BATTERY_COM_RX_CNT;
extern uint16_t BATTERY_COM_RX_STA;       //接收状态标记


/*
 * ########################################
 * ########################################
 * ########################################
 * ########################################
 * ########################################
*/


/* Lifter status */
extern uint8_t LIFTER_TARGET_STATUS;
extern uint8_t LIFTER_CURRENT_STATUS;
extern uint8_t IS_LIFTER_RUNNING_DOWN;
extern uint8_t IS_LIFTER_RUNNING_UP;


/*
 * ########################################
 * ########################################
 * ########################################
 * ########################################
 * ########################################
*/


/*
 * AGV 状态定义
 * agv status
 * red button pressed --> emergency_mode --> 0xF0
 * green button pressed --> normal_mode --> 0x0F
 */
extern uint8_t AGV_STATUS;
#define AGV_STATUS_NORMAL 0x0F
#define AGV_STATUS_EMERGENCY 0xF0

extern uint8_t RED_BUTTON_TRIGGER;
extern uint8_t GREEN_BUTTON_TRIGGER;
extern uint8_t EMERGENCY_BUTTON_TRIGGER;

/*
 * ########################################
 * ########################################
 * ########################################
 * ########################################
 * ########################################
*/


/* Nvidia status */
#define NVIDIA_TIMEOUT_TRUE 1
#define NVIDIA_TIMEOUT_FALSE 0
extern uint8_t IS_NVIDIA_TIMEOUT;


/*
 * ########################################
 * ########################################
 * ########################################
 * ########################################
 * ########################################
*/


/* Nvidia serial msg */
/** 从英伟达板发送的数据，作为全局变量存储 **/
#define NVIDIA_COM_REC_LEN  			200  		//定义最大接收字节数 200
extern u8  NVIDIA_COM_RX_BUF[NVIDIA_COM_REC_LEN]; 	//接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
extern u16 NVIDIA_COM_RX_STA;       				//接收状态标记
extern u8  NVIDIA_COM_RX_BUF_BACKUP[NVIDIA_COM_REC_LEN]; 	//接收缓冲,最大USART_REC_LEN个字节.末字节为换行符


/*
 * ########################################
 * ########################################
 * ########################################
 * ########################################
 * ########################################
*/


/* AGV Servo */
extern uint32_t wheel_servo_node_id[4];
extern uint8_t wheel_servo_total_numbers;
//extern int32_t wheel_encoder_fl, wheel_encoder_fr, wheel_encoder_bl, wheel_encoder_br;
//extern int16_t servo_status_code_fl, servo_status_code_fr, servo_status_code_bl, servo_status_code_br;
typedef struct motor_encoder
{
    int32_t fl, fr, bl, br;
} motor_encoder_type;

extern motor_encoder_type motor_encoder;

typedef struct servo_status
{
    int16_t fl, fr, bl, br;
} servo_status_type;

extern servo_status_type servo_status_code;

/*
 * ########################################
 * ########################################
 * ########################################
 * ########################################
 * ########################################
*/


/*
 * 安全时间差 定义
 * If the time gap between the commands send from nvidia is larger than 200ms,
 * the ARM board will send the stopping command to stop the wheel motor.
 */
#define SAFETY_TIME_GAP_BETWEEN_CMDS 100 			// ms
#define NVIDIA_TIMEOUT_DECELERATION 1.0				// 1m/s^2
#define NVIDIA_TIMEOUT_AGV_MAX_RUNNING_TIME 1.0		// 2s

/*
 * ########################################
 * ########################################
 * ########################################
 * ########################################
 * ########################################
*/


/** ARM板发送给伺服电机前，转换数据单位的系数 **/
#define driver_conversion 2730


/*
 * ########################################
 * ########################################
 * ########################################
 * ########################################
 * ########################################
*/







#endif

