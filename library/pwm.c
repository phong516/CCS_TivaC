/*
 * pwm.c
 *
 *  Created on: Jul 28, 2023
 *      Author: Phong
 */

#include "pwm.h"

void pwmClockEnable(uint8_t pwmModule){
    SYSCTL->RCGCPWM |= (1U << pwmModule);
}

void gpioClockState(uint8_t port, uint8_t state){
    if (state == 1){
        SYSCTL->RCGCGPIO |= (1U << port); //enable clock for GPIO port
    }
    else {
        SYSCTL->RCGCGPIO &= ~(1U << port); //disable clock for GPIO port
    }
}

void pwmClockDivisorState(uint8_t state){
    if (state == 0){
        SYSCTL->RCC &= ~(1U << bitRCC_USEPWMDIV); //disable clock divisor for the PWM clock
    }
    else {
        SYSCTL->RCC |= (1U << bitRCC_USEPWMDIV); //enable clock divisor for the PWM clock
    }
}

void pwmClockDivisorConfig(uint8_t divisor){
    SYSCTL->RCC &= ~(0b111U << bitRCC_PWMDIV);
    SYSCTL->RCC |= (divisor << bitRCC_PWMDIV);
}



void pwmCountModeConfig(uint32_t PWMn_BASE, uint8_t generator, uint8_t countMode){
    __IO uint32_t *_n_CTL = (uint32_t *)(PWMn_BASE + _n_CTL_OFFSET + _GENERATOR_OFFSET * generator);
    *_n_CTL &= ~(1U << 0); // disable PWM generator
    if (countMode == PWM_COUNTDOWN){ //page 1266
        *_n_CTL &= ~(1U << bit_n_CTL_countMode); // count-down mode
    }
    else {
        *_n_CTL |= (1U << bit_n_CTL_countMode); // count-up mode
    }
}

void pwmLoadConfig(uint32_t PWMn_BASE, uint8_t generator, uint32_t loadValue){
    __IO uint32_t *_n_LOAD = (uint32_t *)(PWMn_BASE + _n_LOAD_OFFSET + _GENERATOR_OFFSET * generator);
    *_n_LOAD = loadValue;
}

void pwmCompareConfig(uint32_t PWMn_BASE, uint8_t generator, uint8_t compareAB, uint16_t compareValue){
    __IO uint32_t *_n_CMPx = (uint32_t *)(PWMn_BASE + _n_CMPA_OFFSET + _GENERATOR_OFFSET * generator + _1_REGISTER_OFFSET * compareAB);
    *_n_CMPx = compareValue;
}

void pwmGenABConfig(uint32_t PWMn_BASE, uint8_t generator, uint8_t genAB,
                   uint8_t bDown, uint8_t bUp, 
                   uint8_t aDown, uint8_t aUp, 
                   uint8_t counterLoad, uint8_t counterZero){
    __IO uint32_t *_n_GENx = (uint32_t *)(PWMn_BASE + _n_GENA_OFFSET + _GENERATOR_OFFSET * generator + _1_REGISTER_OFFSET * genAB);
    *_n_GENx &= ~(0b11111111U << 0); // clear the bits of PWMGENx register
    *_n_GENx |= bDown << bitGENA_ACTCMPBD;
    *_n_GENx |= bUp << bitGENA_ACTCMPBU;
    *_n_GENx |= aDown << bitGENA_ACTCMPAD;
    *_n_GENx |= aUp << bitGENA_ACTCMPAU;
    *_n_GENx |= counterLoad << bitGENA_ACTLOAD;
    *_n_GENx |= counterZero << bitGENA_ACTZERO;
}

void pwmOutputState(uint32_t PWMn_BASE, uint8_t generator, uint8_t outputSignal){
    __IO uint32_t *_n_CTL = (uint32_t *)(PWMn_BASE + _n_CTL_OFFSET + _GENERATOR_OFFSET * generator);
    __IO uint32_t *PWMENABLE = (uint32_t *)(PWMn_BASE + _PWMENABLE_OFFSET);
    *_n_CTL |= (1U << 0); // enable PWM generator
    *PWMENABLE |= (1U << (2 * generator + outputSignal)); // enable PWM output
}
