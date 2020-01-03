#ifndef __USART_H__
#define __USART_H__
#include "Rcc.h"

UART_HandleTypeDef UART_Initure;
UART_HandleTypeDef UART_TwoIniture;

uint8_t rxbuff_one[9];
uint8_t rxbuff_two[9];

void Usart1_Config(void);
void Usart2_Config(void);
void NVIC_Init(void);
#endif