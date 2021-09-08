/* 
 * File:   uart.h
 * Author: lejla
 *
 * Created on 14 August 2021, 10:00
 */

#ifndef UART_H
#define	UART_H

enum base_val {
    BIN = 2, OCT = 8, DEC = 10, HEX = 16
};

uint8_t available();
uint8_t availableForWrite();
void begin(int speed);
void end();
void flush();
int8_t peek();
void write(int8_t data);
void print(const char *string);
void println(const char *string);
void printInt(const int32_t number, enum base_val value);
void printlnInt(const int32_t number, enum base_val value);
int8_t read();
uint8_t readBytes(int8_t * const buffer, const uint8_t length);
int32_t parseInt();

#endif	/* UART_H */

