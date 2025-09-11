#ifndef __XPT2046_H__
#define __XPT2046_H__

// 控制字结构：S (1) | A2 A1 A0 (通道) | MODE (1=8位) | SER/DFR (1=单端) | PD1 PD0 (电源模式)
// 通道定义 (A2, A1, A0)：
#define XPT2046_XP_8    0x9C   // 1001 1100 AIN0 8位 单端 始终供电 
#define XPT2046_YP_8    0xDC   // 1101 1100 AIN1 8位 单端 始终供电 
#define XPT2046_VBAT_8  0xAC   // 1010 1100 AIN2 8位 单端 始终供电 
#define XPT2046_AUX_8   0xEC   // 1110 1100 AIN3 8位 单端 始终供电 

// 12位模式命令字（MODE=0）
#define XPT2046_XP_12   0x94   // 1001 0100 AIN0 12位 单端 始终供电
#define XPT2046_YP_12   0xD4   // 1101 0100 AIN1 12位 单端 始终供电
#define XPT2046_VBAT_12 0xA4   // 1010 0100 AIN2 12位 单端 始终供电
#define XPT2046_AUX_12  0xE4   // 1110 0100 AIN3 12位 单端 始终供电

unsigned int XPT2046_ReadAD(unsigned char Command);

#endif