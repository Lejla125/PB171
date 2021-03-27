/* 
 * File:   mylib.h
 * Author: lejla
 *
 * Created on 27 March 2021, 12:56
 */

#ifndef MYLIB_H
#define	MYLIB_H

uint8_t bitValue(uint8_t b);
uint8_t bitClear(uint8_t *number, uint8_t b);
uint8_t bitRead(uint8_t number, uint8_t b);
void bitSet(uint8_t *number, uint8_t b);
void bitWrite(uint8_t *number, uint8_t b, uint8_t val);
uint8_t highByte(int number);
uint8_t lowByte(int number);
#endif	/* MYLIB_H */

