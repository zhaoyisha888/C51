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
		UART_SendByte(sec);//������ԽС��������Խ�ȶ�
        sec ++;
        Delay(1000);//�������ʹ��췢�����ݿ��ܻ���ִ�����ʱ�ȶ�
	}
}
