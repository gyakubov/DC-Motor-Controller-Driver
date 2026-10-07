#ifndef __EEPROM_H
#define __EEPROM_H

void EEPROM_Write(unsigned char address, unsigned char databyte);
unsigned char EEPROM_Read(unsigned char address);

#endif