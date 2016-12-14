#include <msp430.h>
#include "uscia0_spi.h"
/*
 * uscia0_spi.c
 *
 *  Created on: 2016. dec. 14.
 *      Author: lmajer
 */


void init_spi()
{
    P1SEL       |=  BIT1 + BIT2 + BIT4;                     //
    P1SEL2      |=  BIT1 + BIT2 + BIT4;                     //


    UCA0CTL1    =   UCSWRST;                                // Held SPI in Reset

    UCA0CTL0    |=  UCCKPL      +                           // Clock Polarity in Inactive state is High
                    UCMSB       +                           // MSB First
                    //UC7BIT    +                           // 7 Bit Character Length
                    UCMST       +                           // Master Mode
                    UCMODE_0    +                           // 3 Pin SPI
                    UCSYNC;                                 // Synchronous mode

    UCA0CTL1    |=   UCSSEL_2;                              // BRCLK Source is SMCLK

    UCA0BR0     |=  0x02;                                    // /2
    UCA0BR1     |=  0;                                      //
    UCA0MCTL     =   0;                                      // No Modulation

    UCA0CTL1    &=  ~UCSWRST;                               // Enable SPI

    IE2         |=  UCA0RXIE;                               // RX interrupt enable
}

unsigned char transferSpi(unsigned char data)
{
    while (!(IFG2 & UCA0TXIFG));                            // USCI_A0 TX buffer ready?
    UCA0TXBUF   =   data;                                   // Load data and start transfer
    __bis_SR_register(CPUOFF + GIE);                        // CPU OFF and waiting for interrupt
    return UCA0RXBUF;                                       // Return with RX data
}

// USCIA0RX interrupt

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCIA0RX_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCIAB0RX_VECTOR))) USCIA0RX_ISR (void)
#else
#error Compiler not supported!
#endif
{
    __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR). Interrupt wakes up MCU
}
