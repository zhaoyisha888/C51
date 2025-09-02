#include <REGX52.H>

/**
 * @brief 定时器0初始化  1ms@11.0592MHz
 * @param None
 * @retval None
 */
void Timer0_Init()
{
    // TMOD = 0x01;   
    //与或式赋值
    TMOD &= 0xF0; //低四位清零，高四位保持不变
    TMOD |= 0x01; //最低位设为1，高四位保持不变
    TF0 = 0;
    TR0 = 1;
    TH0 = 0xFC;
    TL0 = 0x66;
    ET0 = 1;
    EA = 1;
    PT0 = 0;
}


/**
 * @brief 定时器0的中断服务函数模板
 * @param None
 * @retval None
 */

// void Timer0_Routine() interrupt 1    
// {
//     static unsigned int T0Count;
//     TH0 = 0xFC;
//     TL0 = 0x66;
//     T0Count ++;
//     if(T0Count >= 1000)
//     {
//         T0Count = 0;
//         P2_0 ~= P2_0;
//     }
// }
