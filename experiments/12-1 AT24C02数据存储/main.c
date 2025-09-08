#include <REGX52.H>
#include "delay.h"
#include "LCD1602.h"
#include "key.h"
#include "AT24C02.h"

unsigned char Data,KeyNumber;
unsigned int num = 0;

void main()
{
    LCD1602_Init();
    LCD1602_ShowString(1,1,"E2PROM");
    // 此处作为测试，可以分别注释写入和读取，达到测试掉电不丢失的功能
    // AT24C02_WriteByte(1,66);
    // Delay(5);          //每次写入都要延时，确保时序完整有效
    // Data = AT24C02_ReadByte(1);
	// LCD1602_ShowNum(2,1,Data,3);

    
	while(1)
	{
        KeyNumber = Key();

        LCD1602_ShowNum(2,1,num,5);
        

        if(KeyNumber == 1)
        {
            num ++;
            LCD1602_ShowNum(2,1,num,5);
        }
        if(KeyNumber == 2)
        {
            num --;
            LCD1602_ShowNum(2,1,num,5);
        }
        if(KeyNumber == 3)
        {
            AT24C02_WriteByte(0,num%256);
            Delay(5);
            AT24C02_WriteByte(1,num/256);
            Delay(5);
            LCD1602_ShowString(1,8,"Write OK");
            Delay(1000);
            LCD1602_ShowString(1,8,"        ");
        }
        if(KeyNumber == 4)
        {
            num = AT24C02_ReadByte(0);
            num |= AT24C02_ReadByte(1) << 8;
            LCD1602_ShowNum(2,1,num,5);
            LCD1602_ShowString(1,8,"Read OK");
            Delay(1000);
            LCD1602_ShowString(1,8,"        ");
        }
		
	}
}