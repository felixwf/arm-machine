#ifndef __STATE_MACHINE_APP_H
#define __STATE_MACHINE_APP_H


typedef struct
{
    uint32_t status1;
    uint32_t status2;
    uint32_t status3;
} StatusManager_TypeDef;

extern StatusManager_TypeDef StatusManager;


#define State0         ((uint32_t)0x00000000)
#define State1         ((uint32_t)0x00000001)
#define State2         ((uint32_t)0x00000002)
#define State3         ((uint32_t)0x00000003)
extern uint32_t g_stauts;



#endif


