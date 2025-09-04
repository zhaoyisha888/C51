#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "delay.h"

void main()
{
	LCD1602_Init();
	DS1302_Init();

	LCD1602_ShowString(1,14,"RTC");
	LCD1602_ShowString(1,1,"  -  -  ");
	LCD1602_ShowString(2,1,"  :  :  ");

	DS1302_SetTime();
	
	while(1)
	{
		DS1302_ReadTime();

		//读出数据后向屏幕显示
		LCD1602_ShowNum(1,1,DS1302_Time[0],2);
		LCD1602_ShowNum(1,4,DS1302_Time[1],2);
		LCD1602_ShowNum(1,7,DS1302_Time[2],2);

		LCD1602_ShowNum(2,1,DS1302_Time[3],2);
		LCD1602_ShowNum(2,4,DS1302_Time[4],2);
		LCD1602_ShowNum(2,7,DS1302_Time[5],2);

		LCD1602_ShowNum(1,10,DS1302_Time[6],1);


	}
}