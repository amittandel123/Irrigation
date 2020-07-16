
#include"lcd.h"
#include"keypad.h"

sbit Row1=P2^0;
sbit Row2=P2^1;
sbit Row3=P2^2;
sbit Row4=P2^3;
sbit Col1=P2^4;
sbit Col2=P2^5;
sbit Col3=P2^6;
sbit Col4=P2^7;

unsigned int Scan_Col1();
unsigned int Scan_Col2();
unsigned int Scan_Col3();
unsigned int Scan_Col4();

unsigned int Key_Value=0,WKey_Count=0,CKey_Count=0;
unsigned char position=192;
unsigned int Water_Time;
unsigned int Chem_Time;

int Water_Flag = 1;
int Chem_Flag = 0;

void Scan_Keypad()
{
//	Initialize_LCD();
	while(1)
	{
		Col1=Col2=Col3=Col4=1;	// Make column pins i/p
		Row1=Row2=Row3=Row4=0;	// Make Row pins o/p
		if(Col1==0)
			Key_Value = Scan_Col1();
		else if(Col2==0)
			Key_Value = Scan_Col2();
		else if(Col3==0)
			Key_Value = Scan_Col3();
		else if(Col4==0)
			Key_Value = Scan_Col4();
		if(Key_Value != '\0')
		{
			if(Key_Value == 15)	/* Key - D,Start Program */
			{
				Send_Command_LCD(0x80);		// Set Cursor at 1st Line
				Display_Data_LCD("PROGRAM STARTED",15);
				break;
			}
			// Else Set Water Time
			else if(Water_Flag)	
			{
				WKey_Count++;
				if(WKey_Count == 1)
				{
					Water_Time = Key_Value * 100;
					Display_Char_LCD(Key_Value);
					Send_Command_LCD(position+1);		// Set Cursor at 2nd Line 2nd Position
				}else 
				if(WKey_Count == 2)
				{
					Water_Time = Water_Time + Key_Value * 10;
					Display_Char_LCD(Key_Value);
					Send_Command_LCD(position+2);		// Set Cursor at 2nd Line 3rd Position
				}else 
				if(WKey_Count == 3)
				{
					Water_Time = Water_Time + Key_Value;
					Display_Char_LCD(Key_Value);
					Send_Command_LCD(position+11);		// Set Cursor at 2nd Line 11th Position, below Chemical
					Water_Flag = 0;		// Reset Water Flag & set Chem Flag
					Chem_Flag = 1;
					WKey_Count = 0;		// Reset waterkey count
				}
			}
			// If water time is set then Set Chemical Time
			else if(Chem_Flag)	
			{
				CKey_Count++;
				if(CKey_Count == 1)
				{
					Chem_Time = Key_Value * 100;
					Display_Char_LCD(Key_Value);
					Send_Command_LCD(position+12);		// Set Cursor at 2nd Line 12th Position
				}else 
				if(CKey_Count == 2)
				{
					Chem_Time = Water_Time + Key_Value * 10;
					Display_Char_LCD(Key_Value);
					Send_Command_LCD(position+13);		// Set Cursor at 2nd Line 13th Position
				}else 
				if(CKey_Count == 3)
				{
					Chem_Time = Water_Time + Key_Value;
					Display_Char_LCD(Key_Value);
					Send_Command_LCD(position);		// Set Cursor at 2nd Line 3rd Position
					Water_Flag = 1;		// again allow to set water time if required
					Chem_Flag = 0;		// reset chem flag
					CKey_Count = 0;		// reset chem-key count
				}
			}
		}
	}
}

unsigned int Scan_Col1()
{
	Row1=Row2=Row3=Row4=1;
	Row1=0;
	if(Col1==0)	/* 1 */
	{
		while(Col1==0);
		return 1;
	}
	Row1=1;
	Row2=0;
	if(Col1==0) /* 4 */
	{
		while(Col1==0);
		return 4;
	}
	Row2=1;
	Row3=0;
	if(Col1==0) /* 7 */
	{
		while(Col1==0);
		return 7;
	}
	Row3=1;
	Row4=0;
	if(Col1==0)	/* * */
	{
		while(Col1==0);
//		return 10;
		return '\0';
	}
	Row4=1;
			return '\0';
}

unsigned int Scan_Col2()
{
	Row1=Row2=Row3=Row4=1;
	Row1=0;
	if(Col2==0)	/* 2 */
	{
		while(Col2==0);
		return 2;
	}
	Row1=1;
	Row2=0;
	if(Col2==0)	/* 5 */
	{
		while(Col2==0);
		return 5;
	}
	Row2=1;
	Row3=0;
	if(Col2==0)	/* 8 */
	{
		while(Col2==0);
		return 8;
	}
	Row3=1;
	Row4=0;
	if(Col2==0)	/* 0 */
	{
		while(Col2==0);
		return 0;
	}
	Row4=1;
			return '\0';
}

unsigned int Scan_Col3()
{
	Row1=Row2=Row3=Row4=1;
	Row1=0;
	if(Col3==0)	/* 3 */
	{
		while(Col3==0);
		return 3;
	}
	Row1=1;
	Row2=0;
	if(Col3==0)	/* 6 */
	{
		while(Col3==0);
		return 6;
	}
	Row2=1;
	Row3=0;
	if(Col3==0)	/* 9 */
	{
		while(Col3==0);
		return 9;
	}
	Row3=1;
	Row4=0;
	if(Col3==0)	/* # */
	{
		while(Col3==0);
//		return 11;
		return '\0';
	}
	Row4=1;
			return '\0';
}

unsigned int Scan_Col4()
{
	Row1=Row2=Row3=Row4=1;
	Row1=0;
	if(Col4==0)	/* A */
	{
		while(Col4==0);
//		return 12;
				return '\0';
	}
	Row1=1;
	Row2=0;
	if(Col4==0)	/* B */
	{
		while(Col4==0);
//		return 13;
				return '\0';
	}
	Row2=1;
	Row3=0;
	if(Col4==0)	/* C */
	{
		while(Col4==0);
//		return 14;
				return '\0';
	}
	Row3=1;
	Row4=0;
	if(Col4==0)	/* D */
	{
		while(Col4==0);
		return 15;
	}
	Row4=1;
			return '\0';
}