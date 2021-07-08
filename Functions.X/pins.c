#include <stdint.h>
#include <xc.h>
#include "mylib.h"
#include <stdbool.h>

enum mode {ANALOG_INPUT = 0, INPUT = 1, INPUT_PULLUP = 2, OUTPUT = 3};
enum ports {A, B, C, D, E};
enum values {LOW = 0, HIGH = 1};

uint8_t pinToIndex(uint8_t pin){
    uint8_t pins[36] = {2, 3, 4, 5, 6, 7, 14, 13,  //pins A0..A7
                         33, 34, 35, 36, 37, 38, 39, 40, // pins B0..B7
                         15, 16, 17, 18, 23, 24, 25, 26, // pins C0..C7
                         19, 20, 21, 22, 27, 28, 29, 30, // pins D0..D7
                         8, 9, 10, 1}; // pins E0..E3
    uint8_t i;
    for(i=0; i<36; i++){
        if (pins[i] == pin){
            break;
        }
    }
    return i;
 }

enum ports convertToPort(uint8_t i){
    if(i >= 0 && i <= 7) {
        return A;
    }
    else if (i >= 8 && i <= 15){
        return B;
    }
    else if (i >= 16 && i <= 23){
       return C;
    }
    else if (i >= 24 && i <= 31){
        return D;
    }
    else {
        return E;
    }
}

