#include <REGX52.H>
#include "delay.h"
#include "nixie.h"
#include "motor.h"
#include "IR.h"


unsigned char command,speed;

void main()
{
	IR_Init();
	Motor_Init();
	

	while(1)
	{
		if(IR_GetDataFlag())
		{
			command = IR_GetCommand();


			if(command == IR_0) {speed=0;}
			if(command == IR_1) {speed=1;}
			if(command == IR_2) {speed=2;}
			if(command == IR_3) {speed=3;}

			if(speed==0) { Motor_SetSpeed(0); }
			if(speed==1) { Motor_SetSpeed(25); }
			if(speed==2) { Motor_SetSpeed(50); }
			if(speed==3) { Motor_SetSpeed(75); }
		}
		Nixie(1,speed);
	}
}