#include <stdint.h>

 inline uint8_t bitValue(uint8_t b){
    return 1 << b;
}

inline void bitClear(uint8_t *number, uint8_t b){
    *number &= ~bitValue(b);
}

inline uint8_t bitRead(uint8_t number, uint8_t b){
    return (number >> b) & 0x01;
}

inline void bitSet(uint8_t *number, uint8_t b){
    *number |= bitValue(b);
}

 inline void bitWrite(uint8_t *number, uint8_t b, uint8_t val){
    val ? bitSet(number, b) : bitClear(number, b);
}

 inline uint8_t lowByte(int number){
    return number & 0xFF;
}

 inline uint8_t highByte(int number){
    return (number >> 8) & 0xFF;
}
 inline void setBit(volatile unsigned char *p, uint8_t b){
     *p |= bitValue(b);
 }
 
 inline void clearBit(volatile unsigned char *p, uint8_t b){
     *p |= ~bitValue(b);
 }
 inline uint8_t readBit(volatile unsigned char *p, uint8_t b){
    return (*p >> b) & 0x01;
}