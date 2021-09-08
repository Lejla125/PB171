/* 
 * File:   fun.c
 * Author: lejla
 *
 * Created on 27 March 2021, 15:51
 */

#include <stdio.h>
#include <stdlib.h>
#include "bits.h"
#include "pins.h"
#include "delays.h"
#include "uart.h"
#include "eeprom.h"

/*
 * 
 */

void enable_uart_interrupts() {
    RCONbits.IPEN = 0; //disable interrupt priorities
    INTCONbits.GIE = 1; //enable global interrupts
    INTCONbits.PEIE = 1; //enable peripheral interrupts
    PIE1bits.TX1IE = 1; // enable EUSART1 transmit interrupt
    PIE1bits.RC1IE = 1; //enable EUSART1 receive interrupt
}

int main(int argc, char** argv) {
    
    printf("%d\n", bitValue(5));
    uint8_t a = 14;
    bitWrite(&a, 0, 1);
    printf("%d\n", a);
    printf("%d", bitRead(8, 3));

    pinMode(33, OUTPUT);
    pinMode(15, INPUT);
    printf("%d", digitalRead(18));
    delay(300);

    return (EXIT_SUCCESS);
}

