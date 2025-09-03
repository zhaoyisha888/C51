#include <REGX52.H>
#include "delay.h"

sbit RCK = P3^5;   //RCLK
sbit SCK = P3^6;   //SRCLK
sbit SER = P3^4;   //SER

#define MatixLED_Port P0


/**
 * @brief 74HC595写入一个字节
 * @param Byte 要写入的字节
 * @retval 无
 */
void _74HC595_WriteByte(unsigned char Byte)
{
	unsigned char i;
	for ( i = 0; i < 8; i++)
	{
		SER = Byte & (0x80>>i);     //从高位到低位
		SCK = 1;
		SCK = 0;
	}
	RCK = 1;
	RCK = 0;
}


/**
 * @brief LED点阵屏显示一列数据
 * @note 按列拼接即可获得图形
 * @param Column 要选择的列，范围：0~7，0在最左边
 * @param Data 选择列显示的数据，高位在上，1为亮，0为灭
 * @retval 无
 */
void MatixLED_ShowColumn(unsigned char Column, unsigned char Data)
{
	_74HC595_WriteByte(Data);
	MatixLED_Port = ~ (0x80 >> Column);      //位选
	Delay(1);                     //延时显示
	MatixLED_Port = 0xFF;                    //位清零
}

void main()
{
	SCK = 0;
	RCK = 0;
	while(1)
	{
		MatixLED_ShowColumn(0, 0x3C);  
		MatixLED_ShowColumn(1, 0x42);  
		MatixLED_ShowColumn(2, 0xA9);  
		MatixLED_ShowColumn(3, 0x85);   
		MatixLED_ShowColumn(4, 0x85);   
		MatixLED_ShowColumn(5, 0xA9); 
		MatixLED_ShowColumn(6, 0x42); 
		MatixLED_ShowColumn(7, 0x3C); 
	}
}