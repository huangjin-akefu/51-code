#include <reg51.h>
#ifndef _DS18B20_H_
#define _DS18B20_H_

/*************管脚配置*************/
sbit DQ=P2^3;

/*************函数声明*************/
/***********底层驱动函数*************/
void Delay_18B20(int x);//延时函数
void delayms(int n);
void Init_DS18B20();////初始化DS18B20
unsigned char Read_Byte();//读一个字节
void Write_Byte(unsigned char dat);//写一个字节

/*********基础应用函数**************/	
double Read_Temp();//返回读取温度 

#endif
