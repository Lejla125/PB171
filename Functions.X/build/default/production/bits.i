# 1 "bits.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files/Microchip/MPLABX/v5.45/packs/Microchip/PIC18F-K_DFP/1.4.87/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "bits.c" 2
# 1 "./bits.h" 1
# 11 "./bits.h"
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\stdint.h" 1 3



# 1 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\musl_xc8.h" 1 3
# 4 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\stdint.h" 2 3
# 22 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\stdint.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 127 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned long uintptr_t;
# 142 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long intptr_t;
# 158 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\bits/alltypes.h" 3
typedef signed char int8_t;




typedef short int16_t;




typedef __int24 int24_t;




typedef long int32_t;





typedef long long int64_t;
# 188 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long long intmax_t;





typedef unsigned char uint8_t;




typedef unsigned short uint16_t;




typedef __uint24 uint24_t;




typedef unsigned long uint32_t;





typedef unsigned long long uint64_t;
# 229 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned long long uintmax_t;
# 22 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\stdint.h" 2 3


typedef int8_t int_fast8_t;

typedef int64_t int_fast64_t;


typedef int8_t int_least8_t;
typedef int16_t int_least16_t;

typedef int24_t int_least24_t;
typedef int24_t int_fast24_t;

typedef int32_t int_least32_t;

typedef int64_t int_least64_t;


typedef uint8_t uint_fast8_t;

typedef uint64_t uint_fast64_t;


typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;

typedef uint24_t uint_least24_t;
typedef uint24_t uint_fast24_t;

typedef uint32_t uint_least32_t;

typedef uint64_t uint_least64_t;
# 144 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\stdint.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\bits/stdint.h" 1 3
typedef int16_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
# 144 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\stdint.h" 2 3
# 11 "./bits.h" 2


__attribute__((inline)) uint8_t bitValue(uint8_t b);
__attribute__((inline)) void bitClear(uint8_t *number, uint8_t b);
__attribute__((inline)) uint8_t bitRead(uint8_t number, uint8_t b);
__attribute__((inline)) void bitSet(uint8_t *number, uint8_t b);
__attribute__((inline)) void bitWrite(uint8_t *number, uint8_t b, uint8_t val);
__attribute__((inline)) uint8_t lowByte(int number);
__attribute__((inline)) uint8_t highByte(int number);
__attribute__((inline)) void setBit(volatile unsigned char *p, uint8_t b);
__attribute__((inline)) void clearBit(volatile unsigned char *p, uint8_t b);
__attribute__((inline)) uint8_t readBit(volatile unsigned char *p, uint8_t b);
# 1 "bits.c" 2


__attribute__((inline)) uint8_t bitValue(uint8_t b) {
    return 1 << b;
}

__attribute__((inline)) void bitClear(uint8_t *number, uint8_t b) {
    *number &= ~bitValue(b);
}

__attribute__((inline)) uint8_t bitRead(uint8_t number, uint8_t b) {
    return (number >> b) & 0x01;
}

__attribute__((inline)) void bitSet(uint8_t *number, uint8_t b) {
    *number |= bitValue(b);
}

__attribute__((inline)) void bitWrite(uint8_t *number, uint8_t b, uint8_t val) {
    val ? bitSet(number, b) : bitClear(number, b);
}

__attribute__((inline)) uint8_t lowByte(int number) {
    return number & 0xFF;
}

__attribute__((inline)) uint8_t highByte(int number) {
    return (number >> 8) & 0xFF;
}

__attribute__((inline)) void setBit(volatile unsigned char *p, uint8_t b) {
    *p |= bitValue(b);
}

__attribute__((inline)) void clearBit(volatile unsigned char *p, uint8_t b) {
    *p |= ~bitValue(b);
}

__attribute__((inline)) uint8_t readBit(volatile unsigned char *p, uint8_t b) {
    return (*p >> b) & 0x01;
}
