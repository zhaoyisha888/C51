#include <REGX52.H>
#include <INTRINS.H>

sbit OneWire_DQ=P3^7;

/**
 * @brief 初始化 OneWire 总线（复位 + 等待从机应答）
 * @note 主机步骤：
 *       1. 拉低总线 ≥480us，表示复位脉冲；
 *       2. 释放总线，延时 15~60us；
 *       3. 从机会在 60~240us 内拉低总线作为存在脉冲（Presence Pulse）。
 * @retval 0: 检测到存在脉冲（初始化成功）;1: 无应答（初始化失败/未连接从机）
 */
unsigned char OneWire_Init(void)
{
    unsigned char i;
    unsigned char ACKBit;

    EA=0;
	OneWire_DQ=1;
    OneWire_DQ=0;
    //等待500us
	i = 230;while (--i);

    OneWire_DQ=1;
	//等待70us
	i = 32;while (--i);

    ACKBit = OneWire_DQ;

    //等待500us
	i = 230;while (--i);
    EA=1;

    return ACKBit;
}

/**
 * @brief 发送 1 位数据到总线
 * @param Bit 要发送的位值（0 或 1）
 * @note 发送时序：
 *       - 写 0：主机拉低总线 60us 左右，再释放；
 *       - 写 1：主机拉低总线 1~15us 后立即释放，整个时隙约 60us。
 * @retval 无
 */
void OneWire_SendBit(unsigned char Bit)
{
    unsigned char i;

    EA=0;
    OneWire_DQ=0;
    //等待10us
	i = 4;while (--i);

    OneWire_DQ=Bit;
    //等待50us
    i = 22;while (--i);

    OneWire_DQ=1;
    EA=1;
}

/**
 * @brief 从总线接收 1 位数据
 * @note 读取时序：
 *       1. 主机拉低总线 ≥1us 作为起始；
 *       2. 释放总线，延时 15us 左右；
 *       3. 采样总线电平：低=0，高=1；
 *       4. 整个读时隙持续约 60us。
 * @retval Bit 接收到的位值
 */
unsigned char OneWire_ReceiveBit(void)
{
    unsigned char i;
    unsigned char Bit;

    EA=0;
    OneWire_DQ=0;
    //等待5us
	i = 2;while (--i);

    OneWire_DQ=1;
    //等待5us
    i = 2;while (--i);

    Bit = OneWire_DQ;
    //等待50us
    i = 22;while (--i);
    EA=1;
	
    return Bit;
}

/**
 * @brief 发送 1 字节数据
 * @param Byte 要发送的数据
 * @note 按位依次发送，低位在前（LSB First）。
 */
void OneWire_SendByte(unsigned char Byte)
{
    unsigned char i;

    for(i=0;i<8;i++)
    {
        OneWire_SendBit(Byte & (0x01<<i));
    }
}

/**
 * @brief 接收 1 字节数据
 * @note 按位依次接收，低位在前（LSB First）。
 * @retval 接收到的字节
 */
unsigned char OneWire_ReceiveByte(void)
{
    unsigned char i;
    unsigned char Byte=0x00;

    for(i=0;i<8;i++)
    {
        if(OneWire_ReceiveBit())
        {
            Byte |= (0x01 << i);
        }
    }

    return Byte;
}