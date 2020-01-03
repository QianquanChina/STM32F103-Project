#ifndef __TIM2_H__
#define __TIM2_H__
#include "Rcc.h"

void Tim2_Init(void);
void Tim2_Nvic(void);


struct Flag_Time flag_time ;
struct Flag_Time 
{
    uint16_t Pid_Flag;
    uint16_t Key_Flag;
    uint8_t  San_Flag;
    uint8_t  KeyT_Flag;
};


#endif