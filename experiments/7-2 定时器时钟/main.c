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
        //主循环不断刷新界面显示
        LCD1602_ShowNum(2,1,hour,2); 
        LCD1602_ShowNum(2,4,minute,2);
        LCD1602_ShowNum(2,7,second,2);

    }
}

/*
这个函数在 定时器0溢出时被自动调用，大概 每 1ms 进入一次。
也就是说：
每 1ms → 进一次中断。
每 1000 次中断（1秒） → 秒数加一。
秒满60 → 分钟加一。
分钟满60 → 小时加一。
小时满24 → 归零。
*/
void Timer0_Routine() interrupt 1            
{
    static unsigned int T0Count;
    TH0 = 0xFC;                              //重新装载初值，保证下次还是 1ms 定时。
    TL0 = 0x66;                              
    T0Count ++;                              //每进一次中断，计数器加1。
    if(T0Count >= 1000)                      //当累计 1000 次中断（约 1000ms = 1秒）
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
