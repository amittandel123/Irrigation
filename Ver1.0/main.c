
/**************************************************
Date: 26 April 2017
Author: Amit Tandel
Description: No timer, Delay using for loop
						 Keypad not added
***************************************************/


#include<reg51.h>
/* Motors */
sbit R1		= P3^0;
sbit R2		= P3^1;
/* All Valves */
sbit R3		= P0^0;
sbit R4		= P0^1;
sbit R5		= P0^2;
sbit R6		= P0^3;
sbit R7		= P0^4;
sbit R8		= P0^5;
sbit R9		= P0^6;
sbit R10	= P0^7;
/* Keypad */
void Delay(unsigned int);
void main(void)
{
	P0 = 0;
	P3 = 0;
	R3 = 1;
	Delay(1);
	R1 = 1;
	Delay(5);
	R2 = 1;
	Delay(5);
	R2 = 0;
	Delay(10);
	
	R4 = 1;
	Delay(1);
	R3 = 0;
	Delay(5);
	R2 = 1;
	Delay(5);
	R2 = 0;
	Delay(10);
	
	R5 = 1;
	Delay(1);
	R4 = 0;
	Delay(5);
	R2 = 1;
	Delay(5);
	R2 = 0;
	Delay(10);
	
	R6 = 1;
	Delay(1);
	R5 = 0;
	Delay(5);
	R2 = 1;
	Delay(5);
	R2 = 0;
	Delay(10);
	
	R7 = 1;
	Delay(1);
	R6 = 0;
	Delay(5);
	R2 = 1;
	Delay(5);
	R2 = 0;
	Delay(10);
	
	R8 = 1;
	Delay(1);
	R7 = 0;
	Delay(5);
	R2 = 1;
	Delay(5);
	R2 = 0;
	Delay(10);
	
	R9 = 1;
	Delay(1);
	R8 = 0;
	Delay(5);
	R2 = 1;
	Delay(5);
	R2 = 0;
	Delay(10);
	
	R10 = 1;
	Delay(1);
	R9 = 0;
	Delay(5);
	R2 = 1;
	Delay(5);
	R2 = 0;
	Delay(10);
	
	R1 = 0;
	Delay(5);
	R10 = 0;
}

void Delay(unsigned int value)
{
	unsigned int i;
	for(j=0;j<value;j++)
		for(i=0;i<60000;i++);
}