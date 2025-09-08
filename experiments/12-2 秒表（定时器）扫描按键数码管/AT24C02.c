#include <REGX52.H>
#include "I2C.h"

//定义从机地址 0xA0为写地址，0xA1为读地址
#define AT24C02_Address  0xA0      

/**
 * @brief AT24C02写入一个字节
 * @param WordAddress 要写入的字节地址
 * @param Data 要写入的字节数据
 * @retval 无
 */
void AT24C02_WriteByte(unsigned char WordAddress,unsigned char Data)
{
    unsigned char ACK;

    I2C_Start();

    //发送从机地址：向某从机写入
    I2C_SendByte(AT24C02_Address);
    I2C_ReceiveACK();

    //发送字地址：向从机写入字地址
    I2C_SendByte(WordAddress);
    I2C_ReceiveACK();

    //发送数据：向从机写入需要写入的数据
    I2C_SendByte(Data);
    I2C_ReceiveACK();

    I2C_Stop();
}

/**
 * @brief AT24C02读取一个字节
 * @param WordAddress 要读取的字节地址
 * @retval Data 读取到的字节数据
 */
unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
    unsigned char Data;

    I2C_Start();

    //发送从机地址：向某从机写入
    I2C_SendByte(AT24C02_Address);
    I2C_ReceiveACK();

    //发送字地址：向从机写入字地址
    I2C_SendByte(WordAddress);
    I2C_ReceiveACK();

    I2C_Start();

    //发送从机地址：从某从机读出
    I2C_SendByte(AT24C02_Address|0x01);
    I2C_ReceiveACK();

    //接收数据：接收从机发送的数据
    Data = I2C_ReceiveByte();
    I2C_SendACK(1);

    I2C_Stop();

    return Data;
}