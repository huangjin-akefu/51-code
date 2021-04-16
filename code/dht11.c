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
		//等待延时40us后拉高，根据拉高时间判断数据0或1
		while(DHT11_PIN==0);
		Delay40us();
		dat<<=1;
		if(DHT11_PIN)
		dat=dat+1;
		else
			dat=dat+0;
		//传完一位后等待拉低继续传下一位
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
	Delay18ms();//总线拉低18ms，起始信号
	DHT11_PIN=1;//总线拉高40us，结束起始信号
	Delay40us();
	while(DHT11_PIN && i<80 )i++;//等待DHT11拉低，如果拉低就响应
	if(DHT11_PIN==0 && i<80)//响应时间没有超就证明响应成功，否则出错
	{
		i=0;
		while(DHT11_PIN==0 && i<80 )i++;//等待DHT11拉低80us后变高，如果拉高就响应
		if(DHT11_PIN==1 &&i<80)//DHT11响应拉高，接下来要等待80us
		{
			i=0;Delay40us();Delay40us();//等待DHT11拉高80us后,开始传输数据
			if(DHT11_PIN==0)
			{
				//开始接受数据
				Humi_H=receive_byte();
				Humi_L=receive_byte();
				Temp_H=receive_byte();
				Temp_L=receive_byte();
				check=receive_byte();
				//判断数据有效否
				if(check==(Humi_H+Humi_L+Temp_H+Temp_L))
					ok=1;
			}
		}
	}
	return(ok);
}