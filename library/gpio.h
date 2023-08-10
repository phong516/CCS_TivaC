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

#define FALLING_EDGE 0U
#define RISING_EDGE  1U

#define _GPIOAFSEL_OFFSET   0x420

/**
 * @brief Initialize clock state for GPIO port
 *
 * @ref page 406
 *
 * @param port GPIO ports, from 0 to 5 (PORTA to PORTF)
 * @param state 1 for enable, 0 for disable
 *
 * @return none
 **/
void gpioClockState(uint8_t port, uint8_t state);

/**
 * @brief Config GPIO pin to be output or input
 * 
 * @param gpioPortX GPIOA to GPIOF or GPIOA_AHB to GPIOF_AHB
 * @param pin   0 to 7
 * @param IOType 0: input, 1: output
 */
void configGPIOInOut(GPIOA_Type *gpioPortX, uint8_t pin, uint8_t IOType);

/**
 * @brief Config GPIO pin interrupt edge type
 * 
 * @ref IS page 664
 * @ref IBE page 665
 * @ref IEV page 666
 * @ref IM page 667
 * @ref ICR page 670
 * 
 * @param gpioPortX GPIOA to GPIOF or GPIOA_AHB to GPIOF_AHB
 * @param pin  0 to 7
 * @param edgeType 0: falling edge, 1: rising edge
 */
void configGPIOInterrupt(GPIOA_Type *gpioPortX, uint8_t pin, uint8_t edgeType);

/**
 * @brief config alternate pin function
 * 
 * @ref AFSEL: page 671
 * @ref PCTL: page 688
 * @ref DEN: page 682
 * 
 * @param port GPIOA to GPIOF
 * @param pin 0 to 7
 * @param alternateFunction 0 to 15, page 1351 of datasheet
 * 
 * @return none
 */
void alternatePinConfig(GPIOA_Type *port, uint8_t pin, uint8_t alternateFunction);
#endif /* GPIO_H_ */
