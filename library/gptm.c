#include "library/gptm.h"
#include "library/interrupt.h"

static uint32_t tickCtr = 0;

inline void __timerClockEnable(uint8_t timer)
{
    SYSCTL->RCGCTIMER |= (1U << timer);
}

inline void __timerEnable(TIMER0_Type *timer)
{
    timer->CTL |= (1U << 0);
}

inline void __timerDisable(TIMER0_Type *timer)
{
    timer->CTL &= ~(1U << 0);
}

inline void __configTimer(TIMER0_Type *timer, uint32_t timerConfig)
{
    timer->CFG = timerConfig;
}

inline void __configTimerA(TIMER0_Type *timer, uint32_t timerAMode, uint32_t timerAPrescaler, uint32_t timerAInterval)
{
    timer->TAMR = timerAMode;
    timer->TAPR = timerAPrescaler - 1UL;
    timer->TAILR = timerAInterval - 1UL;
}

inline void __configTimerB(TIMER0_Type *timer, uint32_t timerBMode, uint32_t timerBPrescaler, uint32_t timerBInterval)
{
    timer->TBMR = timerBMode;
    timer->TAPR |= timerBPrescaler - 1UL;
    timer->TBILR = timerBInterval;
}

inline void __configTimerInt(TIMER0_Type *timer, uint32_t timerInterrupt){
    timer->IMR |= timerInterrupt;
}

uint32_t getTimerIntStatus(TIMER0_Type *timer, uint8_t mis){
    return (mis == 0) ? timer->RIS : timer->MIS;
}

inline void __clearTimerInt(TIMER0_Type *timer, uint32_t timerInterrupt){
    timer->ICR |= timerInterrupt;
}

inline void __timerDelayIntInit(){
    __timerClockEnable(0);
    __timerDisable(TIMER0);
    __configTimer(TIMER0, GPTMCFG_1632_16);
    __configTimerA(TIMER0, GPTMAMR_PERIODIC, 250UL, 64UL);
    __clearTimerInt(TIMER0, 0x1UL);
    __configTimerInt(TIMER0, GPTMIMR_TimeoutA);
    __timerEnable(TIMER0);
    configISER(TIMER0A_IRQn, 3, 1);

}

uint32_t getTickTimer0A(){
    __disable_irq();
    uint32_t tickNow = tickCtr;
    __enable_irq();
    return tickNow;
}

inline void __timerDelayInt_ms(uint32_t msTick){
    uint32_t tickStart = getTickTimer0A();
    while ((getTickTimer0A() - tickStart) < msTick);
}

void Timer0A_IRQHandler(void){
    ++tickCtr;
    __clearTimerInt(TIMER0, getTimerIntStatus(TIMER0, 1));
}

