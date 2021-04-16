 

#ifndef _OLED12864_H_
#define _OLED12864_H_			  	   
//#include <reg51.h>
#include "STC8.h"
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据
#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	
/*********************12864管脚配置*************************/
sbit OLED_CS  =P4^0; //片选
sbit OLED_DC  =P4^1;//数据/命令控制
sbit OLED_RST =P4^2;//复位
sbit OLED_SDIN=P4^3;//D1（MOSI） 数据
sbit OLED_SCL =P4^4;//时钟 D0 SCLK 



#define OLED_CS_Clr()  OLED_CS=0
#define OLED_CS_Set()  OLED_CS=1

#define OLED_RST_Clr() OLED_RST=0
#define OLED_RST_Set() OLED_RST=1

#define OLED_DC_Clr() OLED_DC=0
#define OLED_DC_Set() OLED_DC=1

#define OLED_SCLK_Clr() OLED_SCL=0
#define OLED_SCLK_Set() OLED_SCL=1

#define OLED_SDIN_Clr() OLED_SDIN=0
#define OLED_SDIN_Set() OLED_SDIN=1;

 

    						  
 					   
/***************************函数声明**************************************/
/***************************底层驱动函数**************************************/
void OLED_delayms(unsigned int ms);
void OLED_Write_CMD_DAT(unsigned char dat,unsigned char cmd);
void OLED_Set_X_Y(unsigned char x, unsigned char y);//定位坐标

/*************************基础应用函数************************************/
void OLED_Init(void);
void OLED_Clear(void);
void OLED_Show_On(void);
void OLED_Show_Off(void);	   							   		    
		//显示字符函数  hang为行值取值范围0-7， lie为列值取值范围0-120，dat为ASCII字符  //
void OLED_Show_Char(unsigned char hang,unsigned char lie,unsigned char dat);//显示一个字符
		//显示字符串函数  hang为行值取值范围0-7， lie为列值取值范围0-120，p为字符串地址  //
void OLED_Show_String(unsigned char hang,unsigned char lie,unsigned char *p);	 //显示字符串
		//显示中文函数	hang为行值取值范围0-7， lie为列值取值范围0-112，num为中文数组行号  //
void OLED_Show_Chinese(unsigned char hang,unsigned char lie,unsigned char num);//显示中文
		//显示自定义位数整数显示	hang为行值取值范围0-7， lie为列值取值范围0-112，dat为要显示的数字，len长度
void OLED_Show_Num(unsigned char hang,unsigned char lie,unsigned long num,unsigned char len);//显示数字，hang行,lie列，dat数字，len长度
		//显示自定义图片，start为显示起始行，图片靠左显示
void OLED_Show_Pic(unsigned char start,unsigned char *pic);//显示图片，start起始行,*pic图片数据指针

#endif  
	 



