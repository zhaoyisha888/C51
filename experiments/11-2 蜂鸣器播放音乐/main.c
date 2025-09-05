#include <REGX52.H>
#include "timer0.h"
#include "delay.h"

sbit Buzzer = P2^5;

// 节拍宏定义 
#define SPEED 500   // 四分音符基准时长(ms)，改快改慢只调这个

// === 音阶表 ===
unsigned int FrequencyTable[] = {
    0,      // 0:休止符
    262,294,330,349,392,440,494,    // 1~7: 中音 C D E F G A B
    523,587,659,698,784,880,988,    // 8~14: 高音 C D E F G A B
    131,147,165,175,196,220,247     // 15~21: 低音 C D E F G A B
};

// === 小星星 ===
// {音符, 时值}  (时值=几分音符的分母，4=四分音符，2=二分音符，8=八分音符)
unsigned char code Song[][2] = {
    {1,4},{1,4},{5,4},{5,4},{6,4},{6,4},{5,2},  // 1 1 5 5 6 6 5
    {4,4},{4,4},{3,4},{3,4},{2,4},{2,4},{1,2},  // 4 4 3 3 2 2 1

    {5,4},{5,4},{4,4},{4,4},{3,4},{3,4},{2,2},  // 5 5 4 4 3 3 2
    {5,4},{5,4},{4,4},{4,4},{3,4},{3,4},{2,2},  // 5 5 4 4 3 3 2

    {1,4},{1,4},{5,4},{5,4},{6,4},{6,4},{5,2},  // 1 1 5 5 6 6 5
    {4,4},{4,4},{3,4},{3,4},{2,4},{2,4},{1,2}   // 4 4 3 3 2 2 1
};

unsigned int reload;   // 当前频率对应的定时器装载值
unsigned char SongIndex = 0;   // 当前播放到的音符序号


/**
 * @brief 计算定时器装载值
 * @param freq 要播放的频率，单位Hz
 * @retval 定时器装载值
 */
unsigned int GetReloadValue(unsigned int freq)
{
    if(freq == 0) return 0;  // 休止符
    return 65536 - (11059200/12) / (2*freq);
}

/**
 * @brief 播放音符
 * @param note 音符序号，0=休止符，1~21=中音C~高音B
 * @param beat 时值，4=四分音符，2=二分音符，8=八分音符
 * @retval 无
 */
void Music_Play(unsigned char note, unsigned char beat)
{
    unsigned int time = SPEED * 4 / beat;  // 时长 = SPEED × (4/beat)

    reload = GetReloadValue(FrequencyTable[note]);

    Delay(time * 0.9);   // 保持 90% 时间发声
    reload = 0;          // 关蜂鸣器
    Delay(time * 0.1);   // 留 10% 间隔，避免连音
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
 * @brief 定时器中断，产生方波
 * @param 无
 * @retval 无
 */
void Timer0_Routine() interrupt 1
{
    if(reload == 0)
    {
        Buzzer = 1;  // 不响
    }
    else
    {
        TH0 = reload / 256;
        TL0 = reload % 256;
        Buzzer = !Buzzer;
    }
}