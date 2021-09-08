/* 
 * File:   buffer.h
 * Author: lejla
 *
 * Created on 27 August 2021, 09:31
 */

#ifndef BUFFER_H
#define	BUFFER_H

#include <stdint.h>

#define BUFFER_SIZE 64

struct buffer {
    int8_t buf[BUFFER_SIZE];
    uint8_t head;
    uint8_t tail;
    uint8_t size;
};

#define BUFFER_INIT(buffer_name) struct buffer buffer_name = {\
    .buf = { [0 ... BUFFER_SIZE - 1] = -1 }, \
    .head = 0, \
    .tail = 0, \
    .size = 0, \
}

void bufferStore(struct buffer * const buffer, const int8_t byte);
int8_t bufferLoad(struct buffer * const buffer);
int8_t bufferPeek(const struct buffer * const buffer);
uint8_t bufferSize(const struct buffer * const buffer);
int8_t bufferGet(const struct buffer * const buffer, const uint8_t index);

#endif	/* BUFFER_H */

