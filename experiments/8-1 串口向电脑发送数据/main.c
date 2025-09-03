#include <REGX52.H>
#include "delay.h"
#include "timer0.h"
#include "UART.h"

unsigned char sec;

void main()
{
    UART_Init();
    
	while(1)
	{
		UART_SendByte(sec);//波特率越小发送数据越稳定
        sec ++;
        Delay(1000);//若波特率过快发送数据可能会出现错误，延时稳定
	}
}
