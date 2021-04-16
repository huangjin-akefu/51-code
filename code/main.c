#include "reg51.h"
#include "lcd1602.h"
#include "ds1302.h"
#include "key.h"
#include "delay.h" 
#include "screen.h"
#include "display.h"

int LCD1602_Gbiao(unsigned char hang,unsigned char lie,unsigned char dat);
unsigned char key3_mode,temp=25,n=0,key1_mode,key1_time,SetPlace,i;
unsigned int bj=1801,xh=1236,flag;

extern unsigned char TIME;


void main()
{
	LCD1602_Init();
	while(1)
	{
		Ds1302_Read_Time();
		if(key4_scan()!=0)
		{
			key1_mode++;
			key1_mode%=3;	
		}
			switch(key1_mode) 
		  {
		 		case 0:information_display();break;
				case 1:
	    }	
   }
	  
	 
}
