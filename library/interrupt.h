/*
 * interrupt.h
 *
 *  Created on: Jul 29, 2023
 *      Author: Phong
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "TM4C123GH6PM.h"
#include "core_cm4.h"

/**
 * @brief Enable interrupt and set priority
 * 
 * @ref NVIC page 124
 * @ref ISER page 141
 * 
 * @param interruptNum  order of interrupt
 * @param priority      priority of interrupt
 * @param enable        0: disable, 1: enable
 */
inline void configISER(IRQn_Type interruptNum, uint32_t priority, uint8_t enable);

#endif /* INTERRUPT_H_ */
