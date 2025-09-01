#ifndef __LCD1602_H__
#define __LCD1602_H_

void LCD1602_Init();
void LCD1602_WriteCommand(unsigned char Command);
void LCD1602_WriteData(unsigned char Data);
void LCD1602_ShowChar(unsigned char Line,unsigned char Column,char Char);
void LCD1602_ShowString(unsigned char Line,unsigned char Column,char *String);
void LCD1602_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
void LCD1602_ShowSignedNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length);
void LCD1602_ShowHexNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length);
void LCD1602_ShowBinNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length);


#endif
