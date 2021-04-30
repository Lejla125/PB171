/* 
 * File:   pins.h
 * Author: lejla
 *
 * Created on 26 April 2021, 10:35
 */

#ifndef PINS_H
#define	PINS_H

#include <stdint.h>
#include <xc.h>
#include "mylib.h"

enum values {LOW = 0, HIGH = 1};

void pinMode(uint8_t pin, uint8_t mode);
enum values digitalRead(uint8_t pin);

#endif	/* PINS_H */

