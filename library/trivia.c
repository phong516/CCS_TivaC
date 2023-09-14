/*
* trivia.c
*
* Created on: Sep 13, 2023
*       Author: Phong
*/

#include "library/trivia.h"

uint16_t linearInterpolation(uint16_t x, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1){
    uint16_t y = y0 + (x - x0) * (y1 - y0) / (x1 - x0);
    return y;
}

void intToString(uint32_t value, char* str, uint8_t bufferSize) {
    int i = bufferSize - 1;
    str[i] = '\0'; // Null-terminate the string

    // Handle the case when the value is zero separately
    if (value == 0) {
        str[--i] = '0';
        return;
    }

    while (value > 0 && i > 0) {
        str[--i] = '0' + (value % 10);
        value /= 10;
    }

    // If the buffer is not large enough, handle the truncation or error condition here
    // For example, set an error flag or truncate the string representation
}

int getNumberOfDigits(uint32_t number) {
    if (number == 0) {
        return 1;  // Special case for zero
    }

    uint8_t count = 0;
    while (number > 0) {
        number /= 10;
        count++;
    }

    return count;
}
