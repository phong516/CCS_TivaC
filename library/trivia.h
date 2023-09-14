/*
* trivia.h
*
* Created on: Sep 13, 2023
*       Author: Phong
*/
#ifndef TRIVIA_H_
#define TRIVIA_H_

#include <stdint.h>

extern uint16_t linearInterpolation(uint16_t x, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);    

extern void intToString(uint32_t value, char* str, uint8_t bufferSize);

extern int getNumberOfDigits(uint32_t number);

#endif /* TRIVIA_H_ */
