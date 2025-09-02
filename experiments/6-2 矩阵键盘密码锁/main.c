#include <REGX52.H>
#include "delay.h"
#include "LCD1602.h"
#include "matrixKey.h"

/**
 * 此工程用于制作密码锁实验
 * S1~S10为密码：S1~S9作为1~9输入，S10作为0输入，
 * S11为确认，S12为取消
 */

unsigned char KeyNumber;
unsigned int password;
unsigned int count;
void main()
{
    LCD1602_Init();
    LCD1602_ShowString(1,1,"Password:");
	LCD1602_ShowNum(2,1,0,4);        //提示密码位数
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
                    password += KeyNumber % 10;    //获取密码
                    count ++;
                }
            }
            LCD1602_ShowNum(2,1,password,4);  //更新显示

            if(KeyNumber == 11)                     //确认键
            {   
                if(password == 1234)
                {
                    LCD1602_ShowString(1,14,"ok "); 
                    password = 0;                    //密码清零
                    count = 0;                       //计次清零
                    LCD1602_ShowNum(2,1,password,4);  //更新显示
                }else
                {
                    LCD1602_ShowString(1,14,"err");  
                    password = 0;
                    count = 0;
                    LCD1602_ShowNum(2,1,password,4);  //更新显示
                }
            }
            if(KeyNumber == 12)                    //取消键，全部清零
            {   
                password = 0;
                count = 0;
				LCD1602_ShowString(1,14,"   ");    //清空判断状态
                LCD1602_ShowNum(2,1,password,4);   //更新显示
            }
        } 
    }   
}
	

	
