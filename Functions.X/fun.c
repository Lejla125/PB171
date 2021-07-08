/* 
 * File:   fun.c
 * Author: lejla
 *
 * Created on 27 March 2021, 15:51
 */

#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "pins.h"
#include "mydelays.h"

/*
 * 
 */
enum mode {ANALOG_INPUT = 0, INPUT = 1, INPUT_PULLUP = 2, OUTPUT = 3};

int main(int argc, char** argv) {
    
    printf("%d\n", bitValue(5));
    uint8_t a = 14;
    bitWrite(&a, 0, 1);
    printf("%d\n",a);
    printf("%d", bitRead(8,3));
    
    pinMode(33, OUTPUT);
    pinMode(15, INPUT);
    printf("%d", digitalRead(18));
    delay(300);
    
    return (EXIT_SUCCESS);
}

