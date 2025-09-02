#include <REGX52.H>

/**
 * @brief ��ʱ��0��ʼ��  1ms@11.0592MHz
 * @param None
 * @retval None
 */
void Timer0_Init()
{
    // TMOD = 0x01;   
    //���ʽ��ֵ
    TMOD &= 0xF0; //����λ���㣬����λ���ֲ���
    TMOD |= 0x01; //���λ��Ϊ1������λ���ֲ���
    TF0 = 0;
    TR0 = 1;
    TH0 = 0xFC;
    TL0 = 0x66;
    ET0 = 1;
    EA = 1;
    PT0 = 0;
}


/**
 * @brief ��ʱ��0���жϷ�����ģ��
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
