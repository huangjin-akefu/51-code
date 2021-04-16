#include "key.h"
#include "delay.h"
/* 按键1 没有按下返回0，短按返回1，长按返回2*/
unsigned char key1_scan(void)
{
	unsigned char i,dat;
	i=0;dat=0;
	if(key1==0)
	{
		Delay_1ms();
		if(key1==0)
		{
			while((key1==0) && (i<200))
			{Delay_xms(5);i++;}
			
			if(i<200)
				dat=1;
			else
				dat=2;
		}
	}
	return(dat);
}
/* 按键2  没有按下返回0，短按返回1，长按返回2*/
unsigned char key2_scan(void)
{
	unsigned char i,dat;
	i=0;dat=0;
	if(key2==0)
	{
		Delay_1ms();
		if(key2==0)
		{
			while((key2==0) && (i<200)){Delay_xms(3);i++;}
			
			if(i<200)
				dat=1;
			else
				dat=2;
		}
	}
	return(dat);
}
/* 按键3 没有按下返回0，短按返回1，长按返回2*/
unsigned char key3_scan(void)
{
	unsigned char i,dat;
	i=0;dat=0;
	if(key3==0)
	{
		Delay_1ms();
		if(key3==0)
		{
			while((key3==0) && (i<200)){Delay_xms(3);i++;}
			
			if(i<200)
				dat=1;
			else
				dat=2;
		}
	}
	return(dat);
}
/* 按键4 没有按下返回0，短按返回1，长按返回2*/
unsigned char key4_scan(void)
{
	unsigned char i,dat;
	i=0;dat=0;
	if(key4==0)
	{
		Delay_1ms();
		if(key4==0)
		{
			while((key4==0) && (i<200)){Delay_xms(3);i++;}
			
			if(i<200)
				dat=1;
			else
				dat=2;
		}
	}
	return(dat);
}