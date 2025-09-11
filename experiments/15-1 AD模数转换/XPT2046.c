#include <REGX52.H>
#include "delay.h"
#include <INTRINS.H>

//引脚定义
sbit XPT2046_DIN=P3^4;    // 单片机通过此线向XPT2046发送控制字节
sbit XPT2046_CS=P3^5;     // 片选
sbit XPT2046_DCLK=P3^6;   // 时钟，单片机产生，用于同步数据
sbit XPT2046_DOUT=P3^7;   // XPT2046通过此线向单片机返回ADC转换结果

void Delay10us()		//@11.0592MHz
{
    unsigned char i;
    i = 25;
    while (--i);
}

/**
 * @brief 读取XPT2046的AD值
 * @param Command 命令字
 * @retval AD转换后的数字量，12位模式返回0~4095
 */
unsigned int XPT2046_ReadAD(unsigned char Command)
{
    unsigned char i;
    unsigned int Data = 0;

    //操作前先确保CS为高，维持一段时间，进行一次“软复位”
    XPT2046_CS = 1;
    XPT2046_DCLK = 0; // 时钟线保持低电平
    Delay(1); // 短暂延时

    XPT2046_CS = 0;    //片选信号拉低，开始一次传输

    // 1. 发送命令字 (8bit)
    for(i=0; i<8; i++)
    {
        XPT2046_DIN = Command & (0x80>>i);
        XPT2046_DCLK = 1;
        Delay(1);
        XPT2046_DCLK = 0;
    }

     for(i=0; i<2; i++) 
    {
        XPT2046_DCLK = 1;
        Delay10us();
        XPT2046_DCLK = 0;
        Delay10us();
    }

    //读取16位数据
    for(i=0; i<16; i++)
    {
        XPT2046_DCLK = 1;
        Delay10us();
        Data <<= 1;
        if(XPT2046_DOUT) {
            Data |= 0x01;
        }
        XPT2046_DCLK = 0;
        Delay10us();
    }

    //读取完成后，严格结束本次操作
    XPT2046_CS = 1;
    // 确保DIN在空闲时为低电平，避免干扰
    XPT2046_DIN = 0; 

    //丢弃低4位（后4位是无效位），保留高12位
    Data >>= 4; 
    Data &= 0x0FFF;

    return Data; // 直接返回，值已经是8位或12位
}