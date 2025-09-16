#include <INTRINS.H>
void Delay(unsigned int x_ms)	//@11.0592MHz
{
	unsigned char i, j;
	while(x_ms)
	{
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
		x_ms--;
	}
}