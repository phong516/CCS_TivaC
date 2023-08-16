/*
 * pwm.c
 *
 *  Created on: Aug 12, 2023
 *      Author: Phong
 */
#include "library/i2c.h"

inline void __i2cClockEnable(uint32_t i2cModule){
    SYSCTL->RCGCI2C |= i2cModule;
}

inline void __configI2CPinType(GPIOA_Type *port, uint8_t pin){
    port->ODR |= pin;
}

inline void __enableI2cMaster(I2C0_Type *i2c){
    i2c->MCR |= I2C_MASTER_FUNCTION;
}

inline void __configI2cTimePeriod(I2C0_Type *i2cModule, uint32_t timePeriod){
    i2cModule->MTPR = timePeriod;
}

uint8_t getI2cError(I2C0_Type *i2cModule){
    return (i2cModule->MCS & I2C_ERROR_BITS);
}

inline void __i2cWaitTilIdle(I2C0_Type *i2cModule){
    while (i2cModule->MCS & I2C_BUSY_BIT);
}

inline void __i2cWaitTilBusIdle(I2C0_Type *i2cModule){
    while(i2cModule->MCS & I2C_BUS_BUSY_BIT);
}

uint8_t i2cTransmit(I2C0_Type *i2cModule, uint8_t slaveAddress, uint8_t slaveMemoryAddress, uint8_t *data, uint8_t byteCount){
    uint8_t error;
    i2cModule->MSA = (slaveAddress << 1);
    i2cModule->MDR = slaveMemoryAddress;
    i2cModule->MCS = I2C_START_BIT | I2C_RUN_BIT;

    __i2cWaitTilIdle(i2cModule);
    error = getI2cError(i2cModule);
    if (error) return error;

    while (byteCount-- > 1){
        i2cModule->MDR = *data++;
        i2cModule->MCS = I2C_RUN_BIT;
        __i2cWaitTilIdle(I2C3);
        error = getI2cError(i2cModule);
        if (error) return error;
    }
    i2cModule->MDR = *data;
    i2cModule->MCS = I2C_RUN_BIT | I2C_STOP_BIT;
    __i2cWaitTilIdle(i2cModule);
    error = getI2cError(i2cModule);
    __i2cWaitTilBusIdle(i2cModule);
    if (error) return error;
    return 0;
}

uint8_t i2cReceive(I2C0_Type *i2cModule, uint8_t slaveAddress, uint8_t slaveMemoryAddress, uint8_t *data, uint8_t byteCount){
    uint8_t error;
    i2cModule->MSA = (slaveAddress << 1);
    i2cModule->MDR = slaveMemoryAddress;
    i2cModule->MCS = I2C_START_BIT | I2C_RUN_BIT;
    __i2cWaitTilIdle(i2cModule);
    error = getI2cError(i2cModule);
    if (error) return error;

    i2cModule->MSA |= I2C_MASTER_RECEIVE_BIT;
    if (byteCount == 1){
        i2cModule->MCS = I2C_START_BIT | I2C_STOP_BIT | I2C_RUN_BIT;
    }
    else {
        i2cModule->MCS = I2C_START_BIT | I2C_ACK_BIT | I2C_RUN_BIT;
    }


    __i2cWaitTilIdle(i2cModule);
    error = getI2cError(i2cModule);
    if (error) return error;

    *data++ = i2cModule->MDR;

    while (--byteCount){
        i2cModule->MCS = I2C_RUN_BIT | I2C_ACK_BIT;

        __i2cWaitTilIdle(i2cModule);
        error = getI2cError(i2cModule);
        if (error) return error;

        *data++ = i2cModule->MDR;
    }

    i2cModule->MCS = I2C_RUN_BIT | I2C_STOP_BIT;

    __i2cWaitTilIdle(i2cModule);
    error = getI2cError(i2cModule);
    if (error) return error;

    __i2cWaitTilBusIdle(i2cModule);
    return 0;
}
