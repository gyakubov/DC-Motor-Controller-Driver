/*
Program: DC Motor Controller
Author:  Morgan Demers
Dates:   Created: 1/9/2011
         Last Updated On: 9/13/2013

Project Website: http://morgandemers.com

Prerequisite: This code is designed to work with the Controller & 
              Driver circuits found at the 'Project Website' url 
              above. It is also designed to be run on a PIC18LF14K50,
              though should easily adapt to a PIC18F14K50. Any other
              PIC used will require the updating of the I/O pin assignments,
              other PIC settings, and probably also the modification of 
              the Controller Board Layout / Schematic. That being said, if
              you are attempting to recreate what I have done, it would be 
              ideal to follow my suggested parts list in order to achieve 
              similar results.

Disclaimer:  This is probably as polished of a product as it is going to get at
             this point. My time is fairly limited - I did my best to comment
             a lot of the code, and clean it up a bit. Feel free to make modifications
             as need be ( at your own risk ) and be sure to pay attention to the
             License below.

Description: This controller maintains speed by using a closed loop PID control
             algorithm. The feedback comes from an encoder wheel ( either with
             slots or black & white lines ) which is mounted to the main machine 
             tool spindle. If you would like to place the encoder wheel elsewhere
             you will have to modify the code to account for any pulley / gear 
             ratios... Other methods of attaining feedback could be used ( hall 
             effect sensor, etc... ) however the resolution of the encoder is 
             essential to good response times...

			 My setup ( on my Gingery Lathe ) has a 24x2 LCD display, 3 buttons and
             a knob as the interface into the controller. The knob is used to set the
             RPM target, and the 3 buttons are for 'left','menu','right'. The code 
             is fairly clever in that when the menu button is held, and the left or right
             buttons are pressed, it will allow you to rotate through an unlimited number
             of main menus. When the menu button itself is pressed you get rotated through the
             menu's sub menus. The left and right buttons are used for incrementing / 
             decrementing menu data on screen ( unless the menu button is held down ). If you 
             hold down the left or right buttons for a set amount of time, a multiplier will
             be applied to the button's value, and at a regular timed interval the menu data
             will continue to be updated until the button is no longer pressed. This allows for
             the quick modification of numbers without a keypad / many buttons. I
             have had fairly good success using this interface on my lathe, and it reduces
             the number of I/O pins drastically... If you want to change how the UI is setup
             on your particular system, you will have to make quite a few modifications both
             to the code and to the Controller's board layout / schematic. Also, at this point
             I have maxed out the PIC18LF14K50's available I/O pins, and thus you would have
             to upgrade to a PIC with more pins ( > 20pin ) which would require a big design
             change on the Controller's board layout / schematic.

			 * one possible solution to the I/O issue would be to add a helper board with an
               additional PIC18. The current controller board is setup for I2C, so you could probably 
               move the User Interface stuff onto a separate PIC18, and communicate with it via
               I2C. I'd like to do this at some point when I add ELS to my lathe, but at this 
               point I have not done any work on this as of yet...

             There are 4 parts to this program.

             a. Main Program ( this file ) - initializes PIC, Has main program
                variables, handles reading / storing settings to EEPROM, handles
                interrupts, etc...

				Basic Order Of Business:
                ------------------------
                1. PIC Initialized ( I/O pins configured, PWM setup, ADC setup, etc.. )
				2. Settings Read From EEPROM
				3. User Interface Initialized
				4. System Enters Main Program Loop
				   4i.  Timer0 Interrupts ( High Priority ) at some Sampling Frequency which 
                        flags Main Program Loop to process the sample, run PID algo, process 
                        the user interface, etc...
				   4ii. Low Priority, Interrupt on Change detected on UI Buttons, Tach input, 
                        Current limit input, or ADC RPM Knob Available - process buttons, 
                        update encoder count, etc..and whatever was changed here will be 
                        processed at next Timer0 Interrupt.

			 b. PID Library ( PID.c, PID.h ) - contains the meat and potatoes of
                the PID control algorithm. This library could be used in other programs
                as it does not care about the specifics of this particular case.

             c. User Interface Library ( UI.c, UI.h, LCD.c, LCD.h ) - Handles all the 
                User Interface processing - what to do with button changes, management 
                of which menu the user is viewing, and how to get the menu data onto the 
                LCD screen. Requires that this main program code has two functions 
                'update_menu_data' and 'render_menu' to help the UI library determine
                what should actually be displayed on the LCD, and what program variables
                need to be updated when a menu item is altered.

			 d. Helper Libraries
				1. EEPROM.h, EEPROM.c - Has functions to actually write to, read from, EEPROM
                2. Delay.h, Delay.c - Has functions to pause by second, millisecond, microsecond
				3. stdio.h, need itoa(), 

License: This work is licensed under the Creative Commons 
         Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
         To view a copy of this license, visit 
         http://creativecommons.org/licenses/by-nc-sa/3.0/.

Modifications: { please list modifier name, modification date, modification description }

10/01/2013 - Morgan Demers - Changed Timer0 to operate at 500hz, and updated the current limiting code to incorporate
                            a software based low pass filter in order to prevent false triggering from the PWM
                            pulses. When the current limit detect count is greater than a set threshold current
                            limiting will take effect. The current configuration allows the system to initiate 
                            current limiting at half the 1khz frequency of the 4/23 update which may correct some
                            discrepancy Darren was seeing between his bike computer and the tach output. more data
                            is collected per tick in order to determine if current limiting should take place.

4/23/2013 - Morgan Demers - Updated Timer0 to run at 1khz such that we can use it to check for Current Limiting
                            at a fixed 1khz frequency. Have new variables SAMPLES_PER_TICK which defines how
                            frequently we want to process the PID algo, update display, etc... We also have 
                            TICKS_PER_S which is used throughout the code to determine RPM, setpoint, etc...
                            Added a new ticks[2] variable that accumulates until it is >= SAMPLES_PER_TICK at 
                            which point do_tick=1 and stuff is processed as usual... This was mainly done for
                            no-tach setups, as well as the case where the spindle is stalled and no tach 
                            readings are being made. Basically current limiting was checked whenever an interrupt
                            on changed fired, but not the best situation.

4/9/2013 - Morgan Demers - Added 'TACHOMETER_ENABLED' and 'PID_ENABLED' constants. Used throughout
                           the code to allow for 'open loop variable speed control' or 'closed loop
                           variable speed control'. The tachometer can be used in both instances...

						   Also added 'slow start' and 'slow shutdown' to prevent major current spikes
                           when starting the motor. Duty cycle ramp set with 'STARTUP_DUTY_RAMP' and 
                           'startup_duty' is where the accumulator resides for startup. 'SHUTDOWN_DUTY_DROP'
                           is where the shutdown duty cycle drop resides and 'last_duty' added to accomodate
                           that.

*/

