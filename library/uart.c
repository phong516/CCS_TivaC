#include "library/uart.h"

void enableUARTModule(uint8_t uartModule, uint8_t port, uint8_t txPin, uint8_t rxPin){
    SYSCTL->RCGCUART |= (1U << uartModule);
    SYSCTL->RCGCGPIO |= (1U << port);
    GPIOA_Type *gpioPort;
    UART0_Type *uart;
    switch(port){
        case 0: 
            gpioPort = GPIOA;
            break;
        case 1:
            gpioPort = GPIOB;
            break;
        case 2:
            gpioPort = GPIOC;
            break;
        case 3:
            gpioPort = GPIOD;
            break;
        case 4:
            gpioPort = GPIOE;
            break;
        case 5:
            gpioPort = GPIOF;
            break;
        default:
            return;
    }

    switch(uartModule){
        case 0: 
            uart = UART0;
            break;
        case 1:
            uart = UART1;
            break;
        case 2:
            uart = UART2;
            break;
        case 3:
            uart = UART3;
            break;
        case 4:
            uart = UART4;
            break;
        case 5:
            uart = UART5;
            break;
        case 6:
            uart = UART6;
            break;
        case 7:
            uart = UART7;
            break;
        default:
            return;
    }
    
    alternatePinConfig(gpioPort, txPin, 0x1);
    alternatePinConfig(gpioPort, rxPin, 0x1);
    uart->CTL &= ~(1U << 0);
    uart->IBRD = 10U;
    uart->FBRD = 54U;
    uart->LCRH = 0x60;
    uart->CC &= ~(0b1111U);
    uart->CTL |= (1U << 0);
}

void uartTransmitByte(UART0_Type *uart, uint8_t data){
    while (uart->FR & TXFF != 0);
    uart->DR = data;
}

void uartTransmitBuffer(UART0_Type *uart, uint8_t *data){
    while(*data != '\0'){
        uartTransmitByte(uart, *data);
        data++;
    }
}

