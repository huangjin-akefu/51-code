
#ifndef _SEG_TIME_H_
#define _SEG_TIME_H_
//��Դ������ö�ʱ��������ʵ�ֶ�̬��ʾ����ʱ���ɽ��ִ����������ʱ����ܺ�������
#include <reg51.h>
#define Duan_Port  P1   //����ܶ�������

//#define delay_time 19 	//��ʾ��ʱʱ��

sbit wei1=P2^4;    //�����λ������
sbit wei2=P2^5;		 //�����λ������
sbit wei3=P2^6;		 //�����λ������
sbit wei4=P2^7;		 //�����λ������


void Time0_Init();
void Time1_IRQ(void);
/** �л���ʾ����       ����               ģʽ             ��ʱʱ��    **/
void Display_T(unsigned int dat ,unsigned char n , unsigned char delay_ms);
#endif
