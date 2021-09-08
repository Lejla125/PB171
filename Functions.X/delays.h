/* 
 * File:   delays.h
 * Author: lejla
 *
 * Created on 01 May 2021, 22:14
 */

#ifndef DELAYS_H
#define	DELAYS_H

#include <stdint.h>
#include <pic18.h>
#include <time.h>

void delay(uint32_t ms);
void delayMicroseconds(uint32_t us);
uint32_t millis(void);
uint32_t micros(void);

#endif	/* DELAYS_H */

