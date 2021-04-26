/* 
 * File:   pins.h
 * Author: lejla
 *
 * Created on 26 April 2021, 10:35
 */

#ifndef PINS_H
#define	PINS_H

#include <stdint.h>
#include <stdbool.h>
#include <xc.h>
#include "mylib.h"

void pinMode(uint8_t pin, uint8_t mode);
bool digitalRead(uint8_t pin);

#endif	/* PINS_H */

