#include "library/uart.h"

void enableUARTModule(uint8_t uartModule){
    uint8_t port, txPin, rxPin;
    SYSCTL->RCGCUART |= (1U << uartModule);
    GPIOA_Type *gpioPort;
    UART0_Type *uart;
    switch(uartModule){
        case 0: 
            uart = UART0;
            gpioPort = GPIOA;
            port = 0;
            rxPin = 0;
            txPin = 1;
            break;
        case 1:
            uart = UART1;
            gpioPort = GPIOB;
            port = 1;
            rxPin = 0;
            txPin = 1;
            break;
        case 2:
            uart = UART2;
            gpioPort = GPIOD;
            port = 3;
            rxPin = 6;
            txPin = 7;
            break;
        case 3:
            uart = UART3;
            gpioPort = GPIOC;
            port = 2;
            rxPin = 6;
            txPin = 7;
            break;
        case 4:
            uart = UART4;
            gpioPort = GPIOC;
            port = 2;
            rxPin = 4;
            txPin = 5;
            break;
        case 5:
            uart = UART5;
            gpioPort = GPIOE;
            port = 4;
            rxPin = 4;
            txPin = 5;
            break;
        case 6:
            uart = UART6;
            gpioPort = GPIOD;
            port = 3;
            rxPin = 4;
            txPin = 5;
            break;
        case 7:
            uart = UART7;
            gpioPort = GPIOE;
            port = 4;
            rxPin = 0;
            txPin = 1;
            break;
        default:
            return;
    }
    SYSCTL->RCGCGPIO |= (1U << port);
    alternatePinConfig(gpioPort, rxPin, 0x1);
    alternatePinConfig(gpioPort, txPin, 0x1);
    uart->CTL &= ~(1U << 0);
    uart->CTL |= (1U << 8);
    uart->CTL &= ~(1U << 9);
    uart->IBRD = 104U;   // 16MHz / (16 * 9600) = 104.1666666666667
    uart->FBRD = 11U;   // 0.1666666666667 * 64 + 0.5 = 11.1666666666667
    uart->LCRH |= (0x3 << 5);   // 8-bit data
    uart->CC &= ~(0b1111U);
    uart->CTL |= (1U << 0);
}

void uartTransmitByte(UART0_Type *uart, uint8_t *data){
    while (uart->FR & TXFF);
    uart->DR = *data;
  }

void uartTransmitBuffer(UART0_Type *uart, uint8_t *data, uint8_t dataSize){
    while(dataSize--){
        uartTransmitByte(uart, data++);
    }
}

