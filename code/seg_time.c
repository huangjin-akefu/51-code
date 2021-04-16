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
	TR1=1;//��ʱ��
	ET1=1;
	EA=1;
}
/** �л���ʾ����       ����               ģʽ             ��ʱʱ��    **/
void Display_T(unsigned int dat ,unsigned char n , unsigned char delay_ms)
{
	switch(n)
		{
			case 0:dis_num[0]=segdat[dat/1000%10];
						dis_num[1]=segdat[dat/100%10];
						dis_num[2]=segdat[dat/10%10];
						dis_num[3]=segdat[dat%10];break;  //ģʽ0����ʾ����
			case 1:dis_num[0]=segdat[dat/1000%10];
						dis_num[1]=segdat[dat/100%10]&0x7f;
						dis_num[2]=segdat[dat/10%10];
						dis_num[3]=segdat[dat%10];break;//ģʽ1����ʾ��λС��
			case 2:dis_num[0]=segdat[dat/10%10];
						dis_num[1]=segdat[dat%10];
						dis_num[2]=segdat[16];
						dis_num[3]=segdat[15];break;//ģʽ2����ʾ�������
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
	
	Duan_Port=0xff;//��Ӱ
	switch(t_cnt)
	{
		case 0:		Duan_Port=dis_num[0];//�Ͷ�������
							wei4=1;
							wei1=0; //��һλ��ʾ
							break;
		case 1:		Duan_Port=dis_num[1];//�Ͷ�������
						  wei1=1;
							wei2=0; //��2λ��ʾ
							break;
		case 2:		Duan_Port=dis_num[2];//�Ͷ�������
						  wei2=1;
							wei3=0; //��3λ��ʾ
							break;
		case 3:		Duan_Port=dis_num[3];//�Ͷ�������
						  wei3=1;
							wei4=0; //��4λ��ʾ
							break;
	}
	
}