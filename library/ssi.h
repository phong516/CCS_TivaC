/*
 * SSI.h
 *
 *  Created on: Aug 18, 2023
 *      Author: Phong
 */

#ifndef SSI_H_
#define SSI_H_

#include "TM4C123GH6PM.h"

/* Step to initialize and config SPI
1. enable run mode clock for ssi SYSCTL->RCGCSSI
2. enable RCGCGPIO for the apporiate SSI module
3. set the ssi pins to alternate function
4. assign ssi function to pins
5. enable pin digital 
6. disable ssi operation in SSI->CR1
7. select master or slave mode
8. config the SSI clocksource in SSI->CC
9. config the clock prescale divisor in SSI->CPSR, must be an even number from 2 to 254
10. config clock rate, clock phase, protocol mode and data size in SSI->CR0
 BITRATE = SYSCLK / (CPSR * (1 + SCR))
 SCR from 0 to 255
 */

#define SYSCTL_RCGC_SSI0            0x01UL
#define SYSCTL_RCGC_SSI1            0x02UL
#define SYSCTL_RCGC_SSI2            0x04UL
#define SYSCTL_RCGC_SSI3            0x08UL

#define SSI_CR1_EOT_INT_ENABLE      0x10U
#define SSI_CR1_MS_SLAVE_MODE       0x4U
#define SSI_CR1_SSE_SSI_ENABLE      0x2U
#define SSI_CR1_LBM_LOOPBACK_MODE   0x1U

#define SSI_CLKSRC_SYSCLK           0x0U
#define SSI_CLKSRC_PIOSC            0x5U

#define SSI_CR0_SCR_BIT             0x8U

#define SSI_CR1_SPH_2ND_CLK_EDGE    0x80U
#define SSI_CR1_SPO_HIGH_STATE      0x40U
#define SSI_CR1_FRF_TI              0x10U
#define SSI_CR1_FRF_MICROWIRE       0x20U
#define SSI_CR1_DSS_4BIT            0x3U
#define SSI_CR1_DSS_5BIT            0x4U
#define SSI_CR1_DSS_6BIT            0x5U
#define SSI_CR1_DSS_7BIT            0x6U
#define SSI_CR1_DSS_8BIT            0x7U
#define SSI_CR1_DSS_9BIT            0x8U
#define SSI_CR1_DSS_10BIT           0x9U
#define SSI_CR1_DSS_11BIT           0xAU
#define SSI_CR1_DSS_12BIT           0xBU
#define SSI_CR1_DSS_13BIT           0xCU
#define SSI_CR1_DSS_14BIT           0xDU
#define SSI_CR1_DSS_15BIT           0xEU
#define SSI_CR1_DSS_16BIT           0xFU

#define SSI_SR_TNF_TX_FIFO_NOT_FULL 0x2U
#define SSI_SR_BSY_BUSY             0x10U

/**
 * @brief enable run mode clock for SSI module
 * @ref RCGCSSI: page 346
 * @param SSImodule SSI0 to SSI3
 */
inline void __enableSSImodule(uint8_t SSImodule);

/**
 * @brief config the SSI->CR1 based on datasheet
 * @brief on reset, TXRIS interrupts TXFIFO <= 1/2 full, master mode, SSI operation disabled, 
                    normal serial port operation enabled
 * @ref SSI_CR1: page 971
 * 
 * @param SSImodule SSI0 to SSI3
 */
inline void __configSSICR1(SSI0_Type *SSImodule, uint8_t config);

/**
 * @brief enable the SSI module to operate
 * 
 * @ref SSI->CR1_SSE: page 971
 * 
 * @param SSImodule SSI0 to SSI3
 */
inline void __enableSSIoperation(SSI0_Type *SSImodule);

/**
 * @brief disable the SSI module to operate
 * 
 * @ref SSI->CR1_SSE: page 971
 * 
 * @param SSImodule SSI0 to SSI3
 */
inline void __disableSSIoperation(SSI0_Type *SSImodule);

/**
 * @brief config the clock source for SSI module
 * 
 * @ref SSI->CC: page 984
 * 
 * @param SSImodule SSI0 to SSI3
 * @param clkSource SYSCLK or PIOSC
 */
inline void __configSSIclk(SSI0_Type *SSImodule, uint8_t clkSource);

/**
 * @brief config the clock prescale divisor
 * 
 * @ref SSI->PSR: page 976
 * 
 * @param SSImodule SSI0 to SSI3
 * @param clkPrescale must be an even number from 2 to 254
 */
inline void __configSSIclkPrescale(SSI0_Type *SSImodule, uint8_t clkPrescale);

/**
 * @brief config the SSI->CR0 based on datasheet: serial clock rate and others
 * @brief on reset, CLOCKRATE not set, clock phase 1st edge, clock polarity low, format SPI, DATA SIZE not set
 * 
 * @ref SSI->CR0: page 969
 * 
 * @param SSImodule SSI0 to SSI3
 * @param serialClkRate calcuated from the formula: BITRATE = SYSCLK / (CPSR * (1 + SCR)) (from 0 to 255)
 * @param dataSize 4bit to 16bit
 * @param otherConfig clock phase, clock polarity, format, data size
 */
inline void __configSSICR0(SSI0_Type *SSImodule, uint16_t serialClkRate, uint16_t dataSize, uint16_t otherConfig);

/**
 * @brief wait until the TX FIFO is not full
 * 
 * @param SSImodule SSI0 to SSI3
 */
inline void __waitTxSSInotFull(SSI0_Type *SSImodule);

/**
 * @brief wait until the SSI module is not busy
 * 
 * @param SSImodule SSI0 to SSI3
 */
inline void __waitTxSSIdone(SSI0_Type *SSImodule);

/**
 * @brief send data to the SSI module
 * 
 * @param SSImodule SSI0 to SSI3
 * @param data 4bit to 16bit based on the data size config
 */
inline void __txSSI(SSI0_Type *SSImodule, uint16_t data);

#endif /* SSI_H_ */
