#include <REGX52.H>
#include "delay.h"


sbit LCD_RS=P2^6;
sbit LCD_RW=P2^5;
sbit LCD_E=P2^7;
#define LCD_DataPort P0

/**
 * @brief ��LCDд��һ������
 * @param Command Ҫд��������ֽ�
 * @retval None
 */
void LCD1602_WriteCommand(unsigned char Command)
{ 
    LCD_RS=0;
    LCD_RW=0;
    LCD_DataPort=Command;
    LCD_E=1;
    Delay(1);
    LCD_E=0;
    Delay(1);
}

/**
 * @brief ��LCDд��һ������
 * @param Data Ҫд��������ֽ�
 * @retval None
 */
void LCD1602_WriteData(unsigned char Data)
{ 
    LCD_RS=1;
    LCD_RW=0;
    LCD_DataPort=Data;
    LCD_E=1;
    Delay(1);
    LCD_E=0;
    Delay(1);
}

/**
 * @brief ��ʼ��LCD1602
 * @note ��ʼ��Ϊ8λ���ݽӿڣ���ʾ�������أ����ƣ�����
 * @param None
 * @retval None
 */
void LCD1602_Init()
{ 
    LCD1602_WriteCommand(0x38);  //8λ���ݽӿڣ�������ʾ��5*7����
    LCD1602_WriteCommand(0x0C);  //��ʾ�������أ���˸��
    LCD1602_WriteCommand(0x06);  //���ݶ�д�����󣬹�����ƣ����治��
    LCD1602_WriteCommand(0x01);  //��긴λ������
}

/**
 * @brief ����LCD���λ��
 * @param Line �кţ���Χ1-2
 * @param Column �кţ���Χ1-16
 * @retval None
 */
void LCD1602_SetCursor(unsigned char Line,unsigned char Column)
{ 
    if(Line==1){
        LCD1602_WriteCommand(0x80|(Column-1));
    }else if(Line==2){
        LCD1602_WriteCommand(0x80|(Column-1)+0x40);
    }
}

/**
 * @brief ��ָ��λ����ʾһ���ַ�
 * @param Line �кţ���Χ1-2
 * @param Column �кţ���Χ1-16
 * @param Char Ҫ��ʾ���ַ�
 * @retval None
 */
void LCD1602_ShowChar(unsigned char Line,unsigned char Column,char Char)
{ 
    LCD1602_SetCursor(Line,Column);
    LCD1602_WriteData(Char);
}

/**
 * @brief ��ָ��λ����ʾһ���ַ���
 * @param Line �кţ���Χ1-2
 * @param Column �кţ���Χ1-16
 * @param String Ҫ��ʾ����'\0'��β���ַ���
 * @retval None
 */
void LCD1602_ShowString(unsigned char Line,unsigned char Column,char *String)  //��char String[]�ȼ�
{ 
    unsigned char i=0;

    LCD1602_SetCursor(Line,Column);

    for(i=0;String[i]!='\0';i++){
        LCD1602_WriteData(String[i]);
    }
}

/**
 * @brief ����m��n�η�
 * @param m ����
 * @param n ָ��
 * @return int ����m^n�Ľ��
 * @retval None
 */
int LCD1602_Power(int m,int n)
{
    int i;
    int Result=1;
    for(i=0;i<n;i++){
        Result*=m;
    }
    return Result;
}

/**
 * @brief ��ָ��λ����ʾһ���޷�������
 * @param Line �кţ���Χ1-2
 * @param Column �кţ���Χ1-16
 * @param Number Ҫ��ʾ���޷�������
 * @param Length Ҫ��ʾ���ֵĳ���,��Χ1-16
 * @retval None
 */
void LCD1602_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{ 
    unsigned char i;

    LCD1602_SetCursor(Line,Column);

    for(i=Length;i>0;i--){
        LCD1602_WriteData('0'+ Number/LCD1602_Power(10,i-1)%10);
    }

}

/**
 * @brief ��ָ��λ����ʾһ���з�������
 * @param Line �кţ���Χ1-2
 * @param Column �кţ���Χ1-16
 * @param Number Ҫ��ʾ���з�������
 * @param Length Ҫ��ʾ���ֵĳ���(����������λ),��Χ1-15
 * @retval None
 */
void LCD1602_ShowSignedNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length)
{ 
    unsigned char i;
    unsigned int Number1;
    LCD1602_SetCursor(Line,Column);
    if(Number<0)
    {
        LCD1602_WriteData('-');
        Number1 = -Number;
    }else
    {
        LCD1602_WriteData('+');
        Number1 = Number;
    }
    for(i=Length;i>0;i--){
        LCD1602_WriteData('0'+ Number1/LCD1602_Power(10,i-1)%10);
    }

}

/**
 * @brief ��ָ��λ����ʾһ��16��������
 * @param Line �кţ���Χ1-2
 * @param Column �кţ���Χ1-16
 * @param Number Ҫ��ʾ��16��������
 * @param Length Ҫ��ʾ���ֵĳ���,��Χ1-16
 * @retval None
 */
void LCD1602_ShowHexNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length)
{ 
    unsigned char i;
    unsigned char single_num;
    LCD1602_SetCursor(Line,Column);
    for(i=Length;i>0;i--){
        single_num = Number/LCD1602_Power(16,i-1)%16;
        if(single_num<10)
            LCD1602_WriteData('0'+single_num);
        else
            LCD1602_WriteData('A'+single_num-10);
    }

}

/**
 * @brief ��ָ��λ����ʾһ��2��������
 * @param Line �кţ���Χ1-2
 * @param Column �кţ���Χ1-16
 * @param Number Ҫ��ʾ��2��������
 * @param Length Ҫ��ʾ���ֵĳ���,��Χ1-16
 * @retval None
 */
void LCD1602_ShowBinNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length)
{ 
    unsigned char i;
    LCD1602_SetCursor(Line,Column);
    
    for(i=Length;i>0;i--){
        LCD1602_WriteData('0'+Number/LCD1602_Power(2,i-1)%2);
    }

}
