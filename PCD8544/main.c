#include <msp430.h> 
#include "types.h"
#include "ports.h"
#include "uscia0_spi.h"
#include "pcd8544.h"

void init_ports();

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    init_ports();
    init_spi();
    init_lcd();
	
    while(1)
    {

    }

	return 0;
}

void init_ports(void)
{
    P1in.bits = &P1IN;
    P1out.bits = &P1OUT;

    P2in.bits = &P2IN;
    P2out.bits = &P2OUT;

    P3in.bits = &P3IN;
    P3out.bits = &P3OUT;

    P3DIR   |=  BIT0 + BIT1;        // P3.0 and 3.1 Outputs
    P2DIR   |=  BIT0;               // P2.0 Output
}
