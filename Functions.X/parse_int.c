#include "parse_int.h"

int8_t getStartIndex(const struct buffer * const buffer) {
    for (int8_t i = 0; i < bufferSize(buffer); i++) {
        const char c = bufferGet(buffer, i);
        if (c >= '0' && c <= '9') {
            return i;
        }
    }
    return -1;
}

int8_t getEndIndex(const struct buffer * const buffer, const int8_t start_index) {
    if (start_index == -1) return -1;

    int8_t index = start_index + 1;
    char c;
    while (index < bufferSize(buffer)) {
        c = bufferGet(buffer, index);

        if (c >= '0' && c <= '9') index++;
        else break;
    }
    return index;
}

int8_t isNegative(struct buffer * const buffer, const int8_t start_index) {
    if (start_index == 0) return 0;
    if (bufferGet(buffer, start_index - 1) == '-') return 1;
    return 0;
}

int32_t parse_int(struct buffer * const buffer, int8_t start, const int8_t end, const int8_t negative) {
    for (uint8_t i = 0; i < start; i++) {
        bufferLoad(buffer);
    }
    while (start < end && bufferGet(buffer, start) == '0') {
        bufferLoad(buffer);
        start++;
    }
    if (start == end) {
        return 0;
    }
    int32_t result = bufferLoad(buffer) - '0';
    start++;
    while (start < end) {
        result *= 10;
        result += bufferLoad(buffer) - '0';
        start++;
    }
    return negative ? -result : result;
}
