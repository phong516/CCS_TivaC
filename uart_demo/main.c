/* Generates 10KHz and 50% duty cycle on PF2 pin of TM4C123 Tiva C Launchpad */
/* PWM1 module and PWM generator 3 of PWM1 module is used */
#include "TM4C123GH6PM.h"
#include "library/gpio.h"
#include "library/uart.h"

void uart_transmitter(uint8_t data);
void delay(uint32_t counter);

int main(void)
{
    enableUARTModule(0, 1, 1, 0);
    delay(1);
    while(1)
    {
        uart_transmitter('H');
        uart_transmitter('E');
        uart_transmitter('L');
        uart_transmitter('L');
        uart_transmitter('O');
        uart_transmitter('\n');
        delay(100);
    }
}

void uart_transmitter(uint8_t data){
    while((UART5->FR & 0x20) != 0); /* wait until Tx buffer not full */
    UART5->DR = data;
}

void delay(uint32_t counter){
    for (uint32_t i = 0; i < counter; i++);
}
