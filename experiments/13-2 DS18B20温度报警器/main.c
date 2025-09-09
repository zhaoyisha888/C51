#include <REGX52.H>
#include "DS18B20.h"
#include "LCD1602.h"
#include "key.h"
#include "AT24C02.h"
#include "delay.h"
#include "Timer0.h"

float T,TShow;
char TH = 0,TL = 0;
unsigned char key_num;

void main()
{
	DS18B20_ConvertT();          //上电先转换一次温度，防止第一次读数据错误
	Delay(1000);                 //等待转换完成
	TH = AT24C02_ReadByte(0);    //读取温度阈值数据
	TL = AT24C02_ReadByte(1);

	if(TH > 125 || TL < -55 || TH < TL)
	{
		TH = 50;        //如果阈值非法，则设为默认值
		TL = 5;
	}

	LCD1602_Init();
	LCD1602_ShowString(1,1,"T:");
	LCD1602_ShowString(2,1,"TH:");
	LCD1602_ShowString(2,9,"TL:");
	LCD1602_ShowSignedNum(2,4,TH,3);
	LCD1602_ShowSignedNum(2,12,TL,3);

	Timer0_Init();

	while(1)
	{
		key_num = Key();
		//温度读取及显示
		DS18B20_ConvertT();          //转换温度
		T = DS18B20_ReadT();        //读取温度
		if(T < 0)
		{
			LCD1602_ShowString(1,3,"-");
			TShow = -T;
		}
		else
		{
			LCD1602_ShowString(1,3,"+");
			TShow = T;
		}
		LCD1602_ShowNum(1,4,TShow,3);        //显示温度整数
		LCD1602_ShowChar(1,7,'.');        //显示温度小数点
		LCD1602_ShowNum(1,8,(unsigned int)(TShow*100)%100,2);  //显示温度小数


		//温度阈值判断及显示
		if(key_num)
		{
			if(key_num == 1)     //按键1：TH增加阈值
			{
				TH++;
				if(TH > 125)
				{
					TH = 125;
				}
			}
			if(key_num == 2)     //按键2：TH减少阈值
			{
				TH--;
				if(TH <= TL)
				{
					TH ++;
				}
			}
			if(key_num == 3)     //按键3：TL增加阈值
			{
				TL++;
				if(TL >= TH)
				{
					TL--;
				}
			}
			if(key_num == 4)     //按键4：TL减少阈值
			{
				TL--;
				if(TL < -55)
				{
					TL = -55;
				}
			}
			LCD1602_ShowSignedNum(2,4,TH,3);     
			LCD1602_ShowSignedNum(2,12,TL,3);
			AT24C02_WriteByte(0,TH);              //AT24C02保存阈值数据
			Delay(5);
			AT24C02_WriteByte(1,TL);
			Delay(5);
		}
		if(T > TH)           //温度超出阈值
		{
			LCD1602_ShowString(1,13,"OV:H");
		}
		else if(T < TL)       //温度低于阈值
		{
			LCD1602_ShowString(1,13,"OV:L");
		}
		else
		{
			LCD1602_ShowString(1,13,"    ");
		}
	}
}

void Timer0_Routine() interrupt 1    
{
    static unsigned int T0Count;
    TH0 = 0xFC; 
    TL0 = 0x66;
    T0Count ++;
    if(T0Count >= 20)
    {
        T0Count = 0;
 
		//出现问题：按钮按下时处于中断，导致温度在按钮按下状态时无法变化

		/**原因和解决办法
		* DS18B20 单总线通信需要严格的微秒级时序
		* 为避免中断打乱时序，在关键的读写操作中短暂关闭总中断(EA=0)
		* 操作完成后立即恢复(EA=1)
		* 注意：关闭时间应尽量短，否则可能丢失按键等中断信号
		* 但是EA=0 时，CPU 完全屏蔽所有中断请求，即使有中断触发，CPU 也不会响应
		* 若存在其他中断源，可能会被屏蔽  */
        Key_Loop();      

    }
}