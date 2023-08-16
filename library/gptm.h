#include "TM4C123GH6PM.h"

#define GPTMCFG_1632_32     0x0UL
#define GPTMCFG_3264_64     0x0UL
#define GPTMCFG_1632_32RTC  0x1UL
#define GPTMCFG_3264_64RTC  0x1UL
#define GPTMCFG_1632_16     0x4UL
#define GPTMCFG_3264_32     0x4UL

#define GPTMAMR_ONESHOT     0x1UL
#define GPTMAMR_PERIODIC    0x2UL
#define GPTMAMR_CAPTURE     0x3UL

#define GPTMIMR_TimeoutA    0x1UL
#define GPTMIMR_TimeoutB    0x100UL
/**
 * @brief Enable the clock for the timer
 * @ref RCGCTIMER: page 338
 * 
 * @param timer 0 to 5
 * @return ** void 
 */
inline void __timerClockEnable(uint8_t timer);

/**
 * @brief Enable the timer
 * @ref TIMERCTL: page 737

 * 
 * @param timer TIMER0 to TIMER5
 * 
 * @return void
 */
inline void __timerEnable(TIMER0_Type *timer);

/**
 * @brief Disable the timer
 * @ref TIMERCTL: page 737

 * @param timer TIMER0 to TIMER5
 * 
 * @return void 
 */
inline void __timerDisable(TIMER0_Type *timer);

/**
 * @brief Configure the timer
 * 
 * @param timer TIMER0 to TIMER5
 * @param timerConfig 16bit, 32bit, 64bit, 32bit RTC, 64bit RTC
 * @ref TIMERCFG: page 727
 * 
 * @return void 
 */
inline void __configTimer(TIMER0_Type *timer, uint32_t timerConfig);

/**
 * @brief config Timer A Mode, Prescaler and Interval

 * @ref TIMERAMODE: page 729 
 * @ref TIMERAPRESCALER: 760
 * @ref TIMERAINTERVAL: page 756

 * @param timer TIMER0 to TIMER5
 * @param timerAMode based on datasheet 
 * @param timerAPrescaler prescaler value, 2^(mode (16, 32 or 64) bit) / (SYSCLK / prescaler) = period in seconds to overflow (delay time)
 * @param timerAInterval based on datasheet
 */
inline void __configTimerA(TIMER0_Type *timer, uint32_t timerAMode, uint32_t timerAPrescaler, uint32_t timerAInterval);

/**
 * @brief config Timer B Mode, Prescaler and Interval
 * 
 * @ref TIMERBMODE: page 729 
 * @ref TIMERBPRESCALER: 761
 * @ref TIMERAINTERVAL: page 757

 * @param timer TIMER0 to TIMER5
 * @param timerBMode based on datasheet 
 * @param timerBPrescaler prescaler value, 2^(mode bit) / (SYSCLK / prescaler) = period in seconds to overflow (delay time)
 * @param timerBInterval based on datasheet
 */
inline void __configTimerB(TIMER0_Type *timer, uint32_t timerBMode, uint32_t timerBPrescaler, uint32_t timerBInterval);

/**
 * @brief config Timer interrupt mode
 * @ref GPTMIMR: page 745
 * 
 * @param timer TIMER0 to TIMER5
 * @param timerInterrupt base on datasheet
 */
inline void __configTimerInt(TIMER0_Type *timer, uint32_t timerInterrupt);

/**
 * @brief get the current status of the timer interrupt GPTMRIS or GPTMMIS
 * 
 * @ref GPTMRIS: page 748
 * @ref GPTMMIS: page 751
 * 
 * @param timer TIMER0 to TIMER5
 * @param mis 1 for mis, 0 for ris
 * @return uint32_t status of the timer interrupt
 */
uint32_t getTimerIntStatus(TIMER0_Type *timer, uint8_t mis);

/**
 * @brief clear the timer interrupt
 * 
 * @ref GPTMICR: page 754
 * 
 * @param timer TIMER0 to TIMER5
 * @param timerInterrupt 
 */
inline void __clearTimerInt(TIMER0_Type *timer, uint32_t timerInterrupt);

uint32_t getTickTimer0A();

inline void __timerDelayIntInit();

inline void __timerDelayInt_ms(uint32_t msTick);

