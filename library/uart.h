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

#define TXFF (1U << 5)

/**
 * @brief Initialize UART module
 * 
 * @param uartModule 0 to 7
 * @param port      0 to 7
 * @param txPin     0 to 7
 * @param rxPin     0 to 7
 */
void enableUARTModule(uint8_t uartModule, uint8_t port, uint8_t rxPin, uint8_t txPin);

/**
 * @brief Transmit a byte
 * 
 * @param uart uart module, from UART0 to UART7
 * @param data byte to transmit (8-bit data)
 */
void uartTransmitByte(UART0_Type *uart, uint8_t data);

/**
 * @brief Transmit a buffer
 * 
 * @param uart uart module, from UART0 to UART7
 * @param data buffer to transmit (contains many bytes)
 */
void uartTransmitBuffer(UART0_Type *uart, uint8_t *data);

#endif /* UART_H_ */
