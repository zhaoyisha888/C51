#include <REGX52.H>

/**
 * @brief 初始化外部中断0
 * @note 下降沿触发，高电平有效，中断优先级高
 * @param None
 * @retval None
 */
void Int0_Init(void)
{
	IT0 = 1;
	IE = 0;
	EX0 = 1;
	EA = 1;
	PX0 = 1;
}

/**
 * @brief 外部中断0中断服务函数
 * @note 按键按下时，number加1
 * @param None
 * @retval None
 */
// void Int0_Routine(void) interrupt 0
// {
// 	    /*
//      code
//      */
// }
