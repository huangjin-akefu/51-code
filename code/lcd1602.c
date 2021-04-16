#include <reg51.h>

#include "lcd1602.h"


void LCD1602_Delay()
{
	int i,j;
	for(i=0; i<=10; i++)
	for(j=0; j<=20; j++);
}

/********************************************************************
* ���� : Write_CMD(unsigned char del)
* ���� : 1602�����
* ���� : ���������ֵ
* ��� : ��
***********************************************************************/

void Write_CMD(unsigned char del)	 //дָ��   ���룺RS=L��Rw=L��                          
{						//	D0~D7= ָ���룬E=�����壻
	LCD_PORT = del;			 //�����D0~D7=����
	RS = 0;
	RW = 0;
	E = 0;
	LCD1602_Delay();
	E = 1;
	LCD1602_Delay();
}


/********************************************************************
* ���� : Write_DAT(unsigned char del)
* ���� : 1602д���ݺ���
* ���� : ��Ҫд��1602������
* ��� : ��
***********************************************************************/

void Write_DAT(unsigned char del)  //д����  ���룺RS=H��RW=L��
{
	LCD_PORT = del;		   //D0~D7=���ݣ�E=������
	RS = 1;
	RW = 0;			   //�������
	E = 0;
	LCD1602_Delay();
	E = 1;
	LCD1602_Delay();
}

/********************************************************************
* ���� : LCD1602_init()
* ���� : 1602��ʼ������ο�1602������
* ���� : ��
* ��� : ��
***********************************************************************/
void LCD1602_Init(void)
{
	Write_CMD(0x01); //��ʾ��0
	Write_CMD(0x38); //��ʾģʽ���� ������16*2��ʾ��5*7����8λ���ݽӿ�  
	Write_CMD(0x0c); // ��ʾ���ع�������
	Write_CMD(0x06); //��ʾ����ƶ�����
//	Write_CMD(0xd0);
}

/********************************************************************
* ���� : LCD1602_char(unsigned char hang,unsigned char lie,char sign)
* ���� : �ı�Һ����ĳλ��ֵ�����Ҫ�õ�0�У���5���ַ���ʾ"b" �����øú�������
		 LCD1602_char(0,5,'b')
* ���� : �У��У���Ҫ����1602������
* ��� : ��
***********************************************************************/
void LCD1602_char(unsigned char hang,unsigned char lie,char dat)
{
	unsigned char a;
	if(hang == 0) a = 0x80;
	if(hang == 1) a = 0xc0;
	a = a + lie;
	Write_CMD(a);//����дָ���
	Write_DAT(dat);//����д���ݺ���
}

/********************************************************************
* ���� : LCD1602_string(unsigned char hang,unsigned char lie,unsigned char *p)
* ���� : �ı�Һ����ĳλ��ֵ�����Ҫ�õ�һ�У�������ַ���ʼ��ʾ"ab cd ef" �����øú�������
	 	 LCD1602_string(1,5,"ab cd ef;")
* ���� : �У��У���Ҫ����1602������
* ��� : ��
***********************************************************************/
void LCD1602_string(unsigned char hang,unsigned char lie,unsigned char *p)
{
	unsigned char a;
	if(hang == 0) a = 0x80;//0x80�����һ�е�һ����
	if(hang == 1) a = 0xc0;	 //	����ڶ��еĵ������
	a = a + lie ;
	Write_CMD(a);
	while(1)
	{
		if(*p == '\0') break;
		Write_DAT(*p);
		p++;
	}
}
/********************************************************************
* ���� : void LCD1602_2num(unsigned char hang,unsigned char lie,unsigned int dat)
* ���� : ���Ҫ�õ�һ�У�������ַ���ʾ����12345�����øú�������
		 LCD1602_2num(1,5,12345)
* ���� : �У��У���Ҫ����1602������
* ��� : ��
* ��չ : �ɸ��ı����������ͣ�char��long int��ͬʱ��Ӧ���ĺ�����a�Ķ������ͣ��ɸı����������ʾ��Χ��
***********************************************************************/
void LCD1602_2num(unsigned char hang,unsigned char lie,unsigned int dat)
{
	unsigned int a; //���崫�ݱ���a
	unsigned int i=1; //��ֵλ����¼����i   
	a = dat;  //��ʾ������ֵ���ݸ�a
	while((a/10)!=0)  //����������λ��
	{
		a/=10;
		i++;
	}
	a = dat;   //��ʾ������ֵ���ݸ�a       
	for(i;i>0;i--)  //��λ������ʾ����
	{
		LCD1602_char( hang,lie+i-1,a%10+'0');
		a/=10;
	}
}

/********************************************************************
* ���� : void LCD1602_2floatnum(unsigned char hang,unsigned char lie,float dat)
* ���� : ���Ҫ�õ�һ�У�������ַ���ʾС��23.445������2λС�������øú�������
		 LCD1602_2num(1,5,23.445��2)
* ���� : �У��У���Ҫ����1602�����ݣ�����С��λ��
* ��� : ��
***********************************************************************/
void LCD1602_2floatnum(unsigned char hang,unsigned char lie,float dat,unsigned char kept)
{
	float a;    //���帡�����ݴ��ݱ���
	unsigned long int b,c;  //�����������ݴ��ݱ���
	unsigned char i=1,j;    //������ֵλ��������С�����������
	a = dat;    //����Ҫ��ʾ�ĸ�����ֵ��a
	for(j=0;j<kept;j++)  //���ݱ���λ�������������Ŵ�
	{
		a *= 10;
	}
	b=a; //�������Ͳ��ָ�b
	c=a; //�������Ͳ��ָ�c
	while((b/10)!=0) //������ʾ���ֵ�λ��
	{
		b/=10;
		i++;
	}
	i += 1;  //����С����ʾλ����
	for(i;i>0;i--) // ��λ��ʾ��תΪ�����ĸ�������
	{
		if(kept==0) //����С����λ���жϣ���ʾС����
		{
			LCD1602_char( hang,lie+i-1,'.');
		}			
		else //��ʾ����
		{
			LCD1602_char( hang,lie+i-1,c%10+'0');
			c/=10;
		}
		kept--;
	}
}

//void LCD1602_2num(unsigned char hang,unsigned char lie,unsigned int dat)
//{
//	LCD1602_char( hang,lie,dat/10%10+'0');
//	LCD1602_char( hang,lie+1,dat%10+'0');
//}

void LCD1602_timenum(unsigned char hang,unsigned char lie,unsigned int dat,unsigned char length)
{
	unsigned int a; //���崫�ݱ���a
	unsigned char b;
	a = dat;  //��ʾ������ֵ���ݸ�a 
	b = length;
	while(length>0)  //��λ������ʾ����
	{
		LCD1602_char( hang,lie+length-1,a%10+'0');
		a/=10;
		length--;
	}
}
//����ַ���˸���ú���
//mode:0,�޹�꣬�ֲ���;1:�޹�꣬�ַ���;2:�й�꣬�ֲ���;3:�й�꣬�ַ�����
void LCD1602_cursorset(unsigned char hang,unsigned char lie,unsigned char mode)
{
	unsigned char a,b;
	if(hang == 0) a = 0x80;
	if(hang == 1) a = 0xc0;
	a = a+lie;
	b = 0x0c + mode;
	Write_CMD(a);
	Write_CMD(b);
}


