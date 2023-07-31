/*
 * pwm.h
 *
 *  Created on: Jul 28, 2023
 *      Author: Phong
 */

#ifndef PWM_H_
#define PWM_H_

#include "TM4C123GH6PM.h"

#define PWM_COUNTDOWN       0U
#define PWM_COUNTUP         1U

#define bitRCC_USEPWMDIV    20U
#define bitRCC_PWMDIV       17U
#define bit_n_CTL_countMode 1U
#define bitGENA_ACTCMPBD    10U
#define bitGENA_ACTCMPBU    8U
#define bitGENA_ACTCMPAD    6U
#define bitGENA_ACTCMPAU    4U
#define bitGENA_ACTLOAD     2U
#define bitGENA_ACTZERO     0U

#define _n_CTL_OFFSET       0x040UL
#define _n_LOAD_OFFSET      0x050UL
#define _n_CMPA_OFFSET      0x058UL
#define _n_GENA_OFFSET      0x060UL
#define _PWMENABLE_OFFSET   0x008UL

#define _GENERATOR_OFFSET   0X040UL
#define _1_REGISTER_OFFSET  0X004UL

/**
 * @brief Initialize clock for PWM module
 * 
 * @ref page 354
 * 
 * @param pwmModule: 0 for PWM0, 1 for PWM1
 * 
 * @return none
 **/
void pwmClockEnable(uint8_t pwmModule);

/**
 * @brief Initialize clock state for GPIO port
 * 
 * @ref page 406
 * 
 * @param port GPIO ports, from 0 to 5 (PORTA to PORTF)
 * @param state 1 for enable, 0 for disable
 * 
 * @return none
 **/
void gpioClockState(uint8_t port, uint8_t state);

/**
 * @brief Initialize clock divisor for the PWM clock
 * 
 * @ref page 254
 * 
 * @param state 0 for clock system, 1 for clock divisor
 * 
 * @return none
 * 
 */
void pwmClockDivisorState(uint8_t state);

/**
 * @brief configure clock divisor for the PWM clock
 * 
 * @ref page 254
 * 
 * @param divisor: 0x0: /2, 0x1: /4, 0x2: /8, 0x3: /16, 0x4: /32, 0x5: /64, 0x6: /64, 0x7: /64
 * 
 * @return none
 * 
 */
void pwmClockDivisorConfig(uint8_t divisor);



/**
 * @brief config count mode for PWM generator
 * 
 * @ref page 1266
 * 
 * @param PWMn_BASE PWM0_BASE or PWM1_BASE
 * @param generator 0 to 3
 * @param countMode 0 for count-down, 1 for count-up
 * 
 * @return none
 */
void pwmCountModeConfig(uint32_t PWMn_BASE, uint8_t generator, uint8_t countMode);

/**
 * @brief config load value of PWM generator
 * 
 * @ref page 1278
 * 
 * @param PWMn_BASE PWM0_BASE or PWM1_BASE
 * @param generator 0 to 3
 * @param loadValue 16-bit value
 */
void pwmLoadConfig(uint32_t PWMn_BASE, uint8_t generator, uint32_t loadValue);

/**
 * @brief config compare value of PWM generator
 * 
 * @param PWMn_BASE PWM0_BASE or PWM1_BASE
 * @param generator 0 to 3
 * @param compareAB 0 for cmpA, 1 for cmpB
 * @param compareValue 16-bit value
 */
void pwmCompareConfig(uint32_t PWMn_BASE, uint8_t generator, uint8_t compareAB, uint16_t compareValue);

/**
 * @brief config PWM generator A or B output
 * 
 * @ref page 1282
 * 
 * @param PWMn_BASE PWM0_BASE or PWM1_BASE
 * @param generator 0 to 3
 * @param genAB 0 for generator A, 1 for generator B
 * @param bDown 0x0: do nothing, 0x1: invert genAB, 0x2: drive genAB Low, 0x3: drive genAB High
 * @param bUp 0x0: do nothing, 0x1: invert genAB, 0x2: drive genAB Low, 0x3: drive genAB High
 * @param aDown 0x0: do nothing, 0x1: invert genAB, 0x2: drive genAB Low, 0x3: drive genAB High
 * @param aUp 0x0: do nothing, 0x1: invert genAB, 0x2: drive genAB Low, 0x3: drive genAB High
 * @param counterLoad 0x0: do nothing, 0x1: invert genAB, 0x2: drive genAB Low, 0x3: drive genAB High
 * @param counterZero 0x0: do nothing, 0x1: invert genAB, 0x2: drive genAB Low, 0x3: drive genAB High
 */
void pwmGenABConfig(uint32_t PWMn_BASE, uint8_t generator, uint8_t genAB,
                   uint8_t bDown, uint8_t bUp, 
                   uint8_t aDown, uint8_t aUp, 
                   uint8_t counterLoad, uint8_t counterZero);

/**
 * @brief enable PWM output for a generator and output signal
 * 
 * @ref CTL: page 1266
 * @ref ENABLE: page 1247
 * 
 * @param PWMn_BASE PWM0_BASE or PWM1_BASE
 * @param generator 0 to 3
 * @param outputSignal 0 genA, 1 for genB
 */
void pwmOutputState(uint32_t PWMn_BASE, uint8_t generator, uint8_t outputSignal);

#endif /* PWM_H_ */
