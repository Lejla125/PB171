#include <stdint.h>
#include <math.h>

uint8_t bitValue(uint8_t b){
    return pow(2, b);
}

uint8_t bitClear(uint8_t number, uint8_t b){
    return number &= ~(1 << b);
}

uint8_t bitRead(uint8_t number, uint8_t b){
    char oldb = b;
    number &= 1 << b;
    return number / pow(2, oldb);
}

void bitSet(uint8_t *number, uint8_t b){
    *number |= 1 << b;
}

void bitWrite(uint8_t *number, uint8_t b, uint8_t val){
    if (val == 0) 
        *number &= ~(1 << b);
    else
      *number |= 1 << b;  
}

uint8_t lowByte(int number){
    return number&0xFF;
}

uint8_t highByte(int number){
    return (number>>8) & 0xFF;
}