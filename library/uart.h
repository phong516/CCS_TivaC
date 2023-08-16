/*
 * interrupt.h
 *
 *  Created on: Jul 31, 2023
 *      Author: Phong
 */

#ifndef UART_H_
#define UART_H_

#include "TM4C123GH6PM.h"
#include "library/gpio.h"

#define TXFE    0x80UL    /* (1U << 7) */
#define RXFF    0x40UL    /* (1U << 6) */
#define TXFF    0x20UL     /* (1U << 5) */
#define RXFE    0x10UL     /* (1U << 4) */

/**
 * @brief Initialize UART module
 * 
 * @param uartModule 0 to 7
 * @param port      0 to 7
 * @param txPin     0 to 7
 * @param rxPin     0 to 7
 */
void enableUARTModule(uint8_t uartModule);


void uartTransmitByte(UART0_Type *uart, uint8_t byte);

/**
 * @brief Transmit a buffer
 * 
 * @param uart uart module, from UART0 to UART7
 * @param data buffer to transmit (contains many bytes)
 */
void uartTransmitBuffer(UART0_Type *uart, uint8_t *data, uint8_t dataSize);

/**
 * @brief Receive a byte and clear the holding register
 * 
 * @param uart uart module, from UART0 to UART7
 *
 * @return uint8_t received byte
 **/
uint32_t uartReceiveByte(UART0_Type *uart);

/**
 * @brief get the status of the uart interrupt, ris or mis
 * 
 * @param uart uart module, from UART0 to UART7
 * @param mis 0 for ris, 1 for mis
 * 
 * @return uint32_t status of the interrupt 
 */
uint32_t uartIntStatus(UART0_Type *uart, uint8_t mis);

/**
 * @brief clear the interrupt flag
 * 
 * @param uart uart module, from UART0 to UART7
 * @param intFlag the flag to clear
 * 
 * @return none
 */
void uartIntClear(UART0_Type *uart, uint32_t intFlag);

/**
 * @brief check if the RX uart is busy or not
 * 
 * @param uart uart module, from UART0 to UART7
 * @return uint8_t 0 if RX not busy, 1 if RX busy
 */
uint8_t isRxBusy(UART0_Type *uart);

/**
 * @brief check if the TX uart is busy or not
 * 
 * @param uart uart module, from UART0 to UART7
 * @return uint8_t 0 if not TX busy, 1 if TX busy
 */
uint8_t isTxBusy(UART0_Type *uart);

/**
 * @brief enable the RX uart interrupt
 * 
 * @param uart uart module, from UART0 to UART7
 * 
 * @return none
 */
void enableRxInt(UART0_Type *uart);


#endif /* UART_H_ */
