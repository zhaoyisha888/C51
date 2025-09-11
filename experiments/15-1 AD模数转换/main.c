#include <REGX52.H>
#include "delay.h"
#include "LCD1602.h"
#include "XPT2046.h"

unsigned int ADValue = 0;

void main()
{
	LCD1602_Init();
	LCD1602_ShowString(1,1,"ADJ  NTC  GR");
	while(1)
	{
		// 使用8位模式读取可调电阻，范围0-255
        XPT2046_ReadAD(XPT2046_XP_8);   // 第一次丢弃，稳定读数
        ADValue = XPT2046_ReadAD(XPT2046_XP_12);
        LCD1602_ShowNum(2,1,ADValue,4); // 显示3位数字就够了

        // 使用12位模式读取热敏电阻，范围0-4095
        XPT2046_ReadAD(XPT2046_YP_12);   // 第一次丢弃
        ADValue = XPT2046_ReadAD(XPT2046_YP_12);
        LCD1602_ShowNum(2,6,ADValue,4);


        // 使用8位模式读取光敏电阻，范围0-255
        XPT2046_ReadAD(XPT2046_VBAT_8); // 第一次丢弃
        ADValue = XPT2046_ReadAD(XPT2046_VBAT_12);
        LCD1602_ShowNum(2,11,ADValue,4);

        LCD1602_ShowNum(2,16,1,1);

        Delay(100);
	}
}