#define XTAL_FREQ 4000000L // Set PIC Frequency (clock/4) 

// Define Controller Mode Constants
#define PID_ENABLED 1 // 1 = Closed Loop PID Control ( TACHOMETER_ENABLED 1 required ), 0 = Open Loop Control

// Define Sample Timing Constants
//
// - no point setting to higher value than
//   encoder wheel resolution.. 
//
// - My Current setup has an encoder wheel with 96 transitions,
//   you will want to modify the below definitions based on your
//   own setup...
//
// - Timer0 H:L set to the below, used to
//   set the frequency of the sampling interrupt.
#define SAMPLE_TIMER_H 0xF7
#define SAMPLE_TIMER_L 0xDC
#define SAMPLE_TIMER (unsigned int)(((unsigned int)SAMPLE_TIMER_H<<8)|(SAMPLE_TIMER_L))
#define SAMPLES_PER_S 480
#define TICKS_PER_S 96
#define SAMPLES_PER_TICK (unsigned int)(SAMPLES_PER_S/TICKS_PER_S)

// Define PWM / Motor Control Constants
#define ABSOLUTE_MAX_RPM 1500
#define ABSOLUTE_MAX_DUTY 511 // Adjust When Changing Frequency ( duty cycle resolution dependent of pwm frequency, higher frequency lower duty resolution... )
#define PWM_PERIOD 0xA0 // PWM FREQUENCY SET TO 25khz ( take advantage of 9bit duty cycle resolution )
#define PWM_PRESCALE 0x00 // 1:1 postscale, prescaler = 1

// Define Current Limiting Constants
#define CURRENT_LIMITING_ENABLED 1
#define CURRENT_LIMIT_THRESHOLD 0.50
#define CURRENT_LIMITED_COUNT (unsigned int)(SAMPLES_PER_TICK*CURRENT_LIMIT_THRESHOLD)

// Define Startup / Shutdown Constants
#define STARTUP_DUTY_RAMP 1
#define SHUTDOWN_DUTY_DROP 1

// Define Tachometer Constants
#define TACHOMETER_ENABLED 1
#define MAX_ENCODER_RESOLUTION 192 // Maximum Number of Transitions On The Encoder Wheel

// Define I/O pins
#define TACH PORTAbits.RA0  // Tachometer Sensor
#define CLIM PORTAbits.RA1  // Current Limit Sensor
#define L_BTN PORTAbits.RA3 // Interface Left Button
#define M_BTN PORTAbits.RA4 // Interface Menu Button
#define R_BTN PORTAbits.RA5 // Interface Right Button
#define M_DIR PORTCbits.RC4 // Motor Relay ( For Forward / Reverse )

// Define PWM pins / access ( currently using P1A ( RC5 )
#define PWM_EN PSTRCONbits.STRA 
#define PWM PORTCbits.RC5

// Define Where LCD is connected
#define	LCD_RS PORTBbits.RB7
#define	LCD_RW PORTBbits.RB5
#define LCD_EN PORTCbits.RC6
#define LCD_DATA PORTC

// Define System Constants
#define MAX_ADC_VALUE 1020 // Max Value Expected From Analog 2 Digital Converter

// Unique ID
#define ID 125 // Program ID #, Whenever changing EEPROM Settings Change This Number To Ensure The EEPROM Is Cleared...

// STALL DETECT Constants
#define STALL_TIMEOUT (TICKS_PER_S/5) // Number Of Timer Interrupts To Wait ( while 0 rpm ) before detecting a stall situation...

// Includes
#include <p18lf14k50.h>
#include <stdlib.h> // Need some basic string functions...
#include "EEPROM.h" // EEPROM read / write functions
#if PID_ENABLED
#include "PID.h" // Proportional / Integral / Derivative functions ( for closed loop motor control )
#endif
#include "Delay.h" // Delay functions
#include "UI.h" // User Interface functions
#include "LCD.h"

// Configuration Bits
#pragma config FOSC = IRC
#pragma config WDTEN = OFF
#pragma config LVP = OFF
#pragma config MCLRE = OFF

// SAFE START VARIABLES
static unsigned char INIT = 1; // Do Not Process Any Interrupts Until INIT=0

// Sampling Variables
static char do_tick = 0; // Notify main loop that we are ready to process next sample ( instead of calling the function in the high isr )
static unsigned int ticks[3] = {0,0,0}; // Counter variables

// Interrupt On Change Helpers
static unsigned char IOC_states[4] = {0,0,0,0}; // Stores Current States of IOC pins

// PID / RPM Variables
static char gains[4][2] = {{2,1},{1,2},{2,30},{0,1}}; // Fractional Array Representations Of PID Constants - easier to set with 2 buttons than a floating point number
static int rpm_actual = 0; // Actual Current RPM ( determined by tachometer input )
static int rpm_target = 0; // RPM Target, determined from Potentiometer hooked up to ADC pin
#if !PID_ENABLED
static int rpm_target_duty = 0; // RPM Target Duty, For Open Loop Speed Control Has PWM Duty Cycle Value
#endif
static int startup_duty = 0; // Startup Duty Cycle Accumulator, Once >= duty value controller takes over and this is set to -1 until system paused...
static int last_duty = 0; // Preserve Last Duty Cycle Value For Slow Stop
static double rpm_error = 0; // Current Error in RPM, though this value represents the error in encoder counts vs. setpoint during a sampling time
static int update_rpm_value = -1; // Helper variable, set when new ADC data is in from the Potentiometer, If != -1, system will determine new RPM & setpoint
static unsigned int MAX_DUTY = 150; // Maximum Duty Cycle Value That Can Be Set ( 150 = Conservative, which would be good for testing a new setup )
static unsigned int MAX_RPM = 1500;
static unsigned int MIN_RPM = 1;
static unsigned char PAUSED = 1; // Start Paused For Safety..

