/*
 * interrupt.c
 *
 *  Created on: Jul 29, 2023
 *      Author: Phong
 */
#include "interrupt.h"

void configISER(IRQn_Type interruptNum, uint32_t priority, uint8_t enable){
    // Set priority
    NVIC_SetPriority(interruptNum, priority);
    // Enable interrupt
    if(enable){
        NVIC_EnableIRQ(interruptNum);
    }
    else{
        NVIC_DisableIRQ(interruptNum);
    }
}
