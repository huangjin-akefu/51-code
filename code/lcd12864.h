#ifndef __LCD12864_H__
#define __LCD12864_H__
#include <reg51.h>

/*********************12864管脚配置*************************/
#define LCD_Port P0
sbit  RS=P1^5;
sbit  RW=P1^6;
sbit   E=P1^7;
sbit CS1=P2^0;			   //片选信号
sbit CS2=P2^1;			   

/*************************************************************************/

/***************************函数声明**************************************/
/***************************底层驱动函数**************************************/
void LCD_Delayms(unsigned int t);
void Lcd_Write_CMD(unsigned char dat);
void Lcd_Write_DAT(unsigned char dat);
void Lcd_Set_X(unsigned char x);
void Lcd_Set_Y(unsigned char y);
void Lcd_Set_X_Y(unsigned char x, unsigned char y);//设置坐标


/***************************基础应用函数**************************************/
void Lcd_Init();//初始化
void Lcd_Clear();//清屏
void Lcd_Show_On();//LCD显示开
void Lcd_Show_Off();//LCD显示关
	//显示字符函数  hang为行值取值范围0-7， lie为列值取值范围0-120，dat为ASCII字符  //
void Lcd_Show_Char(unsigned char hang, unsigned char lie, unsigned char dat );
//显示字符串函数  hang为行值取值范围0-7， lie为列值取值范围0-120，p为字符串地址  //
void Lcd_Show_String(unsigned char hang, unsigned char lie, unsigned char *p );
//显示整数数据，  hang为行值取值范围0-7， lie为列值取值范围0-120，dat为整型数据  //
void Lcd_Show_Num(unsigned char hang, unsigned char lie, unsigned int dat);
//显示浮点型数据，  hang为行值取值范围0-7， lie为列值取值范围0-120，dat为整型数据 ，kept为保留小数位数  //
void Lcd_Show_floatNum(unsigned char hang, unsigned char lie, float dat,unsigned char kept);
	//显示中文函数	hang为行值取值范围0-7， lie为列值取值范围0-112，num为中文数组行号  //
void Lcd_Show_Chinese( unsigned char hang, unsigned char lie, unsigned char num );

/***************************用户函数**************************************/

/*************************************************************************/

#endif
