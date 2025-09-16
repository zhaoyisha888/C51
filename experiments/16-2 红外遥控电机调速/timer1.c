#include <REGX52.H>

/**
 * @brief 定时器1初始化  100us@11.0592MHz
 * @param None
 * @retval None
 */
void Timer1_Init()
{
    // TMOD = 0x01;   
    //与或式赋值
    TMOD &= 0x0F; 
    TMOD |= 0x10; 
    TF1 = 0;
    TR1 = 1;
    //驱动电机一般来说越快越稳定，不然容易抖动
    TL1 = 0xA4;		
    TH1 = 0xFF;		
    ET1 = 1;
    EA = 1;
    PT1 = 0;
}


/**
 * @brief 定时器0的中断服务函数模板
 * @note 中断函数与主函数耦合高，使用时要复制到主函数里
 * @note 定时器0溢出时被自动调用，大概每 1ms 进入一次
 * @param None
 * @retval None
 */

// void Timer1_Routine() interrupt 3   
// {
//     static unsigned int T1Count;
//     TL1 = 0xA4;		
//     TH1 = 0xFF;		
//     T1Count ++;
//     if(T1Count >= 1000)
//     {
//         T1Count = 0;
//         /*
//         code
//         */
//     }
// }
