#ifndef _KEY_H_
#define _KEY_H_

#include <reg51.h>

sbit key1=P3^2;    //�����λ������
sbit key2=P3^3;		 //�����λ������
sbit key3=P3^4;		 //�����λ������
sbit key4=P3^5;		 //�����λ������

/* ����1 û�а��·���0���̰�����1����������2*/
unsigned char key1_scan(void);
/* ����2 û�а��·���0���̰�����1����������2*/
unsigned char key2_scan(void);
/* ����3 û�а��·���0���̰�����1����������2*/
unsigned char key3_scan(void);
/* ����4 û�а��·���0���̰�����1����������2*/
unsigned char key4_scan(void);
#endif

