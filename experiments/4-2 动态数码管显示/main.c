#include <REGX52.H>
#include "delay.h"

unsigned char NixieNumber[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};


void Nixie(unsigned int location, unsigned int number)
{ 
    switch (location)
    {
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

    //消影操作
    Delay(1); //稳定显示当前段码
    P0=0x00;    //清屏

//数码管动态显示利用人眼视觉暂留作用，造成多个数码管同时显示的效果
//本质是不停扫描每个数码管，并显示当前数字
//即 “位码 段码 位码 段码 位码 段码” 这种过程不断扫描
//但是在 段码 位码 切换过程中，需要短暂延时并清屏，否则会导致显示篡位错误
}

void main()
{   
    //动态扫描数码管，放在主循环中
	while(1)
	{
        //同时显示，会出现显示篡位错误，需要消影
        Nixie(7,7);
//        Delay(20);   //延时闪烁显示
        Nixie(6,6);
//        Delay(20);
        Nixie(3,3);
//        Delay(20);
	}
}