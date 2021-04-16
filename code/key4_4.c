#include "key4_4.h"
#include "delay.h"

unsigned char keybord_sacn(void)
{
	unsigned char h,l,keynum,i=0;
  keynum=0;h=0;l=0;i=0;
  KEY_PORT=0xf0;//��Ϊ1����Ϊ0��Ŀ���Ƿ�������һ�б�����
  if(KEY_PORT!=0xf0)	//�������ԭ����ֵ��֤���а�������
  {
		Delay_1ms();
		if(KEY_PORT!=0xf0)  //�����ٴ�ȷ�ϰ����Ƿ���Ч
		{
			switch(KEY_PORT)					//ȷ������һ�еİ���������
			{
				 case(0xe0):   l=1;break;		   //��һ��
				 case(0xd0):   l=2;break;
				 case(0xb0):   l=3;break;
				 case(0x70):   l=4;break;
				 default : break;
			}
			KEY_PORT=0x0f;		// //��Ϊ0����Ϊ1��Ŀ���Ƿ�������һ�б�����
			switch(KEY_PORT)					//ȷ������һ�еİ���������
			{
				 case(0x0e):   h=1;break;		   //��һ��
				 case(0x0d):   h=2;break;
				 case(0x0b):   h=3;break;
				 case(0x07):   h=4;break;
				 default : break;
			}
			if(h>0 && l>0)//�ٴ�ȷ�ϰ��������Ƿ���Ч,���ж���Ϊ0ʱ������Ч��
			keynum=(h-1)*4+l;//�����кź��кſ�����ȷ������һ��������
			while(KEY_PORT!=0x0f && i<255){Delay_1ms();i++;}//�жϰ����ͷ�
		}		
  }
  return (keynum);
}

/*��������Ӧ���ݺ���*/
/* ������Ч���أ�
			0-9��Ӧ0-9��
	 ������Ч���أ�255
*/
unsigned char read_keydat(void)
{
	unsigned char temp=0,num=0,shibie_dat=255;
	temp=keybord_sacn();
	if(temp!=0)//������Ч
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
				case 12: shibie_dat='C';//c�����
					break;
				case 13: shibie_dat='.';//
					break;
				case 14: shibie_dat=0;
					break;
				case 15: shibie_dat='=';//=
					break;
				case 16: shibie_dat='D';//��ɾ
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
