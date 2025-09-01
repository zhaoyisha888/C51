#include <REGX52.H>
#include "delay.h"

unsigned char NixieNumber[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};


void Nixie(unsigned int location, unsigned int number)
{ 
    switch (location)
    {
        //����������ܣ���0ʱѡ��
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
    // //λѡ������ʾλ�ã���������2^3����8λ���� LED 0~7
	// P2_4=0;
    // P2_3=1;
    // P2_2=0;

    // //��ѡ�������ʾ���֣��ֱ��Ӧԭ��ͼ�и�����ܴ���dp,g,f,e,d,c,b,a
    // P0=0x06;   //��ʾ����1����b,cΪ1������Ϊ0��0000 0110
    
    Nixie(7,2);
	while(1)
	{

	}
}