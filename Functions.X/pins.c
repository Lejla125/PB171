#include "pins.h"

uint8_t pinToIndex(uint8_t pin) {
    uint8_t pins[36] = {2, 3, 4, 5, 6, 7, 14, 13, //pins A0..A7
        33, 34, 35, 36, 37, 38, 39, 40, // pins B0..B7
        15, 16, 17, 18, 23, 24, 25, 26, // pins C0..C7
        19, 20, 21, 22, 27, 28, 29, 30, // pins D0..D7
        8, 9, 10, 1}; // pins E0..E3
    uint8_t i;
    for (i = 0; i < 36; i++) {
        if (pins[i] == pin) {
            break;
        }
    }
    return i;
}

enum ports convertToPort(uint8_t i) {
    if (i >= 0 && i <= 7) {
        return A;
    } else if (i >= 8 && i <= 15) {
        return B;
    } else if (i >= 16 && i <= 23) {
        return C;
    } else if (i >= 24 && i <= 31) {
        return D;
    } else {
        return E;
    }
}

uint8_t convertToBit(uint8_t i) {
    if (i >= 0 && i <= 7) {
        return i;
    } else if (i >= 8 && i <= 15) {
        return i - 8;
    } else if (i >= 16 && i <= 23) {
        return i - 16;
    } else if (i >= 24 && i <= 31) {
        return i - 24;
    } else {
        return i - 32;
    }
}

