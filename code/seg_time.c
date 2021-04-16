#include "seg_time.h"
#include "delay.h"
unsigned char t_cnt=0,ys=4;
unsigned char dis_num[4]={0};
unsigned char code segdat[ ]=
 {0xC0,/*0*/
	0xF9,/*1*/
	0xA4,/*2*/
	0xB0,/*3*/
	0x99,/*4*/
	0x92,/*5*/
	0x82,/*6*/
	0xF8,/*7*/
	0x80,/*8*/
	0x90,/*9*/
	0x88,/*A*/
	0x83,/*b*/
	0xC6,/*C*/
	0xA1,/*d*/
	0x86,/*E*/
	0x8E,/*F*/
	0xE3,/*u*/};

void Time0_Init()
{
	TMOD|=0x10;
	TH1=(65536-1000*ys)/256;
	TL1=(65536-1000*ys)%256;
	TF1=0;
	TR1=1;//定时器
	ET1=1;
	EA=1;
}
/** 切换显示内容       数据               模式             延时时间    **/
void Display_T(unsigned int dat ,unsigned char n , unsigned char delay_ms)
{
	switch(n)
		{
			case 0:dis_num[0]=segdat[dat/1000%10];
						dis_num[1]=segdat[dat/100%10];
						dis_num[2]=segdat[dat/10%10];
						dis_num[3]=segdat[dat%10];break;  //模式0，显示整数
			case 1:dis_num[0]=segdat[dat/1000%10];
						dis_num[1]=segdat[dat/100%10]&0x7f;
						dis_num[2]=segdat[dat/10%10];
						dis_num[3]=segdat[dat%10];break;//模式1，显示两位小数
			case 2:dis_num[0]=segdat[dat/10%10];
						dis_num[1]=segdat[dat%10];
						dis_num[2]=segdat[16];
						dis_num[3]=segdat[15];break;//模式2，显示特殊符号
			default: break;
		}	
	ys=delay_ms;
}

void Time1_IRQ(void) interrupt 3
{
	TH1=(65536-1000*ys)/256;
	TL1=(65536-1000*ys)%256;
	t_cnt++;
	t_cnt=t_cnt%4;
	
	Duan_Port=0xff;//消影
	switch(t_cnt)
	{
		case 0:		Duan_Port=dis_num[0];//送段码数据
							wei4=1;
							wei1=0; //第一位显示
							break;
		case 1:		Duan_Port=dis_num[1];//送段码数据
						  wei1=1;
							wei2=0; //第2位显示
							break;
		case 2:		Duan_Port=dis_num[2];//送段码数据
						  wei2=1;
							wei3=0; //第3位显示
							break;
		case 3:		Duan_Port=dis_num[3];//送段码数据
						  wei3=1;
							wei4=0; //第4位显示
							break;
	}
	
}