/* Example code to transmit data with SPI1 module of TM4C123 */
/* Transmits character A and B with a delay of one second */
#include "TM4C123GH6PM.h"
#include "library/gpio.h"
#include "library/ssi.h"
#include "library/systick.h"

/* Main routine of code */
int main(void)
{
    __enableSSImodule(SYSCTL_RCGC_SSI1);
    gpioClockState(3, 1);
    gpioClockState(5, 1);

    alternatePinConfig(GPIOD, 0, 0x2);
    alternatePinConfig(GPIOD, 3, 0x2);

    GPIOF->DEN |= (1<<2);         /* set PF2 pin digital */
    GPIOF->DIR |= (1<<2);         /* set PF2 pin output */
    GPIOF->DATA |= (1<<2);        /* keep SS idle high */
    __disableSSIoperation(SSI1);
    __configSSIclk(SSI1, SSI_CLKSRC_SYSCLK);
    __configSSIclkPrescale(SSI1, 4);
    __configSSICR0(SSI1, 0, SSI_CR1_DSS_8BIT, 0);
    __enableSSIoperation(SSI1);

    unsigned char val1 = 'A';
    unsigned char val2 = 'B';

    while(1)
        {
    __txSSI(SSI1, val1); /* write a character */
    SysTick_delayHz(1);
    __txSSI(SSI1, val2); /* write a character */
    SysTick_delayHz(1);
    }
}
