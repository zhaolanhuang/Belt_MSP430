/*
 * ======== Standard MSP430 includes ========
 */


#include <msp430.h>
#include "Interrupt.h"
#include "Count.h"
#include "Init.h"
#include "Global.h"
#include "Time.h"
#include "Bluetooth.h"
//unsigned char  buffer[7200];
/*
 *  ======== main ========
 */
int main(int argc, char *argv[])

{

	WDTCTL = WDTPW + WDTHOLD;//Halt the DOG
	P1DIR |= BIT0;
	P1OUT ^= BIT0;
	AT45DB081_init();

	FlushFlash();
	ReadPointer();
	USCI_A0_init();
	ALL_Init();

    _bis_SR_register(LPM1_bits + GIE);

    return (0);
}

