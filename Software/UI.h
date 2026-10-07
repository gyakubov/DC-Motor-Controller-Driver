#ifndef __UI_H
#define __UI_H

// Define Interface Constants
#ifndef LCD_WIDTH
#define LCD_WIDTH 24 // Character Width Of LCD ( Assuming We Have 2 Line LCD )
#endif

// Assume 'SAMPLES_PER_S' defined somewhere so we can properly time interface updates...
#ifndef SAMPLES_PER_S
#define SAMPLES_PER_S 100
#endif

#define BUTTON_COUNT 3 // Number Of Buttons ( Currently Changing Won't do Anything Really... )
#define BUTTON_HOLD_TIME 4 // Delay Before Considering A Button Held
#define BUTTON_HOLD_MULTIPLIER 10 // When A Button Is Held, It's Value Is Multiplied By This To Create A 'Speed Up' Effect
#define INTERFACE_UPDATE_DELAY (SAMPLES_PER_S/6) // Main Program Calls 'ui_process' at some timed interval, only update the interface every INTERFACE_UPDATE_DELAYth time

// Global Accessible Variables

// External Functions That Need To Be Defined
extern void update_menu_data(unsigned char menu_id,unsigned char sub_menu_id,int value);
extern void render_menu(unsigned char menu_id, unsigned char sub_menu_id, unsigned char line_width, char *line1, char* line2);

// Interface Functions
void ui_init(void);
void ui_process(unsigned int ticks);
void goto_menu(unsigned char menu_id,unsigned char sub_menu_id);
int get_button_state(char button_id);
char get_menu_direction(void);
void process_buttons(void);
int process_button(unsigned char button_id, unsigned char button_value);
void process_menu_action(unsigned char button_id,unsigned char button_state,char value);
void render_lcd(void);
void scopy_right(char* s1, const char* s2,unsigned char len);
void sjoin(char * d,const char* s);
void sjoinrom(char* d, const rom char* s);
char * ftoa(float n, char p, char *d); // Simply Floating Point Precision to String Function

#endif