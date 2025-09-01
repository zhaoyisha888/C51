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

    //��Ӱ����
    Delay(1); //�ȶ���ʾ��ǰ����
    P0=0x00;    //����

//����ܶ�̬��ʾ���������Ӿ��������ã���ɶ�������ͬʱ��ʾ��Ч��
//�����ǲ�ͣɨ��ÿ������ܣ�����ʾ��ǰ����
//�� ��λ�� ���� λ�� ���� λ�� ���롱 ���ֹ��̲���ɨ��
//������ ���� λ�� �л������У���Ҫ������ʱ������������ᵼ����ʾ��λ����
}

void main()
{   
    //��̬ɨ������ܣ�������ѭ����
	while(1)
	{
        //ͬʱ��ʾ���������ʾ��λ������Ҫ��Ӱ
        Nixie(7,7);
//        Delay(20);   //��ʱ��˸��ʾ
        Nixie(6,6);
//        Delay(20);
        Nixie(3,3);
//        Delay(20);
	}
}