#include <stdint.h>
#include <pic18.h>
#include <time.h>

#define _XTAL_FREQ 16000000  //16 MHz maximum frequency

void delay(unsigned long ms){
    while(ms > 0)
   {
       __delay_ms(1);
      ms--;
    }
}

void delayMicroseconds(unsigned long us){
    while(us > 0)
   {
       __delay_us(1);
      us--;
    }
}

unsigned long seconds(){
    clock_t clk_ticks = clock();
    unsigned long seconds = clk_ticks / CLOCKS_PER_SEC;
    return seconds;
}

unsigned long millis(){
    return seconds() * 1000;
}

unsigned long micros(){
    return seconds() * 1000000;
}