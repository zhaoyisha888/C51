#include <REGX52.H>

sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;

//发送接收都以主机为主体，操作的一直都是主机

/**
 * @brief I2C发送起始信号
 * @note 起始信号：SCL 高电平期间，SDA 从高电平切换到低电平
 * @param 无
 * @retval 无
 */
void I2C_Start(void)
{
    I2C_SDA = 1;
    I2C_SCL = 1;
    I2C_SDA = 0;
    I2C_SCL = 0;
}

/**
 * @brief I2C发送停止信号
 * @note 停止信号：SCL 高电平期间，SDA 从低电平切换到高电平
 * @param 无
 * @retval 无
 */
void I2C_Stop(void)
{
    I2C_SDA = 0;
    I2C_SCL = 1;
    I2C_SDA = 1;
}

/**
 * @brief I2C发送字节
 * @note 发送字节：SCL 低电平期间，SDA 输出字节数据的每一位
 * @param Byte 要发送的字节数据
 * @retval 无
 */
void I2C_SendByte(unsigned char Byte)
{
    unsigned char i;
    for(i = 0; i < 8; i ++)
    {
        I2C_SDA = Byte & (0x80 >> i);
        I2C_SCL = 1;
        I2C_SCL = 0;
    }
}

/**
 * @brief I2C接收字节
 * @note 接收字节：SCL 低电平期间，SDA 输入字节数据的每一位
 * @param 无
 * @retval Byte 接收到的字节数据
 */
unsigned char I2C_ReceiveByte(void)
{
    unsigned char Byte = 0x00,i;
    I2C_SDA = 1;
    for(i = 0; i < 8; i ++)
    {
        I2C_SCL = 1;
        if(I2C_SDA)
        {
            Byte |= (0x80 >> i);
        }
        I2C_SCL = 0;
    }
    return Byte;
}

/**
 * @brief I2C发送应答位
 * @note 发送应答：SCL 低电平期间，SDA 输出应答位
 * @param ACKBit 要发送的应答位，0 表示应答，1 表示非应答
 * @retval 无
 */
void I2C_SendACK(unsigned char ACKBit)
{
    I2C_SDA = ACKBit;
    I2C_SCL = 1;
    I2C_SCL = 0;
}

/**
 * @brief I2C接收应答位
 * @note 接收应答：SCL 低电平期间，SDA 输入应答位
 * @param 无
 * @retval ACKBit 接收到的应答位，0 表示应答，1 表示非应答
 */
unsigned char I2C_ReceiveACK(void)
{
    unsigned char ACKBit;
    I2C_SDA = 1;
    I2C_SCL = 1;
    ACKBit = I2C_SDA;
    I2C_SCL = 0;
    return ACKBit;
}