// Current Limit Variables
static unsigned char CURRENT_LIMITED = 0;
static unsigned int CURRENT_LIMIT_LAST_DETECTED = 0;
static unsigned int CURRENT_LIMIT_DETECTED = 0; // Did Current Limiting Kick In At All During Sample Period?
static unsigned char current_limit_count_sample = 0; // The Value Of The Last Sampling's Current Limit Count

// TACH Variables
static unsigned char ENCODER_RESOLUTION = 96; // Number of transistions on the encoder wheel ( configurable via interface )
static double encoder_count_setpoint = 0; // Computed Setpoint from RPM target - represents expected count value per sampling time
static int encoder_count_sample = 0; // Current Sample's Encoder Transition Counter
static int encoder_count_last_sample = 0; // The Value Of The Last Sampling's Encoder Transition Count
static short long encoder_count = 0; // Encoder Wheel Transistion Counter For The Current Second ( used to determine actual RPM )

// TACH POWERED DIVIDING HEAD
static unsigned char INDEXER_LAST_TACH = 0;
static unsigned char INDEXER_DUTY_LOCK = 0; // Indicate When The INDEXER_DUTY Produces a Transition On The Encoder
static unsigned char INDEXER_DUTY = 0; // Duty Cycle To Use For Spindle Indexer - Miniumum To Rotate Encoder
static unsigned char INDEXER_TX = 1; // Number Of Transitions To Go
static unsigned char INDEXER_ON = 0; // Counter When Spindle Indexer Is On
static unsigned char INDEXER_BRAKING = 0; // Last State Before End Of Sequence To Stop Motor...

// Settings Storage Variables
static unsigned char update_settings = 0; // Update EEPROM settings flag. 1 = Save Settings To EEPROM At Next Available Moment

// Settings Storage Functions
void save_settings(void); // Save Settings To EEPROM
unsigned char read_settings(void); // Read Settings From EEPROM

// Interrupt Functions
void LOW_ISR(void); // Handles Interrupt On Change Pins, Low Priority Interrupts ( ADC, etc.. )
void HIGH_ISR(void); // Handles Timer0 Interrupt ( Sample Timer )

// Sampling Functions
void tick(void); // Called Whenever The Timer0 Interrupt Fires...

// Required User Interface Functions ( from UI.h )
void update_menu_data(unsigned char menu_id,unsigned char sub_menu_id,int value); // Menu Data Has Changed, Update Appropriate Variable
void render_menu(unsigned char menu_id, unsigned char sub_menu_id, unsigned char line_width, char *line1, char* line2); // UI Calls When LCD Menu Needs To Be Updated

// PID / RPM / Motor Control Functions
void update_ks(char k_id); // Converts PID fractional gains to floating point constants
void update_rpm_target(void); // Helper For 'update_rpm', calculates the Encoder Count Setpoint
void update_rpm(void); // Whenever a change in RPM ( on the adjustment Potentiometer ) this function updates the rpm target
void set_duty(unsigned int d); // Sets the PWM duty cycle

// High Priority Interrupt Vector
#pragma code high_vector=0x08
void high_interrupt(void) {
	_asm GOTO HIGH_ISR _endasm
}
#pragma code

// Low Priority Interrupt Vector
#pragma code low_vector=0x18
void low_interrupt(void) {
	_asm GOTO LOW_ISR _endasm
}
#pragma code

// LOW PRIORITY INTERRUPT SERVICE ROUTINE
#pragma interruptlow LOW_ISR
void LOW_ISR(void) {
	char t;

	if( INTCONbits.RABIF == 1 ) { // On Change...
		if( INIT == 0 ) {
			if( IOC_states[2] != M_BTN ) { // Menu Button
				process_button(1,(unsigned char)M_BTN);
				IOC_states[2] = M_BTN;
			}
			if( IOC_states[0] != L_BTN ) { // Left Button
				process_button(0,(unsigned char)L_BTN);
				IOC_states[0] = L_BTN;
			}
			if( IOC_states[1] != R_BTN ) { // Right Button
				process_button(2,(unsigned char)R_BTN);
				IOC_states[1] = R_BTN;
			}

#if TACHOMETER_ENABLED
			if( IOC_states[3] != TACH ) { // Tachometer
				// Increment Encoder Wheel Counter for this Sample
            	encoder_count_sample++;

				if( INDEXER_ON > 0 ) {
					if( !INDEXER_DUTY_LOCK ) {
						INDEXER_DUTY_LOCK = 1;
						//INDEXER_DUTY++;
					} else {
						INDEXER_LAST_TACH = TACH;
						INDEXER_ON--;
						set_duty(0);
						if( !INDEXER_ON ) {
							INDEXER_BRAKING = 2;
							M_DIR = !M_DIR;
						}
					}
				}

				IOC_states[3] = TACH;
			}
#endif
		}

		INTCONbits.RABIF = 0;
	}

	if( PIR1bits.ADIF == 1 ) { // ADC Ready With New Data From 'RPM Adjustment' Potentiometer
		update_rpm_value = (((int)ADRESH)<<8)|(ADRESL);
		PIR1bits.ADIF = 0;
	}
}

// HIGH PRIORITY INTERRUPT SERVICE ROUTINE
#pragma interrupt HIGH_ISR
void HIGH_ISR(void) {
	if( INTCONbits.TMR0IF == 1 ) {
#if CURRENT_LIMITING_ENABLED
		if( !CLIM && !CURRENT_LIMITED ) {
			current_limit_count_sample++;

			if( current_limit_count_sample >= CURRENT_LIMITED_COUNT ) {
				CURRENT_LIMIT_DETECTED++;
				CURRENT_LIMITED = 1;
				set_duty(0);
			}
		}
#endif

		ticks[2]++;

		if( ticks[2] >= SAMPLES_PER_TICK ) {
#if TACHOMETER_ENABLED
        	encoder_count_last_sample = encoder_count_sample; // Set Current Sample Count to 'last_sample' variable

			// Reset Encoder Wheel Sample Counter For Next Sample
        	encoder_count_sample = 0;
#endif

			// Set Flag To Notify Main Loop That We Can Process The Sample
			do_tick = 1;

			// Reset Tick Counter
			ticks[2] = 0;
		}      

		TMR0H = SAMPLE_TIMER_H;
		TMR0L = SAMPLE_TIMER_L;

		INTCONbits.TMR0IF = 0;
	}
}

