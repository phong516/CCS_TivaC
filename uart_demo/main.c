#include "TM4C123GH6PM.h"
#include "library/uart.h"
int main(){
	enableUARTModule(7, 0, 1, 0);
    uint8_t data[] = "Hello world\n";
    uartTransmitBuffer(UART0, data);
	while (1);
	return 0;
}

void Q_onAssert(char const *module, int loc) {
    /* TBD: damage control */
    (void)module; /* avoid the "unused parameter" compiler warning */
    (void)loc;    /* avoid the "unused parameter" compiler warning */
    NVIC_SystemReset();
}