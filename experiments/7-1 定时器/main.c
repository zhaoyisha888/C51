#include <REGX52.H>
#include "timer0.h"

void main()
{
    Timer0_Init();
    while (1)
    {
        
    }
}



void Timer0_Routine() interrupt 1     //定时器0的中断程序
{
    static unsigned int T0Count;
    TH0 = 0xFC;
    TL0 = 0x66;
    T0Count ++;
    if(T0Count >= 1000)
    {
        T0Count = 0;
        P2_0 = ~P2_0;
    }
}
