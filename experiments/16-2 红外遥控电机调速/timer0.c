#include <REGX52.H>

//====================��ʱ��0�Ķ�ʱ�ж�ģʽ=======================//
/**
 * @brief ��ʱ��0��ʼ��  1ms@11.0592MHz
 * @param None
 * @retval None
 */
void Timer0_InitTimer()
{
    // TMOD = 0x01;   
    //���ʽ��ֵ
    TMOD &= 0xF0; //����λ���㣬����λ���ֲ���
    TMOD |= 0x01; //���λ��Ϊ1������λ���ֲ���
    TH0 = 0xFC;
    TL0 = 0x66;
    TF0 = 0;
    TR0 = 1;         //��ʱ��0��ʼ��ʱ
    ET0 = 1; 
    EA = 1;
    PT0 = 0;
}

/**
 * @brief ��ʱ��0���жϷ�����ģ��
 * @note �жϺ�������������ϸߣ�ʹ��ʱҪ���Ƶ���������
 * @note ��ʱ��0���ʱ���Զ����ã����ÿ 1ms ����һ��
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


//====================��ʱ��0���ü���=======================//
/**
 * @brief ��ʱ��0�ļ���ģʽ��ʼ��
 * @param None
 * @retval None
 */
void Timer0_InitCounter()
{
    // TMOD = 0x01;   
    //���ʽ��ֵ
    TMOD &= 0xF0; //����λ���㣬����λ���ֲ���
    TMOD |= 0x01; //���λ��Ϊ1������λ���ֲ���
    // TH0 = 0xFC;
    // TL0 = 0x66;
    TH0 = 0;
    TL0 = 0;
    TF0 = 0;
    TR0 = 0;        //��ʱ��0�Ƿ�ʼ��ʱ��0-ֹͣ 1-��ʼ
}

/**
 * @brief ��ʱ��0���ü�����ֵ
 * @param Value Ҫ���õļ�����ֵ����Χ��0~65535
 * @retval None
 */
void Timer0_SetCounter(unsigned int Value)
{
    TH0 = Value/256;
    TL0 = Value%256;
}

/**
 * @brief ��ʱ��0��ȡ������ֵ
 * @param None
 * @retval ������ֵ����Χ��0~65535
 */
unsigned int Timer0_GetCounter(void)
{
    return (TH0 << 8) | TL0;
}

/**
 * @brief ��ʱ��0����ֹͣ����
 * @param Flag ����ֹͣ��־  0��ֹͣ���� 1����ʼ����
 * @retval None
 */
void Timer0_RunCounter(unsigned char Flag)
{
    TR0 = Flag;
}
