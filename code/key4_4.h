#ifndef _KEY4_4_H_
#define _KEY4_4_H_

#include <reg51.h>
#define	KEY_PORT  P3

//矩阵键盘扫描函数：无按键按下或无效时返回0；有效返回1-16
unsigned char keybord_sacn();//矩阵键盘扫描函数

/*读按键对应数据函数*/
/* 按键有效返回：
			0-9对应0-9，
	 按键无效返回：255
*/
unsigned char read_keydat(void);
unsigned long pow(unsigned int x,unsigned int n);
#endif

