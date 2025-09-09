#include <REGX52.H>
#include "delay.h"


sbit LCD_RS=P2^6;
sbit LCD_RW=P2^5;
sbit LCD_E=P2^7;
#define LCD_DataPort P0

/**
 * @brief 向LCD写入一个命令
 * @param Command 要写入的命令字节
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
 * @brief 向LCD写入一个数据
 * @param Data 要写入的数据字节
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
 * @brief 初始化LCD1602
 * @note 初始化为8位数据接口，显示开，光标关，右移，清屏
 * @param None
 * @retval None
 */
void LCD1602_Init()
{ 
    LCD1602_WriteCommand(0x38);  //8位数据接口，两行显示，5*7点阵
    LCD1602_WriteCommand(0x0C);  //显示开，光标关，闪烁关
    LCD1602_WriteCommand(0x06);  //数据读写操作后，光标右移，画面不动
    LCD1602_WriteCommand(0x01);  //光标复位，清屏
}

/**
 * @brief 设置LCD光标位置
 * @param Line 行号，范围1-2
 * @param Column 列号，范围1-16
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
 * @brief 在指定位置显示一个字符
 * @param Line 行号，范围1-2
 * @param Column 列号，范围1-16
 * @param Char 要显示的字符
 * @retval None
 */
void LCD1602_ShowChar(unsigned char Line,unsigned char Column,char Char)
{ 
    LCD1602_SetCursor(Line,Column);
    LCD1602_WriteData(Char);
}

/**
 * @brief 在指定位置显示一个字符串
 * @param Line 行号，范围1-2
 * @param Column 列号，范围1-16
 * @param String 要显示的以'\0'结尾的字符串
 * @retval None
 */
void LCD1602_ShowString(unsigned char Line,unsigned char Column,char *String)  //与char String[]等价
{ 
    unsigned char i=0;

    LCD1602_SetCursor(Line,Column);

    for(i=0;String[i]!='\0';i++){
        LCD1602_WriteData(String[i]);
    }
}

/**
 * @brief 计算m的n次方
 * @param m 底数
 * @param n 指数
 * @return int 返回m^n的结果
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
 * @brief 在指定位置显示一个无符号数字
 * @param Line 行号，范围1-2
 * @param Column 列号，范围1-16
 * @param Number 要显示的无符号数字
 * @param Length 要显示数字的长度,范围1-16
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
 * @brief 在指定位置显示一个有符号数字
 * @param Line 行号，范围1-2
 * @param Column 列号，范围1-16
 * @param Number 要显示的有符号数字
 * @param Length 要显示数字的长度(不包含符号位),范围1-15
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
 * @brief 在指定位置显示一个16进制数字
 * @param Line 行号，范围1-2
 * @param Column 列号，范围1-16
 * @param Number 要显示的16进制数字
 * @param Length 要显示数字的长度,范围1-16
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
 * @brief 在指定位置显示一个2进制数字
 * @param Line 行号，范围1-2
 * @param Column 列号，范围1-16
 * @param Number 要显示的2进制数字
 * @param Length 要显示数字的长度,范围1-16
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
