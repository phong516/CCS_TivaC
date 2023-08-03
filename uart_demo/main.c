#include "library/uart.h"
#include "library/interrupt.h"

int main(void){
    enableUARTModule(0);
    configISER(UART0_IRQn, 3, 1);
    enableRxInt(UART0);
    const uint8_t data[] = "Enter";
    uartTransmitBuffer(UART0, data, 5);

    while(1)
    {
    }
}

void UART0_IRQHandler(){
    uint32_t intFlags = uartIntStatus(UART0, 1);
    uartIntClear(UART0, intFlags);
    while (isRxBusy(UART0)){
        uartTransmitByte(UART0, uartReceiveByte(UART0));
    }
}
