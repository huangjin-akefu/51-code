#ifndef _KEY_H_
#define _KEY_H_

#include <reg51.h>

sbit key1=P3^2;    //数码管位码引脚
sbit key2=P3^3;		 //数码管位码引脚
sbit key3=P3^4;		 //数码管位码引脚
sbit key4=P3^5;		 //数码管位码引脚

/* 按键1 没有按下返回0，短按返回1，长按返回2*/
unsigned char key1_scan(void);
/* 按键2 没有按下返回0，短按返回1，长按返回2*/
unsigned char key2_scan(void);
/* 按键3 没有按下返回0，短按返回1，长按返回2*/
unsigned char key3_scan(void);
/* 按键4 没有按下返回0，短按返回1，长按返回2*/
unsigned char key4_scan(void);
#endif

