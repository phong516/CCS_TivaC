/*
 * gpio.c
 *
 *  Created on: Jul 29, 2023
 *      Author: Phong
 */
#include "library/gpio.h"

void gpioClockState(uint8_t port, uint8_t state){
    if (state == 1){
        SYSCTL->RCGCGPIO |= (1U << port); //enable clock for GPIO port
    }
    else {
        SYSCTL->RCGCGPIO &= ~(1U << port); //disable clock for GPIO port
    }
}

void configGPIOInOut(GPIOA_Type *gpioPortX, uint8_t pin, uint8_t IOType){
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

void configGPIOInterrupt(GPIOA_Type *gpioPortX, uint8_t pin, uint8_t edgeType){
    gpioPortX->IM &= ~0x7U; //enable interrupt for pin
    gpioPortX->IS &= ~(1U << pin); //set pin as edge sensitive
    gpioPortX->IBE &= ~(1U << pin); //set pin as single edge sensitive
    if (edgeType == FALLING_EDGE){
        gpioPortX->IEV &= ~(1U << pin); //falling edge
    }
    else{
        gpioPortX->IEV |= 1U << pin;    //rising edge
    }
    gpioPortX->RIS &= ~0x7U;
    gpioPortX->IM |= (1U << pin); //enable interrupt for pin
}

void alternatePinConfig(GPIOA_Type *port, uint8_t pin, uint8_t alternateFunction){
    port->AFSEL |= (1U << pin); //enable alternate pin
    port->PCTL &= ~(0b1111U << (pin * 4)); // clear the bits of alternate pin config
    port->PCTL |= (alternateFunction << (pin * 4)); // set the bits of alternate pin config
    port->DEN |= (1U << pin); // enable digital function
}

uint8_t gpioIntStatus(GPIOA_Type *gpioPortX, uint8_t misOrRis){
    return (misOrRis) ? (gpioPortX->MIS) : (gpioPortX->RIS);
}

void gpioIntClear(GPIOA_Type *gpioPortX, uint8_t intFlags){
    gpioPortX->ICR |= intFlags;
}
