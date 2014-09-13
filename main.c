/*
 * ======== Standard MSP430 includes ========
 */


#include <msp430.h>
#include "Global.h"

/*
 *  ======== main ========
 */
int main(int argc, char *argv[])

{

	WDTCTL = WDTPW + WDTHOLD;//Halt the DOG

	ALL_Init();

    _bis_SR_register(LPM1_bits + GIE);

    return (0);
}

