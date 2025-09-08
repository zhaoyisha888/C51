#ifndef __NIXIE_H__
#define __NIXIE_H__

void Nixie_Scan(unsigned int location, unsigned int number);
void Nixie_SetBuffer(unsigned int location, unsigned int number);
void Nixie_Loop(void);

#endif
