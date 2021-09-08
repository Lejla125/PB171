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
#include "bits.h"
#include <stdbool.h>

enum modes {
    ANALOG_INPUT = 0, INPUT = 1, INPUT_PULLUP = 2, OUTPUT = 3
};

enum ports {
    A, B, C, D, E
};

enum values {
    LOW = 0, HIGH = 1
};

void pinMode(uint8_t pin, enum modes mode);
enum values digitalRead(uint8_t pin);
void digitalWrite(uint8_t pin, enum values value);
uint16_t analogRead(uint8_t pin);
void analogWrite(uint8_t pin, uint16_t duty_cycle);

#endif	/* PINS_H */

