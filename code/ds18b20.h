#include <reg51.h>
#ifndef _DS18B20_H_
#define _DS18B20_H_

/*************�ܽ�����*************/
sbit DQ=P2^3;

/*************��������*************/
/***********�ײ���������*************/
void Delay_18B20(int x);//��ʱ����
void delayms(int n);
void Init_DS18B20();////��ʼ��DS18B20
unsigned char Read_Byte();//��һ���ֽ�
void Write_Byte(unsigned char dat);//дһ���ֽ�

/*********����Ӧ�ú���**************/	
double Read_Temp();//���ض�ȡ�¶� 

#endif
