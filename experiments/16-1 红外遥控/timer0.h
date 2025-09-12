#ifndef __TIMER0_H__
#define __TIMER0_H_

void Timer0_InitTimer();
void Timer0_InitCounter();
void Timer0_SetCounter(unsigned int Value);
unsigned int Timer0_GetCounter(void);
void Timer0_RunCounter(unsigned char Flag);

#endif
