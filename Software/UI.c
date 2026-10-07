// Includes
#include "UI.h"
#include "LCD.h" // LCD Library Has Code To Actually Initialize, Write To LCD

// Extern Variables From Main Program

// Interface Variables
static char buf[2][LCD_WIDTH+1] = {"",""}; // Buffers For LCD.
static char on_menu = 0; // ID Of Menu Currently Being Viewed
static char on_sub_menu = 0; // ID Of Sub Menu Currently Being Viewed
static char update_menu = 1; // Does The Menu Need To Be Rendered?
static int update_menu_item = 0; // When !0 indicates that menu item's data should change by this variable's value
static char button_states[3][3] = {{0,-1,0}, // Left Button  (on/off,value,hold counter)
								   {0,0,0},  // Menu Button  (on/off,value,hold counter)
								   {0,1,0}}; // Right Button (on/off,value,hold counter)
static unsigned char max_menu = 3; // Define Number Of Main Menus : 0-n
static char menu_dir = 1; // Menu Direction ( Left = -1, Right = 1 )
static unsigned char max_sub_menu[4] = {2,2,7,2}; // Define Number Of Sub-Menus : 0-n
static unsigned char update_lcd = 1; // Does The LCD Need To Be Rendered?

/*
Function: goto_menu
Description: Jump directly to Menu / Sub Menu

Params:
menu_id - main menu id to go to
sub_menu_id - sub_menu_id to go to
*/
void goto_menu(unsigned char menu_id, unsigned char sub_menu_id) {
	on_menu = menu_id;
	on_sub_menu = sub_menu_id;
}

/*
Function: ui_process
Description: Should be called at whatever interval by main
             program in order to update the menu & render
             the LCD

Params:
ticks - counter from main program's timer interrupt routine.
        it gets reset to 0 every second, though that doesn't
        mean much here without knowing the 'samples/s'. We 
        could also pass in, but we are only using it for the
        INTERFACE_UPDATE_DELAY in order to slow down the update
        of the LCD & Menus...
*/
void ui_process(unsigned int ticks) {
		if( update_menu_item != 0 ) {
			update_menu_data(on_menu,on_sub_menu,update_menu_item);
			update_menu_item = 0;
			update_menu = 1;
		}

		if( ticks % INTERFACE_UPDATE_DELAY == 0 ) {
			process_buttons();
			update_menu = 1;
		}

		if( update_menu ) {
			render_menu(on_menu,on_sub_menu,LCD_WIDTH,&buf[0][0],&buf[1][0]);
			update_menu = 0;
			update_lcd = 1;
		}

		if( update_lcd ) {
            render_lcd();
		}
}

/*
Function: ui_init
Description: Initialize LCD & Output Splash Screen
*/
void ui_init(void) {
	lcd_init();
	lcd_clear();

	// Display Splash Screen, Cheezy I know...
	sjoinrom(&buf[0][0],"Gingery Lathe");
	sjoinrom(&buf[1][0],"Morgan Varient - v1.2e");

	render_lcd();
}

int get_button_state(char button_id) {
	char ret = 0;
	char i;

	if( button_id == -1 ) { // Any Buttons Active?
		for( i = 0; i < BUTTON_COUNT; i++) {
			if( button_states[i][0] != 0 ) {
				ret = 1;
				break;
			}
   		} 
	} else if( button_states[button_id][0] != 0 ) { // Button Current Pressed
		if( button_states[button_id][2] < BUTTON_HOLD_TIME ) { // Consdered Held Yet?
			ret = 1;
		} else {
			ret = 2;
		}
	}

	return ret;
}

/*
Function: get_menu_direction
Description: Returns the direction with which the menu last changed

Returns: Last Menu Change Direction ( 1 = Right, -1 = Left )
*/
char get_menu_direction(void) {
	return menu_dir;
}

/*
Function: process_buttons
Description: Checks the button states and increments the
             Button Held Counters for those buttons that are
             On. If a Button is Held, will assign button's
             value multipled by 'BUTTON_HOLD_MULTIPLIER' to
             update_menu_item such that at the next 'ui_process'
             call the menu data will be updated accordingly.
*/
void process_buttons(void) {
	int i;

	for( i = 0; i < 3; i++ ) {
		if( button_states[i][0] == 1 ) {
			if( button_states[i][2] < BUTTON_HOLD_TIME ) {
				button_states[i][2]++; // Delay
			} else if( button_states[i][1] != 0 ) {
				update_menu_item = button_states[i][1]*BUTTON_HOLD_MULTIPLIER;
			}
		}
	}
}

/*
Function: process_button
Description: Called From Main Program when a Button's State
             Changes. The Button's State is defined by 
             'button_value' as 1=ON, 0=OFF. 

Params:
button_id - id number of button
button_value - value of button's state 1=ON, 0=OFF

Returns: Last Known State Of Button
*/
int process_button(unsigned char button_id,unsigned char button_value) {
	int ret;
	ret = 0;

    if( button_value == 1 ) {
		if( button_states[button_id][2] < BUTTON_HOLD_TIME ) {
			ret = 1;
		} else {
			ret = 2;
		}
		
		button_states[button_id][0] = 0;
	} else {
		button_states[button_id][0] = 1;
	}

	button_states[button_id][2] = 0;

	// Process Menu Action...
	process_menu_action(button_id,ret,button_states[button_id][1]);

	// Return Button State
	return ret;
}

