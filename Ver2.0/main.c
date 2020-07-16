/*******************************************************************************
* File Name: main.c
*
* Version: 2.0
*
* Description:
*  This is source code for Irrig System
*	 Timer Added instead of for loop for delay
*
* Note:
*
* Owners:
*  Amit Tandel
*
* Related Document:
*
* Code Tested With:
*
********************************************************************************
* Copyright : All rights reserved.
*******************************************************************************/

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

#define M1_TIME	100
#define M2_TIME 20
#define V_OPEN_TIME 10
void Init_Timer(void)
{
	TMOD=0x01;	/* Timer 0,Mode 1 */
	TH0=0x00;
	TL0=0x00;
}

void Wait(unsigned int value)
{
	unsigned int i;
	for(i=0;i<value;i++);
	{
		TR0=1;		  /* Start the timer */ 
		while(TF0==0);	  /* wait till overflow */ 
		TR0=0;		  /* Stop the timer */ 
		TF0=0;
	}
}

void main(void)
{
	while(1)
	{
		Init_Timer();
		
		P0 = 0;
		P3 = 0;
		R3 = 1;
		Wait(V_OPEN_TIME);
		R1 = 1;
		Wait(M2_TIME);
		R2 = 1;
		Wait(M2_TIME);
		R2 = 0;
		Wait(M1_TIME);
		
		R4 = 1;
		Wait(V_OPEN_TIME);
		R3 = 0;
		Wait(M2_TIME);
		R2 = 1;
		Wait(M2_TIME);
		R2 = 0;
		Wait(M1_TIME);
		
		R5 = 1;
		Wait(V_OPEN_TIME);
		R4 = 0;
		Wait(M2_TIME);
		R2 = 1;
		Wait(M2_TIME);
		R2 = 0;
		Wait(M1_TIME);
		
		R6 = 1;
		Wait(V_OPEN_TIME);
		R5 = 0;
		Wait(M2_TIME);
		R2 = 1;
		Wait(M2_TIME);
		R2 = 0;
		Wait(M1_TIME);
		
		R7 = 1;
		Wait(V_OPEN_TIME);
		R6 = 0;
		Wait(M2_TIME);
		R2 = 1;
		Wait(M2_TIME);
		R2 = 0;
		Wait(M1_TIME);
		
		R8 = 1;
		Wait(V_OPEN_TIME);
		R7 = 0;
		Wait(M2_TIME);
		R2 = 1;
		Wait(M2_TIME);
		R2 = 0;
		Wait(M1_TIME);
		
		R9 = 1;
		Wait(V_OPEN_TIME);
		R8 = 0;
		Wait(M2_TIME);
		R2 = 1;
		Wait(M2_TIME);
		R2 = 0;
		Wait(M1_TIME);
		
		R10 = 1;
		Wait(V_OPEN_TIME);
		R9 = 0;
		Wait(M2_TIME);
		R2 = 1;
		Wait(M2_TIME);
		R2 = 0;
		Wait(M1_TIME);
		
		R1 = 0;
		Wait(M2_TIME);
		R10 = 0;
	}
}

