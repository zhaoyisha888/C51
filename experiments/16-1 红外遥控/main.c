#include <REGX52.H>
#include "LCD1602.h"
#include "delay.h"
#include "IR.h"


unsigned int time,num;
unsigned char Address;
unsigned char Command;

void main()
{
	LCD1602_Init();
	IR_Init();

	LCD1602_ShowString(1,1,"Addr Cmd Num");
	LCD1602_ShowString(2,1,"00   00  00 ");
	
	while(1)
	{	
		
		if(IR_GetDataFlag() || IR_GetRepeatFlag())
		{
			Address = IR_GetAddress();
			Command = IR_GetCommand();

			LCD1602_ShowHexNum(2,1,Address,2);
			LCD1602_ShowHexNum(2,6,Command,2);

			if(Command == IR_VOL_MINUS)
			{
				num --;
			}
			if(Command == IR_VOL_ADD)
			{
				num ++;
			}
			LCD1602_ShowNum(2,10,num,3);
		}

	}
}
