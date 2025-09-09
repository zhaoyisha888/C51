#include <REGX52.H>

sbit LED = P2^0;

void Delay(unsigned int t)
{
    while(t--);
}

void main()
{
    unsigned char Time,i;

    //LED灯不断由暗变亮再变暗，循环此变化过程
    //固定周期（100 个时间单位）
    /**
    * Time=10 → 高电平=10，低电平=90 → 占空比 = 10%。
    * Time=50 → 高电平=50，低电平=50 → 占空比 = 50%。
    * Time=90 → 高电平=90，低电平=10 → 占空比 = 90%。
    */

	while(1)
	{
		for(Time=0;Time<100;Time++)   //LED灯亮度增加，占空比从 0% → 100%
		{
            for(i=0;i<15;i++)       //让 LED 的亮度在当前占空比下保持一小段时间
            {
                LED = 0;            // 点亮 LED（低电平有效）
                Delay(Time);        // 保持一段时间 → 高电平宽度
                LED = 1;            // 熄灭 LED
                Delay(100-Time);    // 保持一段时间 → 低电平宽度
            }
		}
		Delay(50);
		for(Time=100;Time>0;Time--)   //LED灯亮度减少，占空比从 100% → 0%
		{
			for(i=0;i<15;i++)
            {
                LED = 0;
			    Delay(Time);
			    LED = 1;
			    Delay(100-Time);
            }
		}
	}
}