/*
 * gpio.c
 *
 *  Created on: Jul 29, 2023
 *      Author: Phong
 */
#include "gpio.h"

void configGPIOOutput(GPIOA_Type *gpioPortX, uint8_t pin, uint8_t IOType){
    gpioPortX->AFSEL &= ~(1U << pin); //disable alternate pin
    gpioPortX->DEN |= (1U << pin); //enable digital function

    if (IOType == GPIO_INPUT){
        gpioPortX->DIR &= ~(1U << pin); //set pin as output
    }
    else {
        gpioPortX->DIR |= (1U << pin); //set pin as input
    }

    gpioPortX->PUR |= (1U << pin); //enable pull-up resistor
    gpioPortX->PCTL &= ~(0b1111U << (pin * 4)); // clear the bits of alternate pin config
}
