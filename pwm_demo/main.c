/* Generates 10KHz and 50% duty cycle on PF2 pin of TM4C123 Tiva C Launchpad */
/* PWM1 module and PWM generator 3 of PWM1 module is used */
#include "TM4C123GH6PM.h"
#include "pwm.h"
#include "interrupt.h"
#include "gpio.h"

#define SW1 (1U << 4)
#define LED (1U << 2)
#define LOAD 16000U
int main(void)
{
        pwmClockEnable(1);    // enable clock for PWM1 module
        gpioClockState(5, 1); // enable clock for port F
        pwmClockDivisorState(1);
         pwmClockDivisorConfig(0x7); // set clock divisor to 1
        alternatePinConfig(GPIOF, 2, 0x05); // configure PF2 as PWM1_3
        alternatePinConfig(GPIOF, 3, 0x05); // configure PF3 as PWM1_3
        pwmCountModeConfig(PWM1_BASE, 3, 0x0); // configure PWM1_3 as down counter
        pwmLoadConfig(PWM1_BASE, 3, LOAD); // set load value for PWM1_3
        pwmCompareConfig(PWM1_BASE, 3, 0, 500U - 1U); // set compare value for PWM1_3_A
        pwmCompareConfig(PWM1_BASE, 3, 1, 250U - 1U); // set compare value for PWM1_3_B
        pwmGenABConfig(PWM1_BASE, 3, 0,
                        0x0, 0x0,
                        0x1, 0x0,
                        0x3, 0x0);
        pwmGenABConfig(PWM1_BASE, 3, 1,
                        0x1, 0x0,
                        0x0, 0x0,
                        0x2, 0x0);
        pwmOutputState(PWM1_BASE, 3, 0);
        pwmOutputState(PWM1_BASE, 3, 1);
       configGPIOInOut(GPIOF, 4, GPIO_INPUT);
       configGPIOInterrupt(GPIOF, 4, 0);
       configISER(GPIOF_IRQn, 3, 1);
    while(1)
    {

    }
}


void GPIOPortF_IRQHandler(void){
    uint32_t mis = GPIOF->MIS;
    if (mis & SW1){
        uint32_t compareA = PWM1->_3_CMPA;
        uint32_t compareB = PWM1->_3_CMPB;
        if (LOAD - compareA < 1000){
            pwmCompareConfig(PWM1_BASE, 3, 0, 100);
        }
        else{
            pwmCompareConfig(PWM1_BASE, 3, 0, compareA + 500);
        }

        if (compareB < 1000){
            pwmCompareConfig(PWM1_BASE, 3, 1, LOAD - 500);
        }
        else{
            pwmCompareConfig(PWM1_BASE, 3, 1, compareB - 500);
        }

        GPIOF->ICR |= SW1;
    }
}
