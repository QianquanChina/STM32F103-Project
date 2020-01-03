#ifndef __PWM_H__
#define __PWM_H__
#include "Rcc.h"
TIM_HandleTypeDef htim4;
void Pwm_Init(void);
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* htim_pwm);
void HAL_TIM_MspPostInit(TIM_HandleTypeDef* htim);
void Pwm_Gpio_Init(void);

#endif