#ifndef __RCC_H__
#define __RCC_H__
#include <stm32f1xx_hal.h>
void SystemClock_Config(void);
void Delay_Ms(uint32_t i);
void Delay_Us(uint32_t i);
void Error_Handler(const char *errorbuff);
void Num_Char(char *str, double number, uint8_t g, uint8_t l);
#endif