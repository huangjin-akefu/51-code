#include "display.h"

#include "lcd1602.h"

void information_display()
{
	LCD1602_string(0,0,"BJ:DS");
	LCD1602_string(1,0,"XH:");
	LCD1602_2num(0,5,19);
	LCD1602_2num(1,3,12);
}
void Time_display()
{
	
	
	
}

