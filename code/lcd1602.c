#include <reg51.h>

#include "lcd1602.h"


void LCD1602_Delay()
{
	int i,j;
	for(i=0; i<=10; i++)
	for(j=0; j<=20; j++);
}

/********************************************************************
* 名称 : Write_CMD(unsigned char del)
* 功能 : 1602命令函数
* 输入 : 输入的命令值
* 输出 : 无
***********************************************************************/

void Write_CMD(unsigned char del)	 //写指令   输入：RS=L；Rw=L；                          
{						//	D0~D7= 指令码，E=高脉冲；
	LCD_PORT = del;			 //输出：D0~D7=数据
	RS = 0;
	RW = 0;
	E = 0;
	LCD1602_Delay();
	E = 1;
	LCD1602_Delay();
}


/********************************************************************
* 名称 : Write_DAT(unsigned char del)
* 功能 : 1602写数据函数
* 输入 : 需要写入1602的数据
* 输出 : 无
***********************************************************************/

void Write_DAT(unsigned char del)  //写数据  输入：RS=H；RW=L；
{
	LCD_PORT = del;		   //D0~D7=数据；E=高脉冲
	RS = 1;
	RW = 0;			   //输出：无
	E = 0;
	LCD1602_Delay();
	E = 1;
	LCD1602_Delay();
}

/********************************************************************
* 名称 : LCD1602_init()
* 功能 : 1602初始化，请参考1602的资料
* 输入 : 无
* 输出 : 无
***********************************************************************/
void LCD1602_Init(void)
{
	Write_CMD(0x01); //显示清0
	Write_CMD(0x38); //显示模式设置 ，设置16*2显示，5*7点阵，8位数据接口  
	Write_CMD(0x0c); // 显示开关光标的设置
	Write_CMD(0x06); //显示光标移动设置
//	Write_CMD(0xd0);
}

/********************************************************************
* 名称 : LCD1602_char(unsigned char hang,unsigned char lie,char sign)
* 功能 : 改变液晶中某位的值，如果要让第0行，第5个字符显示"b" ，调用该函数如下
		 LCD1602_char(0,5,'b')
* 输入 : 行，列，需要输入1602的数据
* 输出 : 无
***********************************************************************/
void LCD1602_char(unsigned char hang,unsigned char lie,char dat)
{
	unsigned char a;
	if(hang == 0) a = 0x80;
	if(hang == 1) a = 0xc0;
	a = a + lie;
	Write_CMD(a);//调用写指令函数
	Write_DAT(dat);//调用写数据函数
}

/********************************************************************
* 名称 : LCD1602_string(unsigned char hang,unsigned char lie,unsigned char *p)
* 功能 : 改变液晶中某位的值，如果要让第一行，第五个字符开始显示"ab cd ef" ，调用该函数如下
	 	 LCD1602_string(1,5,"ab cd ef;")
* 输入 : 行，列，需要输入1602的数据
* 输出 : 无
***********************************************************************/
void LCD1602_string(unsigned char hang,unsigned char lie,unsigned char *p)
{
	unsigned char a;
	if(hang == 0) a = 0x80;//0x80代表第一行第一个字
	if(hang == 1) a = 0xc0;	 //	代表第二行的第五个字
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
* 名称 : void LCD1602_2num(unsigned char hang,unsigned char lie,unsigned int dat)
* 功能 : 如果要让第一行，第五个字符显示整数12345，调用该函数如下
		 LCD1602_2num(1,5,12345)
* 输入 : 行，列，需要输入1602的数据
* 输出 : 无
* 扩展 : 可更改变量定义类型（char或long int，同时对应更改函数内a的定义类型，可改变数字最大显示范围）
***********************************************************************/
void LCD1602_2num(unsigned char hang,unsigned char lie,unsigned int dat)
{
	unsigned int a; //定义传递变量a
	unsigned int i=1; //数值位数记录变量i   
	a = dat;  //显示的整数值传递给a
	while((a/10)!=0)  //计算整数的位数
	{
		a/=10;
		i++;
	}
	a = dat;   //显示的整数值传递给a       
	for(i;i>0;i--)  //按位倒序显示数据
	{
		LCD1602_char( hang,lie+i-1,a%10+'0');
		a/=10;
	}
}

/********************************************************************
* 名称 : void LCD1602_2floatnum(unsigned char hang,unsigned char lie,float dat)
* 功能 : 如果要让第一行，第五个字符显示小数23.445，保留2位小数，调用该函数如下
		 LCD1602_2num(1,5,23.445，2)
* 输入 : 行，列，需要输入1602的数据，保留小数位数
* 输出 : 无
***********************************************************************/
void LCD1602_2floatnum(unsigned char hang,unsigned char lie,float dat,unsigned char kept)
{
	float a;    //定义浮点数据传递变量
	unsigned long int b,c;  //定义整型数据传递变量
	unsigned char i=1,j;    //定义数值位数计数、小数点计数变量
	a = dat;    //传递要显示的浮点数值给a
	for(j=0;j<kept;j++)  //根据保留位数，将浮点数放大
	{
		a *= 10;
	}
	b=a; //传递整型部分给b
	c=a; //传递整型部分给c
	while((b/10)!=0) //计算显示部分的位数
	{
		b/=10;
		i++;
	}
	i += 1;  //增加小数显示位计数
	for(i;i>0;i--) // 按位显示已转为整数的浮点数据
	{
		if(kept==0) //保留小数点位数判断，显示小数点
		{
			LCD1602_char( hang,lie+i-1,'.');
		}			
		else //显示数字
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
	unsigned int a; //定义传递变量a
	unsigned char b;
	a = dat;  //显示的整数值传递给a 
	b = length;
	while(length>0)  //按位倒序显示数据
	{
		LCD1602_char( hang,lie+length-1,a%10+'0');
		a/=10;
		length--;
	}
}
//光标字符闪烁设置函数
//mode:0,无光标，字不闪;1:无光标，字符闪;2:有光标，字不闪;3:有光标，字符闪。
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


