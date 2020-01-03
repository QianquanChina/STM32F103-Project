#ifndef __PID_H__
#define __PID_H__
#include "Rcc.h"
void Pid_Cacl(void);
void Pid_Display(void);

void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle);
void Tim2Pwm_Init(void);

struct Pid_Value  pid;

struct Pid_Value
{
    float       Set_Point;  //设定目标
    float       Now_Point;  //当前数值
    float       Sum_Error;  //错误累加
    float       Now_Error;  //本次偏差
    float       Pre_Error;  //上次偏差
    float       Kp;         //比例常数
    float       Ti;         //积分常数
    float       Td;         //微分常数
    float       Pout;
    float       Iout;
    float       Dout;
    float       Out;
    float       Out0;
    
    uint8_t     Pid_Start;
    float       T;          //PID计算周期
    uint16_t    Pwm_Cycle;  //Pwm的周期
    uint8_t     Meun_Flag;
       
};

#endif