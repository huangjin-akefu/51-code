 

#ifndef _OLED12864_H_
#define _OLED12864_H_			  	   
//#include <reg51.h>
#include "STC8.h"
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����
#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	
/*********************12864�ܽ�����*************************/
sbit OLED_CS  =P4^0; //Ƭѡ
sbit OLED_DC  =P4^1;//����/�������
sbit OLED_RST =P4^2;//��λ
sbit OLED_SDIN=P4^3;//D1��MOSI�� ����
sbit OLED_SCL =P4^4;//ʱ�� D0 SCLK 



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

 

    						  
 					   
/***************************��������**************************************/
/***************************�ײ���������**************************************/
void OLED_delayms(unsigned int ms);
void OLED_Write_CMD_DAT(unsigned char dat,unsigned char cmd);
void OLED_Set_X_Y(unsigned char x, unsigned char y);//��λ����

/*************************����Ӧ�ú���************************************/
void OLED_Init(void);
void OLED_Clear(void);
void OLED_Show_On(void);
void OLED_Show_Off(void);	   							   		    
		//��ʾ�ַ�����  hangΪ��ֵȡֵ��Χ0-7�� lieΪ��ֵȡֵ��Χ0-120��datΪASCII�ַ�  //
void OLED_Show_Char(unsigned char hang,unsigned char lie,unsigned char dat);//��ʾһ���ַ�
		//��ʾ�ַ�������  hangΪ��ֵȡֵ��Χ0-7�� lieΪ��ֵȡֵ��Χ0-120��pΪ�ַ�����ַ  //
void OLED_Show_String(unsigned char hang,unsigned char lie,unsigned char *p);	 //��ʾ�ַ���
		//��ʾ���ĺ���	hangΪ��ֵȡֵ��Χ0-7�� lieΪ��ֵȡֵ��Χ0-112��numΪ���������к�  //
void OLED_Show_Chinese(unsigned char hang,unsigned char lie,unsigned char num);//��ʾ����
		//��ʾ�Զ���λ��������ʾ	hangΪ��ֵȡֵ��Χ0-7�� lieΪ��ֵȡֵ��Χ0-112��datΪҪ��ʾ�����֣�len����
void OLED_Show_Num(unsigned char hang,unsigned char lie,unsigned long num,unsigned char len);//��ʾ���֣�hang��,lie�У�dat���֣�len����
		//��ʾ�Զ���ͼƬ��startΪ��ʾ��ʼ�У�ͼƬ������ʾ
void OLED_Show_Pic(unsigned char start,unsigned char *pic);//��ʾͼƬ��start��ʼ��,*picͼƬ����ָ��

#endif  
	 