void pinMode(uint8_t pin, enum modes mode) {
    if (pin == 11 ||
            pin == 12 ||
            pin == 31 ||
            pin == 32 ||
            pin < 1 ||
            pin > 40) return;
    if (mode != ANALOG_INPUT && mode != INPUT && mode != INPUT_PULLUP && mode != OUTPUT) return;

    uint8_t port_num = pinToIndex(pin);
    enum ports port = convertToPort(port_num);
    uint8_t bit_val = convertToBit(port_num);

    if (mode == ANALOG_INPUT) {
        switch (port) {
            case A:
                setBit(&TRISA, bit_val);
                setBit(&ANSELA, bit_val);
                break;
            case B:
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
    } else if (mode == INPUT) {
        switch (port) {
            case A:
                setBit(&TRISA, bit_val);
                clearBit(&LATA, bit_val);
                clearBit(&ANSELA, bit_val);
                break;
            case B:
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
    } else if (mode == INPUT_PULLUP) {
        switch (port) {
            case A:
                setBit(&TRISA, bit_val);
                setBit(&LATA, bit_val);
                clearBit(&ANSELA, bit_val);
                break;
            case B:
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
    } else {
        switch (port) {
            case A:
                clearBit(&TRISA, bit_val);
                clearBit(&ANSELA, bit_val);
                break;
            case B:
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

enum values digitalRead(uint8_t pin) {
    uint8_t port_num = pinToIndex(pin);
    enum ports port = convertToPort(port_num);
    uint8_t bit_val = convertToBit(port_num);
    enum values value;

    switch (port) {
        case A:
            value = readBit(&PORTA, bit_val);
            break;
        case B:
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

bool isAnalog(enum ports port, uint8_t bit_val) {
    bool configuration;
    switch (port) {
        case A:
            configuration = readBit(&ANSELA, bit_val);
            break;
        case B:
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

void digitalWrite(uint8_t pin, enum values value) {
    uint8_t port_num = pinToIndex(pin);
    enum ports port = convertToPort(port_num);
    uint8_t bit_val = convertToBit(port_num);

    if (isAnalog(port, bit_val)) return; //check whether pin is ANALOG_INPUT

    switch (port) {
        case A:
            value ? setBit(&LATA, bit_val) : clearBit(&LATA, bit_val);
            break;
        case B:
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

uint16_t analogRead(uint8_t pin) {
    uint8_t port_num = pinToIndex(pin);
    enum ports port = convertToPort(port_num);
    uint8_t bit_val = convertToBit(port_num);

    if (!isAnalog(port, bit_val)) return 1024; //1024 faulty value for adc

    ADCON2bits.ADCS = 0b000; //configure conversion clock, for 16 MHz is 125 ns
    ADCON1bits.PVCFG = 0b00; //A/D VREF+ connected to internal signal, AVDD
    //adc channel configuration
    if (port == A) {
        switch (bit_val) {
            case 0:
                ADCON0bits.CHS = 0b00000; //AN0
                break;
            case 1:
                ADCON0bits.CHS = 0b00001; //AN1
                break;
            case 2:
                ADCON0bits.CHS = 0b00010; //AN2
                break;
            case 3:
                ADCON0bits.CHS = 0b00011; //AN3
                break;
            case 4:
                ADCON0bits.CHS = 0b00100; //AN4
                break;
            default:
                break;
        }
    } else if (port == B) {
        switch (bit_val) {
            case 0:
                ADCON0bits.CHS = 0b01100; //AN12
                break;
            case 1:
                ADCON0bits.CHS = 0b01010; //AN10
                break;
            case 2:
                ADCON0bits.CHS = 0b01000; //AN8
                break;
            case 3:
                ADCON0bits.CHS = 0b01001; //AN9
                break;
            case 4:
                ADCON0bits.CHS = 0b01011; //AN11
                break;
            case 5:
                ADCON0bits.CHS = 0b01101; //AN13         
            default:
                break;
        }
    } else if (port == C) {
        switch (bit_val) {
            case 2:
                ADCON0bits.CHS = 0b01110; //AN14
                break;
            case 3:
                ADCON0bits.CHS = 0b01111; //AN15
                break;
            case 4:
                ADCON0bits.CHS = 0b10000; //AN16
                break;
            case 5:
                ADCON0bits.CHS = 0b10001; //AN17
                break;
            case 6:
                ADCON0bits.CHS = 0b10010; //AN18
                break;
            case 7:
                ADCON0bits.CHS = 0b10011; //AN19
                break;
            default:
                break;
        }
    } else if (port == D) {
        switch (bit_val) {
            case 0:
                ADCON0bits.CHS = 0b10100; //AN20
                break;
            case 1:
                ADCON0bits.CHS = 0b10101; //AN21
                break;
            case 2:
                ADCON0bits.CHS = 0b10110; //AN22
                break;
            case 3:
                ADCON0bits.CHS = 0b10111; //AN23
                break;
            case 4:
                ADCON0bits.CHS = 0b11000; //AN24
                break;
            case 5:
                ADCON0bits.CHS = 0b11001; //AN25
                break;
            case 6:
                ADCON0bits.CHS = 0b11010; //AN26
                break;
            case 7:
                ADCON0bits.CHS = 0b11011; //AN27S
                break;
            default:
                break;
        }
    } else if (port == E) {
        switch (bit_val) {
            case 0:
                ADCON0bits.CHS = 0b00101; //AN5
                break;
            case 1:
                ADCON0bits.CHS = 0b00110; //AN6
                break;
            case 2:
                ADCON0bits.CHS = 0b00111; //AN7
                break;
            default:
                break;
        }
    }
    ADCON2bits.ADFM = 1; //result formatting
    ADCON2bits.ACQT = 0b001; //acquisition time 2 Tad
    ADCON0bits.ADON = 1; //enable adc
    ADCON0bits.GO = 1; //start adc

    while (ADCON0bits.GO == 1); //wait for adc to finish
    PIR1bits.ADIF = 0; //clear the adc interrupt flag, has to be done  even if interrupts are not enabled
    
    uint16_t reading;
    uint16_t low_byte = ADRESL;
    uint16_t high_byte = ADRESH;

    if (ADCON2bits.ADFM == 1) {
        high_byte = high_byte << 8;
    } else {
        high_byte = high_byte << 2;
        low_byte = low_byte >> 6;
    }
    reading = low_byte | high_byte;
    ADCON0bits.ADON = 0; // disable adc

    return reading;
}

void analogWrite(uint8_t pin, uint16_t duty_cycle) {
    //all CCP pins
    if (pin != 17 && pin != 36 && pin != 16 && pin != 38 && pin != 8 && pin != 20 && pin != 10) return;
    if (duty_cycle == 0) {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
    } else if (duty_cycle == 255) {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, HIGH);
    } else {
        //PWM Period  = [(PRx)+ 1] * 4 * T_osc *(TMRx Prescale Value)
        //for F_osc = 16 MHz, PRx = 255 and TMRx Prescale Value = 4, PWM period = 256 us, around 3.9 kHz
        // XTAL freq = 16MHz, F_instr = 16 MHz/4 = 4MHz, T_instr = 1/4 MHz = 0.25 us
        //To obtain a period of 256 us, the timer needs to count 256 us/(T_instr *Prescale) = 256
        uint16_t val = duty_cycle * 4 * 256;
        uint16_t msb = (val & 0b1111111111111100) >> 2;
        uint16_t lsb = val & 0b0000000000000011;
        switch (pin) {
            case 8:
                setBit(&TRISE, 0);
                CCPTMRS0bits.C3TSEL = 0b00; //use Timer2 for CCP3
                PR2 = 255; //256 us/(0.25*4)us
                CCP3CONbits.CCP3M = 0b1111; //PWM mode
                CCP3CONbits.DC3B = lsb;
                CCPR3L = msb;
                PIR1bits.TMR2IF = 0;
                T2CONbits.T2CKPS = 0b01; //prescaler is 4
                T2CONbits.TMR2ON = 1;
                while (PIR1bits.TMR2IF == 0); //wait for timer to overflow
                clearBit(&TRISE, 0);
                break;
            case 10:
                setBit(&TRISE, 2);
                CCPTMRS1bits.C5TSEL = 0b01; //use Timer4 for CCP5
                PR4 = 255; //256 us/(0.25*4)us
                CCP5CONbits.CCP5M = 0b1111; //PWM mode
                CCP5CONbits.DC5B = lsb;
                CCPR5L = msb;
                PIR5bits.TMR4IF = 0;
                T4CONbits.T4CKPS = 0b01; //prescaler is 4
                T4CONbits.TMR4ON = 1;
                while (PIR5bits.TMR4IF == 0); //wait for timer to overflow
                clearBit(&TRISE, 2);
                break;
            case 16:
                setBit(&TRISC, 1);
                CCPTMRS0bits.C2TSEL = 0b01; //use Timer4 for CCP2
                PR4 = 255; //256 us/(0.25*4)us
                CCP2CONbits.CCP2M = 0b1111; //PWM mode
                CCP2CONbits.DC2B = lsb;
                CCPR2L = msb;
                PIR5bits.TMR4IF = 0;
                T4CONbits.T4CKPS = 0b01; //prescaler is 4
                T4CONbits.TMR4ON = 1;
                while (PIR5bits.TMR4IF == 0); //wait for timer to overflow
                clearBit(&TRISC, 1);
                break;
            case 17:
                setBit(&TRISC, 2);
                CCPTMRS0bits.C1TSEL = 0b10; //use Timer6 for CCP1
                PR6 = 255; //256 us/(0.25*4)us
                CCP1CONbits.CCP1M = 0b1111; //PWM mode
                CCP1CONbits.DC1B = lsb;
                CCPR1L = msb;
                PIR5bits.TMR6IF = 0;
                T6CONbits.T6CKPS = 0b01; //prescaler is 4
                T6CONbits.TMR6ON = 1;
                while (PIR5bits.TMR6IF == 0); //wait for timer to overflow
                clearBit(&TRISC, 2);
                break;
            case 20:
                setBit(&TRISD, 1);
                CCPTMRS1bits.C4TSEL = 0b00; //use Timer2 for CCP4
                PR2 = 255; //256 us/(0.25*4)us
                CCP4CONbits.CCP4M = 0b1111; //PWM mode
                CCP4CONbits.DC4B = lsb;
                CCPR4L = msb;
                PIR1bits.TMR2IF = 0;
                T2CONbits.T2CKPS = 0b01; //prescaler is 4
                T2CONbits.TMR2ON = 1;
                while (PIR1bits.TMR2IF == 0); //wait for timer to overflow
                clearBit(&TRISD, 1);
                break;
            case 36:
                setBit(&TRISB, 3);
                CCPTMRS0bits.C2TSEL = 0b01; //use Timer4 for CCP2
                PR4 = 255; //256 us/(0.25*4)us
                CCP2CONbits.CCP2M = 0b1111; //PWM mode
                CCP2CONbits.DC2B = lsb;
                CCPR2L = msb;
                PIR5bits.TMR4IF = 0;
                T4CONbits.T4CKPS = 0b01; //prescaler is 4
                T4CONbits.TMR4ON = 1;
                while (PIR5bits.TMR4IF == 0); //wait for timer to overflow
                clearBit(&TRISB, 3);
                break;
            case 38:
                setBit(&TRISB, 5);
                CCPTMRS0bits.C3TSEL = 0b00; //use Timer2 for CCP3
                PR2 = 255; //256 us/(0.25*4)us
                CCP3CONbits.CCP3M = 0b1111; //PWM mode
                CCP3CONbits.DC3B = lsb;
                CCPR3L = msb;
                PIR1bits.TMR2IF = 0;
                T2CONbits.T2CKPS = 0b01; //prescaler is 4
                T2CONbits.TMR2ON = 1;
                while (PIR1bits.TMR2IF == 0); //wait for timer to overflow
                clearBit(&TRISB, 0);
                break;
            default:
                return;
        }
    }

}