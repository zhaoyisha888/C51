#include <REGX52.H>
#include "delay.h"
#include "timer0.h"

void UART_Init()	    //4800bps@11.0592MHz
{
    PCON &= 0x7F;		//波特率不倍速
	SCON = 0x40;		//8位数据,可变波特率
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xFA;			//设置定时初始值
	TH1 = 0xFA;			//设置定时重载值
	ET1 = 0;			//禁止定时器中断
	TR1 = 1;			//定时器1开始计时

}

void UART_SendByte(unsigned char Byte)
{
    SBUF = Byte;
    while(TI == 0);     //监测到数据，TI置1，即发送
	TI = 0;             //软件复位TI
}

void main()
{
    UART_Init();
    
	while(1)
	{
		UART_SendByte(0x66);//波特率越小发送数据越稳定
        Delay(1);//若波特率过快发送数据可能会出现错误，延时稳定
	}
}
