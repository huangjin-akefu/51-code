#ifndef __LCD12864_H__
#define __LCD12864_H__
#include <reg51.h>

/*********************12864�ܽ�����*************************/
#define LCD_Port P0
sbit  RS=P1^5;
sbit  RW=P1^6;
sbit   E=P1^7;
sbit CS1=P2^0;			   //Ƭѡ�ź�
sbit CS2=P2^1;			   

/*************************************************************************/

/***************************��������**************************************/
/***************************�ײ���������**************************************/
void LCD_Delayms(unsigned int t);
void Lcd_Write_CMD(unsigned char dat);
void Lcd_Write_DAT(unsigned char dat);
void Lcd_Set_X(unsigned char x);
void Lcd_Set_Y(unsigned char y);
void Lcd_Set_X_Y(unsigned char x, unsigned char y);//��������


/***************************����Ӧ�ú���**************************************/
void Lcd_Init();//��ʼ��
void Lcd_Clear();//����
void Lcd_Show_On();//LCD��ʾ��
void Lcd_Show_Off();//LCD��ʾ��
	//��ʾ�ַ�����  hangΪ��ֵȡֵ��Χ0-7�� lieΪ��ֵȡֵ��Χ0-120��datΪASCII�ַ�  //
void Lcd_Show_Char(unsigned char hang, unsigned char lie, unsigned char dat );
//��ʾ�ַ�������  hangΪ��ֵȡֵ��Χ0-7�� lieΪ��ֵȡֵ��Χ0-120��pΪ�ַ�����ַ  //
void Lcd_Show_String(unsigned char hang, unsigned char lie, unsigned char *p );
//��ʾ�������ݣ�  hangΪ��ֵȡֵ��Χ0-7�� lieΪ��ֵȡֵ��Χ0-120��datΪ��������  //
void Lcd_Show_Num(unsigned char hang, unsigned char lie, unsigned int dat);
//��ʾ���������ݣ�  hangΪ��ֵȡֵ��Χ0-7�� lieΪ��ֵȡֵ��Χ0-120��datΪ�������� ��keptΪ����С��λ��  //
void Lcd_Show_floatNum(unsigned char hang, unsigned char lie, float dat,unsigned char kept);
	//��ʾ���ĺ���	hangΪ��ֵȡֵ��Χ0-7�� lieΪ��ֵȡֵ��Χ0-112��numΪ���������к�  //
void Lcd_Show_Chinese( unsigned char hang, unsigned char lie, unsigned char num );

/***************************�û�����**************************************/

/*************************************************************************/

#endif
