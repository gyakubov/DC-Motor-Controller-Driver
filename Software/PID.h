#ifndef __PID_H
#define __PID_H

// Global Accessible Variables
extern double PID_ff;
extern double PID_kp;
extern double PID_ki;
extern double PID_kd;
extern double PID_out;
extern unsigned int PID_out_clamp;
extern double PID_last_error;
extern unsigned char PID_derivative_delay;
extern unsigned char PID_integral_delay;
extern unsigned int PID_integral_clamp;

// Functions

/* Main PID Routine, Pass In Setpoint & Error, Returns 
   new output to be fed back to driver */

int pid(double setpoint,double error);

/* Helper function, computes absolute value of a number
   and returns that value */

double pid_abs(double number);

/* Helper function, used to reset the PID variables - good
   when the system is reset, stopped, started, etc.. */

void pid_reset(void);

#endif