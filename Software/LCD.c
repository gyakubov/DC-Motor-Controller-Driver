/*
 *	LCD Interface
 *  Original Author: Craig Lee (c) 1998
 *
 *  Small Modifications done in this
 *  version by Morgan Demers.
 *	
 */

#include <p18lf14k50.h>
#include "Delay.h"
#include "LCD.h"

/* write a byte to the LCD in 4 bit mode */

void
lcd_write(unsigned char c)
{
	DelayUs(40);
	LCD_DATA &= 0xF0;
	LCD_DATA |= ( ( c >> 4 ) & 0x0F );
	LCD_STROBE();
	LCD_DATA &= 0xF0;
	LCD_DATA |= ( c & 0x0F );
	LCD_STROBE();
}

/*
 * 	Clear and home the LCD
 */

void
lcd_clear(void)
{
	LCD_RS = 0;
	lcd_write(0x1);
	DelayMs(2);
}

/* write a string of chars to the LCD */

void
lcd_string(const char * s, const char fill)
{
	unsigned char p = 0;
	char c;
	LCD_RS = 1;	// write characters
	while(*s != '\0') {
		p++;
		c = *s;
		lcd_write(*s++);
	}

	if( fill && p < LCD_WIDTH ) {
		while( p < LCD_WIDTH ) {
			p++;
			lcd_write(fill);
		}
 	}
}

/* write one character to the LCD */

void
lcd_character(char c)
{
	LCD_RS = 1;	// write characters
	lcd_write( c );
}


/*
 * Go to the specified position in line 1
 */

void
lcd_line1(unsigned char pos)
{
	LCD_RS = 0;
	lcd_write(0x80+pos);
}

/*
 * Go to the specified position in line 2
 */

void
lcd_line2(unsigned char pos)
{
	LCD_RS = 0;
	lcd_write(0xC0+pos);
}
/*
 * Go to the specified position in line 3
 */

void
lcd_line3(unsigned char pos)
{
	LCD_RS = 0;
	lcd_write(0x94+pos);
}
/*
 * Go to the specified position in line 4
 */

void
lcd_line4(unsigned char pos)
{
	LCD_RS = 0;
	lcd_write(0xD4+pos);
}
	
/* initialise the LCD - put into 4 bit mode */
void
lcd_init()
{
	char init_value;

	ADCON0 = 0x00;	// Disable analog pins on PORTA

	init_value = 0x3;
	TRISB  &= 0x80;
	TRISC  &= 0xF0;
	LCD_RS = 0;
	LCD_EN = 0;
	LCD_RW = 0;
	
	DelayMs(15);	// wait 15mSec after power applied,
	LCD_DATA &= 0xF0;
	LCD_DATA |= init_value;
	LCD_STROBE();
	DelayMs(5);
	LCD_STROBE();
	DelayUs(200);
	LCD_STROBE();
	DelayUs(200);
	LCD_DATA &= 0xF0;
	LCD_DATA |= 2;	// Four bit mode
	LCD_STROBE();

	lcd_write(0x28); // Set interface length
	lcd_write(0xC); // Display On, Cursor On, Cursor Blink
	lcd_clear();	// Clear screen
	lcd_write(0x6); // Set entry Mode
}