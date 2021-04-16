#ifndef _DHT11_H_
#define _DHT11_H_
#include <reg51.h>

sbit DHT11_PIN=P2^3;
extern unsigned char Humi_H,Humi_L,Temp_H,Temp_L;
void Delay18ms();
void Delay40us();
unsigned char receive_byte(void);
bit Read_DHT11(void);
#endif