/*
Function: main
Description: The main program function, initializes PIC, sets up I/O pins & features, and
             then enters the main program loop.
*/

void main(void) {
	unsigned char i = 0;

	/*
	BEGIN PIC INIT CODE
	*/

	UCONbits.USBEN = 0; // Disable USB
	OSCCON |= 0x70; // Ensure Internal Clock 16Mhz

	TMR0H = SAMPLE_TIMER_H; // Set Timer0{H:L} register for desired Sampling Time
	TMR0L = SAMPLE_TIMER_L;

	INTCONbits.TMR0IF = 0; // Clear Timer0 Interrupt Flag
	T0CON = 0x81; // 0b10000001 - Timer0 On, 1:4 prescaler ( 15.259 Hz )

	RCONbits.IPEN = 1; // Enable Priority Levels On Interrupts

	WPUA = 0x38; // Weak Pull-Ups Enabled on Port A
	WPUB = 0x00; // Weak Pull-Ups Disabled on Port B

	PORTA &= 0x00;
	TRISA = 0x30; // 0b00110000 - RA4 & RA5 = input
	IOCA = 0x00;

	TRISB = 0x00; // 0b00000000 - Port B Configured As Output
	IOCB = 0x00;

    INTCON2bits.RABPU = 0;
	INTCON2bits.TMR0IP = 1; // Set Timer0 Interrupt Priority to High
	INTCON2bits.RABIP = 0; // Set Port A & B Interrupt On Change Interrupt Priority to Low
	INTCON = 0xE8; // 0b11101000 - Global & Peripheral Interrupts Enabled, Timer0 Overflow Interrupt Enabled, Port A & B Interrupt On Change Interrupts Enabled 

	// Disable Comparators...
	CM1CON0 = 0x00;
	CM2CON0 = 0x00;

	// Disable SRQ...
	SRCON0 = 0x00;
	SRCON1 = 0x00;

	TRISC = 0x80; // 0b10000000 - RC7 = input, RC0-RC6 = output ( RC5 PWM )
	PWM = 0; // RC5 = PWM Output, Ensure 0 on pin at startup...

	// Setup PWM Timer / Pulse Steering on P1A ( RC5 )
	T2CON = 0x04; // 0b00000100 - Enable Timer2
	CCP1CON = 0x0C; // 0b00001100 - Single Output Steering, LSBs of Duty Cycle to 0, PWM Mode - P1A ( RC5 ) Active-High
	CCPR1L = 0x00; // 0b00000000 - Set MSBs of Duty Cycle to 0
	PSTRCON = 0x01; // 0b00000001 - Output Steering Update On Next Instruction

    // Setup PWM Frequency...
    T2CON |= PWM_PRESCALE;
    PR2 = PWM_PERIOD; // Set Period Register for Desired PWM Period

	// Setup ADC on AN9 For RPM Adjustment Potentiometer
	REFCON0 |= 0xB0; // 0b10110000 - FVR ( Fixed Voltage Reference ) enabled, x4 voltage ( 4.096V ) 
	ANSEL = 0x00; // 0b00000000 - RC3,RC2,RC1,RC0,RA4 digital input buffers enabled
	ANSELH = 0x02; // 0b00000010 - AN9 ( RC7 ) digital input buffer disabled, RC6,RB4,RB5 digital input buffers enabled
    ADCON2 = 0xBE; // 0b10111110 - Right Justified, 20 TAD, Fosc/64
	ADCON1 = 0x08; // 0b00001000 - Positive Voltage Reference supplied by FVR ( Fixed Voltage Reference ), Negative Voltage Reference supplied by Vss
	ADCON0 = 0x25; // 0b00100101 - Select AN9 ( RC7 ) as ADC Channel To Use, Enable ADC

	PIR1bits.ADIF = 0; // Clear ADC Interrupt Flag
	PIE1bits.ADIE = 1; // Enable ADC Interrupt
	IPR1bits.ADIP = 0; // Set ADC Interrupt Priority to Low

	/*
	END PIC INIT CODE
	*/

	DelayMs(100);

	M_DIR = 0; // Set Initial Motor Direction ( Forward - CCW )

	// Init User Interface
	ui_init();

	DelayS(2);

	// Load In Settings From EEPROM
	if( read_settings() == 0 ) {
		update_settings = 1; // Must Be First Run, Store Initial Settings To EEPROM...
	}

#if PID_ENABLED
    // Init PID Parameters...
    PID_derivative_delay = 4; // Only Process Derivative Every 4th Call to PID()
    PID_integral_delay = 1; // Process Integral Every Call to PID()
    PID_out_clamp = MAX_DUTY; // Set PID Output Clamp To MAX_DUTY
    PID_integral_clamp = MAX_DUTY; // Set PID Integral Clamp To Max_DUTY

	// Create PID Constants From Gains ( interface input fractions )
	update_ks(-1);
#endif

    // Enable Interrupt On Change Pins
#if TACHOMETER_ENABLED
	IOCA = 0x3B; // 0b00111011 - Interrupt On Change Enabled on RA0, RA1, RA3, RA4, RA5
#else
	IOCA = 0x3A; // 0b00111010 - Interrupt On Change Enabled on RA1, RA3, RA4, RA5
#endif

	// Done Initializing System, Begin Normal Operation..
	INIT = 0;

	goto_menu(0,0);

	while(1) {
		if( update_rpm_value != -1 ) { // ADC Potentiometer Data Ready To Update RPM...
			update_rpm();
		}

		if( do_tick == 1 ) { // Timer0 Interrupt Fired, Time To Process Sample / Do Other Time Sensitive Stuff...
			tick();
		}
	}
}

