/* Generates 10KHz and 50% duty cycle on PF2 pin of TM4C123 Tiva C Launchpad */
/* PWM1 module and PWM generator 3 of PWM1 module is used */
#include "TM4C123GH6PM.h"
#include "pwm.h"
#include "interrupt.h"
#include "gpio.h"
int main(void)
{

//    pwmClockEnable(1);    // enable clock for PWM1 module
//    gpioClockState(5, 1); // enable clock for port F
//    pwmClockDivisorState(1);
//     pwmClockDivisorConfig(0x7); // set clock divisor to 1
//    alternatePinConfig(GPIOF, 2, 0x05); // configure PF2 as PWM1_3
//    alternatePinConfig(GPIOF, 3, 0x05); // configure PF3 as PWM1_3
//    pwmCountModeConfig(PWM1_BASE, 3, 0x0); // configure PWM1_3 as down counter
//    pwmLoadConfig(PWM1_BASE, 3, 16000U); // set load value for PWM1_3
//    pwmCompareConfig(PWM1_BASE, 3, 0, 500U - 1U); // set compare value for PWM1_3_A
//    pwmCompareConfig(PWM1_BASE, 3, 1, 250U - 1U); // set compare value for PWM1_3_B
//    pwmGenABConfig(PWM1_BASE, 3, 0,
//                    0x0, 0x0,
//                    0x1, 0x0,
//                    0x3, 0x0);
//    pwmGenABConfig(PWM1_BASE, 3, 1,
//                    0x1, 0x0,
//                    0x0, 0x0,
//                    0x2, 0x0);
//    pwmOutputState(PWM1_BASE, 3, 0);
//    pwmOutputState(PWM1_BASE, 3, 1);

    configGPIOOutput(GPIOF, 2, GPIO_OUTPUT);
    configGPIOOutput(GPIOF, 4, GPIO_INPUT);
   configISER(GPIOF_IRQn, 3, 1);

    while(1)
    {
            //do nothing
    }
}


/* This function generates delay in ms */
/* calculations are based on 16MHz system clock frequency */

void Delay_ms(int time_ms)
{
    int i, j;
    for(i = 0 ; i < time_ms; i++)
        for(j = 0; j < 3180; j++)
            {}  /* excute NOP for 1ms */
}

void SystemInit(void)
{
    /* use this only if you are using old versions of Keil uvision */
    SCB->CPACR |= 0x00f00000;
}

void GPIOPortF_IRQHandler(void){
    if (GPIOF->DATA & (1U << 4)){
        GPIOF->DATA |= (1U << 2);
    }
    else {
        GPIOF->DATA &= ~(1U << 2);
    }
    // Clear interrupt flag
    GPIOF->ICR |= 0x10;
}
