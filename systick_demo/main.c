#include "TM4C123GH6PM.h"
#include "library/gpio.h"
#include "library/systick.h"
int main()
{
  gpioClockState(5, 1);
  configGPIOInOut(GPIOF, 3, 1);
//  SysTickIntInit();

    while (1)
    {
        GPIOF->DATA ^= 8;
        SysTick_delayHz(2);
//        SysTickInt_delayMs(100);
    }
}



