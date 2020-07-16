 /*******************************************************************************
* File Name: main.c
*	Date: 27 April 2017
* Version: 2.0
* Description:
* This is source code for Irrig System
*	Timer Added instead of for loop for delay
* Note:
* Owners: Amit Tandel
* Related Document:
* Code Tested With:
* PORT 0 : VALVES
* PORT 1 : LCD
* PORT 2 : KEYPAD
* PORT 3 : MOTOR
********************************************************************************
* Copyright : All rights reserved.
*******************************************************************************/

#include<reg51.h>
#include"keypad.h"
#include"lcd.h"

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

#define V_OPEN_TIME 10

void Timer_Init()
{							/* TMOD = |GATE|C/T|M1|M0|GATE|C/T|M1|M0|  */
	TMOD=0x01;	/* Timer 0,Mode 1 - 16 bit timer */
	TH0=0x00;		/* Counting will start from 0 upto 65534 */
	TL0=0x00;		
}
void Wait(unsigned int value)
{     
	unsigned int i;
	TH0=0x00;		/* reloading */
	TL0=0x00;	
	for(i=0;i<=value;i++)
	{
		TR0=1;		  /* Start the timer */ 
		while(TF0==0);	  /* wait till overflow */ 
		TR0=0;		  /* Stop the timer */ 
		TF0=0;			/* Clear the Flag */
	}
}

void main(void)
{
	P0 = 0x00;	// Port 0 as Output for Valves
	P1 = 0x00;	// Port 1 as Output for LCD
	P2 = 0xFF;	// Port 2 as Input for Keypad
	P3 = 0x00;	// Port 3 as Output for Motor

	Timer_Init();
	Initialize_LCD();
	Send_Command_LCD(0x80);		// Set Cursor at 1st Line
	Delay_LCD(5);
	Display_Data_LCD("Water   Chemical",16);
	Delay_LCD(5);
	Send_Command_LCD(0xC0);		// Set Cursor at 2nd Line
	Delay_LCD(5);
	
	Scan_Keypad();

	R3 = 1;	// Open 1st valve 
	Wait(V_OPEN_TIME);
	R1 = 1;	// Start Water Motor
	Wait(Chem_Time);
	R2 = 1;	// Open Chemical Valve
	Wait(Chem_Time);
	R2 = 0;	// Close Chemical Valve
	Wait(Water_Time);

	R4 = 1;	// Open 2nd Valve
	Wait(V_OPEN_TIME);
	R3 = 0;	// Close 1st Valve
	Wait(Chem_Time);
	R2 = 1;
	Wait(Chem_Time);
	R2 = 0;
	Wait(Water_Time);

	R5 = 1;	// Open 3rd Valve
	Wait(V_OPEN_TIME);
	R4 = 0;	// Close 2nd Valve
	Wait(Chem_Time);
	R2 = 1;
	Wait(Chem_Time);
	R2 = 0;
	Wait(Water_Time);

	R6 = 1;
	Wait(V_OPEN_TIME);
	R5 = 0;
	Wait(Chem_Time);
	R2 = 1;
	Wait(Chem_Time);
	R2 = 0;
	Wait(Water_Time);

	R7 = 1;
	Wait(V_OPEN_TIME);
	R6 = 0;
	Wait(Chem_Time);
	R2 = 1;
	Wait(Chem_Time);
	R2 = 0;
	Wait(Water_Time);

	R8 = 1;
	Wait(V_OPEN_TIME);
	R7 = 0;
	Wait(Chem_Time);
	R2 = 1;
	Wait(Chem_Time);
	R2 = 0;
	Wait(Water_Time);

	R9 = 1;
	Wait(V_OPEN_TIME);
	R8 = 0;
	Wait(Chem_Time);
	R2 = 1;
	Wait(Chem_Time);
	R2 = 0;
	Wait(Water_Time);

	R10 = 1;
	Wait(V_OPEN_TIME);
	R9 = 0;
	Wait(Chem_Time);
	R2 = 1;
	Wait(Chem_Time);
	R2 = 0;
	Wait(Water_Time);

	R1 = 0;	// Stop Water Motor
	Wait(Chem_Time);
	R10 = 0;	// Close last Valve
}