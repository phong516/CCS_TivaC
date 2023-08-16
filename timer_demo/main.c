#include "TM4C123GH6PM.h"
#include "library/gpio.h"
#include "library/gptm.h"
#include "library/interrupt.h"

int main()
{
    gpioClockState(5, 1);
    configGPIOInOut(GPIOF, 3, 1);
//    __timerClockEnable(1);
//    __timerDisable(TIMER1);
//    __configTimer(TIMER1, GPTMCFG_1632_16);
//    __configTimerA(TIMER1, GPTMAMR_PERIODIC, 250UL, 6400UL);
//    __clearTimerInt(TIMER1, 0x1UL);
//    __configTimerInt(TIMER1, GPTMIMR_TimeoutA);
//    __timerEnable(TIMER1);
//    configISER(TIMER1A_IRQn, 3, 1);
    __timerDelayIntInit();
    while (1)
    {
        __timerDelayInt_ms(1000);
        GPIOF->DATA ^= 8;
    }
}


