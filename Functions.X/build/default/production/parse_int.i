# 1 "parse_int.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files/Microchip/MPLABX/v5.45/packs/Microchip/PIC18F-K_DFP/1.4.87/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "parse_int.c" 2
# 1 "./parse_int.h" 1
# 11 "./parse_int.h"
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\stdint.h" 1 3



# 1 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\musl_xc8.h" 1 3
# 4 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\stdint.h" 2 3
# 22 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\stdint.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 127 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned long uintptr_t;
# 142 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long intptr_t;
# 158 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\bits/alltypes.h" 3
typedef signed char int8_t;




typedef short int16_t;




typedef __int24 int24_t;




typedef long int32_t;





typedef long long int64_t;
# 188 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long long intmax_t;





typedef unsigned char uint8_t;




typedef unsigned short uint16_t;




typedef __uint24 uint24_t;




typedef unsigned long uint32_t;





typedef unsigned long long uint64_t;
# 229 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned long long uintmax_t;
# 22 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\stdint.h" 2 3


typedef int8_t int_fast8_t;

typedef int64_t int_fast64_t;


typedef int8_t int_least8_t;
typedef int16_t int_least16_t;

typedef int24_t int_least24_t;
typedef int24_t int_fast24_t;

typedef int32_t int_least32_t;

typedef int64_t int_least64_t;


typedef uint8_t uint_fast8_t;

typedef uint64_t uint_fast64_t;


typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;

typedef uint24_t uint_least24_t;
typedef uint24_t uint_fast24_t;

typedef uint32_t uint_least32_t;

typedef uint64_t uint_least64_t;
# 144 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\stdint.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\bits/stdint.h" 1 3
typedef int16_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
# 144 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\stdint.h" 2 3
# 11 "./parse_int.h" 2

# 1 "./buffer.h" 1
# 15 "./buffer.h"
struct buffer {
    int8_t buf[64];
    uint8_t head;
    uint8_t tail;
    uint8_t size;
};
# 29 "./buffer.h"
void bufferStore(struct buffer * const buffer, const int8_t byte);
int8_t bufferLoad(struct buffer * const buffer);
int8_t bufferPeek(const struct buffer * const buffer);
uint8_t bufferSize(const struct buffer * const buffer);
int8_t bufferGet(const struct buffer * const buffer, const uint8_t index);
# 12 "./parse_int.h" 2


int8_t getStartIndex(const struct buffer * const buffer);
int8_t getEndIndex(const struct buffer * const buffer, const int8_t start_index);
int8_t isNegative(struct buffer * const buffer, const int8_t start_index);
int32_t parse_int(struct buffer * const buffer, int8_t start, const int8_t end, const int8_t negative);
# 1 "parse_int.c" 2


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
