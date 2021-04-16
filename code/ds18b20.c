#include "ds18b20.h"

/*************DS18B20�¶ȶ�ȡģ��*************/
void Delay_18B20(int x)//��ʱ����
{
	while(x--) ;
}

void delayms(int n)
{
	unsigned int i,j,k;
	for(k=0;k<n;k++)
	{
		for(i=0;i<2;i++)
			for(j=0;j<239;j++);
	}
}

void Init_DS18B20()//��ʼ��DS18B20
{
	unsigned char x=0;
	DQ = 1;    //DQ��λ
	Delay_18B20(8);  //������ʱ
	DQ = 0;    //��Ƭ����DQ����
	Delay_18B20(80); //��ȷ��ʱ ���� 480us
	DQ = 1;    //��������
	Delay_18B20(14);
	//������ʱ�� ���x=0���ʼ���ɹ� x=1���ʼ��ʧ��
	x=DQ;      
	Delay_18B20(20);
}

unsigned char Read_Byte()//��һ���ֽ�
{
	unsigned char i=0;
	unsigned char dat = 0;
	for (i=8;i>0;i--)
	{
		DQ = 0; // �������ź�
		dat>>=1;
		DQ = 1; // �������ź�
		if(DQ)
		dat|=0x80;
		Delay_18B20(4);
	}
	return(dat);
}

void Write_Byte(unsigned char dat)//дһ���ֽ�
{
	unsigned char i=0;
	for (i=8; i>0; i--)
	{
		DQ = 0;
		DQ = dat&0x01;
		Delay_18B20(5);
		DQ = 1;
		dat>>=1;
	}
}

float Read_Temp()//��ȡ�¶�
{
	unsigned char dat_L=0;
	unsigned char dat_H=0;
	int temp=0;
	float temp_f;	
	Init_DS18B20();
	Write_Byte(0xcc); // ����������кŵĲ���
	Write_Byte(0x44); // �����¶�ת��
	Init_DS18B20();
	Write_Byte(0xcc); //����������кŵĲ���
	Write_Byte(0xbe); //��ȡ�¶�ָ��
	dat_L=Read_Byte();   //�����������ֽ�����   //����8λ 
	dat_H=Read_Byte();                          //����8λ

	temp=dat_H;
	temp<<=8; 
	temp=temp+dat_L; 			//��char���ݺϳ�һ��int���ݡ�
	
	temp_f=temp*0.0625;  	//�õ���ʵʮ�����¶�ֵ
	//��ΪDS18B20���õ�Ĭ��12λ����С�ֱ���0.0625�ȣ�
	//���Զ������ݵ����λ�������0.0625��
	return(temp_f);
}