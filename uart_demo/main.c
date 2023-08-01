#include "TM4C123GH6PM.h"
#include "library/uart.h"
int main(){
	enableUARTModule(0, 0, 1, 0);
	return 0;
}

void Q_onAssert(char const *module, int loc) {
    /* TBD: damage control */
    (void)module; /* avoid the "unused parameter" compiler warning */
    (void)loc;    /* avoid the "unused parameter" compiler warning */
    NVIC_SystemReset();
}