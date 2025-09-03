#include <REGX52.H>

/**
 * @brief 初始化串口
 * @param 无
 * @retval 无
 */
void UART_Init()	    //4800bps@11.0592MHz
{
    PCON &= 0x7F;		//波特率不倍速
	SCON = 0x40;		//8位数据,可变波特率
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xFA;			//设置定时初始值
	TH1 = 0xFA;			//设置定时重载值
	ET1 = 0;			//禁止定时器中断
	TR1 = 1;			//定时器1开始计时

}

/**
 * @brief 串口发送一个字节数据
 * @param Byte 要发送的一个字节数据
 * @retval 无
 */
void UART_SendByte(unsigned char Byte)
{
    SBUF = Byte;
    while(TI == 0);     //监测到数据，TI置1，即发送
	TI = 0;             //软件复位TI
}