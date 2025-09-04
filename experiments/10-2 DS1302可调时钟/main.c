#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "key.h"
#include "timer0.h"

unsigned char KeyNumber,MODE,TimeSetSelect,TimeSetFlashFlag;

void TimeShow(void)
{
    DS1302_ReadTime();

    //读出数据后向屏幕显示
    LCD1602_ShowNum(1,1,DS1302_Time[0],2);
    LCD1602_ShowNum(1,4,DS1302_Time[1],2);
    LCD1602_ShowNum(1,7,DS1302_Time[2],2);
    LCD1602_ShowNum(2,1,DS1302_Time[3],2);
    LCD1602_ShowNum(2,4,DS1302_Time[4],2);
    LCD1602_ShowNum(2,7,DS1302_Time[5],2);
	LCD1602_ShowNum(2,10,DS1302_Time[6],1);
	
}

void TimeSet(void)
{
    //按钮2按下选择设置项
    if(KeyNumber == 2)
    {
        TimeSetSelect ++;
        TimeSetSelect %=7;
    }

    //按钮3按下数据项增加
	if(KeyNumber == 3)
    {
        DS1302_Time[TimeSetSelect]++;
        if(DS1302_Time[0] > 99){DS1302_Time[0] = 0;}
        if(DS1302_Time[1] > 12){DS1302_Time[1] = 1;}

        //判断日期清零，年上限为99，所以整除4即为闰年
        if(DS1302_Time[1]==1 || DS1302_Time[1]==3 || DS1302_Time[1]==5 || DS1302_Time[1]==7 || DS1302_Time[1]==8 || DS1302_Time[1]==10 || DS1302_Time[1]==12)
        {
            if(DS1302_Time[2] > 31){DS1302_Time[2] = 1;}
        }else if(DS1302_Time[1]==4 || DS1302_Time[1]==6 || DS1302_Time[1]==9 || DS1302_Time[1]==11)
        {
            if(DS1302_Time[2] > 30){DS1302_Time[2] = 1;}
        }else if(DS1302_Time[1]==2)
        {
            if(DS1302_Time[0]%4 == 0)
            {
                if(DS1302_Time[2] > 29){DS1302_Time[2] = 1;}
            }else
            {
                if(DS1302_Time[2] > 28){DS1302_Time[2] = 1;}
            }
        }

        if(DS1302_Time[3] > 23){DS1302_Time[3] = 0;}
        if(DS1302_Time[4] > 59){DS1302_Time[4] = 0;}
        if(DS1302_Time[5] > 59){DS1302_Time[5] = 0;}
		if(DS1302_Time[6] > 7){DS1302_Time[6] = 1;}
    }

    //按钮4按下数据项减少
	if(KeyNumber == 4)
    {
        DS1302_Time[TimeSetSelect]--;
        if(DS1302_Time[0] < 0){DS1302_Time[0] = 99;}
        if(DS1302_Time[1] < 1){DS1302_Time[1] = 12;}

        //判断日期清零，年上限为99，所以整除4即为闰年
        if(DS1302_Time[1]==1 || DS1302_Time[1]==3 || DS1302_Time[1]==5 || DS1302_Time[1]==7 || DS1302_Time[1]==8 || DS1302_Time[1]==10 || DS1302_Time[1]==12)
        {
            if(DS1302_Time[2] < 1){DS1302_Time[2] = 31;}
        }else if(DS1302_Time[1]==4 || DS1302_Time[1]==6 || DS1302_Time[1]==9 || DS1302_Time[1]==11)
        {
            if(DS1302_Time[2] < 1){DS1302_Time[2] = 30;}
            if(DS1302_Time[2] > 30){DS1302_Time[2] = 1;}
        }else if(DS1302_Time[1]==2)
        {
            if(DS1302_Time[0]%4 == 0)
            {
                if(DS1302_Time[2] < 1){DS1302_Time[2] = 29;}
                if(DS1302_Time[2] > 29){DS1302_Time[2] = 1;}
            }else
            {
                if(DS1302_Time[2] < 1){DS1302_Time[2] = 28;}
                if(DS1302_Time[2] > 28){DS1302_Time[2] = 1;}
            }
        }

        if(DS1302_Time[3] < 0){DS1302_Time[3] = 23;}
        if(DS1302_Time[4] < 0){DS1302_Time[4] = 59;}
        if(DS1302_Time[5] < 0){DS1302_Time[5] = 59;}
		if(DS1302_Time[6] < 1){DS1302_Time[6] = 7;}
    }
    
    if(TimeSetSelect == 0 && TimeSetFlashFlag == 1)
    {
        LCD1602_ShowString(1,1,"  ");
    }else
    {
        LCD1602_ShowNum(1,1,DS1302_Time[0],2);
    }
    if(TimeSetSelect == 1 && TimeSetFlashFlag == 1)
    {
        LCD1602_ShowString(1,4,"  ");
    }else
    {
        LCD1602_ShowNum(1,4,DS1302_Time[1],2);
    }
    if(TimeSetSelect == 2 && TimeSetFlashFlag == 1)
    {
        LCD1602_ShowString(1,7,"  ");
    }else
    {
        LCD1602_ShowNum(1,7,DS1302_Time[2],2);
    }
    if(TimeSetSelect == 3 && TimeSetFlashFlag == 1)
    {
        LCD1602_ShowString(2,1,"  ");
    }else
    {
        LCD1602_ShowNum(2,1,DS1302_Time[3],2);
    }
    if(TimeSetSelect == 4 && TimeSetFlashFlag == 1)
    {
        LCD1602_ShowString(2,4,"  ");
    }else
    {
        LCD1602_ShowNum(2,4,DS1302_Time[4],2);
    }
    if(TimeSetSelect == 5 && TimeSetFlashFlag == 1)
    {
        LCD1602_ShowString(2,7,"  ");
    }else
    {
        LCD1602_ShowNum(2,7,DS1302_Time[5],2);
    }
	if(TimeSetSelect == 6 && TimeSetFlashFlag == 1)
    {
        LCD1602_ShowString(2,10," ");
    }else
    {
        LCD1602_ShowNum(2,10,DS1302_Time[6],1);
    }
 
    // LCD1602_ShowNum(2,10,TimeSetSelect,1);
    // LCD1602_ShowNum(1,13,TimeSetFlashFlag,1);
}

void main()
{
	LCD1602_Init();
	DS1302_Init();
    Timer0_Init();

	LCD1602_ShowString(1,1,"  -  -  ");
	LCD1602_ShowString(2,1,"  :  :  ");

	DS1302_SetTime();
	
	while(1)
	{
        KeyNumber = Key();
        //按钮1按下交替状态
        if(KeyNumber == 1)
        {
            if(MODE == 0){MODE = 1;TimeSetFlashFlag = 0;}
            else if(MODE == 1){MODE = 0;DS1302_SetTime();}

        }
		switch (MODE)
        {
        case 0:TimeShow();break;
        case 1:TimeSet();break;
        }
	}
}


void Timer0_Routine() interrupt 1    
{
    static unsigned int T0Count;
    TH0 = 0xFC;
    TL0 = 0x66;
    T0Count ++;
    if(T0Count >= 500)
    {
        T0Count = 0;
        TimeSetFlashFlag = !TimeSetFlashFlag;
    }
}