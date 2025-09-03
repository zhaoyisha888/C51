#include <REGX52.H>
#include "UART.h"
#include "delay.h"

void main()
{
	UART_Init();
	while(1)
	{
		
	}
}

void UART_Routine()  interrupt 4
{
	if(RI == 1)         //发送和接收都会触发中断，这里须判断接收中断
	{
		P2 = SBUF;
		UART_SendByte(SBUF);
		RI = 0;
	}
}