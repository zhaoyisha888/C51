#include <REGX52.H>
#include "timer0.h"
#include "LCD1602.h"
#include "delay.h"

unsigned char second = 55,minute = 59,hour = 23;
void main() 
{
    LCD1602_Init();
    Timer0_Init();

    LCD1602_ShowString(1,1,"clock:");
    LCD1602_ShowString(2,1,"  :  :  ");
    
    while(1)
    {   
        //��ѭ������ˢ�½�����ʾ
        LCD1602_ShowNum(2,1,hour,2); 
        LCD1602_ShowNum(2,4,minute,2);
        LCD1602_ShowNum(2,7,second,2);

    }
}

/*
��������� ��ʱ��0���ʱ���Զ����ã���� ÿ 1ms ����һ�Ρ�
Ҳ����˵��
ÿ 1ms �� ��һ���жϡ�
ÿ 1000 ���жϣ�1�룩 �� ������һ��
����60 �� ���Ӽ�һ��
������60 �� Сʱ��һ��
Сʱ��24 �� ���㡣
*/
void Timer0_Routine() interrupt 1            
{
    static unsigned int T0Count;
    TH0 = 0xFC;                              //����װ�س�ֵ����֤�´λ��� 1ms ��ʱ��
    TL0 = 0x66;                              
    T0Count ++;                              //ÿ��һ���жϣ���������1��
    if(T0Count >= 1000)                      //���ۼ� 1000 ���жϣ�Լ 1000ms = 1�룩
    {
        T0Count = 0;
        second ++;
        if(second >= 60)
        {
            second = 0;
            minute ++;
            if(minute >= 60)
            {
                minute = 0;
                hour ++;
                if(hour >= 24)
                {
                    hour = 0;
                }
            }
        }
    }
}
