# MPLAB IDE generated this makefile for use with GNU make.
# Project: DC Motor Controller.mcp
# Date: Wed Sep 11 21:44:37 2013

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

DC\ Motor\ Controller.cof : Delay.o LCD.o main.o PID.o EEPROM.o UI.o
	$(LD) /p18LF14K50 /l"C:\Program Files (x86)\Microchip\mplabc18\v3.40\lib" "Delay.o" "LCD.o" "main.o" "PID.o" "EEPROM.o" "UI.o" /u_CRUNTIME /z__MPLAB_BUILD=1 /m"DC Motor Controller.map" /w /o"DC Motor Controller.cof"

Delay.o : Delay.c Delay.h Delay.c
	$(CC) -p=18LF14K50 "Delay.c" -fo="Delay.o"

LCD.o : LCD.c Delay.h LCD.h LCD.c C:/Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/p18lf14k50.h
	$(CC) -p=18LF14K50 "LCD.c" -fo="LCD.o"

main.o : main.c C:/Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/stdlib.h EEPROM.h PID.h Delay.h UI.h main.c C:/Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/p18lf14k50.h
	$(CC) -p=18LF14K50 "main.c" -fo="main.o"

PID.o : PID.c PID.h PID.c
	$(CC) -p=18LF14K50 "PID.c" -fo="PID.o"

EEPROM.o : EEPROM.c EEPROM.h EEPROM.c C:/Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/p18lf14k50.h
	$(CC) -p=18LF14K50 "EEPROM.c" -fo="EEPROM.o"

UI.o : UI.c UI.h LCD.h UI.c
	$(CC) -p=18LF14K50 "UI.c" -fo="UI.o"

clean : 
	$(RM) "Delay.o" "LCD.o" "main.o" "PID.o" "EEPROM.o" "UI.o" "DC Motor Controller.cof" "DC Motor Controller.hex" "DC Motor Controller.map"

