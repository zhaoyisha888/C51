#include <REGX52.H>
#include <INTRINS.H>
#include "timer0.h"
#include "key.h"

unsigned char KeyNumber,LEDMode;

void main()
{
    P2 = 0xFE;
    Timer0_Init();
    while (1)
    {
        KeyNumber = Key();
        if(KeyNumber)
        {
            if(KeyNumber == 1)
            {
                LEDMode ++;
                if(LEDMode >= 2) LEDMode = 0;
            }
        }
    }
}



void Timer0_Routine() interrupt 1     //定时器0的中断程序
{
    static unsigned int T0Count;
    TH0 = 0xFC;
    TL0 = 0x66;
    T0Count ++;
    if(T0Count >= 500)
    {
        T0Count = 0;
        if(LEDMode == 0)
        {
            P2 = _crol_(P2,1);
        }
        if(LEDMode == 1)
        {
            P2 = _cror_(P2,1);
        }
    }
}
