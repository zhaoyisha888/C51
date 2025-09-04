#include <REGX52.H>
#include "delay.h"
#include "MatixLED.h"

unsigned char Code Animation[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    //此处加上关键字code表示数组存在flash里，后续代码不可更改数组
							 	  0x7F,0x01,0x01,0x1D,0x3F,0x3F,0x77,0x73,    //原来数组存在rom里，可更改
								  0x72,0x62,0x68,0x68,0x4F,0x18,0x18,0xF8,
							 	  0x0F,0x08,0x08,0x00,0x00,0x7A,0x00,0x7A,
								  0x00,0x7A,0x00,0x00,0x00,0x00,0x00,0x00};

void main()
{
	unsigned char i, Offset = 0,Count = 0;
	MatixLED_Init();
	while(1)
	{
		for(i=0;i<8;i++)
		{
			MatixLED_ShowColumn(i, Animation[i + Offset]); 
		}
		Count ++;
		if(Count > 10)
		{
			Count = 0;
			Offset ++;            //逐帧动画可以每次偏移8，因为是8*8点阵屏，偏移8为一帧，偏移量根据列宽设置
			if(Offset > 32)      //偏移超过此数字即数组越界，因为数组Animation[i + Offset]，最大为7+32 = 39，恰好为数组最后一个元素
			{      
				Offset = 0;
			}
		}
		
	}
}