
#include "TM4C123GH6PM.h"
#include "library/uart.h"

void UARTSend(const uint8_t *pui8Buffer, uint32_t ui32Count)
{

    while(ui32Count--)
    {

        while ((UART0->FR & 0x20)){}
            UART0->DR = *pui8Buffer++;
    }
}

int
main(void)
{
    enableUARTModule(0);
    const uint8_t data[] = "Enter";
    UARTSend(data , 5);

    while(1)
    {
    }
}
