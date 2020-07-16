/*
Description: Valaves can be opened by the sequence decided by User.
Water motor & Chemical Motor Timing can be customised as per user requirement for each valve.
*/

#include<reg51.h>
#include<stdio.h>

#define LCD_PORT								P1
#define KEY_PORT								P2
#define LCD_CursorHome1stLine		Send_Command(0x80)
#define LCD_CursorHome2ndLine		Send_Command(0xC0)
#define LCD_CursorBlink					Send_Command(0x0F)
#define LCD_CursorON						Send_Command(0x0E)
#define LCD_MovCursorRight			Send_Command(0x14)

#define TRUE		1
#define FALSE		0
#define ON			1
#define OFF			0
#define OPEN		1
#define CLOSE		0

#define InitWaterTime	1

sbit RS=P3^2;	// LCD RS
sbit EN=P3^3;	// LCD EN
/* Keypad */
sbit ROW1=KEY_PORT^7;
sbit ROW2=KEY_PORT^6;
sbit ROW3=KEY_PORT^5;
sbit ROW4=KEY_PORT^4;
sbit COL1=KEY_PORT^3;
sbit COL2=KEY_PORT^2;
sbit COL3=KEY_PORT^1;
sbit COL4=KEY_PORT^0;
/* Motors */
sbit WATER_MOTOR	= P3^6;
sbit DOSE_MOTOR	= P3^7;
/* All Valves */
sbit VALVE1	= P0^0;
sbit VALVE2	= P0^1;
sbit VALVE3	= P0^2;
sbit VALVE4	= P0^3;
sbit VALVE5	= P0^4;
sbit VALVE6	= P0^5;
sbit VALVE7	= P0^6;
sbit VALVE8	= P0^7;

void Init();
//void Delay(unsigned int value);
void Send_Command(unsigned char comd);
void Display_Char(unsigned char c);
void Display_Data(unsigned char mdata[], unsigned int count);
void Clear_LCD();
void T0M1Delay(void);
void Sec_Delay();
void Minute_Delay();
//void Hour_Delay();

unsigned int ProgStartd = FALSE,ChangeDisplay = 1, ValveSetting = TRUE, WaterSetting = FALSE, DoseSetting = FALSE;
unsigned int WKey_Count=0, DKey_Count=0;
unsigned char LCD1stLine=128,LCD2ndLine=192;
long int Water_Time=0, Dose_Time=0, Time=0;
int j,ValveNumber = 1,Valve_Sequence[9],Water_Sequence[9],Dose_Sequence[9];
	
void Init()
{
	P0=0x00;		// P0 as O/P port for VALVES
	P1=0x00;		// P1 as O/P port for LCD
	P2=0xFF;		// P2 as i/p port for Keypad
	P3=0x00;		// P3 as O/P port for Motor
	
	WATER_MOTOR	= OFF;	// Water Motor OFF
	DOSE_MOTOR	= OFF;	// Chemical Motor OFF
	P0 = OFF;	// All valves OFF
	
	Send_Command(0x38);	// LCD as 2 Line, 5x7 Matrix
	//Delay(5);
	Send_Command(0x0C);	// Display ON, Cursor Blinking
	//Delay(5);
	Clear_LCD();
}

unsigned char ConvertToChar(int num)
{
	char c = num +48;
	return c;
}

void Delay(unsigned int value)
{
	unsigned int u,v;
	for(u=0;u<value;u++)
		for(v=0;v<100;v++);
}

void Sec_Delay(unsigned int sec)
{
	int i,j;
	for(j=0;j<sec;j++)
		for(i=0;i<20;i++)	// 1Sec Delay
			T0M1Delay();
}
void Minute_Delay(unsigned int min)
{
	int i,j;
	for(j=0;j<min;j++)
		for(i=0;i<1200;i++)	// 1Minute Delay
			T0M1Delay();
}

/*************Delay Using Timer *************/
void T0M1Delay()
{
	TMOD = 0x01;	//Timer 0, mode 1 (16 bit)
	TL0 = 0xFD;		// 50mS Delay. FFFFh-4BFDh = B402h = 46082+1 = 46083
	TH0 = 0x4B;		// 46083 X 1.085uS = 50mS
	TR0 = 1;			// Turn ON timer
	while(TF0 == 0);	// wait for TF0 to roll over
	TR0 = 0;			// Turn OFF Timer
	TF0 = 0;			// reset TF0	
}

void Send_Command(unsigned char comd)
{
	RS=0;
	EN=1;
	LCD_PORT = comd;
	Delay(10);
	EN=0;
	Delay(20);
}

