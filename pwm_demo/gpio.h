/*
 * gpio.h
 *
 *  Created on: Jul 29, 2023
 *      Author: Phong
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "TM4C123GH6PM.h"

#define GPIO_INPUT 0U
#define GPIO_OUTPUT 1U

#define _GPIOAFSEL_OFFSET   0x420

void configGPIOOutput(GPIOA_Type *gpioPortX, uint8_t pin, uint8_t IOType);

#endif /* GPIO_H_ */
