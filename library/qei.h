/*
* qei.h
*
* Created on: Sep 11, 2023
*       Author: Phong
*/

#ifndef QEI_H_
#define QEI_H_

#include "TM4C123GH6PM.h"

#define QEI0_BIT            1U // 1U << 0
#define QEI1_BIT            2U // 1U << 1

#define ENABLE_BIT          1U // 1U << 0
#define CAPMODE_PHAB_BIT    8U // 1U << 3
#define RESMODE_IDX_BIT     16U // 1U << 4
#define CAP_VEL_BIT         32U // 1U << 5   

#define INT_DIR_BIT         4U // 1U << 2
#define INT_TIMER_BIT       2U // 1U << 1
#define INT_INDEX_BIT       1U // 1U << 0

/*PD7 and PF0 of QEI0 Phase A is locked, so use QEI1*/


/*
1. Enable the QEI clock
2. Enable the GPIO clock
3. Config GPIO pin to alternate function and output digital
4. Configure the QEI:
- Config QEICTL
- Config QEIMAXPOS
5. Enable the QEI
6. Delay until the encoder position is required.
7. Read the encoder position in QEIPOS
*/

/**
 * @brief enable the QEI module clock
 * @ref RCGCQEI: page 355
 * 
 * @param qeiNum 
 */
extern inline void enableQeiClock(uint8_t qeiModule);

/**
 * @brief configure the QEI control QEICTL
 * @ref QEICTL: page 1312
 * 
 * @param qeiModule 
 * @param config 
 */
extern inline void configQeiControl(QEI0_Type *qeiModule, uint32_t config);

/**
 * @brief configure the QEI maximum position QEIMAXPOS
 * @ref QEIMAXPOS: page 1317
 * 
 * @param qeiModule 
 * @param maxPositionValue uint32_t value
 */
extern inline void configQeiMaxPosition(QEI0_Type *qeiModule, uint32_t maxPositionValue);

/**
 * @brief configure the QEI timer load value QEILOAD
 * @ref QEILOAD: page 1318
 * 
 * @param qeiModule 
 * @param timerLoadValue 
 */
extern inline void configQeiTimerLoad(QEI0_Type *qeiModule, uint32_t timerLoadValue);

/**
 * @brief configure the QEI interrupt
 * @ref QEIINTEN: page 1322
 * 
 * @param qeiModule 
 * @param interrupt 
 */

extern inline void configQeiInterrupt(QEI0_Type *qeiModule, uint8_t intFlags);

/**
 * @brief get the QEI interrupt status
 * @ref QEIISC: page 1326
 * 
 * @param qeiModule 
 * @param interrupt
 * @return uint8_t
 */
extern uint8_t qeiIntStatus(QEI0_Type *qeiModule);

/**
 * @brief 
 * 
 * @param qeiModule 
 * @param intFlags 
 */
extern inline void qeiIntClear(QEI0_Type *qeiModule, uint8_t intFlags);

#endif /* QEI_H_ */