void Display_Char(unsigned char c)
{
	RS=1;
	EN=1;
	LCD_PORT = c;
	Delay(100);
	EN=0;
	Delay(10);
}

void Display_Data(unsigned char mdata[], unsigned int count)
{
	unsigned char x;
	for(x=0;x<count;x++)
	{
		RS=1;
		EN=1;
		LCD_PORT = mdata[x];
		Delay(100);
		EN=0;
	}
	Delay(10);
}

void Clear_LCD()
{
	Send_Command(0x01);
	//Sec_Delay(1);
	Send_Command(0x02);
	//Sec_Delay(1);
}

unsigned int Read_Key()
{
	ROW1 = 0; ROW2 = 1; ROW3 = 1; ROW4 = 1;		
	if(COL1==0)	{		while(COL1==0);		return 1;	}
	if(COL2==0)	{		while(COL2==0);		return 2;	}
	if(COL3==0)	{		while(COL3==0);		return 3;	}
	if(COL4==0)	{		while(COL4==0);		return 10;}	//A
	
	ROW1 = 1; ROW2 = 0; ROW3 = 1; ROW4 = 1;		
	if(COL1==0)	{		while(COL1==0);		return 4;	}
	if(COL2==0)	{		while(COL2==0);		return 5;	}
	if(COL3==0)	{		while(COL3==0);		return 6;	}
	if(COL4==0)	{		while(COL4==0);		return 11;}	//B
	
	ROW1 = 1; ROW2 = 1; ROW3 = 0; ROW4 = 1;		
	if(COL1==0)	{		while(COL1==0);		return 7;	}
	if(COL2==0)	{		while(COL2==0);		return 8;	}
	if(COL3==0)	{		while(COL3==0);		return 9;	}
	if(COL4==0)	{		while(COL4==0);		return 12;} //C
	
	ROW1 = 1; ROW2 = 1; ROW3 = 1; ROW4 = 0;		
	if(COL1==0)	{		while(COL1==0);		return 14;} //*
	if(COL2==0)	{		while(COL2==0);		return 0;	}
	if(COL3==0)	{		while(COL3==0);		return 15;} //#
	if(COL4==0)	{		while(COL4==0);		return 13;} //D
	
	return 'n';	// No key
}

