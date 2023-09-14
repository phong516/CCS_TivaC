/*
* qei.c
*
* Created on: Sep 11, 2023
*       Author: Phong
*/

#include "library/qei.h"

void enableQeiClock(uint8_t qeiModule){
    SYSCTL->RCGCQEI |= qeiModule;
}

void configQeiControl(QEI0_Type *qeiModule, uint32_t config){
    qeiModule->CTL |= config;
}

void configQeiMaxPosition(QEI0_Type *qeiModule, uint32_t maxPositionValue){
    qeiModule->MAXPOS = maxPositionValue;
}

void configQeiTimerLoad(QEI0_Type *qeiModule, uint32_t timerLoadValue){
    qeiModule->LOAD = timerLoadValue;
}

void configQeiInterrupt(QEI0_Type *qeiModule, uint8_t intFlags){
    qeiModule->INTEN |= intFlags;
}

uint8_t qeiIntStatus(QEI0_Type *qeiModule){
    return (qeiModule->ISC);
}

void qeiIntClear(QEI0_Type *qeiModule, uint8_t intFlags){
    qeiModule->ISC |= intFlags;
}
