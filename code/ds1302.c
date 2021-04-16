
#include "ds1302.h"

//---DS1302写入和读取时分秒的地址命令---//
//---秒分时日月周年 最低位读写位;-------//
unsigned char code READ_RTC_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d}; 
unsigned char code WRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};

//---DS1302时钟初始化2019年3月4日星期一12点00分00秒。---//
//---存储顺序是秒分时日月周年,存储格式是用BCD码---//
unsigned char TIME[7] = {58, 59, 23, 31, 3, 2, 20};


void Ds1302_TimeAlys()//日期时间数据判断
{
	if(TIME[1]>59){TIME[1]=0;TIME[2]++;}//分增加到60判定
	if(TIME[2]>23)  //小时增加到24判定
	{
		TIME[2]=0;
		TIME[3]++;
		TIME[5]++;
	}
	if(TIME[5]>7)TIME[5]=1; //星期判定
		if(TIME[4]==2)//2月闰年判断
		{
			if((TIME[6]+2000)%4==0){if(TIME[3]>29){TIME[3]=1;TIME[4]++;}}
			else{if(TIME[3]>28){TIME[3]=1;TIME[4]++;}}
		}
		if((TIME[4]!=2)&&(TIME[4]<8&&(TIME[4]%2==1))||(TIME[4]>7&&(TIME[4]%2==0))) //大月判定
		{
			if(TIME[3]>31){TIME[3]=1;TIME[4]++;}
		}
		if((TIME[4]!=2)&&(TIME[4]<8&&(TIME[4]%2==0))||(TIME[4]>8&&(TIME[4]%2==1)))
		{if(TIME[3]>30){TIME[3]=1;TIME[4]++;}}  //小月判定
		if(TIME[4]>12){TIME[4]=1;TIME[6]++;TIME[6]%=100;}
	}


/*******************************************************************************
* 函 数 名         : Ds1302_Write
* 函数功能         : 向DS1302命令（地址+数据）
* 输    入         : add,dat
* 输    出         : 无
*******************************************************************************/

void Ds1302_Write(unsigned char add, unsigned char dat)
{
    unsigned char n;
    RST = 0;
    _nop_();

    SCLK = 0;//先将SCLK置低电平。
    _nop_();
    RST = 1; //然后将RST(CE)置高电平。
    _nop_();

    for (n=0; n<8; n++)//开始传送八位地址命令
    {
        DSIO = add & 0x01;//数据从低位开始传送
        add >>= 1;
        SCLK = 1;//数据在上升沿时，DS1302读取数据
        _nop_();
        SCLK = 0;
        _nop_();
    }
    for (n=0; n<8; n++)//写入8位数据
    {
        DSIO = dat & 0x01;
        dat >>= 1;
        SCLK = 1;//数据在上升沿时，DS1302读取数据
        _nop_();
        SCLK = 0;
        _nop_();    
    }   
         
    RST = 0;//传送数据结束
    _nop_();
}

/*******************************************************************************
* 函 数 名         : Ds1302_Read
* 函数功能         : 读取一个地址的数据
* 输    入         : add
* 输    出         : dat
*******************************************************************************/

unsigned char Ds1302_Read(unsigned char add)
{
    unsigned char n,dat,dat1;
    RST = 0;
    _nop_();

    SCLK = 0;//先将SCLK置低电平。
    _nop_();
    RST = 1;//然后将RST(CE)置高电平。
    _nop_();

    for(n=0; n<8; n++)//开始传送八位地址命令
    {
        DSIO = add & 0x01;//数据从低位开始传送
        add >>= 1;
        SCLK = 1;//数据在上升沿时，DS1302读取数据
        _nop_();
        SCLK = 0;//DS1302下降沿时，放置数据
        _nop_();
    }
    _nop_();
    for(n=0; n<8; n++)//读取8位数据
    {
        dat1 = DSIO;//从最低位开始接收
        dat = (dat>>1) | (dat1<<7);
        SCLK = 1;
        _nop_();
        SCLK = 0;//DS1302下降沿时，放置数据
        _nop_();
    }

    RST = 0;
    _nop_();    //以下为DS1302复位的稳定时间,必须的。
    SCLK = 1;
    _nop_();
    DSIO = 0;
    _nop_();
    DSIO = 1;
    _nop_();
    return dat; 
}
/*******************************************************************************
* 函 数 名         : BCD_DEC
* 函数功能         : BCD码转十进制码
* 输    入         : 待转换数据BCD码
* 输    出         : 转换后的十进制码
*******************************************************************************/
unsigned char BCD_DEC(unsigned char dat)
{
	return( (dat>>4)*10+(dat&0x0f) );
}
/*******************************************************************************
* 函 数 名         : DEC_BCD
* 函数功能         : 十进制码转BCD码
* 输    入         : 待转换数据十进制码
* 输    出         : 转换后的BCD码
*******************************************************************************/
unsigned char DEC_BCD(unsigned char dat)
{
	return( ((dat/10)<<4) + (dat%10) );
}
/*******************************************************************************
* 函 数 名         : Ds1302_Init_Time
* 函数功能         : 重置时间.
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/

void Ds1302_Init_Time(unsigned char *p)
{
    unsigned char n;
    Ds1302_Write(0x8E,0X00);      //禁止写保护，就是关闭写保护功能
    for (n=0; n<7; n++)//写入7个字节的时钟信号：分秒时日月周年
    {
        Ds1302_Write(WRITE_RTC_ADDR[n],DEC_BCD(p[n])); 
    }
    Ds1302_Write(0x8E,0x80);      //打开写保护功能
}

/*******************************************************************************
* 函 数 名         : Ds1302_Read_Time
* 函数功能         : 读取时钟信息
* 输    入         : 无
* 输    出         : 读取的时间存放在数组TIME[n]
*******************************************************************************/

void Ds1302_Read_Time()
{
    unsigned char n;
    for (n=0; n<7; n++)//读取7个字节的时钟信号：秒分时日月周年
    {
        TIME[n] = BCD_DEC( Ds1302_Read(READ_RTC_ADDR[n]) );
    }
        
}
