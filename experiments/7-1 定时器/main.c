#include <REGX52.H>
#include "timer0.h"
#include "key.h"

unsigned char KeyNumber;

void main()
{
    // Timer0_Init();
    while (1)
    {
        KeyNumber = Key();
        if(KeyNumber)
        {
            if(KeyNumber == 1) P2_0 = ~P2_0;
            if(KeyNumber == 2) P2_1 = ~P2_1;
            if(KeyNumber == 3) P2_2 = ~P2_2;
            if(KeyNumber == 4) P2_3 = ~P2_3;
        }
    }
}



// void Timer0_Routine() interrupt 1     //定时器0的中断程序
// {
//     static unsigned int T0Count;
//     TH0 = 0xFC;
//     TL0 = 0x66;
//     T0Count ++;
//     if(T0Count >= 1000)
//     {
//         T0Count = 0;
//         P2_0 = ~P2_0;
//     }
// }
