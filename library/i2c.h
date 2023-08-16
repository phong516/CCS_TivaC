/*
 * i2c.h
 *
 *  Created on: Aug 12, 2023
 *      Author: Phong
 */

#ifndef I2C_H_
#define I2C_H_

#include "TM4C123GH6PM.h"
#include "library/gpio.h"
/*  GPIOAFSEL: 671
    GPIOPCTL: 688
    GPIOODR: 649 
    I2CMCS: 1020*/
#define BIT0 0x1UL //1 << 0
#define BIT1 0x2UL //1 << 1
#define BIT2 0x4UL //1 << 2
#define BIT3 0x8UL //1 << 3
#define BIT4 0x10UL //1 << 4
#define BIT5 0x20UL //1 << 5
#define BIT6 0x40UL //1 << 6
#define BIT7 0x80UL //1 << 7

#define I2C_MASTER_FUNCTION     0x10UL //1 << 4
#define I2C_BUSY_BIT            0x1UL //1 << 0
#define I2C_ERROR_BITS          0xEUL //0b1110
#define I2C_BUS_BUSY_BIT        0X40UL //1 << 6

#define I2C_RUN_BIT             0x1UL //1 << 0
#define I2C_START_BIT           0x2UL //1 << 1
#define I2C_STOP_BIT            0x4UL //1 << 2
#define I2C_ACK_BIT             0x8UL //1 << 3
#define I2C_HS_BIT              0x10UL //1 << 4

#define I2C_MASTER_RECEIVE_BIT  0x1UL // 1 << 0

/**
 * @brief enable run clock for I2C
 * @ref RCGCI2C: 348
 * 
 * @param i2cModule 
 */
inline void __i2cClockEnable(uint32_t i2cModule);

/**
 * @brief config I2C SDA pin to open drain mode
 * @ref GPIOODR: 676
 * 
 * @param port PORTA to PORTF
 * @param pin 0 to 7
 */
inline void __configI2CPinType(GPIOA_Type *port, uint8_t pin);

/**
 * @brief enable a I2C module to be master
 * @ref: I2CMCR: 1031
 * @param i2c I2C0 to I2C3
 */
inline void __enableI2cMaster(I2C0_Type *i2c);

/**
 * @brief config I2C time period
 * @ref I2CMTPR: 1026
 * 
 * @param i2cModule I2C0 to I2C3
 * @param timePeriod (1 + TIME_PERIOD ) = SYS_CLK /(2* ( SCL_LP + SCL_HP ) * I2C_CLK_Freq)
 */
inline void __configI2cTimePeriod(I2C0_Type *i2cModule, uint32_t timePeriod);

/**
 * @brief get I2C error when transmit or receive data
 * @brief address error, data error, arbitration lost
 * 
 * @ref I2CMCS: 1020
 * 
 * @param i2cModule I2C0 to I2C3
 * @return uint8_t 
 */
uint8_t getI2cError(I2C0_Type *i2cModule);

/**
 * @brief wait until I2C module is idle
 * @ref I2CMCS: 1020
 * 
 * @param i2cModule 
 * @return uint8_t 
 */

inline void __i2cWaitTilIdle(I2C0_Type *i2cModule);

/**
 * @brief wait until I2C bus is idle
 * 
 * @param i2cModule I2C0 to I2C3
 */
inline void __i2cWaitTilBusIdle(I2C0_Type *i2cModule);

/**
 * @brief write data to i2c slave
 * @ref I2CMSA: 1019, set the slave address
 * @ref I2CMDR: 1025, set the data to be sent
 * 
 * @param i2cModule I2C0 to I2C3
 * @param slaveAddress address of the slave
 * @param slaveMemoryAddress memory address of the slave
 * @param data data need to be sent
 * @param byteCount number of bytes need to be sent
 * @return uint8_t error code
 */
uint8_t i2cTransmit(I2C0_Type *i2cModule, uint8_t slaveAddress, uint8_t slaveMemoryAddress, uint8_t *data, uint8_t byteCount);

uint8_t i2cReceive(I2C0_Type *i2cModule, uint8_t slaveAddress, uint8_t slaveMemoryAddress, uint8_t *data, uint8_t byteCount);

#endif /* I2C_H_ */
