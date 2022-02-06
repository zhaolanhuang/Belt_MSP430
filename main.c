/*
 * ======== Standard MSP430 includes ========
 */


#include <msp430.h>
#include "Global.h"

/*
 *  ======== main entry point ========
 */
int main(int argc, char *argv[])

{
	//Disable the Watch DOG
	WDTCTL = WDTPW + WDTHOLD;

	ALL_Init();

	//Enable Low Power Mode 1
    _bis_SR_register(LPM1_bits + GIE);

    return (0);
}

