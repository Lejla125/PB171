#include <stdint.h>
#include <stdbool.h>
#include <xc.h>
#include "mylib.h"

enum mode {ANALOG_INPUT = 0, INPUT = 1, OUTPUT = 2};
enum ports {A, B, C, D, E};
enum ports port;
uint8_t bit_val;

void pinToPort(uint8_t pin){
    uint8_t pins[36] = {2, 3, 4, 5, 6, 7, 14, 13,  //pins A0..A7
                         33, 34, 35, 36, 37, 38, 39, 40, // pins B0..B7
                         15, 16, 17, 18, 23, 24, 25, 26, // pins C0..C7
                         19, 20, 21, 22, 27, 28, 29, 30, // pins D0..D7
                         8, 9, 10, 1}; // pins E0..E3
    for(uint8_t i=0; i<36; i++){
        if (pins[i] == pin){
            if(i >= 0 && i <= 7) {
                port = A;
                bit_val = i;
                break;
            }
            else if (i >= 8 && i <= 15){
                port = B;
                bit_val = i-8;
                break;
            }
            else if (i >= 16 && i <= 23){
                 port = C;
                 bit_val = i-16;
                 break;
            }
            else if (i >= 24 && i <= 31){
                port = D;
                bit_val = i-24;
                break;
            }
            else {
                port = E;
                bit_val = i-32;
                break;
            }
        }
    }
 }
 
 void pinMode(uint8_t pin, uint8_t mode){
     if (pin == 11 || 
             pin == 12 || 
             pin == 31 || 
             pin == 32 || 
             pin < 1 || 
             pin > 40) return;
     if(mode != ANALOG_INPUT && mode != INPUT && mode != OUTPUT) return;
     
     pinToPort(pin);
     if(mode == ANALOG_INPUT){ 
         switch(port) {
             case A:
                TRISA = bitValue(bit_val);
                ANSELA = 1; 
                break;
             case B :
                TRISB = bitValue(bit_val);
                ANSELB = 1;
                break;
             case C:
                 TRISC = bitValue(bit_val);
                 ANSELC = 1;
                 break;
             case D:
                 TRISD = bitValue(bit_val);
                 ANSELD = 1;
                 break;
             case E:
                 TRISE = bitValue(bit_val);
                 ANSELE = 1;
                 break;
             default:
                 break;
         } 
     }
     else if(mode == INPUT){ 
         switch(port) {
             case A:
                TRISA = bitValue(bit_val);
                ANSELA = 0; 
                break;
             case B :
                TRISB = bitValue(bit_val);
                ANSELB = 0;
                break;
             case C:
                 TRISC = bitValue(bit_val);
                 ANSELC = 0;
                 break;
             case D:
                 TRISD = bitValue(bit_val);
                 ANSELD = 0;
                 break;
             case E:
                 TRISE = bitValue(bit_val);
                 ANSELE = 0;
                 break;
             default:
                 break;
         } 
     }
     else {
         switch(port) {
             case A:
                TRISA = ~bitValue(bit_val);
                ANSELA = 0; 
                break;
             case B :
                TRISB = ~bitValue(bit_val);
                ANSELB = 0;
                break;
             case C:
                 TRISC = ~bitValue(bit_val);
                 ANSELC = 0;
                 break;
             case D:
                 TRISD = ~bitValue(bit_val);
                 ANSELD = 0;
                 break;
             case E:
                 TRISE = ~bitValue(bit_val);
                 ANSELE = 0;
                 break;
             default:
                 break;
         } 
     }
 }