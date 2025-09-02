#include <REGX52.H>
#include "delay.h"
#include "LCD1602.h"
#include "matrixKey.h"

unsigned char KeyNumber;
void main()
{
    LCD1602_Init();
    LCD1602_ShowString(1,1,"MatrixKey is:");
	while(1)
    {
        KeyNumber=MatrixKey();
        if(KeyNumber)
        {
            LCD1602_ShowNum(2,1,KeyNumber,2);
        }
    }
	
}
	
	
