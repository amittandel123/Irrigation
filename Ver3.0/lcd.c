/*********************************************************
 * Program to interface 16 X 2 LCD with 8051
 *  Created on: Apr 28, 2017
 *  Author: Amit Tandel
 *
 *	P3.2 = RS
 *	P3.3 = EN
 *
 *	DATA = PORT1
 *********************************************************/
#include"lcd.h"

sbit RS=P3^2;
sbit EN=P3^3;
void Initialize_LCD();
void Display_Data_LCD(unsigned char, unsigned int );
void Display_Char_LCD(unsigned char );
void Send_Command_LCD(unsigned char );
void Clear_LCD();
void Delay_LCD(unsigned int);

void Initialize_LCD()
{
	Send_Command_LCD(0x38);
	Delay_LCD(5);
	Send_Command_LCD(0x0E);
	Delay_LCD(5);
	Clear_LCD();
	Delay_LCD(5);
}

void Send_Command_LCD(unsigned char comd)
{
	RS=0;
	EN=1;
	P1=comd;
	Delay_LCD(5);
	EN=0;
}

void Delay_LCD(unsigned int value)
{
	unsigned int u,v;
	for(u=0;u<value;u++)
		for(v=0;v<100;v++);
}

void Display_Data_LCD(unsigned char mdata[], unsigned int count)
{
	unsigned char x;
	for(x=0;x<count;x++)
	{
		RS=1;
		EN=1;
		P1= mdata[x];
		Delay_LCD(100);
		EN=0;
	}
}

void Display_Char_LCD(unsigned char a)
{
		RS=1;
		EN=1;
		P1= a;
		Delay_LCD(100);
		EN=0;
}

void Clear_LCD()
{
	Send_Command_LCD(0x01);
	Delay_LCD(5);
	Send_Command_LCD(0x02);
	Delay_LCD(5);
}
