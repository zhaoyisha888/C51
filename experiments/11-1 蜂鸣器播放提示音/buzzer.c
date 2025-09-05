#include <REGX52.h>
#include <INTRINS.H>

//蜂鸣器端口
sbit Buzzer = P2^5;      //原理图为旧版P1^5

unsigned int i;

/**
 * @brief 蜂鸣器私有延时函数，延时500us
 * @note 制造一个 0.5ms 的延时，作为无源蜂鸣器方波周期的一半。
 * @param 无
 * @retval 无
 */
void Buzzer_Delay500us()	//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 227;
	while (--i);
}

/**
 * @brief 蜂鸣器发声时长
 * @note 调用 Buzzer_SoundTime(1000); 会循环 2000 次，每次 500us → 总共 1000ms（1秒）。
 * 在这一秒钟里，P2.5 会不断翻转输出，频率大约 = 1 / (2 * 0.0005s) = 1000Hz，蜂鸣器就能发出约 1kHz 的声音。
 * @param x_ms 发生时长，单位：ms
 * @note 每次循环延时0.5ms，所以 x_ms 要循环 2 次才等于 1ms  
 * @retval 无
 */
void Buzzer_SoundTime(unsigned int x_ms)
{
    for(i = 0;i < x_ms*2; i ++)
    {
        Buzzer = ~Buzzer; 
        Buzzer_Delay500us();
    }
}