/*
Function: process_menu_action
Description: Handles the Interaction Between the Buttons & Menu
             System. Pressing the 'Menu' Button will change the
             'Sub Menu', while Holding the 'Menu' Button and
             either Pressing the 'Left' or 'Right' buttons will
             chainge the 'Main Menu'. If the 'Menu' Button is
             not held then the Menu Item's Data will be updated
             by 'Value'.

Params:
button_id - ID of Button
button_state - 1=ON,0=OFF
value - Button Value -1 = Left, 0 = Menu, 1 = Right
*/
void process_menu_action(unsigned char button_id,unsigned char button_state,char value) {
    unsigned char t = 0;

	if( button_id == 1 ) { // Menu Button
		if( button_state == 1 ) {
			on_sub_menu++;
			if( on_sub_menu > max_sub_menu[on_menu] ) {
				on_sub_menu = 0;
			}
		}
	} else {
		if( button_state == 1 ) { // Button On
			t = get_button_state(1); // Get 'Menu' Button's State
			if( t == 2 ) { // Is Menu Held?
				menu_dir = value;
				on_menu += value; // Change Main Menu By Value
				if( on_menu < 0 ) on_menu = max_menu;
				else if( on_menu > max_menu ) on_menu = 0;
				on_sub_menu = 0; // Reset Sub Menu
			} else { // Menu Not Held, Update Menu Data By Value
				update_menu_item += value;
			}
		}
	}

	// Render The Menu
	update_menu = 1;
}

/*
Function: render_lcd
Description: Writes Buffers To LCD
*/
void render_lcd(void) {
	lcd_line1(0);
	lcd_string(&buf[0][0],' ');
	lcd_line2(0);
	lcd_string(&buf[1][0],' ');

    update_lcd = 0;
}

/*
Function: scopy_right
Description: Copy's Contents Of One String to the Right Side
             of Another String. Used for adding small details
             to the right side of the LCD Screen.

Params:
s1 - main string being copied to
s2 - string being copied from
len - length of s1 - could have defined s1_len = strlen but
      s1 is always LCD_WIDTH so we just pass it in...
*/
void scopy_right(char* s1, const char* s2, unsigned char len) {
    unsigned char i = 0;
	unsigned char j = 0;
	unsigned char s2_len = 0;

    while( *(s2+s2_len) != '\0' ) {
        s2_len++;
    }

    for( i = 0; i < len; i++ ) {
        if( *(s1+i) == '\0' ) {
			j = 1;
		}
		if( j == 1 ) {
			*(s1+i) = ' ';
		}
    }

	for( i = 0; i < s2_len; i++ ) {
		j = (len-s2_len)+i;
		*(s1+j) = *(s2+i);
	}

	*(s1+len) = '\0';
}

/*
Function: sjoin
Description: Joins a string to the end of d ( destination string )
             Was using 'sprintf' but that is a bit robust for my needs, 
             this function dropped program memory usage by over 2k when
             it replaced sprintf.

Params:
d - destination string to append to
s - string to join to d
*/
void sjoin(char* d,const char* s) {
	unsigned char i = 0;
    unsigned char j = 0;

    while( *(d+i) != '\0' ) {
        i++;
    }

    while( *(s+j) != '\0' ) {
		*(d+i) = *(s+j);
		i++;
		j++;
    }

    *(d+i) = '\0';
}

/*
Function: sjoinrom
Description: *Appends String From Program Memory

             Joins a string to the end of d ( destination string )
             Was using 'sprintf' but that is a bit robust for my needs, 
             this function dropped program memory usage by over 2k when
             it replaced sprintf.

Params:
d - destination string to append to
s - string to join to d
*/
void sjoinrom(char* d,const rom char* s) {
	unsigned char i = 0;
    unsigned char j = 0;

    while( *(d+i) != '\0' ) {
        i++;
    }

    while( *(s+j) != '\0' ) {
		*(d+i) = *(s+j);
		i++;
		j++;
    }

    *(d+i) = '\0';
}

/*
Function: ftoa
Description: Converts floating point precision number to string

             This is a simple function to convert some floating point precision
             numbers to strings since ftoa is not a function available in
             stdlib.h.

Params:
n - floating point precision number
p - precision ( number of decimal places wanted ... )
d - destination string

Returns:
will return the destination string's pointer ( similar to how itoa works )
*/
char * ftoa(float n, char p, char *d) {
	float t;
	float w = 0;
	int m = 0;
    int digit,t2;
	char i = 0;
    char k = 0;

    *(d+i) = '\0';

	if( n < 0 ) {
		n = -n;
		*(d+i) = '-';
		i++;
	}

	t = n;
	while( t >= 1 ) {
		t = t/10;
		if( t >= 1 ) {
			m++;
		}
	}

    while( p >= 0 ) {
		w = 1;		
		if( m >= 0 ) {
			t2 = m;
			while( t2 > 0 ) { w = w*10; t2--; }
		} else {
			t2 = -m;
			while( t2 > 0 ) { w = w/10; t2--; }
		}

		digit = (int)(n/w);
		n -= digit*w;
		
		*(d+i) = '0'+digit;
		i++;

		if( m == 0 ) {
			if( p > 0 ) {
				*(d+i) = '.';
				i++;
			}

			k = 1;
			p--;
		} else if( k == 1 ) {
			p--;
		}

		m--;
    }

	*(d+i) = '\0';

	return d;
}