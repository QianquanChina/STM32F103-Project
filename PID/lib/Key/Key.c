#include "key.h"
#include "Tim2.h"
#include "Pid.h"
#include "GUI.h"
#include "string.h"
#include "TFT_demo.h"
#include "Lcd_Driver.h"

extern struct Meun meun;
extern struct Pid_Value  pid;
extern struct Flag_Time flag_time;
/********************************************************
* 功    能:按键扫描                                  
* 参    数:按键数值                                            
* 返    值:无
* 说    明:无
*********************************************************/
struct Key_Tim Timer = 
{
    .Keyt_Flag = 0,
};
struct Key_Pid key;
uint8_t key_meun = 2;
void Key_Scans(uint16_t GPIO_Pin)
{
    if( (GPIO_Pin == Key_Add) )
    {
        Delay_Ms(20);
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
        if( (GPIO_Pin == Key_Add) && (KEY_ADD == KEY_ON) )
        {
            /*一级菜单*/
            if( (meun.Frist_meun == 1) && (meun.Second_meun == 0) && (meun.Thired_meun == 0) )
            {
                Gui_DrawFont_GBK16(10, 85, WHITE, WHITE, (uint8_t *)("♂"));
                Gui_DrawFont_GBK16(10, 65, BLUE,  WHITE, (uint8_t *)("♂"));
                key_meun = 2;
            }
            /*二级菜单按钮*/
            if( (meun.Frist_meun == 0) && (meun.Second_meun == 1) && (meun.Thired_meun == 0) )
            {   
                DisplayButtonDown(84, 41, 120, 60);

            }
        }else 
        if( (GPIO_Pin == Key_Add) && (KEY_ADD == KEY_OFF) )
        {   
            /*二级菜单按钮*/
            if( (meun.Frist_meun == 0) && (meun.Second_meun == 1) && (meun.Thired_meun == 0) )
            {   
        
                DisplayButtonUp(84, 41, 120, 60);
                switch (key.select_flag)
                {
                case 1:
                    exit_flag = 0;
                    Timer.Keyt_Flag = 0;
                    flag_time.KeyT_Flag = 0;
                    key.T += 1;
                    memset(key.Buff_T, 0, sizeof(key.Buff_T));
                    Num_Char((char *)key.Buff_T, key.T, 4, 1);
                    Gui_DrawFont_GBK16(35, 25 , BLUE, GRAY0, (uint8_t *)key.Buff_T);
                    break;
                case 2:
                    if(Timer.Keyt_Flag == 1)
                    {
                        key.Set_Point += 10;
                        exit_flag = 0;
                        Timer.Keyt_Flag = 0;
                        flag_time.KeyT_Flag = 0;
                    }else
                    {
                        key.Set_Point += 0.1;
                        exit_flag = 0;
                        Timer.Keyt_Flag = 0;
                        flag_time.KeyT_Flag = 0;                        
                    }
                    memset(key.Buff_SetPoint, 0, sizeof(key.Buff_SetPoint));
                    Num_Char((char *)key.Buff_SetPoint, key.Set_Point, 4, 1);
                    Gui_DrawFont_GBK16(35, 45 , BLUE, GRAY0, (uint8_t *)key.Buff_SetPoint);
                    break;
                case 3:
                    if(Timer.Keyt_Flag == 1)
                    {
                        key.Kp += 10;
                        exit_flag = 0;
                        Timer.Keyt_Flag = 0;
                        flag_time.KeyT_Flag = 0;
                    }else
                    {
                        key.Kp += 0.1;
                        exit_flag = 0;
                        Timer.Keyt_Flag = 0;
                        flag_time.KeyT_Flag = 0;                        
                    }                
                    memset(key.Buff_Kp, 0, sizeof(key.Buff_Kp));
                    Num_Char((char *)key.Buff_Kp, key.Kp, 4, 1);
                    Gui_DrawFont_GBK16(35, 65 , BLUE, GRAY0, (uint8_t *)key.Buff_Kp);
                    break;
                case 4: 
                    if(Timer.Keyt_Flag == 1)
                    {
                        key.Ti += 5000;
                        exit_flag = 0;
                        Timer.Keyt_Flag = 0;
                        flag_time.KeyT_Flag = 0;
                    }else
                    {
                        key.Ti += 100;
                        exit_flag = 0;
                        Timer.Keyt_Flag = 0;
                        flag_time.KeyT_Flag = 0;                        
                    }                                  
                    memset(key.Buff_Ti, 0, sizeof(key.Buff_Ti));
                    Num_Char((char *)key.Buff_Ti, key.Ti, 7, 1);
                    Gui_DrawFont_GBK16(35, 85 , BLUE, GRAY0, (uint8_t *)key.Buff_Ti);                   
                    break;
                case 5:
                    if(Timer.Keyt_Flag == 1)
                    {
                        key.Td += 500;
                        exit_flag = 0;
                        Timer.Keyt_Flag = 0;
                        flag_time.KeyT_Flag = 0;
                    }else
                    {
                        key.Td += 100;
                        exit_flag = 0;
                        Timer.Keyt_Flag = 0;
                        flag_time.KeyT_Flag = 0;                        
                    }                   
                    memset(key.Buff_Td, 0, sizeof(key.Buff_Td));
                    Num_Char((char *)key.Buff_Td, key.Td, 4, 1);
                    Gui_DrawFont_GBK16(35, 105 , BLUE, GRAY0, (uint8_t *)key.Buff_Td);             
                    break; 

                default:
                    break;  
                }                
            } 
        }
    }else 
    if( (GPIO_Pin == Key_Down)  )
    {
        Delay_Ms(20);
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
        if( (GPIO_Pin == Key_Down) && (KEY_DOWN == KEY_ON) )
        {
            /*一级菜单*/
            if( (meun.Frist_meun == 1) && (meun.Second_meun == 0) && (meun.Thired_meun == 0) )
            {
                Gui_DrawFont_GBK16(10, 65, WHITE, WHITE, (uint8_t *)("♂"));
                Gui_DrawFont_GBK16(10, 85, BLUE,  WHITE, (uint8_t *)("♂"));
                key_meun = 3;
            }
            if( (meun.Frist_meun == 0) && (meun.Second_meun == 1) && (meun.Thired_meun == 0) )
            { 
                DisplayButtonDown(84, 61, 120, 80); 
            }
        }else 
        if( (GPIO_Pin == Key_Down) && (KEY_DOWN == KEY_OFF) )
        {
                        
            /*二级菜单按钮*/
            if( (meun.Frist_meun == 0) && (meun.Second_meun == 1) && (meun.Thired_meun == 0) )
            {            
                DisplayButtonUp(84, 61, 120, 80);
                switch (key.select_flag)
                {
                case 1:
                    key.T -= 1;

                    exit_flag = 0;
                    Timer.Keyt_Flag = 0;
                    flag_time.KeyT_Flag = 0;

                    if(key.T <= 0) 
                    {
                        key.T = 0;
                    }
                    memset(key.Buff_T, 0, sizeof(key.Buff_T));
                    Num_Char((char *)key.Buff_T, key.T, 4, 1);
                    Gui_DrawFont_GBK16(35, 25 , BLUE, GRAY0, (uint8_t *)key.Buff_T);
                    break;
                case 2:
                    if(Timer.Keyt_Flag == 1)
                    {
                        key.Set_Point -= 10;
                        exit_flag = 0;
                        Timer.Keyt_Flag = 0;
                        flag_time.KeyT_Flag = 0;
                    }else
                    {
                        key.Set_Point -= 0.1;
                        exit_flag = 0;
                        Timer.Keyt_Flag = 0;
                        flag_time.KeyT_Flag = 0;                        
                    }
                    if(key.Set_Point <= 0)
                    {
                        key.Set_Point = 0;
                    }
                    memset(key.Buff_SetPoint, 0, sizeof(key.Buff_SetPoint));
                    Num_Char((char *)key.Buff_SetPoint, key.Set_Point, 4, 1);
                    Gui_DrawFont_GBK16(35, 45 , BLUE, GRAY0, (uint8_t *)key.Buff_SetPoint);
                    break;
                case 3:
                    if(Timer.Keyt_Flag == 1)
                    {
                        key.Kp -= 10;
                        exit_flag = 0;
                        Timer.Keyt_Flag = 0;
                        flag_time.KeyT_Flag = 0;
                    }else
                    {
                        key.Kp -= 0.1;
                        exit_flag = 0;
                        Timer.Keyt_Flag = 0;
                        flag_time.KeyT_Flag = 0;                        
                    }
                    if(key.Kp <= 0)
                    {
                        key.Kp = 0;
                    }
                    memset(key.Buff_Kp, 0, sizeof(key.Buff_Kp));
                    Num_Char((char *)key.Buff_Kp, key.Kp, 4, 1);
                    Gui_DrawFont_GBK16(35, 65 , BLUE, GRAY0, (uint8_t *)key.Buff_Kp);
                    
                    break;
                case 4:            
                    if(Timer.Keyt_Flag == 1)
                    {
                        key.Ti -= 5000;
                        exit_flag = 0;
                        Timer.Keyt_Flag = 0;
                        flag_time.KeyT_Flag = 0;
                    }else
                    {
                        key.Ti -= 100;
                        exit_flag = 0;
                        Timer.Keyt_Flag = 0;
                        flag_time.KeyT_Flag = 0;                        
                    } 
                    if(key.Ti <= 0)
                    {
                        key.Ti = 0;
                    } 
                    memset(key.Buff_Ti, 0, sizeof(key.Buff_Ti));
                    Num_Char((char *)key.Buff_Ti, key.Ti, 7, 1);
                    Gui_DrawFont_GBK16(35, 85 , BLUE, GRAY0, (uint8_t *)key.Buff_Ti);    
                            
                    break;
                case 5:
                    if(Timer.Keyt_Flag == 1)
                    {
                        key.Td -= 500;
                        exit_flag = 0;
                        Timer.Keyt_Flag = 0;
                        flag_time.KeyT_Flag = 0;
                    }else
                    {
                        key.Td -= 100;
                        exit_flag = 0;
                        Timer.Keyt_Flag = 0;
                        flag_time.KeyT_Flag = 0;                        
                    }  
                    if(key.Td <= 0)
                    {
                        key.Td = 0;
                    }
                    memset(key.Buff_Td, 0, sizeof(key.Buff_Td));
                    Num_Char((char *)key.Buff_Td, key.Td, 4, 1);
                    Gui_DrawFont_GBK16(35, 105 , BLUE, GRAY0, (uint8_t *)key.Buff_Td);           
                    break;                           
                default:
                    break;
                }
            }
            
        }

    }else 
    if( (GPIO_Pin == Key_Cancle) )
    {
        Delay_Ms(20);
        if( (GPIO_Pin == Key_Cancle) && (KEY_CACNCLE == KEY_ON) )
        {
            
            if( (meun.Frist_meun == 0) && (meun.Second_meun == 1 || meun.Thired_meun == 1) )
            {
                DisplayButtonDown(84, 3, 120, 22);  

                //防止二级菜单残留
                key.select_flag = 0;
                flag_time.Key_Flag = 0;
                
                //为了避免因为进入外部中断显示第一个界面造成 第三个界面数据残留问题
                pid.Meun_Flag    = 1;
                //防止第三个界面数据残留问题
                meun.Frist_meun  = 1;
                meun.Second_meun = 0;
                meun.Thired_meun = 0;             
            }
            
        }else 
        if( (GPIO_Pin == Key_Cancle) && (KEY_CACNCLE == KEY_OFF) )
        {
            if( (pid.Meun_Flag == 1) || ( (meun.Frist_meun == 0) && (meun.Second_meun == 1 || meun.Thired_meun == 1) ) )
            {
                DisplayButtonUp(84, 3, 120, 22);
                First_Menu();
                pid.Meun_Flag  = 0; 
            }           
        }       
    }else 
    if( (GPIO_Pin == Key_Enter) )
    {
        Delay_Ms(20);
        if( (GPIO_Pin == Key_Enter) && (KEY_ENTER == KEY_ON) )
        {
            /*一级菜单按钮*/
            if( (meun.Frist_meun == 1) && (meun.Second_meun == 0) && (meun.Thired_meun == 0) )
            {   
                if(key_meun == 2)
                {    
                    Second_Menu(); 
                }else
                if(key_meun == 3)
                {
                    Thired_Meun();
                }
            }    
            /*二级菜单按钮*/
            if( (meun.Frist_meun == 0) && (meun.Second_meun == 1) && (meun.Thired_meun == 0) )
            {             
                DisplayButtonDown(84, 103, 120, 121); 
                if( (key.select_flag <= 5) && (key.select_flag > 0) )
                {
                    pid.Kp = key.Kp;
                    pid.Ti = key.Ti;
                    pid.Td = key.Td;  
                    pid.T  = key.T ; 
                    pid.Set_Point = key.Set_Point;

                    key.select_flag = 0;
                    flag_time.Key_Flag = 0;
                    Gui_DrawFont_GBK16(10, 25, BLUE, GREEN, (uint8_t *)("T :"));
                    Gui_DrawFont_GBK16(10, 45, BLUE, GREEN, (uint8_t *)("Te:"));
                    Gui_DrawFont_GBK16(10, 65, BLUE, GREEN, (uint8_t *)("Kp:"));
                    Gui_DrawFont_GBK16(10, 85, BLUE, GREEN, (uint8_t *)("Ti:"));
                    Gui_DrawFont_GBK16(10, 105,BLUE, GREEN, (uint8_t *)("Td:")); 

                    Num_Char((char *)key.Buff_Kp, pid.Kp, 4, 1);
                    Num_Char((char *)key.Buff_Ti, pid.Ti, 7, 1);
                    Num_Char((char *)key.Buff_Td, pid.Td, 4, 1);
                    Num_Char((char *)key.Buff_T , pid.T , 4, 1);
                    Num_Char((char *)key.Buff_SetPoint, pid.Set_Point, 4, 1);

                    
                    Gui_DrawFont_GBK16(35, 25 , BLUE, GRAY0, (uint8_t *)key.Buff_T);
                    Gui_DrawFont_GBK16(35, 45 , BLUE, GRAY0, (uint8_t *)key.Buff_SetPoint);
                    Gui_DrawFont_GBK16(35, 65 , BLUE, GRAY0, (uint8_t *)key.Buff_Kp);
                    Gui_DrawFont_GBK16(35, 85 , BLUE, GRAY0, (uint8_t *)key.Buff_Ti);
                    Gui_DrawFont_GBK16(35, 105, BLUE, GRAY0, (uint8_t *)key.Buff_Td);
                }
            }
        } else 
        if( (GPIO_Pin == Key_Enter) && (KEY_ENTER == KEY_OFF) )
        {
            /*二级菜单按钮*/
            if( (meun.Frist_meun == 0) && (meun.Second_meun == 1) && (meun.Thired_meun == 0) )
            { 
                DisplayButtonUp(84, 103, 120, 121); 
            }
        }       
    }else 
    if( (GPIO_Pin == Key_Sele) )
    {
        Delay_Ms(20);

        if( (GPIO_Pin == Key_Sele) && (KEY_SELE == KEY_ON) )
        {
            /*二级菜单按钮*/
            if( (meun.Frist_meun == 0) && (meun.Second_meun == 1) && (meun.Thired_meun == 0) )
            {

                DisplayButtonDown(4, 3, 40 , 22);  
                if(++key.select_flag > 5)
                {
                    key.select_flag = 0;
                    flag_time.Key_Flag = 0; 
                    Gui_DrawFont_GBK16(10, 25, BLUE, GREEN, (uint8_t *)("T :"));
                    Gui_DrawFont_GBK16(10, 45, BLUE, GREEN, (uint8_t *)("Te:"));
                    Gui_DrawFont_GBK16(10, 65, BLUE, GREEN, (uint8_t *)("Kp:"));
                    Gui_DrawFont_GBK16(10, 85, BLUE, GREEN, (uint8_t *)("Ti:"));
                    Gui_DrawFont_GBK16(10, 105,BLUE, GREEN, (uint8_t *)("Td:"));

                    Num_Char((char *)key.Buff_Kp, pid.Kp, 4, 1);
                    Num_Char((char *)key.Buff_Ti, pid.Ti, 7, 1);
                    Num_Char((char *)key.Buff_Td, pid.Td, 4, 1);
                    Num_Char((char *)key.Buff_T , pid.T , 4, 1);
                    Num_Char((char *)key.Buff_SetPoint, pid.Set_Point, 4, 1);

                    Gui_DrawFont_GBK16(35, 25 , BLUE, GRAY0, (uint8_t *)key.Buff_T);
                    Gui_DrawFont_GBK16(35, 45 , BLUE, GRAY0, (uint8_t *)key.Buff_SetPoint);
                    Gui_DrawFont_GBK16(35, 65 , BLUE, GRAY0, (uint8_t *)key.Buff_Kp);
                    Gui_DrawFont_GBK16(35, 85 , BLUE, GRAY0, (uint8_t *)key.Buff_Ti);
                    Gui_DrawFont_GBK16(35, 105, BLUE, GRAY0, (uint8_t *)key.Buff_Td);
                }
                if(key.select_flag == 1)
                {
                    key.Kp = pid.Kp;
                    key.Ti = pid.Ti;
                    key.Td = pid.Td;
                    key.T  = pid.T  ;
                    key.Set_Point = pid.Set_Point;
                }
            }  
        }else 
        if( (GPIO_Pin == Key_Sele) && (KEY_SELE == KEY_OFF) )
        {
            /*二级菜单按钮*/
            if( (meun.Frist_meun == 0) && (meun.Second_meun == 1) && (meun.Thired_meun == 0) )
            { 
                DisplayButtonUp(4, 3, 40 , 22);   
            }
        }                
    }
}
/********************************************************
* 功    能:按键初始化                                  
* 参    数:无                                            
* 返    值:无
* 说    明:无
*********************************************************/
void Key_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* GPIO Ports Clock Enable */
    KEY_GPIO_CLK_ENABLE();

    /*Configure GPIO pins : PA3 PA4 PA5 PA6 
                            PA7 */
    GPIO_InitStruct.Pin = Key_Add|Key_Down|Key_Cancle|Key_Enter 
                            |Key_Sele;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;//GPIO_MODE_IT_FALLING
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(KEY_GPIO, &GPIO_InitStruct);

    /* EXTI interrupt init*/
    HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);

    HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);

    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}
/********************************************************
* 功    能:按键中断函数                                  
* 参    数:无                                            
* 返    值:无
* 说    明:无
*********************************************************/
uint8_t exit_flag = 0;

void EXTI3_IRQHandler(void)
{
       
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
}
void EXTI4_IRQHandler(void)
{
   
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);  
}
void EXTI9_5_IRQHandler(void)
{
    
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);
}
/********************************************************
* 功    能:按键回调函数                                  
* 参    数:无                                            
* 返    值:无
* 说    明:无
*********************************************************/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if( (key.select_flag > 0) && ((GPIO_Pin == Key_Add) || (GPIO_Pin == Key_Down )) ) 
    {
        exit_flag = 1;
    }
    Key_Scans(GPIO_Pin);    
}