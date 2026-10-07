#ifndef _LCD_H
#define _LCD_H

// Defininitions
#ifndef LCD_WIDTH
#define LCD_WIDTH	24
#endif

#ifndef LCD_LINES
#define LCD_LINES	2
#endif

#ifndef LCD_RS		// Register Select
#define	LCD_RS		PORTBbits.RB7
#endif

#ifndef LCD_RW
#define	LCD_RW		PORTBbits.RB5
#endif

#ifndef LCD_EN		// Enable
#define LCD_EN		PORTCbits.RC6
#endif

#ifndef LCD_DATA	// Data D4-D7 ( 4 bit mode )
#define LCD_DATA	PORTC
#endif

/* Strobe Enable On / Off */

#define	LCD_STROBE()	((LCD_EN = 1),(LCD_EN=0))

/*	Set the cursor position */

#define	lcd_cursor(x)	lcd_write(((x)&0x7F)|0x80)

/* write a byte to the LCD in 4 bit mode */

extern void lcd_write(unsigned char);

/* Clear and home the LCD */

extern void lcd_clear(void);

/* write a string of characters to the LCD */

extern void lcd_string(const char * s, const char fill);

/* Go to the specified position in line 1 */
extern void lcd_line1(unsigned char pos);

/* Go to the specified position in line 2 */
extern void lcd_line2(unsigned char pos);

/* Go to the specified position in line 3 */
extern void lcd_line3(unsigned char pos);

/* Go to the specified position in line 4 */
extern void lcd_line4(unsigned char pos);
	
/* intialize the LCD - call before anything else */

extern void lcd_init(void);

extern void lcd_character(char);

#endif