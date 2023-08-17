#include "TM4C123GH6PM.h"
#include "library/gpio.h"
#include "library/i2c.h"
#include "library/uart.h"
#include "library/systick.h"
#include "library/interrupt.h"

int main()
{
    enableUARTModule(0);
    SYSCTL->RCGCGPIO |= (1U << 5);
    configGPIOInOut(GPIOF, 2, 1);

  gpioClockState(3, 1);
  __i2cClockEnable(BIT3);
  alternatePinConfig(GPIOD, 0, I2C_PINMUX); //scl
  alternatePinConfig( GPIOD, 1, I2C_PINMUX); //sda
  __configI2CPinType(I2C3_SDA);      //open drain sda
  __enableI2cMaster(I2C3);
  __configI2cTimePeriod(I2C3, 0x07UL); //timePeriod = SYS_CLK / (20 * SCL_CLK) - 1
//  uint8_t data;
  uint8_t dataI2C[2];

  i2cMasterIntEnable(I2C3, I2C_MASTER_INT_BIT);
  configISER(I2C3_IRQn, 3, 1);
  while (1)
    {
        i2cReceive(I2C3, 0x68, 0x0, dataI2C, 2);
        /* BCD to decimal number */
        dataI2C[0] = (dataI2C[0] >> 4) * 10 + (dataI2C[0] & 0x0F);
        dataI2C[1] = (dataI2C[1] >> 4) * 10 + (dataI2C[1] & 0x0F);
        uartTransmitByte(UART0, dataI2C[1]);
        uartTransmitByte(UART0, dataI2C[0]);
//        GPIOF->DATA ^= 4;
        SysTick_delayHz(1);

    }
}

void I2C3_IRQHandler(void){
    if (getI2cError(I2C3)){
        return;
    }
    if ((I2C3->MMIS & I2C_MASTER_INT_BIT) && !(I2C3->MCS & I2C_BUS_BUSY_BIT)){
        GPIOF->DATA ^= 4;

    }
    i2cMasterIntClear(I2C3, i2cMasterIntStatus(I2C3, 1));
}


