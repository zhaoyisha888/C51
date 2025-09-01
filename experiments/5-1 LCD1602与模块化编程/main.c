#include <REGX52.H>
#include "delay.h"
#include "LCD1602.h"

void main()
{ 
    LCD1602_Init();
    LCD1602_ShowChar(1,1,'A');
    LCD1602_ShowString(1,3,"fine");
    LCD1602_ShowNum(1,8,66,2);
    LCD1602_ShowSignedNum(1,11,-8,1);
    LCD1602_ShowHexNum(2,1,0xA5,2);
    LCD1602_ShowBinNum(2,4,0xA5,8);
    LCD1602_ShowChar(2,13,0xDF);
    LCD1602_ShowChar(2,14,'C');
    LCD1602_ShowString(2,16,"hello world!");

    while(1)
    {
        LCD1602_WriteCommand(0x18);
        Delay(500);
    }
}