#include "eeprom.h"

uint8_t eepromRead(uint8_t address) {
    EEADR = address; // set the address to read from
    EECON1bits.EEPGD = 0; //to access EEPROM memory
    EECON1bits.CFGS = 0; // to access EEPROM memory
    EECON1bits.RD = 1; // to read from EEPROM
    uint8_t byte = EEDATA;
    if (byte == 0) byte = 0b11111111; //Locations that have never been written to have the value of 255.
    return byte;
}

void eepromWrite(uint8_t address, uint8_t value) {
    EEADR = address;
    EEDATA = value;
    EECON1bits.EEPGD = 0; //to access EEPROM memory
    EECON1bits.CFGS = 0;
    EECON1bits.WREN = 1;
    INTCONbits.GIE = 0; //disable all interrupts during write operation
    //write sequence
    EECON2 = 0x55;
    EECON2 = 0x0AA;
    EECON1bits.WR = 1; //begin write
    INTCONbits.GIE = 1; //enable interrupts

    while (EECON1bits.WR != 0); // wait for the writing operation to complete
    EECON1bits.WREN = 0; //disable writes on write complete
}

void eepromUpdate(uint8_t address, uint8_t value) {
    uint8_t old_value = eepromRead(address);
    
    if(old_value != value) eepromWrite(address, value);
    else return;
}