/*
Function: update_rpm_target
Description: Helper function for 'update_rpm()', will compute the expected encoder wheel transition 
             count for the required RPM Target ( from ADC value of RPM Adjustment Potentiometer ).
*/
void update_rpm_target(void) {
#if PID_ENABLED
	if( rpm_target >= MIN_RPM ) { // Only Process If Selected RPM Is At Least Minimum
		encoder_count_setpoint = (double)((((double)rpm_target)/60)*((double)ENCODER_RESOLUTION))/TICKS_PER_S; // Expected Transition Count per Sampling Period
	} else {
		encoder_count_setpoint = 0;
	}
#endif
}

/*
Function: update_rpm
Description: Whenever a new ADC value is available this function is called to convert the RPM Adjustment
             Potentiometer ADC value ( found in update_rpm_value ) to the actual RPM ( stored in rpm_target ).
             Uses 'update_rpm_target()' to calculate the actual setpoint for the PID control algorithm...
*/
void update_rpm(void) {
	short long t = 0; // Temporary Variable

    // Compute RPM From update_rpm_value
	t = ((short long)update_rpm_value*MAX_RPM)/MAX_ADC_VALUE;

	if( rpm_target == 0 ) { 
		rpm_target = t;
	} else {
		rpm_target = (int)((t+rpm_target) >> 1); // Do Some Simple Averaging To Smooth ADC input a bit...
	}

	if( rpm_target > MAX_RPM ) { // Clamp the Target RPM to MAX_RPM
		rpm_target = MAX_RPM;
	}

#if TACHOMETER_ENABLED
	// Call Helper Function To Compute Encoder Count Set Point For This New RPM...
	update_rpm_target();
#endif

#if PID_ENABLED == 0
	rpm_target_duty = (int)(((short long)rpm_target*MAX_DUTY)/MAX_RPM);

	if( rpm_target_duty > MAX_DUTY ) {
		rpm_target_duty = MAX_DUTY;
 	}   
#endif
	
	update_rpm_value = -1;
}

