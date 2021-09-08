#include <stdlib.h>
#include "helpers.h"

void swap(char *x, char *y) {
    char t = *x;
    *x = *y;
    *y = t;
}

char* reverse(char *buffer, int i, int j) {
    while (i < j) {
        swap(&buffer[i++], &buffer[j--]);
    }
    return buffer;
}

char* itoa(int value, char* buffer, int base_val) {
    // invalid input
    if (base_val < 2 || base_val > 32) {
        return buffer;
    }

    int n = abs(value);
    int i = 0;

    while (n) {
        int r = n % base_val;

        if (r >= 10) {
            buffer[i++] = 65 + (r - 10);
        } else {
            buffer[i++] = 48 + r;
        }

        n = n / base_val;
    }

    // if the number is 0
    if (i == 0) {
        buffer[i++] = '0';
    }

    // If the base is 10 and the value is negative, the resulting string
    // is preceded with a minus sign (-)
    // With any other base, value is always considered unsigned
    if (value < 0 && base_val == 10) {
        buffer[i++] = '-';
    }

    buffer[i] = '\0';

    // reverse the string and return it
    return reverse(buffer, 0, i - 1);
}