uint8_t convertToBit(uint8_t i){
    if(i >= 0 && i <= 7) {
        return i;
    }
    else if (i >= 8 && i <= 15){
        return i-8;
    }
    else if (i >= 16 && i <= 23){
        return i-16;
    }
    else if (i >= 24 && i <= 31){
        return i-24;
    }
    else {
        return i-32;
    }
}
 
 void pinMode(uint8_t pin, uint8_t mode){
     if (pin == 11 || 
             pin == 12 || 
             pin == 31 || 
             pin == 32 || 
             pin < 1 || 
             pin > 40) return;
     if(mode != ANALOG_INPUT && mode != INPUT && mode != INPUT_PULLUP && mode != OUTPUT) return;
     
     uint8_t port_num = pinToIndex(pin);
     enum ports port = convertToPort(port_num);
     uint8_t bit_val = convertToBit(port_num);
     
     if(mode == ANALOG_INPUT){ 
         switch(port) {
             case A:
                 setBit(&TRISA, bit_val);
                 setBit(&ANSELA, bit_val);
                 break;
             case B :
                 setBit(&TRISB, bit_val);
                 setBit(&ANSELB, bit_val);
                 break;
             case C:
                 setBit(&TRISC, bit_val);
                 setBit(&ANSELC, bit_val);
                 break;
             case D:
                 setBit(&TRISD, bit_val);
                 setBit(&ANSELD, bit_val);
                 break;
             case E:
                 setBit(&TRISE, bit_val);
                 setBit(&ANSELE, bit_val);
                 break;
             default:
                 break;
         } 
     }
     else if(mode == INPUT){ 
         switch(port) {
             case A:
                 setBit(&TRISA, bit_val);
                 clearBit(&LATA, bit_val);
                 clearBit(&ANSELA, bit_val);
                 break;
             case B :
                 setBit(&TRISB, bit_val);
                 clearBit(&LATB, bit_val);
                 clearBit(&ANSELB, bit_val);
                 break;
             case C:
                 setBit(&TRISC, bit_val);
                 clearBit(&LATC, bit_val);
                 clearBit(&ANSELC, bit_val);
                 break;
             case D:
                 setBit(&TRISD, bit_val);
                 clearBit(&LATD, bit_val);
                 clearBit(&ANSELD, bit_val);
                 break;
             case E:
                 setBit(&TRISE, bit_val);
                 clearBit(&LATE, bit_val);
                 clearBit(&ANSELE, bit_val);
                 break;
             default:
                 break;
         } 
     }
     else if(mode == INPUT_PULLUP){ 
         switch(port) {
             case A:
                 setBit(&TRISA, bit_val);
                 setBit(&LATA, bit_val);
                 clearBit(&ANSELA, bit_val);
                 break;
             case B :
                 setBit(&TRISB, bit_val);
                 setBit(&LATB, bit_val);
                 clearBit(&ANSELB, bit_val);
                 break;
             case C:
                 setBit(&TRISC, bit_val);
                 setBit(&LATC, bit_val);
                 clearBit(&ANSELC, bit_val);
                 break;
             case D:
                 setBit(&TRISD, bit_val);
                 setBit(&LATD, bit_val);
                 clearBit(&ANSELD, bit_val);
                 break;
             case E:
                 setBit(&TRISE, bit_val);
                 setBit(&LATE, bit_val);
                 clearBit(&ANSELE, bit_val);
                 break;
             default:
                 break;
         } 
     }
     else {
         switch(port) {
             case A:
                 clearBit(&TRISA, bit_val);
                 clearBit(&ANSELA, bit_val); 
                 break;
             case B :
                 clearBit(&TRISB, bit_val);
                 clearBit(&ANSELB, bit_val);
                 break;
             case C:
                 clearBit(&TRISC, bit_val);
                 clearBit(&ANSELC, bit_val);
                 break;
             case D:
                 clearBit(&TRISD, bit_val);
                 clearBit(&ANSELD, bit_val);
                 break;
             case E:
                 clearBit(&TRISA, bit_val);
                 clearBit(&ANSELE, bit_val);
                 break;
             default:
                 break;
         } 
     }
 }
 
 enum values digitalRead(uint8_t pin){
     uint8_t port_num = pinToIndex(pin);
     enum ports port = convertToPort(port_num);
     uint8_t bit_val = convertToBit(port_num);
     enum values value;
     
     switch(port) {
         case A:
             value = readBit(&PORTA, bit_val); 
             break;
         case B :
             value = readBit(&PORTB, bit_val);
             break;
         case C:
             value = readBit(&PORTC, bit_val);
             break;
         case D:
             value = readBit(&PORTD, bit_val);
             break;
         case E:
             value = readBit(&PORTE, bit_val);
             break;
         default:
             break;
         }
     return value;
 }
 
 bool isAnalog(enum ports port, uint8_t bit_val){
     bool configuration;
     switch(port) {
         case A:
             configuration = readBit(&ANSELA, bit_val); 
             break;
         case B :
             configuration = readBit(&ANSELB, bit_val);
             break;
         case C:
             configuration = readBit(&ANSELC, bit_val);
             break;
         case D:
             configuration = readBit(&ANSELD, bit_val);
             break;
         case E:
             configuration = readBit(&ANSELE, bit_val);
             break;
         default:
             break;
         }
     return configuration;
 }
 
 void digitalWrite(uint8_t pin, enum values value){
     uint8_t port_num = pinToIndex(pin);
     enum ports port = convertToPort(port_num);
     uint8_t bit_val = convertToBit(port_num);
     
     if(isAnalog(port, bit_val)) return; //check whether pin is ANALOG_INPUT
     
     switch(port) {
         case A:
             value ? setBit(&LATA, bit_val) : clearBit(&LATA, bit_val); 
             break;
         case B :
             value ? setBit(&LATB, bit_val) : clearBit(&LATB, bit_val); 
             break;
         case C:
             value ? setBit(&LATC, bit_val) : clearBit(&LATC, bit_val); 
             break;
         case D:
             value ? setBit(&LATD, bit_val) : clearBit(&LATD, bit_val); 
             break;
         case E:
             value ? setBit(&LATE, bit_val) : clearBit(&LATE, bit_val); 
             break;
         default:
             break;
         }
     return;
 }
 
 uint16_t analogRead(uint8_t pin){
     uint8_t port_num = pinToIndex(pin);
     enum ports port = convertToPort(port_num);
     uint8_t bit_val = convertToBit(port_num);
     
     if(!isAnalog(port, bit_val)) return 1024; //1024 faulty value for adc
     
     uint16_t reading;
     uint16_t low_byte = ADRESL;
     uint16_t high_byte = ADRESH;
     
     if(ADCON2bits.ADFM == 1){
         high_byte = high_byte << 8;
     }
     else {
         high_byte = high_byte << 2;
         low_byte = low_byte >> 6;
     }
     reading = low_byte | high_byte;
     
     return reading;    
 }
