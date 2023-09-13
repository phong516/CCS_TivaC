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

#define GPIOA_BIT 0U
#define GPIOB_BIT 1U
#define GPIOC_BIT 2U
#define GPIOD_BIT 3U
#define GPIOE_BIT 4U
#define GPIOF_BIT 5U

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

/**
 * @brief read GPIO interrupt status in RIS or MIS
 * 
 * @ref GPIORIS: page 668
 * @ref GPIOMIS: page 669
 * @ref GPIOICR: page 670
 * 
 * @param gpioPortX 
 * @param misOrRis 1: read MIS, 0: read RIS
 * @return uint8_t interrupt status
 */
uint8_t gpioIntStatus(GPIOA_Type *gpioPortX, uint8_t misOrRis);

/**
 * @brief clear GPIO interrupt flags
 * 
 * @param gpioPortX 
 * @param intFlags interrupt flags to clear
 */
void gpioIntClear(GPIOA_Type *gpioPortX, uint8_t intFlags);

#endif /* GPIO_H_ */
