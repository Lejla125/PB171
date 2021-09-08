#include "buffer.h"

void bufferStore(struct buffer * const buffer, const int8_t byte) {
    if (buffer->size >= BUFFER_SIZE) {
        return;
    }
    buffer->buf[buffer->head] = byte;
    buffer->size++;
    buffer->head = (buffer->head + 1) % BUFFER_SIZE;
}

int8_t bufferLoad(struct buffer * const buffer) {
    if (buffer->size == 0) {
        return -1;
    }
    const int8_t byte = bufferPeek(buffer);
    buffer->buf[buffer->tail] = -1;
    buffer->tail = (buffer->tail + 1) % BUFFER_SIZE;
    buffer->size--;
    return byte;
}

int8_t bufferPeek(const struct buffer * const buffer) {
    const int8_t byte = buffer->buf[buffer->tail];
    return byte;
}

uint8_t bufferSize(const struct buffer * const buffer) {
    return buffer->size;
}

int8_t bufferGet(const struct buffer * const buffer, const uint8_t index) {
    return buffer->buf[(buffer->tail + index) % BUFFER_SIZE];
}
