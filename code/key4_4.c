#include "key4_4.h"
#include "delay.h"

unsigned char keybord_sacn(void)
{
	unsigned char h,l,keynum,i=0;
  keynum=0;h=0;l=0;i=0;
  KEY_PORT=0xf0;//行为1，列为0，目的是方便检测哪一行被按下
  if(KEY_PORT!=0xf0)	//如果不是原来的值就证明有按键按下
  {
		Delay_1ms();
		if(KEY_PORT!=0xf0)  //消抖再次确认按键是否有效
		{
			switch(KEY_PORT)					//确定是哪一行的按键被按下
			{
				 case(0xe0):   l=1;break;		   //第一行
				 case(0xd0):   l=2;break;
				 case(0xb0):   l=3;break;
				 case(0x70):   l=4;break;
				 default : break;
			}
			KEY_PORT=0x0f;		// //行为0，列为1，目的是方便检测哪一列被按下
			switch(KEY_PORT)					//确定是哪一行的按键被按下
			{
				 case(0x0e):   h=1;break;		   //第一行
				 case(0x0d):   h=2;break;
				 case(0x0b):   h=3;break;
				 case(0x07):   h=4;break;
				 default : break;
			}
			if(h>0 && l>0)//再次确认按键按下是否有效,行列都不为0时才算有效。
			keynum=(h-1)*4+l;//根据行号和列号可以以确定是哪一个按键了
			while(KEY_PORT!=0x0f && i<255){Delay_1ms();i++;}//判断按键释放
		}		
  }
  return (keynum);
}

/*读按键对应数据函数*/
/* 按键有效返回：
			0-9对应0-9，
	 按键无效返回：255
*/
unsigned char read_keydat(void)
{
	unsigned char temp=0,num=0,shibie_dat=255;
	temp=keybord_sacn();
	if(temp!=0)//按键有效
		{
			num=temp;
			switch(num)
			{
				case 1: shibie_dat=1;
					break;
				case 2: shibie_dat=2;
					break;
				case 3: shibie_dat=3;
					break;
				case 4: shibie_dat='+';// +
					break;
				case 5: shibie_dat=4;
					break;
				case 6: shibie_dat=5;
					break;
				case 7: shibie_dat=6;
					break;
				case 8: shibie_dat='-';//-
					break;
				case 9: shibie_dat=7;
					break;
				case 10: shibie_dat=8;
					break;
				case 11: shibie_dat=9;
					break;
				case 12: shibie_dat='C';//c清零键
					break;
				case 13: shibie_dat='.';//
					break;
				case 14: shibie_dat=0;
					break;
				case 15: shibie_dat='=';//=
					break;
				case 16: shibie_dat='D';//回删
					break;
				default: 
					break;				
			}
		}
		return(shibie_dat);
}
unsigned long pow(unsigned int x,unsigned int n)
{
   unsigned long xn=1;
   unsigned char i;
  for(i=0;i<n;i++)
  {
    xn=xn*x;
   }
   return xn;
}
