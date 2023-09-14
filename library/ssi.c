/*
 * ssi.c
 *
 *  Created on: Aug 18, 2023
 *      Author: Phong
 */

#include "library/ssi.h"

inline void __enableSSImodule(uint8_t SSImodule){
    SYSCTL->RCGCSSI |= SSImodule;
}

inline void __configSSICR1(SSI0_Type *SSImodule, uint8_t config){
    SSImodule->CR1 |= config;
}

inline void __enableSSIoperation(SSI0_Type *SSImodule){
    SSImodule->CR1 |= SSI_CR1_SSE_SSI_ENABLE;
}

inline void __disableSSIoperation(SSI0_Type *SSImodule){
    SSImodule->CR1 &= ~SSI_CR1_SSE_SSI_ENABLE;
}

inline void __configSSIclk(SSI0_Type *SSImodule, uint8_t clkSource){
    SSImodule->CC = clkSource;
}

inline void __configSSIclkPrescale(SSI0_Type *SSImodule, uint8_t clkPrescale){
    SSImodule->CPSR = clkPrescale;
}

inline void __configSSICR0(SSI0_Type *SSImodule, uint16_t serialClkRate, uint16_t dataSize, uint16_t otherConfig){
    SSImodule->CR0 |= (serialClkRate << SSI_CR0_SCR_BIT) | dataSize | otherConfig;
}

inline void __waitTxSSInotFull(SSI0_Type *SSImodule){
    while(!(SSImodule->SR & SSI_SR_TNF_TX_FIFO_NOT_FULL));
}

inline void __waitTxSSIdone(SSI0_Type *SSImodule){
    while((SSImodule->SR & SSI_SR_BSY_BUSY));
}

inline void __txSSI(SSI0_Type *SSImodule, uint16_t data){
    SSImodule->DR = data;
    __waitTxSSInotFull(SSImodule);
    SSImodule->DR = data;
    __waitTxSSIdone(SSImodule);

}



