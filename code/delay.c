#include "delay.h"
unsigned char a,b;
void Delay_xms(unsigned int p)
{
	for(p;p>0;p--)
	{
		for(b=10;b>0;b--)
		{
		for(a=1;a>0;a--);
		}
	}
}


void Delay_1ms()
{
;
}


