/*
 * LCD_4Bit.h
 *
 *  Created on: Apr 28, 2012
 *      Author: Amit Tandel
 */

#include<reg51.h>
void Initialize_LCD();
void Display_Data_LCD(unsigned char , unsigned int );
void Display_Char_LCD(unsigned char );
void Send_Command_LCD(unsigned char );
void Clear_LCD();
void Delay_LCD(unsigned int);
