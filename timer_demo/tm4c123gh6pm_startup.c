//*****************************************************************************
//
// Startup code for use with TI's Code Composer Studio.
//
// Copyright (c) 2011-2014 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
//*****************************************************************************

#include <stdint.h>

//*****************************************************************************
//
// Forward declaration of the default fault handlers.
//
//*****************************************************************************
void ResetISR(void);
static void NmiSR(void);
static void FaultISR(void);
static void IntDefaultHandler(void);

//*****************************************************************************
//
// External declaration for the reset handler that is to be called when the
// processor is started
//
//*****************************************************************************
extern void _c_int00(void);

extern void SysTick_Handler(void);
extern void GPIOPortA_IRQHandler(void);
extern void GPIOPortB_IRQHandler(void);
extern void GPIOPortC_IRQHandler(void);
extern void GPIOPortD_IRQHandler(void);
extern void GPIOPortE_IRQHandler(void);
extern void UART0_IRQHandler(void);
extern void UART1_IRQHandler(void);
extern void SSI0_IRQHandler(void);
extern void I2C0_IRQHandler(void);
extern void PWMFault_IRQHandler(void);
extern void PWMGen0_IRQHandler(void);
extern void PWMGen1_IRQHandler(void);
extern void PWMGen2_IRQHandler(void);
extern void QEI0_IRQHandler(void);
extern void ADCSeq0_IRQHandler(void);
extern void ADCSeq1_IRQHandler(void);
extern void ADCSeq2_IRQHandler(void);
extern void ADCSeq3_IRQHandler(void);
extern void Watchdog_IRQHandler(void);
extern void Timer0A_IRQHandler(void);
extern void Timer0B_IRQHandler(void);
extern void Timer1A_IRQHandler(void);
extern void Timer1B_IRQHandler(void);
extern void Timer2A_IRQHandler(void);
extern void Timer2B_IRQHandler(void);
extern void Comp0_IRQHandler(void);
extern void Comp1_IRQHandler(void);
extern void Comp2_IRQHandler(void);
extern void SysCtrl_IRQHandler(void);
extern void FlashCtrl_IRQHandler(void);
extern void GPIOPortF_IRQHandler(void);
extern void GPIOPortG_IRQHandler(void);
extern void GPIOPortH_IRQHandler(void);
extern void UART2_IRQHandler(void);
extern void SSI1_IRQHandler(void);
extern void Timer3A_IRQHandler(void);
extern void Timer3B_IRQHandler(void);
extern void I2C1_IRQHandler(void);
extern void QEI1_IRQHandler(void);
extern void CAN0_IRQHandler(void);
extern void CAN1_IRQHandler(void);
extern void CAN2_IRQHandler(void);
extern void Hibernate_IRQHandler(void);
extern void USB0_IRQHandler(void);
extern void PWMGen3_IRQHandler(void);
extern void uDMAST_IRQHandler(void);
extern void uDMAError_IRQHandler(void);
extern void ADC1Seq0_IRQHandler(void);
extern void ADC1Seq1_IRQHandler(void);
extern void ADC1Seq2_IRQHandler(void);
extern void ADC1Seq3_IRQHandler(void);
extern void I2S0_IRQHandler(void);
extern void EBI0_IRQHandler(void);
extern void GPIOPortJ_IRQHandler(void);
extern void GPIOPortK_IRQHandler(void);
extern void GPIOPortL_IRQHandler(void);
extern void SSI2_IRQHandler(void);
extern void SSI3_IRQHandler(void);
extern void UART3_IRQHandler(void);
extern void UART4_IRQHandler(void);
extern void UART5_IRQHandler(void);
extern void UART6_IRQHandler(void);
extern void UART7_IRQHandler(void);
extern void I2C2_IRQHandler(void);
extern void I2C3_IRQHandler(void);
extern void Timer4A_IRQHandler(void);
extern void Timer4B_IRQHandler(void);
extern void Timer5A_IRQHandler(void);
extern void Timer5B_IRQHandler(void);
extern void WideTimer0A_IRQHandler(void);
extern void WideTimer0B_IRQHandler(void);
extern void WideTimer1A_IRQHandler(void);
extern void WideTimer1B_IRQHandler(void);
extern void WideTimer2A_IRQHandler(void);
extern void WideTimer2B_IRQHandler(void);
extern void WideTimer3A_IRQHandler(void);
extern void WideTimer3B_IRQHandler(void);
extern void WideTimer4A_IRQHandler(void);
extern void WideTimer4B_IRQHandler(void);
extern void WideTimer5A_IRQHandler(void);
extern void WideTimer5B_IRQHandler(void);
extern void FPU_IRQHandler(void);
extern void PECI0_IRQHandler(void);
extern void LPC0_IRQHandler(void);
extern void I2C4_IRQHandler(void);
extern void I2C5_IRQHandler(void);
extern void GPIOPortM_IRQHandler(void);
extern void GPIOPortN_IRQHandler(void);
extern void QEI2_IRQHandler(void);
extern void Fan0_IRQHandler(void);
extern void GPIOPortP0_IRQHandler(void);
extern void GPIOPortP1_IRQHandler(void);
extern void GPIOPortP2_IRQHandler(void);
extern void GPIOPortP3_IRQHandler(void);
extern void GPIOPortP4_IRQHandler(void);
extern void GPIOPortP5_IRQHandler(void);
extern void GPIOPortP6_IRQHandler(void);
extern void GPIOPortP7_IRQHandler(void);
extern void GPIOPortQ0_IRQHandler(void);
extern void GPIOPortQ1_IRQHandler(void);
extern void GPIOPortQ2_IRQHandler(void);
extern void GPIOPortQ3_IRQHandler(void);
extern void GPIOPortQ4_IRQHandler(void);
extern void GPIOPortQ5_IRQHandler(void);
extern void GPIOPortQ6_IRQHandler(void);
extern void GPIOPortQ7_IRQHandler(void);
extern void GPIOPortR_IRQHandler(void);
extern void GPIOPortS_IRQHandler(void);
extern void PWM1Gen0_IRQHandler(void);
extern void PWM1Gen1_IRQHandler(void);
extern void PWM1Gen2_IRQHandler(void);
extern void PWM1Gen3_IRQHandler(void);
extern void PWM1Fault_IRQHandler(void);
//*****************************************************************************
//
// Linker variable that marks the top of the stack.
//
//*****************************************************************************
extern uint32_t __STACK_TOP;

