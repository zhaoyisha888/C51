#include <REGX52.H>
#include "onewire.h"

#define DS18B20_SKIP_ROM         0xCC  // 跳过 ROM 指令（单总线时使用，不做设备地址匹配）
#define DS18B20_CONVERT_T         0x44  // 启动温度转换命令
#define DS18B20_READ_SCRATCHPAD  0xBE  // 读取 Scratchpad 寄存器命令

/**
 * @brief 启动 DS18B20 温度转换
 * @note 
 * 1. 发送复位脉冲并等待 DS18B20 应答；
 * 2. 发送 "Skip ROM" (0xCC)，跳过设备地址选择（适用于总线上只有一个传感器的情况）；
 * 3. 发送 "Convert T" (0x44)，通知 DS18B20 开始进行温度转换；
 * 4. 转换完成需要一定时间（取决于分辨率，9~12位约 94ms~750ms）。
 * 5. 转换完成后，DS18B20 会将温度数据存储在其内部的暂存寄存器中。
 * @retval 无
 */
void DS18B20_ConvertT(void)
{
	OneWire_Init();                          // 跳过 ROM，直达所有设备
    OneWire_SendByte(DS18B20_SKIP_ROM);      // 跳过 ROM，直达所有设备
    OneWire_SendByte(DS18B20_CONVERT_T);      // 启动温度转换

}

/**
 * @brief 读取 DS18B20 温度
 * @note 
 * 1. 发送复位脉冲并等待应答；
 * 2. 发送 "Skip ROM" (0xCC)，跳过地址匹配；
 * 3. 发送 "Read Scratchpad" (0xBE)，开始读取寄存器内容；
 按照 DS18B20 数据格式（默认 12 位分辨率，每位 = 0.0625℃）换算温度。
 * @retval float Temperature 温度值（单位：℃）
 */
float DS18B20_ReadT(void)
{
    unsigned char T_LSB, T_MSB;
    int temp;
    float Temperature;

    OneWire_Init();                               // 总线复位
	OneWire_SendByte(DS18B20_SKIP_ROM);           // 跳过 ROM
    OneWire_SendByte(DS18B20_READ_SCRATCHPAD);    // 读取 Scratchpad 寄存器

    T_LSB = OneWire_ReceiveByte();    // 读取温度低字节
    T_MSB = OneWire_ReceiveByte();    // 读取温度高字节
    temp = T_MSB << 8 | T_LSB;        // 合成 16 位数据
    Temperature = temp / 16.0;     

    return Temperature;
}