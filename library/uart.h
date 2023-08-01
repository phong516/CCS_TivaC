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

/**
 * @brief Initialize UART module
 * 
 * @param uartModule 0 to 7
 * @param port      0 to 7
 * @param txPin     0 to 7
 * @param rxPin     0 to 7
 */
void enableUARTModule(uint8_t uartModule, uint8_t port, uint8_t txPin, uint8_t rxPin);


#endif /* UART_H_ */
