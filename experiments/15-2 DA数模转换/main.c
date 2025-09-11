#include <REGX52.H>
#include "delay.h"
#include "timer0.h"


sbit DA = P2^1;    

unsigned char counter,compare,i;



void main()
{
	Timer0_Init();
	
	//设置比较值，控制占空比，比较值越低，占空比越小
	while(1)
	{
		//呼吸灯由暗变亮
		for(i=0;i<100;i++)
		{
			compare = i;
			Delay(10);
		}
		//呼吸灯由亮变暗
		for(i=100;i>0;i--)
		{
			compare = i;
			Delay(10);
		}
	}
}

void Timer0_Routine() interrupt 1    
{
    //每隔100um进入一次定时器
    TL0 = 0xA4;				//设置定时初始值
    TH0 = 0xFF;				//设置定时初始值
    counter++;
	counter %= 100;        //每100ms刷新一次counter
    if(counter < compare)   //计数值小于比较值
    {
        DA = 1;      
    }
    else
    {
        DA = 0;
    }
}