//*****************************************************************************
//
// External declarations for the interrupt handlers used by the application.
//
//*****************************************************************************
// To be added by user

//*****************************************************************************
//
// The vector table.  Note that the proper constructs must be placed on this to
// ensure that it ends up at physical address 0x0000.0000 or at the start of
// the program if located at a start address other than 0.
//
//*****************************************************************************
#pragma DATA_SECTION(g_pfnVectors, ".intvecs")
void (*const g_pfnVectors[])(void) =
{
    (void (*)(void))((uint32_t)&__STACK_TOP),
    // The initial stack pointer
        ResetISR,// The reset handler
        NmiSR,// The NMI handler
        FaultISR,// The hard fault handler
        IntDefaultHandler,// The MPU fault handler
        IntDefaultHandler,// The bus fault handler
        IntDefaultHandler,// The usage fault handler
        0,// Reserved
        0,// Reserved
        0,// Reserved
        0,// Reserved
        IntDefaultHandler,// SVCall handler
        IntDefaultHandler,// Debug monitor handler
        0,// Reserved
        IntDefaultHandler,// The PendSV handler
        SysTick_Handler,// The SysTick handler
        IntDefaultHandler,// GPIO Port A
        IntDefaultHandler,// GPIO Port B
        IntDefaultHandler,// GPIO Port C
        IntDefaultHandler,// GPIO Port D
        IntDefaultHandler,// GPIO Port E
        IntDefaultHandler,// UART0 Rx and Tx
        IntDefaultHandler,// UART1 Rx and Tx
        IntDefaultHandler,// SSI0 Rx and Tx
        IntDefaultHandler,// I2C0 Master and Slave
        IntDefaultHandler,// PWM Fault
        IntDefaultHandler,// PWM Generator 0
        IntDefaultHandler,// PWM Generator 1
        IntDefaultHandler,// PWM Generator 2
        IntDefaultHandler,// Quadrature Encoder 0
        IntDefaultHandler,// ADC Sequence 0
        IntDefaultHandler,// ADC Sequence 1
        IntDefaultHandler,// ADC Sequence 2
        IntDefaultHandler,// ADC Sequence 3
        IntDefaultHandler,// Watchdog timer
        Timer0A_IRQHandler,// Timer 0 subtimer A
        IntDefaultHandler,// Timer 0 subtimer B
        IntDefaultHandler,// Timer 1 subtimer A
        IntDefaultHandler,// Timer 1 subtimer B
        IntDefaultHandler,// Timer 2 subtimer A
        IntDefaultHandler,// Timer 2 subtimer B
        IntDefaultHandler,// Analog Comparator 0
        IntDefaultHandler,// Analog Comparator 1
        IntDefaultHandler,// Analog Comparator 2
        IntDefaultHandler,// System Control (PLL, OSC, BO)
        IntDefaultHandler,// FLASH Control
        IntDefaultHandler,// GPIO Port F
        IntDefaultHandler,// GPIO Port G
        IntDefaultHandler,// GPIO Port H
        IntDefaultHandler,// UART2 Rx and Tx
        IntDefaultHandler,// SSI1 Rx and Tx
        IntDefaultHandler,// Timer 3 subtimer A
        IntDefaultHandler,// Timer 3 subtimer B
        IntDefaultHandler,// I2C1 Master and Slave
        IntDefaultHandler,// Quadrature Encoder 1
        IntDefaultHandler,// CAN0
        IntDefaultHandler,// CAN1
        0,// Reserved
        0,// Reserved
        IntDefaultHandler,// Hibernate
        IntDefaultHandler,// USB0
        IntDefaultHandler,// PWM Generator 3
        IntDefaultHandler,// uDMA Software Transfer
        IntDefaultHandler,// uDMA Error
        IntDefaultHandler,// ADC1 Sequence 0
        IntDefaultHandler,// ADC1 Sequence 1
        IntDefaultHandler,// ADC1 Sequence 2
        IntDefaultHandler,// ADC1 Sequence 3
        0,// Reserved
        0,// Reserved
        IntDefaultHandler,// GPIO Port J
        IntDefaultHandler,// GPIO Port K
        IntDefaultHandler,// GPIO Port L
        IntDefaultHandler,// SSI2 Rx and Tx
        IntDefaultHandler,// SSI3 Rx and Tx
        IntDefaultHandler,// UART3 Rx and Tx
        IntDefaultHandler,// UART4 Rx and Tx
        IntDefaultHandler,// UART5 Rx and Tx
        IntDefaultHandler,// UART6 Rx and Tx
        IntDefaultHandler,// UART7 Rx and Tx
        0,// Reserved
        0,// Reserved
        0,// Reserved
        0,// Reserved
        IntDefaultHandler,// I2C2 Master and Slave
        IntDefaultHandler,// I2C3 Master and Slave
        IntDefaultHandler,// Timer 4 subtimer A
        IntDefaultHandler,// Timer 4 subtimer B
        0,// Reserved
        0,// Reserved
        0,// Reserved
        0,// Reserved
        0,// Reserved
        0,// Reserved
        0,// Reserved
        0,// Reserved
        0,// Reserved
        0,// Reserved
        0,// Reserved
        0,// Reserved
        0,// Reserved
        0,// Reserved
        0,// Reserved
        0,// Reserved
        0,// Reserved
        0,// Reserved
        0,// Reserved
        0,// Reserved
        IntDefaultHandler,// Timer 5 subtimer A
        IntDefaultHandler,// Timer 5 subtimer B
        IntDefaultHandler,// Wide Timer 0 subtimer A
        IntDefaultHandler,// Wide Timer 0 subtimer B
        IntDefaultHandler,// Wide Timer 1 subtimer A
        IntDefaultHandler,// Wide Timer 1 subtimer B
        IntDefaultHandler,// Wide Timer 2 subtimer A
        IntDefaultHandler,// Wide Timer 2 subtimer B
        IntDefaultHandler,// Wide Timer 3 subtimer A
        IntDefaultHandler,// Wide Timer 3 subtimer B
        IntDefaultHandler,// Wide Timer 4 subtimer A
        IntDefaultHandler,// Wide Timer 4 subtimer B
        IntDefaultHandler,// Wide Timer 5 subtimer A
        IntDefaultHandler,// Wide Timer 5 subtimer B
        IntDefaultHandler,// FPU
        0,// Reserved
        0,// Reserved
        IntDefaultHandler,// I2C4 Master and Slave
        IntDefaultHandler,// I2C5 Master and Slave
        IntDefaultHandler,// GPIO Port M
        IntDefaultHandler,// GPIO Port N
        IntDefaultHandler,// Quadrature Encoder 2
        0,// Reserved
        0,// Reserved
        IntDefaultHandler,// GPIO Port P (Summary or P0)
        IntDefaultHandler,// GPIO Port P1
        IntDefaultHandler,// GPIO Port P2
        IntDefaultHandler,// GPIO Port P3
        IntDefaultHandler,// GPIO Port P4
        IntDefaultHandler,// GPIO Port P5
        IntDefaultHandler,// GPIO Port P6
        IntDefaultHandler,// GPIO Port P7
        IntDefaultHandler,// GPIO Port Q (Summary or Q0)
        IntDefaultHandler,// GPIO Port Q1
        IntDefaultHandler,// GPIO Port Q2
        IntDefaultHandler,// GPIO Port Q3
        IntDefaultHandler,// GPIO Port Q4
        IntDefaultHandler,// GPIO Port Q5
        IntDefaultHandler,// GPIO Port Q6
        IntDefaultHandler,// GPIO Port Q7
        IntDefaultHandler,// GPIO Port R
        IntDefaultHandler,// GPIO Port S
        IntDefaultHandler,// PWM 1 Generator 0
        IntDefaultHandler,// PWM 1 Generator 1
        IntDefaultHandler,// PWM 1 Generator 2
        IntDefaultHandler,// PWM 1 Generator 3
        IntDefaultHandler// PWM 1 Fault
};

//*****************************************************************************
//
// This is the code that gets called when the processor first starts execution
// following a reset event.  Only the absolutely necessary set is performed,
// after which the application supplied entry() routine is called.  Any fancy
// actions (such as making decisions based on the reset cause register, and
// resetting the bits in that register) are left solely in the hands of the
// application.
//
//*****************************************************************************
void ResetISR(void)
{
    //
    // Jump to the CCS C initialization routine.  This will enable the
    // floating-point unit as well, so that does not need to be done here.
    //
    __asm("    .global _c_int00\n"
            "    b.w     _c_int00");
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a NMI.  This
// simply enters an infinite loop, preserving the system state for examination
// by a debugger.
//
//*****************************************************************************
static void NmiSR(void)
{
    //
    // Enter an infinite loop.
    //
    while (1)
    {
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a fault
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
static void FaultISR(void)
{
    //
    // Enter an infinite loop.
    //
    while (1)
    {
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives an unexpected
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
static void IntDefaultHandler(void)
{
    //
    // Go into an infinite loop.
    //
    while (1)
    {
    }
}
