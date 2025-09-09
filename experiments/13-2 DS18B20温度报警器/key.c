#include <REGX52.H>
#include "delay.h"

unsigned char Key_KeyNumber;

/**
 * @brief 获取独立按键键码
 * @param None
 * @retval 按键值，范围0-4；无按键按下时返回0
*/
unsigned char Key_GetStatus()
{
    unsigned char KeyNumber = 0;

    if(P3_1 == 0){KeyNumber = 1;}
    if(P3_0 == 0){KeyNumber = 2;}
    if(P3_2 == 0){KeyNumber = 3;}
    if(P3_3 == 0){KeyNumber = 4;}

    return KeyNumber;
}

unsigned char Key()
{
    unsigned char Temp = 0;
    Temp = Key_KeyNumber;
    Key_KeyNumber = 0;
    return Temp;
}

void Key_Loop(void)
{
    static unsigned char NowStatus = 0;
    static unsigned char LastStatus = 0;
    LastStatus = NowStatus;
    NowStatus = Key_GetStatus();
    if(LastStatus == 1 && NowStatus == 0)
    {
        Key_KeyNumber = 1;
    }
    if(LastStatus == 2 && NowStatus == 0)
    {
        Key_KeyNumber = 2;
    }
    if(LastStatus == 3 && NowStatus == 0)
    {
        Key_KeyNumber = 3;
    }
    if(LastStatus == 4 && NowStatus == 0)
    {
        Key_KeyNumber = 4;
    }
}