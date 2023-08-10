#include "TM4C123GH6PM.h"

#define SYSCLK          16000000UL  // 16 MHz
#define SYSCLK_1MS       16000UL     // 16 MHz / 1000Hz
#define STCTRL_COUNT    0x10000     // 1 << 16

/**
 * @brief SysTick delay for "delay" ticks
 * 
 * @ref STCTL page 138
 * @ref STRELOAD page 140
 * @ref STCURRENT page 141
 * 
 * @param delay ticks to delay
 */
void SysTick_delay(uint32_t delay);

void SysTick_delayMs(uint32_t delayMs);

void SysTick_delayHz(uint32_t delayHz);

void SysTickIntInit(void);

uint32_t getTick(void);

void SysTickInt_delayMs(uint32_t ticks);


