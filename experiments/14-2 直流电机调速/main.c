#include <REGX52.H>
#include "delay.h"
#include "nixie.h"
#include "timer0.h"
#include "key.h"

// sbit LED = P2^0;    //LED接在P2.0上，下方Motor更换为LED，并简单修改代码，可以看出LED呼吸效果，注意LED与电机极性相反
sbit Motor = P1^0;    //此接口看自己连线接口是多少，本实验一段接5V，一段接在P1.0上

unsigned char counter,compare;
unsigned char key_number,speed;

void main()
{
	//单片机默认高电平，所以上电一瞬间电机就会收到高电平转动,此为硬件电路缺陷

	Timer0_Init();
	
	// compare = 50;       //设置比较值，控制占空比，比较值越低，占空比越小（参考14-1的readme）
	while(1)
	{
		key_number = Key();
		if(key_number==1)
		{
			speed ++;
			speed = speed%4;

			if(speed==0)
			{
				compare = 0;
			}
			else if(speed==1)
			{
				compare = 25;
			}
			else if(speed==2)
			{
				compare = 50;
			}
			else if(speed==3)
			{
				compare = 75;
			}
		}
		Nixie(1,speed);
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
        Motor = 1;          //电机转动,与LED极性相反,给高电平工作
    }
    else
    {
        Motor = 0;
    }
    
}