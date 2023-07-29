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

/**
 * @brief Config GPIO pin to be output or input
 * 
 * @param gpioPortX GPIOA to GPIOF or GPIOA_AHB to GPIOF_AHB
 * @param pin   0 to 7
 * @param IOType 0: input, 1: output
 */
void configGPIOOutput(GPIOA_Type *gpioPortX, uint8_t pin, uint8_t IOType);

/**
 * @brief Config GPIO pin interrupt edge type
 * 
 * @param gpioPortX GPIOA to GPIOF or GPIOA_AHB to GPIOF_AHB
 * @param pin  0 to 7
 * @param edgeType 
 */
void configGPIOInterrupt(GPIOA_Type *gpioPortX, uint8_t pin, uint8_t edgeType);

#endif /* GPIO_H_ */
