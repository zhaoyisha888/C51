#include <REGX52.H>
#include "delay.h"

unsigned char NixieNumber[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};


void Nixie(unsigned int location, unsigned int number)
{ 
    switch (location)
    {
        //共阴极数码管，给0时选中
        case 8:P2_4=1;P2_3=1;P2_2=1;break;
        case 7:P2_4=1;P2_3=1;P2_2=0;break;
        case 6:P2_4=1;P2_3=0;P2_2=1;break;
        case 5:P2_4=1;P2_3=0;P2_2=0;break;
        case 4:P2_4=0;P2_3=1;P2_2=1;break;
        case 3:P2_4=0;P2_3=1;P2_2=0;break;
        case 2:P2_4=0;P2_3=0;P2_2=1;break;
        case 1:P2_4=0;P2_3=0;P2_2=0;break;
    }
    P0=NixieNumber[number];

}

void main()
{   
    // //位选控制显示位置，三个引脚2^3，共8位控制 LED 0~7
	// P2_4=0;
    // P2_3=1;
    // P2_2=0;

    // //段选择控制显示数字，分别对应原理图中各数码管代号dp,g,f,e,d,c,b,a
    // P0=0x06;   //显示数字1，给b,c为1，其余为0，0000 0110
    
    Nixie(7,2);
	while(1)
	{

	}
}