#include "library/systick.h"

static volatile uint32_t tickCtr = 0;


void SysTick_delay(uint32_t delay){
    SysTick->LOAD = delay - 1UL; 
    SysTick->CTRL = 5U; 
}

void SysTick_delayMs(uint32_t delayMs)
{
    SysTick_delay(SYSCLK_1MS);
    for (uint32_t i = 0; i < delayMs; i++){
        SysTick->VAL = 0;
        while((SysTick->CTRL & STCTRL_COUNT) == 0); // wait until count flag is set
    }
}

void SysTick_delayHz(uint32_t delayHz)
{
    SysTick_delay(SYSCLK / delayHz);
    while((SysTick->CTRL & STCTRL_COUNT) == 0); // wait until count flag is set
}

void SysTickIntInit(void){
    SysTick_Config(SYSCLK_1MS); //1s
    __enable_irq();
}

uint32_t getTick(void){
    uint32_t tick;
    __disable_irq();
    tick = tickCtr;
    __enable_irq();
    return tick;
}

void SysTickInt_delayMs(uint32_t ticks){
    uint32_t tickStart = getTick();
    while ((getTick() - tickStart) < ticks);
}

void SysTick_Handler(void){
    ++tickCtr;
}
