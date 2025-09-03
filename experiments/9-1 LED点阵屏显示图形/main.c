#include <REGX52.H>
#include "delay.h"

sbit RCK = P3^5;   //RCLK
sbit SCK = P3^6;   //SRCLK
sbit SER = P3^4;   //SER

#define MatixLED_Port P0


/**
 * @brief 74HC595д��һ���ֽ�
 * @param Byte Ҫд����ֽ�
 * @retval ��
 */
void _74HC595_WriteByte(unsigned char Byte)
{
	unsigned char i;
	for ( i = 0; i < 8; i++)
	{
		SER = Byte & (0x80>>i);     //�Ӹ�λ����λ
		SCK = 1;
		SCK = 0;
	}
	RCK = 1;
	RCK = 0;
}


/**
 * @brief LED��������ʾһ������
 * @note ����ƴ�Ӽ��ɻ��ͼ��
 * @param Column Ҫѡ����У���Χ��0~7��0�������
 * @param Data ѡ������ʾ�����ݣ���λ���ϣ�1Ϊ����0Ϊ��
 * @retval ��
 */
void MatixLED_ShowColumn(unsigned char Column, unsigned char Data)
{
	_74HC595_WriteByte(Data);
	MatixLED_Port = ~ (0x80 >> Column);      //λѡ
	Delay(1);                     //��ʱ��ʾ
	MatixLED_Port = 0xFF;                    //λ����
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