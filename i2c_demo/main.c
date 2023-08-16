#include "TM4C123GH6PM.h"
#include "library/gpio.h"
#include "library/i2c.h"
#include "library/uart.h"
#include "library/systick.h"


int main()
{
    enableUARTModule(0);
    SYSCTL->RCGCGPIO |= (1U << 5);
    configGPIOInOut(GPIOF, 2, 1);

  gpioClockState(3, 1);
  __i2cClockEnable(BIT3);
  alternatePinConfig(GPIOD, 0, 0x3); //scl
  alternatePinConfig(GPIOD, 1, 0x3); //sda
  __configI2CPinType(GPIOD, BIT1);      //open drain sda
  __enableI2cMaster(I2C3);
  __configI2cTimePeriod(I2C3, 0x07UL); //timePeriod = SYS_CLK / (20 * SCL_CLK) - 1
//  uint8_t data;
  uint8_t dataI2C[2];
  while (1)
    {
//         i2cTransmit(I2C3, 0x68, 0x0, "PHONG", 5);
        i2cReceive(I2C3, 0x68, 0x0, dataI2C, 2);
//        i2cReceive(I2C3, 0x68, 0x0, &data, 1);
//        data = (data >> 4) * 10 + (data & 0x0F);
//        uartTransmitByte(UART0, data);
        dataI2C[0] = (dataI2C[0] >> 4) * 10 + (dataI2C[0] & 0x0F);
        dataI2C[1] = (dataI2C[1] >> 4) * 10 + (dataI2C[1] & 0x0F);
//      uartTransmitByte(UART0, data);
        uartTransmitByte(UART0, dataI2C[1]);
        uartTransmitByte(UART0, dataI2C[0]);

        GPIOF->DATA ^= 4;
        SysTick_delayHz(1);

    }
}


