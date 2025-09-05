#include <REGX52.h>
#include <INTRINS.H>

//�������˿�
sbit Buzzer = P2^5;      //ԭ��ͼΪ�ɰ�P1^5

unsigned int i;

/**
 * @brief ������˽����ʱ��������ʱ500us
 * @note ����һ�� 0.5ms ����ʱ����Ϊ��Դ�������������ڵ�һ�롣
 * @param ��
 * @retval ��
 */
void Buzzer_Delay500us()	//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 227;
	while (--i);
}

/**
 * @brief ����������ʱ��
 * @note ���� Buzzer_SoundTime(1000); ��ѭ�� 2000 �Σ�ÿ�� 500us �� �ܹ� 1000ms��1�룩��
 * ����һ�����P2.5 �᲻�Ϸ�ת�����Ƶ�ʴ�Լ = 1 / (2 * 0.0005s) = 1000Hz�����������ܷ���Լ 1kHz ��������
 * @param x_ms ����ʱ������λ��ms
 * @note ÿ��ѭ����ʱ0.5ms������ x_ms Ҫѭ�� 2 �βŵ��� 1ms  
 * @retval ��
 */
void Buzzer_SoundTime(unsigned int x_ms)
{
    for(i = 0;i < x_ms*2; i ++)
    {
        Buzzer = ~Buzzer; 
        Buzzer_Delay500us();
    }
}