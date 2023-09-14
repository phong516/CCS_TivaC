#include <stdlib.h>
#include "TM4C123GH6PM.h"
#include "library/interrupt.h"
#include "library/gpio.h"
#include "library/uart.h"
#include "library/qei.h"
#include "library/trivia.h"

static inline void initQEI(void);

static uint8_t velFlag = 0;

int main(void)
{
       uint32_t vel = 0;
       uint8_t numDigits = 0;
       char *velStr = (char*)calloc(numDigits + 1, sizeof(char)); //string length + '\0'
       
       enableUARTModule(0);
       initQEI();
    while(1){
        __disable_irq();
        if (velFlag){
            velFlag = 0;
            vel = (QEI1->SPEED) * 0.06;
            numDigits = getNumberOfDigits(vel); //string length
            realloc(velStr, numDigits + 1);     //string length + '\0'
            intToString(vel, velStr, numDigits + 1); //string length + '\0'
            uartTransmitBuffer(UART0, velStr, numDigits + 1); //string length + '\0'
        }
        __enable_irq();
    }
}

void QEI1_IRQHandler(void){
    uint8_t intFlags = qeiIntStatus(QEI1);
    if (intFlags & INT_TIMER_BIT){
        GPIOF->DATA ^= 8U;
        velFlag = 1;
    }
    qeiIntClear(QEI1, intFlags);
}

void initQEI(void){
    gpioClockState(GPIOF_BIT, 1); //to blink led when interrupt occurs
    configGPIOInOut(GPIOF, 3, 1);

    enableQeiClock(QEI1_BIT);
    gpioClockState(GPIOC_BIT, 1);

    configGPIOInOut(GPIOC, 5, GPIO_INPUT); //phase a QEI1
    configGPIOInOut(GPIOC, 6, GPIO_INPUT); //phase b QEI1

    alternatePinConfig(GPIOC, 5, 0x06); // configure PC5 as PHA
    alternatePinConfig(GPIOC, 6, 0x06); // configure PC5 as PHB

    configQeiControl(QEI1, CAPMODE_PHAB_BIT | CAP_VEL_BIT);
    configQeiTimerLoad(QEI1, 3999999); //250ms

    configISER(QEI1_IRQn, 3, 1);
    configQeiInterrupt(QEI1, INT_TIMER_BIT);
    configQeiControl(QEI1, ENABLE_BIT);

}


