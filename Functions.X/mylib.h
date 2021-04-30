/* 
 * File:   mylib.h
 * Author: lejla
 *
 * Created on 27 March 2021, 12:56
 */

#ifndef MYLIB_H
#define	MYLIB_H

#include <stdint.h>

inline uint8_t bitValue(uint8_t b);
inline void bitClear(uint8_t *number, uint8_t b);
inline uint8_t bitRead(uint8_t number, uint8_t b);
inline void bitSet(uint8_t *number, uint8_t b);
inline void bitWrite(uint8_t *number, uint8_t b, uint8_t val);
inline uint8_t highByte(int number);
inline uint8_t lowByte(int number);
inline void setBit(volatile unsigned char *p, uint8_t b);
inline void clearBit(volatile unsigned char *p, uint8_t b);
inline uint8_t readBit(volatile unsigned char *p, uint8_t b);
#endif	/* MYLIB_H */

