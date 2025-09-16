#include <REGX52.H>
#include "timer1.h"

sbit Motor = P1^0;    //此接口看自己连线接口是多少，本实验一段接5V，一段接在P1.0上

unsigned char counter,compare;

/**
 * @brief 电机初始化
 * @param 无
 * @retval 无
 */
void Motor_Init()
{
    Timer1_Init();
}

/**
 * @brief 电机设置速度
 * @param speed 速度值，0-100
 * @retval 无
 */
void Motor_SetSpeed(unsigned char speed)
{
    compare = speed;
}


void Timer1_Routine() interrupt 3    
{
    //每隔100um进入一次定时器
    TL1 = 0xA4;				//设置定时初始值
	TH1 = 0xFF;				//设置定时初始值
    counter++;
	counter %= 100;        //每100ms刷新一次counter
    if(counter < compare)   //计数值小于比较值
    {
        Motor = 1;          //电机转动,与LED极性相反,给高电平工作
    }
    else
    {
        Motor = 0;
    }
    
}