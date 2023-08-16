#include "library/uart.h"
#include "library/interrupt.h"

int main(void){
    enableUARTModule(2);
    configISER(UART2_IRQn, 3, 1);
    enableRxInt(UART2);
    const uint8_t data[] = "Enter: ";
    uartTransmitBuffer(UART2, data, 7);
    SYSCTL->RCGCGPIO |= (1U << 5);
    configGPIOInOut(GPIOF, 2, 1);
    while(1)
    {
    }
}

void UART2_IRQHandler(){
    uint32_t intFlags = uartIntStatus(UART2, 1);
    uartIntClear(UART2, intFlags);
    if (isRxBusy(UART2)){
      uartTransmitByte(UART2, uartReceiveByte(UART2));
        GPIOF->DATA ^= (1U << 2);
    }
}
