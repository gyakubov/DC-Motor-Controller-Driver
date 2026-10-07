#include "EEPROM.h"
#include <p18lf14k50.h>

unsigned char EEPROM_Read(unsigned char address) {  
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EEADR = address;
    EECON1bits.RD = 1;
    return EEDATA; 
}

void EEPROM_Write(unsigned char address, unsigned char databyte) {
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EEDATA = databyte;
    EEADR = address;
    EECON1bits.WREN = 1;
     
    INTCONbits.GIE = 0;
    EECON2 = 0x55;
    EECON2 = 0xAA; 
    EECON1bits.WR = 1;
    INTCONbits.GIE = 1;
     
    while (EECON1bits.WR == 1) { }; 
    EECON1bits.WREN = 0;
}