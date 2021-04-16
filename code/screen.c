#include "screen.h"

void screen_1(unsigned int bj,unsigned int xh)
{
	LCD1602_string(0,0,"BJ:YD");
	LCD1602_string(1,0,"XH:");
	LCD1602_2num(0,5,bj);
	LCD1602_2num(1,3,xh);
}

void screen_2(unsigned char TIME[],unsigned char temp)
{
	LCD1602_string(0,0,"RQ");
	LCD1602_2num(0,3,20);
	LCD1602_timenum(0,5,TIME[0],2);
	LCD1602_string(0,7,"-");
	LCD1602_timenum(0,5,TIME[1],2);
	LCD1602_string(0,10,"-");
	LCD1602_timenum(0,5,TIME[2],2);
	LCD1602_string(0,7,"SJ:");
	LCD1602_timenum(1,3,TIME[3],2);
	LCD1602_string(1,5,":");
	LCD1602_timenum(1,6,TIME[4],2);
	LCD1602_string(1,8,":");
	LCD1602_timenum(1,9,TIME[5],2);
	LCD1602_2num(1,12,temp);
	LCD1602_char(1,14,0xdf);
	LCD1602_char(1,14,'C');
}