#include <REGX52.H>
#include "delay.h"
#include "LCD1602.h"
#include "matrixKey.h"

/**
 * �˹�����������������ʵ��
 * S1~S10Ϊ���룺S1~S9��Ϊ1~9���룬S10��Ϊ0���룬
 * S11Ϊȷ�ϣ�S12Ϊȡ��
 */

unsigned char KeyNumber;
unsigned int password;
unsigned int count;
void main()
{
    LCD1602_Init();
    LCD1602_ShowString(1,1,"Password:");
	LCD1602_ShowNum(2,1,0,4);        //��ʾ����λ��
	while(1)
    {
        KeyNumber = MatrixKey();
        if(KeyNumber)
        {
            if(KeyNumber <= 10)
            {   
                if(count < 4)
                {
                    password *= 10;
                    password += KeyNumber % 10;    //��ȡ����
                    count ++;
                }
            }
            LCD1602_ShowNum(2,1,password,4);  //������ʾ

            if(KeyNumber == 11)                     //ȷ�ϼ�
            {   
                if(password == 1234)
                {
                    LCD1602_ShowString(1,14,"ok "); 
                    password = 0;                    //��������
                    count = 0;                       //�ƴ�����
                    LCD1602_ShowNum(2,1,password,4);  //������ʾ
                }else
                {
                    LCD1602_ShowString(1,14,"err");  
                    password = 0;
                    count = 0;
                    LCD1602_ShowNum(2,1,password,4);  //������ʾ
                }
            }
            if(KeyNumber == 12)                    //ȡ������ȫ������
            {   
                password = 0;
                count = 0;
				LCD1602_ShowString(1,14,"   ");    //����ж�״̬
                LCD1602_ShowNum(2,1,password,4);   //������ʾ
            }
        } 
    }   
}
	

	
