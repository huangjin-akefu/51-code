#ifndef __DS1302_H_
#define __DS1302_H_

//---����ͷ�ļ�---//
#include <reg51.h>
#include <intrins.h>

/*****************DS1302�ܽ�����********************/
sbit DSIO=P1^2;
sbit RST=P1^0;
sbit SCLK=P1^1;

/*****************ȫ�ֱ�������********************/
extern unsigned char TIME[7];   //����ȫ�ֱ�������Ŷ�ȡ��ʱ��

/*****************�ײ���������********************/
void Ds1302_Write(unsigned char add, unsigned char dat);
unsigned char Ds1302_Read(unsigned char add);
unsigned char BCD_DEC(unsigned char dat);
unsigned char DEC_BCD(unsigned char dat);

/*****************����Ӧ�ú���********************/
void Ds1302_Init_Time(unsigned char *p);//����ʱ��
void Ds1302_Read_Time();//��ȡʱ��
void Ds1302_TimeAlys();////����ʱ�������ж�



#endif