/*
Function: tick
Description: Sample Processing Routine that is called when the Timer0 Interrupt fires.
             If the system is running will use the PID library to determine the new
             PWM duty cycle in order to attain rpm_target.

             This function is also fired at a regularly timed interval, and thus other
             time sensitive code is run - for instance every second we want to update the
             Settings in EEPROM if a change was made, and also we would like to update the
             displayed RPM ( rpm_actual ) every second as well...

			 *The function is not called within the interrupt service routine as it is a
              high priority interrupt and we don't want to prevent our lower priority 
              interrupts from firing due to the processing here, so if do_tick == 1 call
              from main program loop.
*/
void tick(void) {
	int duty = 0; // Duty Cycle Variable
	short long t = 0; // Temporary Variable
	unsigned char i = 0; // Temporary Variable

   	ticks[0]++; // Update Tick Counter By 1

#if TACHOMETER_ENABLED
	encoder_count += (short long)encoder_count_last_sample; // Add Last Sample To /s Counter, used to determine RPM
#endif

#if CURRENT_LIMITING_ENABLED
	if( !PAUSED && !CURRENT_LIMITED ) { // Only Run If System Is Not Paused and Is Not Current Limited
#else
	if( !PAUSED ) { // Only Run If System Is Not Paused
#endif
#if PID_ENABLED
        if( encoder_count_setpoint > 0 ) { // Only Run If RPM Target >= MIN_RPM
            rpm_error = encoder_count_setpoint-(double)encoder_count_last_sample; // Calculate RPM Error ( actually error in setpoint vs last sample )
            duty = pid(encoder_count_setpoint,rpm_error); // Have PID control algorithm calculate new duty cycle to maintain RPM

            if( duty < 0 ) { // Ensure duty is a positive number...
                duty = 0;
            }
        }
#else
		duty = rpm_target_duty;
#endif

		// Slow Start Code...
		if( startup_duty != -1 ) {
			startup_duty += STARTUP_DUTY_RAMP;
			if( startup_duty >= duty ) {
				startup_duty = -1;
			} else {
				duty = startup_duty;
			}
		}

		last_duty = duty;
	} else if( INDEXER_ON ) {
		if( !INDEXER_DUTY_LOCK ) { // Increment Duty Until We Have A Lock On Minimum Speed To Rotate Encoder...
			INDEXER_DUTY++;
		}

		duty = INDEXER_DUTY;
	} else if( INDEXER_BRAKING ) {
		INDEXER_BRAKING--;
		if( !INDEXER_BRAKING ) {
			M_DIR = !M_DIR;
			lcd_init(); // Assume LCD Will Fail From Some Spike...
		}
    } else { // If Paused, Ensure That Nothing is Running & PID internals are reset
		startup_duty = 0;

		if( last_duty > 0 ) {
			last_duty -= SHUTDOWN_DUTY_DROP;
			if( last_duty < 0 ) {
				last_duty = 0;
			}

			duty = last_duty;
		} else {
	    	duty = 0;
		}

#if PID_ENABLED
		rpm_error = 0;
        pid_reset();
#endif
	}

	duty:
    set_duty(duty); // Set the actual PWM Duty Cycle via 'set_duty' helper function

#if CURRENT_LIMITING_ENABLED
	// Reset Current Limit Values For Next Sample
    CURRENT_LIMITED = 0;
    current_limit_count_sample = 0;
#endif

    if( ticks[0] % 4 == 0 ) { // Every 4th time tick() called, Check If Stalled, and Get New ADC Value From RPM Adjustment Potentiometer
#if TACHOMETER_ENABLED
		if( PAUSED == 0 && rpm_target > 0 && encoder_count == 0 ) { // Is The Spindle Not Spinning?
			if( ticks[1] >= STALL_TIMEOUT ) { // If Stall Counter >= Stall Timeout, We are Stalled shut'r down for safety...
				PAUSED = 2; // Set Paused Due To Stall State
				goto_menu(0,0); // Jump to Main Menu So User Can See Stalled Message...
			}
			ticks[1]++; // Increment Stall Counter
		} else {
			ticks[1] = 0; // Reset Stall Counter, Detected Spindle Rotation...
		}
#endif

	    // If we can, have ADC capture new value from RPM Adjustment Knob ( AN9 )
	    if( update_rpm_value == -1 && ADCON0bits.GO != 1 ) {
		    ADCON0 = 0x25;
		    ADCON0bits.GO = 1;
 	    }
	}

	ui_process(ticks[0]); // Have User Interface do whatever processing it needs to do

	if( ticks[0] >= TICKS_PER_S ) { // Every Second Compute Actual RPM, Save Settings to EEPROM if Changed, etc...
#if TACHOMETER_ENABLED
		rpm_actual = (int)((encoder_count*60)/ENCODER_RESOLUTION); // Update Actual RPM value to be displayed
		encoder_count = 0; // Reset per second Encoder Transition Counter
#endif
		// Update EEPROM Settings If Need Be...
		if( update_settings == 1 ) {       
			// If Buttons Down, Don't Save As EEPROM
			// Save Requires Disabling Of Interrupts...
			if( get_button_state(-1) == 0 ) {
				save_settings();
				update_settings = 0;
			}
		}

#if CURRENT_LIMITING_ENABLED
		CURRENT_LIMIT_LAST_DETECTED = CURRENT_LIMIT_DETECTED;
		CURRENT_LIMIT_DETECTED = 0;
#endif

        ticks[0] = 0; // Reset Main Tick Counter
    }

	do_tick = 0; // Clear Flag that notifies main program loop to call this function
}


/*
Function: update_ks
Description: Helper function that converts fractional PID gains into their 
             decimal constants. The fractional gains are simply used as a means
             to provide a way to adjust the contants with a 3 button input device...

Parameters:
k_id - Constant ID, if set to -1 will update all constants, otherwise will only
       update the PID constant with this id value. 0=kP,1=kI,2=kD,3=FF
*/
void update_ks(char k_id) {
#if PID_ENABLED
	unsigned char i = 0; // Temporary Variable
    unsigned double j = 0; // Temporary Variable

	for( i = 0; i < 4; i++ ) { // Loop Through Constants
		if( k_id != -1 && k_id != i ) continue; // Ignore Those We Aren't Updating...
		
		if( gains[i][1] == 0 ) { // If Denominator is 0, constant is 0
			j = 0;
		} else {
			j = (double)((((double)gains[i][0]))/((double)gains[i][1]));
		}

        switch(i) { // Update the Appropriate Constant Based on i
            case 0:
				PID_kp = j;
                break;
            case 1:
				PID_ki = j;
				break;
			case 2:
				PID_kd = j;
				break;
			case 3:
				PID_ff = j;
				break;
        }
	}
#endif
}

/*
Function: set_duty
Description: Sets the actual PWM duty cycle

Parameters:
d - duty cycle value
*/
void set_duty(unsigned int d) {
	CCP1CON = (CCP1CON&0x0f)|((d&0x03)<<4);
	CCPR1L = (d>>2);
}

/*
Function: save_settings
Description: Stores the system settings to the PIC's EEPROM
             such that on the next startup we will have the
             same settings, yay!
*/
void save_settings(void) {
	unsigned char tmp = 0;

	EEPROM_Write(0,ID); // Write Program ID Number

    // Save PID Fractional Gains
	EEPROM_Write(1,gains[0][0]); // KP
	EEPROM_Write(2,gains[0][1]);
	EEPROM_Write(3,gains[1][0]); // KI
	EEPROM_Write(4,gains[1][1]);
	EEPROM_Write(5,gains[2][0]); // KD
	EEPROM_Write(6,gains[2][1]);
	EEPROM_Write(7,gains[3][0]); // FF
	EEPROM_Write(8,gains[3][1]);
	EEPROM_Write(9,ENCODER_RESOLUTION); // Store Encoder Resolution

	tmp = (unsigned char)(MAX_DUTY&0xFF); // Store Max Duty 
	EEPROM_Write(10,tmp);
	tmp = (unsigned char)(MAX_DUTY>>8);
	EEPROM_Write(11,tmp);
	tmp = (unsigned char)(MAX_RPM&0xFF); // Store Max RPM
	EEPROM_Write(12,tmp);
	tmp = (unsigned char)(MAX_RPM>>8);
	EEPROM_Write(13,tmp);
}

/*
Function: read_settings
Description: Reads in the system settings from EEPROM.
             If read in ID does not match, return 0 and
             assume we need to reset the EEPROM...

Returns:
a status variable indicating if the EEPROM settings are
valid or not...
*/
unsigned char read_settings(void) {
	unsigned char ret = 0; // Return Variable
	unsigned char tmp = 0; // Temporary Variable.. 
	
	// Check Unique ID, If Exists At Address 0 Assume EEPROM OK...
    tmp = EEPROM_Read(0);

	if( tmp == ID ) { // If read in ID matches ID, Settings OK...
		ret = 1;

		// Read In PID Fractional Gains
		gains[0][0] = EEPROM_Read(1); // KP
		gains[0][1] = EEPROM_Read(2);
		gains[1][0] = EEPROM_Read(3); // KI
		gains[1][1] = EEPROM_Read(4);
		gains[2][0] = EEPROM_Read(5); // KD
		gains[2][1] = EEPROM_Read(6);
		gains[3][0] = EEPROM_Read(7); // FF
		gains[3][1] = EEPROM_Read(8);

		ENCODER_RESOLUTION = EEPROM_Read(9);  // Read In Encoder Resolution

		MAX_DUTY = (((unsigned int)EEPROM_Read(11))<<8)|EEPROM_Read(10); // Read In Max Duty
		MAX_RPM = (((unsigned int)EEPROM_Read(13))<<8)|EEPROM_Read(12); // Read In Max RPM
	}

	return ret;
}

/*
Function: update_menu_data
Description: This function is required by the 'User Interface Library' and when the
             UI is processed, if menu data is to be updated the UI processing
             routine will call this function with the update value such that
             the actual variables can be changed ( UI Library doesn't care what the
             actual menu's data variables are ).

             "Menu Data" refers to any variable that can be changed on the
             "Menu" that is currently being viewed. The Left & Right buttons
             will setup the firing of this function by loading a numeric 
             update value into the 'update_menu_item' variable.

Parameters:
menu_id - ID of the currently menu being viewed currently
sub_menu_id - ID of the sub_menu currently being viewed
value - The update value of the currently selected menu item
*/
void update_menu_data(unsigned char menu_id,unsigned char sub_menu_id,int value) {
	unsigned char toggle[3] = {1,0,0}; // A Quick Lookup Table For Toggling States On / Off
	int i,j = 0; // Temporary Variables
	short long t = 0; // Temporary Variable

	switch(menu_id) {
        case 0: // Main Menu
			if( !(INDEXER_ON || INDEXER_BRAKING) ) {
           		switch(sub_menu_id) {
					case 0: // RPM & RPM Target Sub Menu
						/*
						On Start / Stop Menu, The Left Button Exclusively Makes Changes
						other than the RPM Adjustment knob which is handled elsewhere.
						The Left Button Value is -1, so we test x for that to determine
						if the Left Button has been pressed.	

						We Also check The Left Button's State to ensure that it is not
						being 'Held' - would result in spindle start / stop / start /
						stop / etc... which is not safe of course.
						*/
						if( value == -1 && get_button_state(0) != 2 ) {
							PAUSED = toggle[PAUSED];
						}
						break;
					case 1: // Forward | Reverse Sub Menu
						if( PAUSED && PID_out <= 0 ) {
							M_DIR = toggle[M_DIR];
						}
						break;
					case 2: // Encoder as Spindle Indexer Functionality...
						if( PAUSED ) {
							if( value < 0 ) {
								INDEXER_TX += value*-1;
								if( INDEXER_TX > ENCODER_RESOLUTION ) {
									INDEXER_TX = 1;
								}
							} else {
								INDEXER_ON = INDEXER_TX;
								IOC_states[3] = INDEXER_LAST_TACH;
							}
						}
						break;
				}
			}
            break;
		case 2: // PID Constant Menus
			i = (int)(sub_menu_id >> 1);
			j = sub_menu_id-(i*2);

			gains[i][j] += value;
			if( gains[i][j] < 0 ) gains[i][j] = 100+gains[i][j];
			else if( gains[i][j] > 100 ) gains[i][j] = gains[i][j]-100;

			// Convert Fractional Gains To Decimal Constants
			update_ks(i);

			// Set Flag Stating That EEPROM Needs Updating
			update_settings = 1;
			break;
		case 3: // Other Settings Menus
			switch(sub_menu_id) {
			  case 0: // MAX DUTY
				MAX_DUTY += value;
				if( MAX_DUTY < 0 ) MAX_DUTY = 0;
				else if( MAX_DUTY > ABSOLUTE_MAX_DUTY ) MAX_DUTY = ABSOLUTE_MAX_DUTY;
#if PID_ENABLED
                PID_out_clamp = MAX_DUTY;
                PID_integral_clamp = MAX_DUTY;
#endif
			    break;
			  case 1: // MAX RPM
				MAX_RPM += value;
				if( MAX_RPM < 0 ) MAX_RPM = 0;
				else if( MAX_RPM > ABSOLUTE_MAX_RPM ) MAX_RPM = ABSOLUTE_MAX_RPM;

				if( rpm_target > MAX_RPM ) {
					rpm_target = MAX_RPM;
					update_rpm_target();
				}
				break;
			  case 2: // ENCONDER RESOLUTION
				ENCODER_RESOLUTION += value;
				if( ENCODER_RESOLUTION < 1 ) ENCODER_RESOLUTION = 1;
				else if( ENCODER_RESOLUTION > MAX_ENCODER_RESOLUTION ) ENCODER_RESOLUTION = MAX_ENCODER_RESOLUTION;
			    break;
			}

			// Set Flag Stating That EEPROM Needs Updating
			update_settings = 1;
			break;
	}
}

/*
Function: render_menu
Description: This function is required by the 'User Interface Library' and is called
             from the User Interface processing routine whenever the lcd strings need to
             be rendered. The 'User Interface Library' doesn't care what the actual menus
             display, and for portability is handled by the main program.

             The UI passes in the currently selected menu & sub_menu, the line width of the
             LCD display being used, and the two string pointers ( line1 & line2 ). Modifications
             would be needed both here, and to UI.h & UI.c in order to expand to 3 or 4 line 
             LCD displays...

Parameters:
menu_id - ID of the currently menu being viewed currently
sub_menu_id - ID of the sub_menu currently being viewed
line_width - Character width of the LCD display
line1 - String Pointer for LCD Line 1
line2 - String POinter for LCD Line 2
*/
void render_menu(unsigned char menu_id, unsigned char sub_menu_id, unsigned char line_width, char *line1, char* line2) {
	int i,j = 0; // Temporary Variables
	char gain_labels[4][5] = {"Kp (","Ki (","Kd (","FF ("}; // Lookup Table for PID Gain Constant Labels
	char str[9] = ""; // Temporary String
	char str2[9] = ""; // Temporary String 2
	unsigned char show_rpm = 1; // Flag Indicating If We Should Show The Actual RPM on the right side of Line1

    // Clear Lines...
    *line1 = '\0';
    *line2 = '\0';

	switch(menu_id) {
		case 0: // Main Menu
			switch(sub_menu_id) {
              case 0: // RPM & RPM Target Sub Menu
				sjoinrom(line2,"TRG: ");
				sjoin(line2,itoa(rpm_target,&str[0])); // Show RPM Target on Line 2

			    if( PAUSED != 0 ) { // Show Paused Message On Line 1
					if( PAUSED == 2 ) { // Paused due to Stall...
						sjoinrom(line1,"STALLED!");
					} else { // Paused
				    	sjoinrom(line1,"PAUSED");
					}

					str[0] = '\0';
					sjoinrom(&str[0],"L=Start");
					scopy_right(line2,&str[0],line_width);
			    } else { // Running Show Actual RPM on Line 1
#if TACHOMETER_ENABLED
				    sjoinrom(line1,"RPM: ");
					sjoin(line1,itoa(rpm_actual,&str[0]));
#else
					sjoinrom(line1,"RUNNING");
#endif
					str[0] = '\0'; // Clear Temporary String...
					sjoinrom(&str[0],"DUTY: ");
#if PID_ENABLED
					sjoin(&str[0],ftoa(100*((float)(PID_out/ABSOLUTE_MAX_DUTY)),1,&str2[0]));
#else
					sjoin(&str[0],ftoa(100*((float)(((double)rpm_target_duty)/ABSOLUTE_MAX_DUTY)),1,&str2[0]));
#endif
					sjoinrom(&str[0],"%");
					scopy_right(line1,&str[0],line_width);

					str[0] = '\0';
					sjoinrom(&str[0],"L=Stop");
					scopy_right(line2,&str[0],line_width);

					show_rpm = 0;
			    }
                break;
			  case 1: // Forward | Reverse Sub Menu
				if( M_DIR == 0 ) {
					sjoinrom(line1,"Forward - CCW");
					if( PAUSED && PID_out <= 0 ) {
						sjoinrom(line2,"L=Rev."); // Indicate Action To Switch Direction ( press left button )
					} else {
						sjoinrom(line2,"Stop Motor To Change Dir");
					}
				} else {
					sjoinrom(line1,"Reverse - CW");
					if( PAUSED && PID_out <= 0 ) {
						sjoinrom(line2,"L=Fwd."); // Indicate Action To Switch Direction ( press left button )
					} else {
						sjoinrom(line2,"Stop Motor To Change Dir");
					}
				}
                break;
			  case 2: // Spindle Indexer Menu
				sjoinrom(line1,"Indexer");
				if( INDEXER_ON ) {
					sjoinrom(line2,"RUNNING: ");
					sjoin(line2,itoa((int)INDEXER_ON,&str[0]));
				} else {
					sjoinrom(line2,"Step ");
					sjoin(line2,itoa((int)INDEXER_TX,&str[0]));

					str[0] = '\0';
					sjoinrom(&str[0],"R=Go");
					scopy_right(line2,&str[0],line_width);
				}

				show_rpm = 1;
			    break;
			}
			break;
		case 1: // Debug / Info Menu
            switch(sub_menu_id) {
	          case 0: // Last To Setpoint Errors Sub Menu
#if PID_ENABLED
				sjoinrom(line1,"ER0:");
				sjoin(line1,itoa((int)rpm_error,&str[0]));
				sjoinrom(line2,"ER1:");
				sjoin(line2,itoa((int)PID_last_error,&str[0]));
#else
				goto_menu(1,1); // Menu Only Relevant For PID Closed Loop Mode
#endif
			    break;
			  case 1: // Duty Cycle Sub Menu
				sjoinrom(line1,"DUTY:");
#if PID_ENABLED
				sjoin(line2,ftoa(100*((float)(PID_out/ABSOLUTE_MAX_DUTY)),1,&str[0]));
#else
				sjoin(line2,ftoa(100*((float)(((double)rpm_target_duty)/ABSOLUTE_MAX_DUTY)),1,&str[0]));
#endif
				sjoinrom(line2,"% (");
#if PID_ENABLED
				sjoin(line2,itoa((int)PID_out,&str[0]));
#else
				sjoin(line2,itoa(rpm_target_duty,&str[0]));
#endif
				sjoinrom(line2,"/");
				sjoin(line2,itoa((int)ABSOLUTE_MAX_DUTY,&str[0]));
				sjoinrom(line2,")");
				break;
			  case 2: // Show Target Setpoint vs. Last Sample
#if TACHOMETER_ENABLED
				sjoinrom(line1,"TRG ");
				sjoin(line1,ftoa((float)(encoder_count_setpoint),1,&str[0])); 
				sjoinrom(line2,"ENC ");
				sjoin(line2,itoa(encoder_count,&str[0]));
				sjoinrom(line2,".0");
#else
				goto_menu(1,0); // Menu Only Relevant for Tachometer Enabled
#endif
                break;
			}
			break;
		case 2: // PID Constants Menu
#if PID_ENABLED
			i = (int)(sub_menu_id >> 1); // Determine Which PID Constant We Are Viewing
			j = sub_menu_id-(i*2); // Determine If We Are Working On Numerator or Denominator

			sjoin(line1,&gain_labels[i][0]);
			sjoin(line1,itoa(j,&str[0]));
			sjoinrom(line1,")"); // Line 1 = {constant label} ({0=numerator,1=denominator})
			sjoin(line2,itoa((int)gains[i][0],&str[0]));
			sjoinrom(line2,"/");
			sjoin(line2,itoa((int)gains[i][1],&str[0])); // Line 2 = {constant numerator}/{constant denominator}
#else
			goto_menu(2+get_menu_direction(),0);
#endif
			break;
		case 3: // Other Settings Menus
			switch(sub_menu_id) {
			  case 0: // Max Duty Sub Menu
				sjoinrom(line1,"Max DUTY");
				sjoin(line2,ftoa(100*((float)((float)MAX_DUTY)/ABSOLUTE_MAX_DUTY),1,&str[0])); // Output as precentage...
				sjoinrom(line2,"%");
				break;
			  case 1: // Max RPM Sub Menu
				sjoinrom(line1,"Max RPM");
				sjoin(line2,itoa(MAX_RPM,&str[0]));
				break;
			  case 2: // Encoder Wheel Resolution Sub Menu
#if TACHOMETER_ENABLED
				sjoinrom(line1,"Enc. Resolution");
				sjoin(line2,itoa((int)ENCODER_RESOLUTION,&str[0]));
#else
				goto_menu(3,0);
#endif
				break;
			}
			break;
	}

	// Add |L, |R, |M modifiers for Hold Down Status on Buttons
    str[0] = '\0'; // Clear Temporary String...

	if( get_button_state(0) == 2 ) {
		sjoinrom(&str[0]," |L");
		scopy_right(line2,&str[0],line_width);
	} else if( get_button_state(1) == 2 ) {
		sjoinrom(&str[0]," |M");
		scopy_right(line2,&str[0],line_width);
	} else if( get_button_state(2) == 2 ) {
		sjoinrom(&str[0]," |R");
		scopy_right(line2,&str[0],line_width);
	} else if( !PAUSED && CURRENT_LIMIT_LAST_DETECTED ) {
		sjoinrom(&str[0]," |CL");
		scopy_right(line2,&str[0],line_width);
	}

#if TACHOMETER_ENABLED
	if( show_rpm == 1 ) { // Show Actual RPM on right side of Line 1
		str[0] = '\0'; // Clear Temporary String...
		sjoinrom(&str[0],"RPM: ");
		sjoin(&str[0],itoa(rpm_actual,&str2[0]));
		scopy_right(line1,&str[0],line_width);
	}
#endif
}