#include "ds18b20.h"

/*************DS18B20温度读取模块*************/
void Delay_18B20(int x)//延时函数
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

void Init_DS18B20()//初始化DS18B20
{
	unsigned char x=0;
	DQ = 1;    //DQ复位
	Delay_18B20(8);  //稍做延时
	DQ = 0;    //单片机将DQ拉低
	Delay_18B20(80); //精确延时 大于 480us
	DQ = 1;    //拉高总线
	Delay_18B20(14);
	//稍做延时后 如果x=0则初始化成功 x=1则初始化失败
	x=DQ;      
	Delay_18B20(20);
}

unsigned char Read_Byte()//读一个字节
{
	unsigned char i=0;
	unsigned char dat = 0;
	for (i=8;i>0;i--)
	{
		DQ = 0; // 给脉冲信号
		dat>>=1;
		DQ = 1; // 给脉冲信号
		if(DQ)
		dat|=0x80;
		Delay_18B20(4);
	}
	return(dat);
}

void Write_Byte(unsigned char dat)//写一个字节
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

float Read_Temp()//读取温度
{
	unsigned char dat_L=0;
	unsigned char dat_H=0;
	int temp=0;
	float temp_f;	
	Init_DS18B20();
	Write_Byte(0xcc); // 跳过读序号列号的操作
	Write_Byte(0x44); // 启动温度转换
	Init_DS18B20();
	Write_Byte(0xcc); //跳过读序号列号的操作
	Write_Byte(0xbe); //读取温度指令
	dat_L=Read_Byte();   //连续读两个字节数据   //读低8位 
	dat_H=Read_Byte();                          //读高8位

	temp=dat_H;
	temp<<=8; 
	temp=temp+dat_L; 			//两char数据合成一个int数据。
	
	temp_f=temp*0.0625;  	//得到真实十进制温度值
	//因为DS18B20采用的默认12位，最小分辨率0.0625度，
	//所以读回数据的最低位代表的是0.0625度
	return(temp_f);
}