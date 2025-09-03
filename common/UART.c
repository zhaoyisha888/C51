#include <REGX52.H>

/**
 * @brief 初始化串口
 * @param 无
 * @retval 无
 */
void UART_Init()	    //4800bps@11.0592MHz
{
    PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//允许接收，0x40只发送不接收
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xFA;			//设置定时初始值
	TH1 = 0xFA;			//设置定时重载值
	ET1 = 0;			//禁止定时器中断
	TR1 = 1;			//定时器1开始计时
    EA = 1;             //接收时启动所有中断，仅发送可注释
    ES = 1;             //接收时启动串口中断，仅发送可注释
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

/**
 * @brief 串口中断服务函数
 * @param 无
 * @retval 无
 */
// void UART_Routine()  interrupt 4
// {
// 	if(RI == 1)         //发送和接收都会触发中断，这里须判断接收中断
// 	{
//         /*
//         code        
//         */
// 		RI = 0;
// 	}
// }