void main()
{
	Init();
	LCD_CursorHome1stLine;
	Display_Data("Welcome !!!",11);
	LCD_CursorHome2ndLine;
	Display_Data("Select Sequence",15);
	Sec_Delay(3);
	LCD_CursorBlink;
	while(1)
	{
		unsigned char Key = 'n';
		while(Key == 'n')
		{
			if(ChangeDisplay)
			{
				ChangeDisplay = FALSE;
				LCD_CursorHome1stLine;
				switch(ValveNumber)
				{
					case 1 : 
						//LCD_CursorHome1stLine;
						Display_Data("1st Valve : ",12);
						LCD_CursorHome2ndLine;
						Display_Data("W:        D:   ",15);
						Send_Command(LCD1stLine+12);
					break;
					case 2 : 
						//LCD_CursorHome1stLine;
						Display_Data("2nd Valve : ",12);
						//LCD_CursorHome2ndLine;
						//Display_Data("W:        D:   ",15);
						//Send_Command(LCD1stLine+12);
					break;
					case 3 : 
						//LCD_CursorHome1stLine;
						Display_Data("3rd Valve : ",12);
						//LCD_CursorHome2ndLine;
						//Display_Data("W:        D:   ",15);
						//Send_Command(LCD1stLine+12);
					break;					
					case 4 : 
						//LCD_CursorHome1stLine;
						Display_Data("4th Valve : ",12);
						//LCD_CursorHome2ndLine;
						//Display_Data("W:        D:   ",15);
						//Send_Command(LCD1stLine+12);
					break;
					case 5 : 
						//LCD_CursorHome1stLine;
						Display_Data("5th Valve : ",12);
						//LCD_CursorHome2ndLine;
						//Display_Data("W:        D:   ",15);
						//Send_Command(LCD1stLine+12);
					break;
					case 6 : 
						//LCD_CursorHome1stLine;
						Display_Data("6th Valve : ",12);
						//LCD_CursorHome2ndLine;
						//Display_Data("W:        D:   ",15);
						//Send_Command(LCD1stLine+12);
					break;
					case 7 : 
						//LCD_CursorHome1stLine;
						Display_Data("7th Valve : ",12);
						//LCD_CursorHome2ndLine;
						//Display_Data("W:        D:   ",15);
						//Send_Command(LCD1stLine+12);
					break;
					case 8 : 
						//LCD_CursorHome1stLine;
						Display_Data("8th Valve : ",12);
						//LCD_CursorHome2ndLine;
						//Display_Data("W:        D:   ",15);
						//Send_Command(LCD1stLine+12);
					break;					
				}
			}
			Key = Read_Key();
			if(Key != 'n')
			{
				if(Key == 10)	// A means OK for that Valve-setting
				{
					ChangeDisplay = TRUE;
					ValveNumber++;	// Increment ValveNumber
					if(ValveNumber > 8)	// Restart Valve Sequence if Number of Valves exceeds 8
					{
						ValveNumber = 1;
					}
				}
				if(Key == 13)	// Start program on D
				{
					ProgStartd = TRUE;
					Clear_LCD();
					LCD_CursorHome1stLine;
					Display_Data("Program Started",15);
					LCD_CursorHome2ndLine;
					break;	// break from while(Key == 'n')
				}
				if(ValveSetting == TRUE)
				{
					if((Key > 0)&&(Key < 9))	// accept only 1 to 8
					{
						Send_Command(LCD1stLine+12);
						Display_Char(ConvertToChar(Key));
						Valve_Sequence[ValveNumber] = Key;
						ValveSetting = FALSE;
						WaterSetting = TRUE;
						Send_Command(LCD2ndLine+2);	// Set cursor at 2nd line 2nd position
					}					
				}
				else if(WaterSetting == TRUE)
				{
					++WKey_Count;
					if(WKey_Count == 1)
					{
						Water_Time = Key*100;
						Display_Char(ConvertToChar(Key));
					}
					else if(WKey_Count == 2)
					{
						Water_Time = Water_Time + Key*10;
						Display_Char(ConvertToChar(Key));
					}
					else if(WKey_Count == 3)
					{
						Water_Time = Water_Time + Key;
						Display_Char(ConvertToChar(Key));
						WaterSetting = FALSE;
						DoseSetting = TRUE;
						WKey_Count = 0;
						Water_Sequence[ValveNumber] = Water_Time;	// Store water time in array
						Send_Command(LCD2ndLine+12);	// Set Cursor at 2nd Line 12th Position
					}
				}
				else if(DoseSetting == TRUE)
				{
					++DKey_Count;
					if(DKey_Count == 1)
					{
						Dose_Time = Key*100;
						Display_Char(ConvertToChar(Key));
					}
					else if(DKey_Count == 2)
					{
						Dose_Time = Dose_Time + Key*10;
						Display_Char(ConvertToChar(Key));
					}
					else if(DKey_Count == 3)
					{
						Dose_Time = Dose_Time + Key;
						Display_Char(ConvertToChar(Key));
						ValveSetting = TRUE;
						DoseSetting = FALSE;
						DKey_Count = 0;
						Dose_Sequence[ValveNumber] = Dose_Time;	// Store Dose time in array
						Send_Command(LCD1stLine+12);	// Set Cursor at 1st Line
					}
				}
			}
		} // while(Key == 'n') loop
		
		if(ProgStartd)
		{
				Clear_LCD();
			/* Start Motors & Open Valves */
			ProgStartd = FALSE;	/* RESET Program status */
			//Time = Water_Time-Chem_Time-InitWaterTime;	// 
			//Time = 1;	// For testing purpose
			for(j = 1; j <= ValveNumber; j++)
			{
				switch(Valve_Sequence[j])
				{
					case 1:
						VALVE1 = OPEN;
						LCD_CursorHome2ndLine;
						Display_Data("VALVE 1 OPEN",12);
						Sec_Delay(10);	// WAIT FOR 10 SEC
						P0 = 0x01;	// Valve 1 OPEN, rest Closed
						WATER_MOTOR = ON;
						Minute_Delay(InitWaterTime);
						//if(Dose_Sequence[j]>0)
							DOSE_MOTOR = ON;
						Minute_Delay(Dose_Sequence[j]);
						DOSE_MOTOR = OFF;
						Minute_Delay(Water_Sequence[j]);
						//Minute_Delay(Time);
					break;
					
					case 2:
						VALVE2 = OPEN;
						LCD_CursorHome2ndLine;
						Display_Data("VALVE 2 OPEN",12);
						Sec_Delay(10);	// WAIT FOR 10 SEC
						P0 = 0x02;	// Valve 2 OPEN, rest Closed
						WATER_MOTOR = ON;
						Minute_Delay(InitWaterTime);
						//if(Dose_Sequence[j]>0)
							DOSE_MOTOR = ON;
						Minute_Delay(Dose_Sequence[j]);
						DOSE_MOTOR = OFF;
						Minute_Delay(Water_Sequence[j]);
						//Minute_Delay(Time);
					break;
					
					case 3:
						VALVE3 = OPEN;
						LCD_CursorHome2ndLine;
						Display_Data("VALVE 3 OPEN",12);			
						Sec_Delay(10);	// WAIT FOR 10 SEC
						P0 = 0x04;	// Valve 3 OPEN, rest Closed
						WATER_MOTOR = ON;
						Minute_Delay(InitWaterTime);
						//if(Dose_Sequence[j]>0)
							DOSE_MOTOR = ON;
						Minute_Delay(Dose_Sequence[j]);
						DOSE_MOTOR = OFF;
						Minute_Delay(Water_Sequence[j]);
						//Minute_Delay(Time);			
					break;
					
					case 4:
						VALVE4 = OPEN;
						LCD_CursorHome2ndLine;
						Display_Data("VALVE 4 OPEN",12);			
						Sec_Delay(10);	// WAIT FOR 10 SEC
						P0 = 0x08;	// Valve 4 OPEN, rest Closed
						WATER_MOTOR = ON;
						Minute_Delay(InitWaterTime);
						//if(Dose_Sequence[j]>0)
							DOSE_MOTOR = ON;
						Minute_Delay(Dose_Sequence[j]);
						DOSE_MOTOR = OFF;
						Minute_Delay(Water_Sequence[j]);
						//Minute_Delay(Time);			
					break;	
				
					case 5:
						VALVE5 = OPEN;
						LCD_CursorHome2ndLine;
						Display_Data("VALVE 5 OPEN",12);			
						Sec_Delay(10);	// WAIT FOR 10 SEC
						P0 = 0x10;	// Valve 5 OPEN, rest Closed
						WATER_MOTOR = ON;
						Minute_Delay(InitWaterTime);
						//if(Dose_Sequence[j]>0)
							DOSE_MOTOR = ON;
						Minute_Delay(Dose_Sequence[j]);
						DOSE_MOTOR = OFF;
						Minute_Delay(Water_Sequence[j]);
						//Minute_Delay(Time);			
					break;
					
					case 6:
						VALVE6 = OPEN;
						LCD_CursorHome2ndLine;
						Display_Data("VALVE 6 OPEN",12);			
						Sec_Delay(10);	// WAIT FOR 10 SEC
						P0 = 0x20;	// Valve 6 OPEN, rest Closed
						WATER_MOTOR = ON;
						Minute_Delay(InitWaterTime);
						//if(Dose_Sequence[j]>0)
							DOSE_MOTOR = ON;
						Minute_Delay(Dose_Sequence[j]);
						DOSE_MOTOR = OFF;
						Minute_Delay(Water_Sequence[j]);
						//Minute_Delay(Time);			
					break;
					
					case 7:
						VALVE7 = OPEN;
						LCD_CursorHome2ndLine;
						Display_Data("VALVE 7 OPEN",12);			
						Sec_Delay(10);	// WAIT FOR 10 SEC
						P0 = 0x40;	// Valve 7 OPEN, rest Closed
						WATER_MOTOR = ON;
						Minute_Delay(InitWaterTime);
						//if(Dose_Sequence[j]>0)
							DOSE_MOTOR = ON;
						Minute_Delay(Dose_Sequence[j]);
						DOSE_MOTOR = OFF;
						Minute_Delay(Water_Sequence[j]);
						//Minute_Delay(Time);			
					break;
					
					case 8:
						VALVE8 = OPEN;
						LCD_CursorHome2ndLine;
						Display_Data("VALVE 8 OPEN",12);			
						Sec_Delay(10);	// WAIT FOR 10 SEC
						P0 = 0x80;	// Valve 8 OPEN, rest Closed
						WATER_MOTOR = ON;
						Minute_Delay(InitWaterTime);
						//if(Dose_Sequence[j]>0)
							DOSE_MOTOR = ON;
						Minute_Delay(Dose_Sequence[j]);
						DOSE_MOTOR = OFF;
						Minute_Delay(Water_Sequence[j]);
						//Minute_Delay(Time);			
					break;
					default: break;
				}	// end of switch()
			}	// end of for()
			
			WATER_MOTOR = OFF;
			Sec_Delay(10);	// WAIT FOR 10 SEC
			P0 = OFF;	// Close All valves
			
			Clear_LCD();
			LCD_CursorHome1stLine;
			Display_Data("Program Finished",16);
			LCD_CursorHome2ndLine;
			Display_Data("RESET to Start",14);
			//break;	// break from forever loop
		}
	}	// while(1) loop
}