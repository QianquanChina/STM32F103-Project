#include "Pwm.h"

/********************************************************
* 功    能:PWM初始化                                  
* 参    数:无                                            
* 返    值:无
* 说    明:无
*********************************************************/
TIM_HandleTypeDef htim4;
void Pwm_Init(void)
{
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};

    htim4.Instance = TIM4;
    htim4.Init.Prescaler = 7200-1; //7200-1;
    htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim4.Init.Period = 2000-1; //2000-1;
    htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
    {
        Error_Handler("HAL_TIM_PWM_Init");
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
    {
        Error_Handler("HAL_TIMEx_MasterConfigSynchronization");
    }
    /*
    TIM_OCMODE_PWM1模式 
    在向上计数时，一旦TIMx_CNT<TIMx_CCRx时通道x为有效电平，否则为
    无效电平；在向下计数时，一旦TIMx_CNT>TIMx_CCRx时通道1为无效电
    平(OC1REF=0)，否则为有效电平(OC1REF=1)。
    TIM_OCMODE_PWM2模式 

    PWM模式2－ 在向上计数时，一旦TIMx_CNT<TIMx_CCRx时通道1为无效电
    平，否则为有效电平；在向下计数时，一旦TIMx_CNT>TIMx_CCRx时通道x
    为有效电平，否则为无效电平。   
    */
    sConfigOC.OCMode = TIM_OCMODE_PWM1;

    /*
    Pulse为比较设定值
    */
    sConfigOC.Pulse = 1000;
    /*
    设置有效电平，此时高电平是有效电平。
    */
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
    {
        Error_Handler("HAL_TIM_PWM_ConfigChannel");
    }
    sConfigOC.Pulse = 400;
    if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
    {
        Error_Handler("HAL_TIM_PWM_ConfigChannel");
    }
    sConfigOC.Pulse = 300;
    if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
    {
        Error_Handler("HAL_TIM_PWM_ConfigChannel");
    }
    sConfigOC.Pulse = 200;
    if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
    {
        Error_Handler("HAL_TIM_PWM_ConfigChannel");
    }
    HAL_TIM_MspPostInit(&htim4);
}
/********************************************************
* 功    能:PWM初始化回调函数                                  
* 参    数:TIM_HandleTypeDef类型的参数                                  
* 返    值:无
* 说    明:无
*********************************************************/
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* htim_pwm)
{
    if(htim_pwm->Instance==TIM4)
    {
        __HAL_RCC_TIM4_CLK_ENABLE();
    }

}

void HAL_TIM_MspPostInit(TIM_HandleTypeDef* htim)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(htim->Instance==TIM4)
    {
    
        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**TIM4 GPIO Configuration    
        PB6     ------> TIM4_CH1
        PB7     ------> TIM4_CH2
        PB8     ------> TIM4_CH3
        PB9     ------> TIM4_CH4 
        */
        GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
        
        /*
        复用推挽功能输出
        */
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    }

}
/********************************************************
* 功    能:PWM的GPIO初始化                                  
* 参    数:无                                            
* 返    值:无
* 说    明:无
*********************************************************/
void Pwm_Gpio_Init(void)
{
    __HAL_RCC_GPIOB_CLK_ENABLE();
}