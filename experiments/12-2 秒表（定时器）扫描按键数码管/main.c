#include <REGX52.H>
#include "delay.h"
#include "Timer0.h"
#include "Key.h"
#include "nixie.h"
#include "AT24C02.h"
#include "I2C.h"

unsigned char KeyNumber, Temp;
unsigned char min,sec,minsec;
unsigned char runflag;

void main()
{
	Timer0_Init();
	while(1)
	{
		KeyNumber = Key();
		if(KeyNumber == 1)
		{
			runflag = !runflag;
		}
		if(KeyNumber == 2)
		{
			min = 0;
			sec = 0;
			minsec = 0;
		}
		if(KeyNumber == 3)
		{
			AT24C02_WriteByte(0, min);
			Delay(5);
			AT24C02_WriteByte(1, sec);
			Delay(5);
			AT24C02_WriteByte(2, minsec);
			Delay(5);
		}
		if(KeyNumber == 4)
		{
			min = AT24C02_ReadByte(0);
			sec = AT24C02_ReadByte(1);
			minsec = AT24C02_ReadByte(2);
		}
		Nixie_SetBuffer(1, min/10);
		Nixie_SetBuffer(2, min%10);
		Nixie_SetBuffer(3, 11);
		Nixie_SetBuffer(4, sec/10);
		Nixie_SetBuffer(5, sec%10);
		Nixie_SetBuffer(6, 11);
		Nixie_SetBuffer(7, minsec/10);
		Nixie_SetBuffer(8, minsec%10);
	}
}

void Second_Loop()
{
	if(runflag)
    {
        minsec ++;
		if(minsec >= 100)
		{
			minsec = 0;
			sec ++;
			if(sec >= 60)
			{
				sec = 0;
				min ++;
				if(min >= 60)
				{
					min = 0;
				}
			}
		}
    }
    
}

 void Timer0_Routine() interrupt 1    
 {
    static unsigned int T0Count1,T0Count2,SecondCount;
    TH0 = 0xFC;
    TL0 = 0x66;
    T0Count1 ++;
    if(T0Count1 >= 20)      //每20毫秒调用一次
    {
        T0Count1 = 0;
        Key_Loop();
    }
	T0Count2 ++;
    if(T0Count2 >= 1)      //每1毫秒调用一次
    {
    	T0Count2 = 0;
        Nixie_Loop();
    }
	SecondCount ++;
    if(SecondCount >= 10)         //每10毫秒调用一次
    {
        SecondCount = 0;
        Second_Loop();
    }
 }