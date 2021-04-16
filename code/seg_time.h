
#ifndef _SEG_TIME_H_
#define _SEG_TIME_H_
//该源程序采用定时计数器来实现动态显示的延时，可解决执行其它程序时数码管黑屏现象
#include <reg51.h>
#define Duan_Port  P1   //数码管段码引脚

//#define delay_time 19 	//显示延时时间

sbit wei1=P2^4;    //数码管位码引脚
sbit wei2=P2^5;		 //数码管位码引脚
sbit wei3=P2^6;		 //数码管位码引脚
sbit wei4=P2^7;		 //数码管位码引脚


void Time0_Init();
void Time1_IRQ(void);
/** 切换显示内容       数据               模式             延时时间    **/
void Display_T(unsigned int dat ,unsigned char n , unsigned char delay_ms);
#endif
