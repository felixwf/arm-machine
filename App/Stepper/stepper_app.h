#ifndef __STEPPER_APP_H
#define __STEPPER_APP_H
#include "stepper_drv.h"
#include "modbus_rtu.h"


void Stepper_App_Init(void);
void msg_init(ArmMachine_TypeDef *ArmMachineMsg);

#endif

