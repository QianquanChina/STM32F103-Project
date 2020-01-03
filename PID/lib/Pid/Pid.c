#include "Pid.h"
#include "Key.h"
#include "Pwm.h"
#include "Tim2.h"
#include "Ds18b20.h"
#include "TFT_demo.h"
#include "GUI.h"
#include "Ds18b20.h"
#include "Lcd_Driver.h"
extern TIM_HandleTypeDef htim4;
extern struct Meun meun;
extern struct Flag_Time flag_time ;

struct Pid_Value pid = 
{
    .Set_Point = 40.0    , 
    .Now_Error = 0       ,
    .Pre_Error = 0       ,
    .Kp        = 790     ,
    .T         = 250     ,
    .Ti        = 4050000 ,
    .Td        = 1000    ,
    .Pwm_Cycle = 200     ,//周期时间
    .Sum_Error = 0       ,
    .Out0      = 1       ,
    .Pout      = 0       , 
    .Dout      = 0       ,
    .Iout      = 0       ,
    .Pid_Start = 0       ,

};
/********************************************************
* 功    能:Pid计算                                  
* 参    数:无                                            
* 返    值:无
* 说    明:无
*********************************************************/
uint8_t uc, ucDs18b20Id[8];
char temp_buf[22] = {0};
void Pid_Cacl(void)
{
    float ti, td, ki, kd, delek, sout;
    if( (meun.Frist_meun == 0) && (meun.Second_meun == 0) && (meun.Thired_meun == 1) )
    {
        //获得当前温度
        while( DS18B20_Init() )	
        {
            printf("\r\n no ds18b20 exit \r\n");
        }   
        DS18B20_ReadId ( ucDs18b20Id  );           // 读取 DS18B20 的序列号
        pid.Now_Point = DS18B20_GetTemp_MatchRom ( ucDs18b20Id );
        if(pid.Pid_Start == 1)
        {
            //获得本次偏差
            pid.Now_Error = pid.Set_Point - pid.Now_Point;
            pid.Pout = pid.Kp * pid.Now_Error;
            //历史偏差总和
            pid.Sum_Error += pid.Now_Error;
            //微分运算的依据
            delek = pid.Now_Error - pid.Pre_Error;

            ti = pid.T / pid.Ti;
            ki = ti * pid.Kp;
            //积分输出
            pid.Iout = ki * pid.Sum_Error;

            td = pid.Td / pid.T;
            kd = pid.Kp * td;
            pid.Dout = kd * delek;

            sout = pid.Pout + pid.Iout + pid.Dout;

            if(sout > pid.Pwm_Cycle)
            {
                pid.Out = pid.Pwm_Cycle * 10;
                __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, pid.Out);
            }else 
            if(sout < 0)
            {
                pid.Out = pid.Out0;
                __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, pid.Out);
            }
            else
            {
                pid.Out = sout* 10;
                __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, pid.Out);
            }
            //更新偏差数值
            pid.Pre_Error = pid.Now_Error;       
            Pid_Display();
            //重新开始计算时间
            flag_time.Pid_Flag = 0;
            pid.Pid_Start = 0; 
        }
    }
}
/********************************************************
* 功    能:Pid显示                                  
* 参    数:无                                            
* 返    值:无
* 说    明:无
*********************************************************/
void Pid_Display(void)
{
    uint8_t pid_buff[128] = {0};
    if( (meun.Frist_meun == 0) && (meun.Second_meun == 0) && (meun.Thired_meun == 1) )
    {
        Num_Char(temp_buf, pid.Now_Point, 3, 2);
        printf("Temp:%s\n",temp_buf);
        Gui_DrawFont_GBK16(0, 5, BLUE, GRAY0, (uint8_t *)temp_buf );
        if(pid.Out >= 0)
        {
            Num_Char((char *)(pid_buff), pid.Out, 4, 3);
            Gui_DrawFont_GBK16(50, 45, BLUE, GRAY0, (uint8_t *)pid_buff );
            Gui_DrawFont_GBK16(115, 45, BLUE, GRAY0, (uint8_t *)"+" );
        }else 
        {
            pid.Out *= (-1);
            Num_Char((char *)(pid_buff), pid.Out, 4, 3);
            Gui_DrawFont_GBK16(50, 45, BLUE, GRAY0, (uint8_t *)pid_buff );
            Gui_DrawFont_GBK16(115, 45, BLUE, GRAY0, (uint8_t *)"-" );    
        }
    }

    if( (meun.Frist_meun == 0) && (meun.Second_meun == 0) && (meun.Thired_meun == 1) )
    {
        if(pid.Pout >= 0)
        {
            if(pid.Pout >= 9999.999)
            {
                pid.Pout = 9999.999;   
            }
            Num_Char((char *)(pid_buff), pid.Pout, 4, 3);
            Gui_DrawFont_GBK16(50, 65, BLUE, GRAY0, (uint8_t *)pid_buff );
            Gui_DrawFont_GBK16(115, 65, BLUE, GRAY0, (uint8_t *)"+" ); 
        }else
        {         
            pid.Pout *= (-1);   
            if(pid.Pout <= -9999.999)
            {
                pid.Pout = -9999.999;   
            }               
            Num_Char((char *)(pid_buff), pid.Pout, 4, 3);
            Gui_DrawFont_GBK16(50, 65, BLUE, GRAY0, (uint8_t *)pid_buff );
            Gui_DrawFont_GBK16(115, 65, BLUE, GRAY0, (uint8_t *)"-" ); 
        }
    }

    if( (meun.Frist_meun == 0) && (meun.Second_meun == 0) && (meun.Thired_meun == 1) )
    {
        if(pid.Dout >= 0)
        {
            Num_Char((char *)(pid_buff), pid.Dout, 4, 3);
            Gui_DrawFont_GBK16(50,  105, BLUE, GRAY0, (uint8_t *)pid_buff );
            Gui_DrawFont_GBK16(115, 105, BLUE, GRAY0, (uint8_t *) "+" );
        }else
        {
            pid.Dout *= (-1);
            Num_Char((char *)(pid_buff), pid.Dout, 4, 3);
            Gui_DrawFont_GBK16(50,  105, BLUE, GRAY0, (uint8_t *)pid_buff );
            Gui_DrawFont_GBK16(115, 105, BLUE, GRAY0,(uint8_t *) "-" );       
        }  
    }

    if( (meun.Frist_meun == 0) && (meun.Second_meun == 0) && (meun.Thired_meun == 1) )
    {
        if(pid.Iout >= 0)
        {
            Num_Char((char *)(pid_buff), pid.Iout, 4, 3);
            Gui_DrawFont_GBK16(50,  85, BLUE, GRAY0, (uint8_t *)pid_buff );
            Gui_DrawFont_GBK16(115, 85, BLUE, GRAY0, (uint8_t *)"+" );
        }else
        {
            pid.Iout *= (-1); 
            Num_Char((char *)(pid_buff), pid.Iout, 4, 3);
            Gui_DrawFont_GBK16(50,  85, BLUE, GRAY0, (uint8_t *)pid_buff );
            Gui_DrawFont_GBK16(115, 85, BLUE, GRAY0,(uint8_t *) "-" );
        }
    }
}

