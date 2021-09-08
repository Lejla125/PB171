#include <stdint.h>
#include <xc.h>
#include <pic18.h>
#include "uart.h"
#include "buffer.h"
#include "delays.h"
#include "helpers.h"
#include "parse_int.h"

#define _XTAL_FREQ 16000000  //16 MHz maximum frequency

BUFFER_INIT(receive_buffer);
BUFFER_INIT(transmit_buffer);

void __interrupt() myIsr(void) {
    if (PIE1bits.TX1IE && PIR1bits.TX1IF) {
        if (bufferSize(&transmit_buffer)) {
            TXREG1 = bufferLoad(&transmit_buffer);
        }
        PIR1bits.TX1IF = 0;
    }
    if (PIE1bits.RC1IE && PIR1bits.RC1IF) {
        const uint8_t byte = RCREG1;
        bufferStore(&receive_buffer, byte);
        PIR1bits.RC1IF = 0;
    }
}

//This microcontroller has two Enhanced Universal Synchronous 
//Asynchronous Receiver Transmitter (EUSART) modules 
//but I will write the code for only one module 
// since the code for the second one is exactly the same but uses different registers

uint8_t available() {
    return bufferSize(&receive_buffer);
}

uint8_t availableForWrite() {
    return BUFFER_SIZE - bufferSize(&transmit_buffer);
}

void begin(int speed) {
    SPBRG = (uint8_t) ((_XTAL_FREQ / 64) / speed) - 1; // 25 for Fosc = 16 MHz, baud rate 9600, asynchronous mode and 8-bit BRG
    BAUDCON1bits.BRG16 = 0;
    TXSTA1bits.BRGH = 0;
    TXSTA1bits.TXEN = 1; // enable transmission
    TXSTA1bits.TX9 = 0; // use 8-bit transmission
    RCSTA1bits.SPEN = 1; // enable Serial port (TX and RX pins)
    RCSTA1bits.CREN = 1; //enable reception
    RCSTA1bits.RX9 = 0; //8-bit reception
    SYNC1 = 0; // for asynchronous reception
}

void end() {
    RCSTA1bits.SPEN = 0; // disable Serial port (TX and RX pins)
    TXSTA1bits.TXEN = 0; //disable transmission
    RCSTA1bits.CREN = 0; //disable reception
}

void flush() {
    while (availableForWrite() < BUFFER_SIZE);
}

int8_t peek() {
    return bufferPeek(&receive_buffer);
}

void write(int8_t data) {
    if (!bufferSize(&transmit_buffer) && PIR1bits.TX1IF == 0) {
        TXREG1 = data;
    } else {
        bufferStore(&transmit_buffer, data);
    }
}

void print(const char *string) {
    uint8_t i = 0;

    while (string[i] != '\n') {
        write(string[i]);
        i++;
    }
}

void println(const char *string) {
    print(string);
    write('\n');
}

void printInt(const int32_t number, enum base_val value) {
    char buffer[32];
    itoa(number, buffer, value);
    print(buffer);
}

void printlnInt(const int32_t number, enum base_val value) {
    printInt(number, value);
    write('\n');
}

int8_t read() {
    return bufferLoad(&receive_buffer);
}

uint8_t readBytes(int8_t * const buffer, const uint8_t length) {
    const uint32_t timeout = 1000;
    const uint32_t start = millis();
    uint8_t index = 0;

    while (millis() - start < timeout) { //the timeout is set to 1 second
        while (index < length && bufferSize(&receive_buffer) > 0) {
            buffer[index] = bufferLoad(&receive_buffer);
            index++;
        }
        if (index == length) {
            break;
        }
    }
    return index;
}

int32_t parseInt() {
    const uint32_t timeout = 1000;
    const uint32_t start = millis();
    int8_t start_index = -1;
    int8_t end_index = -1;
    while (millis() - start < timeout) {
        start_index = getStartIndex(&receive_buffer);
        end_index = getEndIndex(&receive_buffer, start_index);
        if (end_index != -1 && end_index != bufferSize(&receive_buffer)) {
            break;
        }
    }
    const int8_t negative = isNegative(&receive_buffer, start_index);
    const int32_t result = parse_int(&receive_buffer, start_index, end_index, negative);
    return result;
}



