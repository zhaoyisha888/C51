#include <REGX52.H>

//====================定时器0的定时中断模式=======================//
/**
 * @brief 定时器0初始化  1ms@11.0592MHz
 * @param None
 * @retval None
 */
void Timer0_InitTimer()
{
    // TMOD = 0x01;   
    //与或式赋值
    TMOD &= 0xF0; //低四位清零，高四位保持不变
    TMOD |= 0x01; //最低位设为1，高四位保持不变
    TH0 = 0xFC;
    TL0 = 0x66;
    TF0 = 0;
    TR0 = 1;         //定时器0开始计时
    ET0 = 1; 
    EA = 1;
    PT0 = 0;
}

/**
 * @brief 定时器0的中断服务函数模板
 * @note 中断函数与主函数耦合高，使用时要复制到主函数里
 * @note 定时器0溢出时被自动调用，大概每 1ms 进入一次
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
//         /*
//         code
//         */
//     }
// }


//====================定时器0设置计数=======================//
/**
 * @brief 定时器0的计数模式初始化
 * @param None
 * @retval None
 */
void Timer0_InitCounter()
{
    // TMOD = 0x01;   
    //与或式赋值
    TMOD &= 0xF0; //低四位清零，高四位保持不变
    TMOD |= 0x01; //最低位设为1，高四位保持不变
    // TH0 = 0xFC;
    // TL0 = 0x66;
    TH0 = 0;
    TL0 = 0;
    TF0 = 0;
    TR0 = 0;        //定时器0不计时
}

/**
 * @brief 定时器0设置计数器值
 * @param Value 要设置的计数器值，范围：0~65535
 * @retval None
 */
void Timer0_SetCounter(unsigned int Value)
{
    TH0 = Value/256;
    TL0 = Value%256;
}

/**
 * @brief 定时器0获取计数器值
 * @param None
 * @retval 计数器值，范围：0~65535
 */
unsigned int Timer0_GetCounter(void)
{
    return (TH0 << 8) | TL0;
}

/**
 * @brief 定时器0启动停止控制
 * @param Flag 启动停止标志  0：停止计数 1：开始计数
 * @retval None
 */
void Timer0_RunCounter(unsigned char Flag)
{
    TR0 = Flag;
}
