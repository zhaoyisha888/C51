#include <REGX52.H>
#include "timer0.h"
#include "delay.h"

sbit Buzzer = P2^5;

// ���ĺ궨�� 
#define SPEED 500   // �ķ�������׼ʱ��(ms)���Ŀ����ֻ�����

// === ���ױ� ===
unsigned int FrequencyTable[] = {
    0,      // 0:��ֹ��
    262,294,330,349,392,440,494,    // 1~7: ���� C D E F G A B
    523,587,659,698,784,880,988,    // 8~14: ���� C D E F G A B
    131,147,165,175,196,220,247     // 15~21: ���� C D E F G A B
};

// === С���� ===
// {����, ʱֵ}  (ʱֵ=���������ķ�ĸ��4=�ķ�������2=����������8=�˷�����)
unsigned char code Song[][2] = {
    {1,4},{1,4},{5,4},{5,4},{6,4},{6,4},{5,2},  // 1 1 5 5 6 6 5
    {4,4},{4,4},{3,4},{3,4},{2,4},{2,4},{1,2},  // 4 4 3 3 2 2 1

    {5,4},{5,4},{4,4},{4,4},{3,4},{3,4},{2,2},  // 5 5 4 4 3 3 2
    {5,4},{5,4},{4,4},{4,4},{3,4},{3,4},{2,2},  // 5 5 4 4 3 3 2

    {1,4},{1,4},{5,4},{5,4},{6,4},{6,4},{5,2},  // 1 1 5 5 6 6 5
    {4,4},{4,4},{3,4},{3,4},{2,4},{2,4},{1,2}   // 4 4 3 3 2 2 1
};

unsigned int reload;   // ��ǰƵ�ʶ�Ӧ�Ķ�ʱ��װ��ֵ
unsigned char SongIndex = 0;   // ��ǰ���ŵ����������


/**
 * @brief ���㶨ʱ��װ��ֵ
 * @param freq Ҫ���ŵ�Ƶ�ʣ���λHz
 * @retval ��ʱ��װ��ֵ
 */
unsigned int GetReloadValue(unsigned int freq)
{
    if(freq == 0) return 0;  // ��ֹ��
    return 65536 - (11059200/12) / (2*freq);
}

/**
 * @brief ��������
 * @param note ������ţ�0=��ֹ����1~21=����C~����B
 * @param beat ʱֵ��4=�ķ�������2=����������8=�˷�����
 * @retval ��
 */
void Music_Play(unsigned char note, unsigned char beat)
{
    unsigned int time = SPEED * 4 / beat;  // ʱ�� = SPEED �� (4/beat)

    reload = GetReloadValue(FrequencyTable[note]);

    Delay(time * 0.9);   // ���� 90% ʱ�䷢��
    reload = 0;          // �ط�����
    Delay(time * 0.1);   // �� 10% �������������
}

void main()
{
    Timer0_Init();
    while(1)
    {
        for(SongIndex=0; SongIndex<sizeof(Song)/2; SongIndex++)
        {
            Music_Play(Song[SongIndex][0], Song[SongIndex][1]);
        }
    }
}

/**
 * @brief ��ʱ���жϣ���������
 * @param ��
 * @retval ��
 */
void Timer0_Routine() interrupt 1
{
    if(reload == 0)
    {
        Buzzer = 1;  // ����
    }
    else
    {
        TH0 = reload / 256;
        TL0 = reload % 256;
        Buzzer = !Buzzer;
    }
}