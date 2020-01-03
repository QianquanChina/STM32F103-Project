#include "Usart.h"

UART_HandleTypeDef UART_Initure;
UART_HandleTypeDef UART_TwoIniture;
/********************************************************
* 功    能:串口一的Print重定向                                   
* 参    数:无                                            
* 返    值:无
* 说    明:无
*********************************************************/
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif 
PUTCHAR_PROTOTYPE
{
    HAL_UART_Transmit(&UART_Initure    , (uint8_t *)&ch, 1, 0xFFFF);
    return ch;
}
int _write(int32_t file, uint8_t *ptr, int32_t len)
{
    int DataIdx;	
    for (DataIdx = 0; DataIdx < len; DataIdx++)	
    {			
        __io_putchar(*ptr++);    
    }	
    return len;	
}
/********************************************************
* 功    能:串口一初始化                                  
* 参    数:无                                            
* 返    值:无
* 说    明:无
*********************************************************/
void Usart1_Config(void)
{
    
    UART_Initure.Instance        = USART1;  
    UART_Initure.Init.BaudRate   = 9600;  
    UART_Initure.Init.WordLength = UART_WORDLENGTH_8B;  
    UART_Initure.Init.StopBits   = UART_STOPBITS_1;  
    UART_Initure.Init.Parity     = UART_PARITY_NONE;  
    UART_Initure.Init.HwFlowCtl  = UART_HWCONTROL_NONE;  
    UART_Initure.Init.Mode       = UART_MODE_TX_RX;
    UART_Initure.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&UART_Initure) != HAL_OK)
    {
        Error_Handler("HAL_UART_Init");
    }
    Delay_Ms(1);
}
/********************************************************
* 功    能:串口二初始化                                  
* 参    数:无                                            
* 返    值:无
* 说    明:无
*********************************************************/
void Usart2_Config(void)
{
    UART_TwoIniture.Instance        = USART2;  
    UART_TwoIniture.Init.BaudRate   = 9600;  
    UART_TwoIniture.Init.WordLength = UART_WORDLENGTH_8B;  
    UART_TwoIniture.Init.StopBits   = UART_STOPBITS_1;  
    UART_TwoIniture.Init.Parity     = UART_PARITY_NONE;  
    UART_TwoIniture.Init.HwFlowCtl  = UART_HWCONTROL_NONE;  
    UART_TwoIniture.Init.Mode       = UART_MODE_TX_RX;
    UART_TwoIniture.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&UART_TwoIniture) != HAL_OK)
    {
        Error_Handler("UART_TwoIniture");
    }
    Delay_Ms(1);
}
/********************************************************
* 功    能:串口初始化回调设置函数                                  
* 参    数:无                                            
* 返    值:无
* 说    明:无
*********************************************************/
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(huart->Instance==USART1)
    {

        __HAL_RCC_USART1_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**USART1 GPIO Configuration    
        PA9     ------> USART1_TX
        PA10     ------> USART1_RX 
        */
        GPIO_InitStruct.Pin   = GPIO_PIN_9;
        GPIO_InitStruct.Mode  = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_10;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }else 
    if(huart->Instance==USART2)
    {
        __HAL_RCC_USART2_CLK_ENABLE();
    
        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**USART2 GPIO Configuration    
        PA2     ------> USART2_TX
        PA3     ------> USART2_RX 
        */
        GPIO_InitStruct.Pin = GPIO_PIN_2;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_3;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }

}
/********************************************************
* 功    能:串口中断优先级和中断使能                                  
* 参    数:无                                            
* 返    值:无
* 说    明:无
*********************************************************/
void NVIC_Init(void)
{
    /* USART1_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
    /* USART2_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);

}
/********************************************************
* 功    能:串口一中断函数                                  
* 参    数:无                                            
* 返    值:无
* 说    明:无
*********************************************************/
void USART1_IRQHandler(void)
{
    HAL_UART_IRQHandler(&UART_Initure);
}
/********************************************************
* 功    能:串口二中断函数                                   
* 参    数:无                                            
* 返    值:无
* 说    明:无
*********************************************************/
void USART2_IRQHandler(void)
{
    HAL_UART_IRQHandler(&UART_TwoIniture);
}
/********************************************************
* 功    能:串口回调函数                                   
* 参    数:无                                            
* 返    值:无
* 说    明:无
*********************************************************/
uint8_t rxbuff_one[9];
uint8_t rxbuff_two[9];
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart == &UART_Initure)
    {
        HAL_UART_Transmit(&UART_Initure,   rxbuff_one, 1, 0xFF);
	    HAL_UART_Receive_IT(&UART_Initure, rxbuff_one, 1);
    }else
    if(huart == &UART_TwoIniture)
    {
        HAL_UART_Transmit(&UART_TwoIniture,   rxbuff_two, 1, 0xFF);
	    HAL_UART_Receive_IT(&UART_TwoIniture, rxbuff_two, 1);        
    }
    
}