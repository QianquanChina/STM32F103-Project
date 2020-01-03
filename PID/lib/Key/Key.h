#ifndef __KEY_H__
#define __KEY_H__
#include "Rcc.h"

void Key_Init(void);
void Key_Scans(uint16_t GPIO_Pin);

uint8_t key_meun;
uint8_t exit_flag;
struct Key_Pid key;

struct Key_Pid 
{
    float      Kp;
    float      Ti;
    float      Td;
    float      T ;
    float      Set_Point;
    uint8_t select_flag;
    uint8_t Buff_SetPoint[128];
    uint8_t Buff_T[128];
    uint8_t Buff_Kp[128];
    uint8_t Buff_Ti[128];
    uint8_t Buff_Td[128];
};
struct Key_Tim Timer;

struct Key_Tim
{
    uint8_t Keyt_Flag;
};


#define KEY_GPIO                       GPIOA
#define KEY_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOA_CLK_ENABLE();

#define Key_Add       GPIO_PIN_3
#define Key_Down      GPIO_PIN_4
#define Key_Cancle    GPIO_PIN_5 
#define Key_Enter     GPIO_PIN_6 
#define Key_Sele      GPIO_PIN_7

#define KEY_ADD       HAL_GPIO_ReadPin(KEY_GPIO, Key_Add)
#define KEY_DOWN      HAL_GPIO_ReadPin(KEY_GPIO, Key_Down)
#define KEY_CACNCLE   HAL_GPIO_ReadPin(KEY_GPIO, Key_Cancle)
#define KEY_ENTER     HAL_GPIO_ReadPin(KEY_GPIO, Key_Enter)
#define KEY_SELE      HAL_GPIO_ReadPin(KEY_GPIO, Key_Sele)
#define KEY_ON        0
#define KEY_OFF       1



#endif