
#include "oled12864.h"

#include "lib_12864.h"  

void OLED_delayms(unsigned int ms)//24MHz，1T
{                         
	unsigned char i, j;
	i = 32;
	j = 40*ms;
	do
	{
		while (--j);
	} while (--i);
}
//void OLED_delayms(unsigned int ms)//12MHz，12T
//{
//	unsigned char i, j;
//	i = 2*ms;
//	j = 239;
//	do
//	{
//		while (--j);
//	} while (--i);
//}
#if OLED_MODE==1
//向SSD1106写入一个字节。
//dat:要写入的数据/命令
//cmd:数据/命令标志 0,表示命令;1,表示数据;
void OLED_Write_CMD_DAT(unsigned char dat,unsigned char cmd)
{
	DATAOUT(dat);	    
	if(cmd)
	  OLED_DC_Set();
	else 
	  OLED_DC_Clr();		   
	OLED_CS_Clr();
	OLED_WR_Clr();	 
	OLED_WR_Set();
	OLED_CS_Set();	  
	OLED_DC_Set();	 
} 	    	    
#else
//向SSD1306写入一个字节。
//dat:要写入的数据/命令
//cmd:数据/命令标志 0,表示命令;1,表示数据;
void OLED_Write_CMD_DAT(unsigned char dat,unsigned char cmd)
{	
	unsigned char i;			  
	if(cmd)
	  OLED_DC_Set();
	else 
	  OLED_DC_Clr();		  
	OLED_CS_Clr();
	for(i=0;i<8;i++)
	{			  
		OLED_SCLK_Clr();
		if(dat&0x80)
			{
		   OLED_SDIN_Set();
			}
else
		   OLED_SDIN_Clr();
				OLED_SCLK_Set();
		dat<<=1;   
	}				 		  
	OLED_CS_Set();
	OLED_DC_Set();   	  
} 
#endif
	void OLED_Set_X_Y(unsigned char x, unsigned char y) 
{ 
	OLED_Write_CMD_DAT(0xb0+y,OLED_CMD);
	OLED_Write_CMD_DAT(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_Write_CMD_DAT((x&0x0f)|0x01,OLED_CMD); 
}   	  
//开启OLED显示    
void OLED_Show_On(void)
{
	OLED_Write_CMD_DAT(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_Write_CMD_DAT(0X14,OLED_CMD);  //DCDC ON
	OLED_Write_CMD_DAT(0XAF,OLED_CMD);  //Show ON
}
//关闭OLED显示     
void OLED_Show_Off(void)
{
	OLED_Write_CMD_DAT(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_Write_CMD_DAT(0X10,OLED_CMD);  //DCDC OFF
	OLED_Write_CMD_DAT(0XAE,OLED_CMD);  //Show OFF
}		   			 
//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLED_Clear(void)  
{  
	unsigned char i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_Write_CMD_DAT (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_Write_CMD_DAT (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_Write_CMD_DAT (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_Write_CMD_DAT(0,OLED_DATA); 
	} //更新显示
}


//在指定位置显示一个字符,包括部分字符
void OLED_Show_Char(unsigned char hang,unsigned char lie,unsigned char dat)
{      	
	unsigned char c=0,i=0,x,y;	
	x=lie;y=hang;
		c=dat-' ';//得到偏移后的值			
		if(x>Max_Column-1){x=0;y=y+2;}
			OLED_Set_X_Y(x,y);	
			for(i=0;i<8;i++)
			OLED_Write_CMD_DAT(ZIFU[c*16+i],OLED_DATA);
			OLED_Set_X_Y(x,y+1);
			for(i=0;i<8;i++)
			OLED_Write_CMD_DAT(ZIFU[c*16+i+8],OLED_DATA);
}
//m^n函数
unsigned long oled_pow(unsigned char m,unsigned char n)
{
	unsigned long result=1;	 
	while(n--)result*=m;    
	return result;
}				  
 
//len :数字的位数
//num:数值(0~4294967295);	 		  
void OLED_Show_Num(unsigned char hang,unsigned char lie,unsigned long num,unsigned char len)
{         	
	unsigned char t,temp;
	unsigned char enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_Show_Char(hang,lie+8*t,' ');
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_Show_Char(hang,lie+8*t,temp+'0'); 
	}
} 
//显示一个字符串
void OLED_Show_String(unsigned char hang,unsigned char lie,unsigned char *p)
{
	unsigned char j=0;
	while (p[j]!='\0')
	{		OLED_Show_Char(hang,lie,p[j]);
			lie+=8;
		if(lie>120){lie=0;hang+=2;}
			j++;
	}
}
//显示汉字
void OLED_Show_Chinese(unsigned char hang,unsigned char lie,unsigned char num)
{      			    
	unsigned char t,adder=0,x,y;
	x=lie;y=hang;
	OLED_Set_X_Y(x,y);	
    for(t=0;t<16;t++)
		{
				OLED_Write_CMD_DAT(HANZI[2*num][t],OLED_DATA);
				adder+=1;
     }	
		OLED_Set_X_Y(x,y+1);	
    for(t=0;t<16;t++)
			{	
				OLED_Write_CMD_DAT(HANZI[2*num+1][t],OLED_DATA);
				adder+=1;
      }					
}
///***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
//void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
//{ 	
// unsigned int j=0;
// unsigned char x,y;
//  
//  if(y1%8==0) y=y1/8;      
//  else y=y1/8+1;
//	for(y=y0;y<y1;y++)
//	{
//		OLED_Set_X_Y(x0,y);
//    for(x=x0;x<x1;x++)
//	    {      
//	    	OLED_Write_CMD_DAT(BMP[j++],OLED_DATA);	    	
//	    }
//	}
//} 


//初始化SSD1306					    
void OLED_Init(void)
{
  OLED_RST_Set();
	OLED_delayms(100);
	OLED_RST_Clr();
	OLED_delayms(100);
	OLED_RST_Set(); 

	OLED_Write_CMD_DAT(0xAE,OLED_CMD);//--turn off oled panel
	OLED_Write_CMD_DAT(0x00,OLED_CMD);//---set low column address
	OLED_Write_CMD_DAT(0x10,OLED_CMD);//---set high column address
	OLED_Write_CMD_DAT(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Show Start Line (0x00~0x3F)
	OLED_Write_CMD_DAT(0x81,OLED_CMD);//--set contrast control register
	OLED_Write_CMD_DAT(0xCF,OLED_CMD); // Set SEG Output Current Brightness
	OLED_Write_CMD_DAT(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_Write_CMD_DAT(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_Write_CMD_DAT(0xA6,OLED_CMD);//--set normal Show
	OLED_Write_CMD_DAT(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_Write_CMD_DAT(0x3f,OLED_CMD);//--1/64 duty
	OLED_Write_CMD_DAT(0xD3,OLED_CMD);//-set Show offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_Write_CMD_DAT(0x00,OLED_CMD);//-not offset
	OLED_Write_CMD_DAT(0xd5,OLED_CMD);//--set Show clock divide ratio/oscillator frequency
	OLED_Write_CMD_DAT(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_Write_CMD_DAT(0xD9,OLED_CMD);//--set pre-charge period
	OLED_Write_CMD_DAT(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_Write_CMD_DAT(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_Write_CMD_DAT(0x12,OLED_CMD);
	OLED_Write_CMD_DAT(0xDB,OLED_CMD);//--set vcomh
	OLED_Write_CMD_DAT(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_Write_CMD_DAT(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_Write_CMD_DAT(0x02,OLED_CMD);//
	OLED_Write_CMD_DAT(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_Write_CMD_DAT(0x14,OLED_CMD);//--set(0x10) disable
	OLED_Write_CMD_DAT(0xA4,OLED_CMD);// Disable Entire Show On (0xa4/0xa5)
	OLED_Write_CMD_DAT(0xA6,OLED_CMD);// Disable Inverse Show On (0xa6/a7) 
	OLED_Write_CMD_DAT(0xAF,OLED_CMD);//--turn on oled panel

	OLED_Clear();
	OLED_Set_X_Y(0,0); 	
}  

//图片显示，可显示128*n（n<64）图片
void OLED_Show_Pic(unsigned char start,unsigned char *Pic)
{
	unsigned char i,n;		    
	for(i=start;i<8;i++)  
	{  
		OLED_Write_CMD_DAT (0xb0+i,OLED_CMD);    //设置页地址
		OLED_Write_CMD_DAT (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_Write_CMD_DAT (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_Write_CMD_DAT(*(Pic+(i-start)*128+n),OLED_DATA); 
	} //更新显示
}