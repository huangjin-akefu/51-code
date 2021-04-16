#include "dht11.h"
#include "intrins.h"
unsigned char Humi_H=10,Humi_L,Temp_H,Temp_L;
void Delay18ms()	
{
	unsigned char i, j;

	i = 37;
	j = 266;
	do
	{
		while (--j);
	} while (--i);
}


void Delay40us()	//@12MHz	
{
	unsigned char i;

	_nop_();
	i = 17;
	while (--i);
}

unsigned char receive_byte(void)
{
	unsigned char i=0,dat=0;
	for(i=0;i<8;i++)
	{
		//�ȴ���ʱ40us�����ߣ���������ʱ���ж�����0��1
		while(DHT11_PIN==0);
		Delay40us();
		dat<<=1;
		if(DHT11_PIN)
		dat=dat+1;
		else
			dat=dat+0;
		//����һλ��ȴ����ͼ�������һλ
		while(DHT11_PIN==1);
	}
	return(dat);
}

bit Read_DHT11(void)
{
	bit ok;
	unsigned char i,check;
	ok=0;i=0;
	DHT11_PIN=1;
	DHT11_PIN=0;
	Delay18ms();//��������18ms����ʼ�ź�
	DHT11_PIN=1;//��������40us��������ʼ�ź�
	Delay40us();
	while(DHT11_PIN && i<80 )i++;//�ȴ�DHT11���ͣ�������;���Ӧ
	if(DHT11_PIN==0 && i<80)//��Ӧʱ��û�г���֤����Ӧ�ɹ����������
	{
		i=0;
		while(DHT11_PIN==0 && i<80 )i++;//�ȴ�DHT11����80us���ߣ�������߾���Ӧ
		if(DHT11_PIN==1 &&i<80)//DHT11��Ӧ���ߣ�������Ҫ�ȴ�80us
		{
			i=0;Delay40us();Delay40us();//�ȴ�DHT11����80us��,��ʼ��������
			if(DHT11_PIN==0)
			{
				//��ʼ��������
				Humi_H=receive_byte();
				Humi_L=receive_byte();
				Temp_H=receive_byte();
				Temp_L=receive_byte();
				check=receive_byte();
				//�ж�������Ч��
				if(check==(Humi_H+Humi_L+Temp_H+Temp_L))
					ok=1;
			}
		}
	}
	return(ok);
}