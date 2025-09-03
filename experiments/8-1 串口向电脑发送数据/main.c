#include <REGX52.H>
#include "delay.h"
#include "timer0.h"

void UART_Init()	    //4800bps@11.0592MHz
{
    PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x40;		//8λ����,�ɱ䲨����
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TMOD |= 0x20;		//���ö�ʱ��ģʽ
	TL1 = 0xFA;			//���ö�ʱ��ʼֵ
	TH1 = 0xFA;			//���ö�ʱ����ֵ
	ET1 = 0;			//��ֹ��ʱ���ж�
	TR1 = 1;			//��ʱ��1��ʼ��ʱ

}

void UART_SendByte(unsigned char Byte)
{
    SBUF = Byte;
    while(TI == 0);     //��⵽���ݣ�TI��1��������
	TI = 0;             //�����λTI
}

void main()
{
    UART_Init();
    
	while(1)
	{
		UART_SendByte(0x66);//������ԽС��������Խ�ȶ�
        Delay(1);//�������ʹ��췢�����ݿ��ܻ���ִ�����ʱ�ȶ�
	}
}
