#ifndef _LCD1602_H_
#define _LCD1602_H_
#include <reg51.h>
/*****************LCD1602�ܽ�����********************/
#define LCD_PORT P0  //���ݶ˿�
sbit E=P1^7;		//1602ʹ������
sbit RW=P1^6;		//1602��д����	
sbit RS=P1^5;		//1602����/����ѡ������

/*******************��������************************/
/*****************�ײ���������********************/
void LCD1602_Delay();
void Write_CMD(unsigned char del);	 //дָ��
void Write_DAT(unsigned char del);  //д����

/*****************����Ӧ�ú���********************/
void LCD1602_Init();   //��ʼ��
//��ʾ�ַ�����  hangΪ��ֵȡֵ��Χ0-1�� lieΪ��ֵȡֵ��Χ0-15��datΪASCII�ַ�  //
void LCD1602_char(unsigned char hang,unsigned char lie,char dat);//��ʾ�ַ�
//��ʾ�ַ�������  hangΪ��ֵȡֵ��Χ0-1�� lieΪ��ֵȡֵ��Χ0-15��*pΪ�ַ��������ַ  //
void LCD1602_string(unsigned char hang,unsigned char lie,unsigned char *p);//��ʾ�ַ���
//��ʾ�������ֺ���  hangΪ��ֵȡֵ��Χ0-1�� lieΪ��ֵȡֵ��Χ0-15��datΪ��������  //
void LCD1602_2num(unsigned char hang,unsigned char lie,unsigned int dat);//��ʾ���ͣ�long int������
//��ʾ���������ֺ���  hangΪ��ֵȡֵ��Χ0-1�� lieΪ��ֵȡֵ��Χ0-15��datΪ���������� ��keptΪ����С������ //
void LCD1602_2floatnum(unsigned char hang,unsigned char lie,float dat,unsigned char kept);

/***************************�û�����**************************************/
void LCD1602_timenum(unsigned char hang,unsigned char lie,unsigned int dat,unsigned char length);

//����ַ���˸���ú���
//mode:0,�޹�꣬�ֲ���;1:�޹�꣬�ַ���;2:�й�꣬�ֲ���;3:�й�꣬�ַ�����
void LCD1602_cursorset(unsigned char hang,unsigned char lie,unsigned char mode);
#endif
