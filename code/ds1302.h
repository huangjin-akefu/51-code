#ifndef __DS1302_H_
#define __DS1302_H_

//---包含头文件---//
#include <reg51.h>
#include <intrins.h>

/*****************DS1302管脚配置********************/
sbit DSIO=P1^2;
sbit RST=P1^0;
sbit SCLK=P1^1;

/*****************全局变量声明********************/
extern unsigned char TIME[7];   //加入全局变量，存放读取的时间

/*****************底层驱动函数********************/
void Ds1302_Write(unsigned char add, unsigned char dat);
unsigned char Ds1302_Read(unsigned char add);
unsigned char BCD_DEC(unsigned char dat);
unsigned char DEC_BCD(unsigned char dat);

/*****************基础应用函数********************/
void Ds1302_Init_Time(unsigned char *p);//重置时间
void Ds1302_Read_Time();//读取时间
void Ds1302_TimeAlys();////日期时间数据判断



#endif
