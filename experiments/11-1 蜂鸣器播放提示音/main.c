#include <REGX52.H>
#include "nixie.h"
#include "key.h"
#include "buzzer.h"

unsigned char KeyNumber;

void main()
{
	while(1)
	{
		KeyNumber = Key();
		if(KeyNumber)
		{
			Nixie(1,KeyNumber);
			Buzzer_SoundTime(1000);           //·äÃùÆ÷Ïì1Ãë
			
		}
	}
}