/* 
 * File:   eeprom.h
 * Author: lejla
 *
 * Created on 01 September 2021, 13:15
 */

#ifndef EEPROM_H
#define	EEPROM_H

#include <stdint.h>
#include <pic18.h>

uint8_t eepromRead(uint8_t address);
void eepromWrite(uint8_t address, uint8_t value);
void eepromUpdate(uint8_t address, uint8_t value);
#endif	/* EEPROM_H */

