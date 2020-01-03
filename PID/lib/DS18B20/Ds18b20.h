#ifndef __DS18B20_H
#define	__DS18B20_H
#include "Rcc.h"
uint8_t ucDs18b20Id [ 8 ];
/************************** DS18B20 连接引脚定义********************************/
#define      DS18B20_DQ_SCK_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define      DS18B20_DQ_GPIO_CLK                       RCC_APB2Periph_GPIOE

#define      DS18B20_DQ_GPIO_PORT                      GPIOB
#define      DS18B20_DQ_GPIO_PIN                       GPIO_PIN_0


/************************** DS18B20 函数宏定义********************************/
#define      DS18B20_DQ_0	                            HAL_GPIO_WritePin( DS18B20_DQ_GPIO_PORT ,DS18B20_DQ_GPIO_PIN, GPIO_PIN_RESET)
#define      DS18B20_DQ_1	                            HAL_GPIO_WritePin(DS18B20_DQ_GPIO_PORT,DS18B20_DQ_GPIO_PIN, GPIO_PIN_SET)
#define      DS18B20_DQ_IN()	                        HAL_GPIO_ReadPin( DS18B20_DQ_GPIO_PORT, DS18B20_DQ_GPIO_PIN ) 
/************************** DS18B20 函数声明 ********************************/
uint8_t                  DS18B20_Init                      ( void );
void                     DS18B20_ReadId                    ( uint8_t * ds18b20_id );
float                    DS18B20_GetTemp_SkipRom           ( void );
float                    DS18B20_GetTemp_MatchRom          ( uint8_t * ds18b20_id );

#endif /* __DS18B20_H */






