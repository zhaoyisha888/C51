#include <REGX52.H>
#include "delay.h"
#include "MatixLED.h"

unsigned char Code Animation[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    //�˴����Ϲؼ���code��ʾ�������flash��������벻�ɸ�������
							 	  0x7F,0x01,0x01,0x1D,0x3F,0x3F,0x77,0x73,    //ԭ���������rom��ɸ���
								  0x72,0x62,0x68,0x68,0x4F,0x18,0x18,0xF8,
							 	  0x0F,0x08,0x08,0x00,0x00,0x7A,0x00,0x7A,
								  0x00,0x7A,0x00,0x00,0x00,0x00,0x00,0x00};

void main()
{
	unsigned char i, Offset = 0,Count = 0;
	MatixLED_Init();
	while(1)
	{
		for(i=0;i<8;i++)
		{
			MatixLED_ShowColumn(i, Animation[i + Offset]); 
		}
		Count ++;
		if(Count > 10)
		{
			Count = 0;
			Offset ++;            //��֡��������ÿ��ƫ��8����Ϊ��8*8��������ƫ��8Ϊһ֡��ƫ���������п�����
			if(Offset > 32)      //ƫ�Ƴ��������ּ�����Խ�磬��Ϊ����Animation[i + Offset]�����Ϊ7+32 = 39��ǡ��Ϊ�������һ��Ԫ��
			{      
				Offset = 0;
			}
		}
		
	}
}