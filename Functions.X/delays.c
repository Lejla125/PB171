#include "delays.h"

#define _XTAL_FREQ 16000000  //16 MHz maximum frequency

void delay(uint32_t ms) {
    while (ms > 0) {
        __delay_ms(1);
        ms--;
    }
}

void delayMicroseconds(uint32_t us) {
    while (us > 0) {
        __delay_us(1);
        us--;
    }
}

uint32_t seconds() {
    clock_t clk_ticks = clock();
    uint32_t seconds = clk_ticks / CLOCKS_PER_SEC;
    return seconds;
}

uint32_t millis(void) {
    return seconds() * 1000;
}

uint32_t micros(void) {
    return seconds() * 1000000;
}