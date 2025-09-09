#include <REGX52.H>
#include "delay.h"
#include "LCD1602.h"
#include "DS18B20.h"

unsigned char ACK;
float T;

void main()
{
	DS18B20_ConvertT();		//上电先转换一次温度，防止第一次读数据错误
	Delay(1000);			//等待转换完成
	LCD1602_Init();
	LCD1602_ShowString(1,1,"Temperature:");
	// ACK = OneWire_Init();           //测试
	// LCD1602_ShowNum(2,1,ACK,3);
	
	while(1)
	{
		DS18B20_ConvertT();
		T = DS18B20_ReadT();
		if(T < 0)
		{
			LCD1602_ShowString(2,1,"-");
			T = -T;
		}
		else
		{
			LCD1602_ShowString(2,1,"+");
		}
		LCD1602_ShowNum(2,2,T,3);
		LCD1602_ShowChar(2,5,'.');
		LCD1602_ShowNum(2,6,((unsigned long)(T*10000)%10000),4);
	}
}