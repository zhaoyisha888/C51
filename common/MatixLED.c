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
 * @brief LED��������ʼ��
 * @note ��ʼ��ʱ������λ��Ϊ0
 * @retval ��
 */
void MatixLED_Init()
{
    SCK = 0;
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