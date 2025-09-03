#include <REGX52.H>

sbit RCK = P3^5;   //RCLK
sbit SCK = P3^6;   //SRCLK
sbit SER = P3^4;   //SER

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

void main()
{
	SCK = 0;
	RCK = 0;
	_74HC595_WriteByte(0xFF);
	while(1)
	{
		P0 = 0;
	}
}