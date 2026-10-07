#include	"PID.h"

// PID Constants
double PID_ff = 0; // Feed Forward Constant
double PID_kp = 0; // Proportional Constant
double PID_ki = 0; // Integral Constant
double PID_kd = 0; // Derivative Constant

// PID Output Variables
double PID_out = 0; // Last Calculated Output From pid() routine
unsigned int PID_out_clamp = 0; // If != 0, Clamp PID_out to Assigned Value

// PID Error Variables
double PID_last_error = 0; // Last Known Error Value

// PID Derivative Variables
       unsigned char PID_derivative_delay = 1; // If != 0, Only process the derivative part every 'PID_derivative_delay'th time that pid() is called
static unsigned char PID_derivative_time = 0; // Counter that works in conjunction with 'PID_derivative_delay'
static double        PID_derivative = 0; // Derivative Value

// PID Integral Variables
unsigned char PID_integral_delay = 1; // If != 0, Only process the integral part every 'PID_integral_delay'th time that pid() is called
static unsigned char PID_integral_time = 0; // Counter that works in conjunction with 'PID_integral_delay'
unsigned int PID_integral_clamp = 0; // If != 0, Clamp PID_integral to Assigned Value
static double       PID_integral = 0; // Integral Value
static double       PID_integral_sample = 0; // Error Accumulator
static unsigned char PID_integral_limited = 0; // Integral Term Clamped Flag, 1=Clamped,0=Not Clamped

/*
Function: pid_reset
Description: Reset the PID system to initial defaults - good to call this
             if we are ever going to drastically change the system - when
             the PID constants are changed potentially, or when the system
             is stopped / started.
*/
void pid_reset(void) {
    PID_out = 0;
    PID_integral = 0;
    PID_integral_sample = 0;
    PID_derivative = 0;
    PID_last_error = 0;
}

/*
Function: pid_abs
Description: Helper function which computes the absolute value of a double
             precision number.

Params:
number - number to compute the absolute value of

Returns:
a double precision number representing the absolute value of the number param
*/
double pid_abs(double number) {
    if( number < 0 ) {
        return number*-1;
    } else {
        return number;
    }
}

/*
Function: pid
Description: Main pid computation function - based on the very well known
             and documented PID algorithm that has been used for years
             in many industrial controllers. Lots of information can be
             had by searching google for 'PID Algorthm' and I will not go
             into an indepth description of how it works here.

             Should be called by the main program at some reliable interval 
             with an expected setpoint value & error value. The setpoint value 
             is only used for the Feed Forward calculation, everything else 
             relies solely on the error value being passed in. The function 
             returns an output that should be fed back into the controller.
             
             ie: for PWM motor ( or heater ) control, this value could be used 
             to set the DUTY cycle of the PWM output.

Params:
setpoint - The expected value which was used when computing the error. This
           value is only used if Feed Forward is enabled.

error - The error of the closed loop control system determined by the 
        setpoint minus "some feedback sensor value". The pid() function attempts
        to reduce the error value to 0, and adjusts PID_out in order to attempt
        to achieve that.
*/
int pid(double setpoint,double error) {
    double tmp = 0;

    /*
    Only Run the PID Process if error != 0

    --- future addition could be to add an acceptable 
        error band such that when we are close enough
        to the setpoint we will assume the system is
        stable.
    */
    if( error != 0 ) {
    	// Handle Derivative Part
        PID_derivative_time++; // Increment Counter
        
        if( PID_derivative_time >= PID_derivative_delay ) { // If Counter >= Delay Process
    	    PID_derivative = error-PID_last_error;

            PID_derivative_time = 0; // Reset Counter
            PID_last_error = error;
        }

    	// Handle Integral Part
    	PID_integral_time++; // Increment Counter
    	PID_integral_sample += error; // Add Error To Sample

    	if( PID_integral_time >= PID_integral_delay ) { // If Counter >= Delay Process
			if( PID_integral_limited == 0 ) { // Don't Process If PID Output Is Clamped
        		PID_integral_sample /= PID_integral_time; // Determine Average Sample Over Time Period
        		PID_integral += PID_integral_sample; // Add Sample to Current Integral Value

        		if( PID_integral_clamp > 0 && pid_abs(PID_integral) > PID_integral_clamp ) { // If PID_integral_clamp set, determine if PID_integral should be clamped
            		if( PID_integral < 0 ) {
                		PID_integral = (double)(PID_integral_clamp*-1);
            		} else {
                		PID_integral = (double)PID_integral_clamp;
            		}
        		}
			}

        	PID_integral_sample = 0; // Reset the Integral Sample
        	PID_integral_time = 0; // Reset the Integral Counter
    	}

    	// Calculate PID Output, applying Gain Constants To Terms
		PID_out = error*PID_kp;
    	PID_out += PID_integral*PID_ki;
        PID_out += PID_derivative*PID_kd;

		if( PID_ff != 0 ) { // Feed Forward
			PID_out += setpoint*PID_ff;
		}

    	if( PID_out_clamp > 0 && pid_abs(PID_out) > PID_out_clamp ) { // If PID_out_clamp set, determine if PID_out should be clampled
        	if( PID_out < 0 ) {
            	PID_out = (double)(PID_out_clamp*-1);
        	} else {
            	PID_out = (double)PID_out_clamp;
        	}

			// Set flag to prevent Integral term from being processed
			PID_integral_limited = 1;
    	} else {
			PID_integral_limited = 0;
		}
    }

    return (int)PID_out;
}