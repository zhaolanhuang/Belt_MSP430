/*
 * Init.c
 *
 *  Created on: 2014-8-21
 *      Author: HP
 */
#include "Init.h"


void ALL_Init()
{
	BCSplus_init();//Clock System Init
	GPIO_Init();//I/O Port Init
#ifdef SAVE
	AT45DB081_init();//Flash Moudle Init
	FlushFlash();
	ReadPointer(); //Read

#endif
	USCI_A0_init();
	TA0_Init();//Timmer Init
}
void GPIO_Init() //SET P1.3(U1) P1.4(U2) as D_TRigger and CHA input.
{
	P1DIR &= ~(BIT3+BIT4); //P1.0 as INPUT
	P1REN |= BIT3+BIT4;	//Enable Resistor
	P1OUT &= ~(BIT3+BIT4);	//Resistor PULL DOWN


}

void TA0_Init()
{
	TA0CTL = 0;
	TA1CTL = 0;
	TA1CCR0 = 12500;//100ms/pulze
	TA1CCTL0 |= CCIE;
	TACCTL0 |= CCIE;
	TACCR0 = TIMMER_PERIOD;//1750,1000
	TA0CTL |= TASSEL_2 + ID_0 + MC_1;
	TA1CTL |= TASSEL_2 + ID_3 + MC_1;

}


void BCSplus_init(void)
{
    /*
     * Basic Clock System Control 2
     *
     * SELM_0 -- DCOCLK
     * DIVM_0 -- Divide by 1
     * ~SELS -- DCOCLK
     * DIVS_0 -- Divide by 1
     * ~DCOR -- DCO uses internal resistor
     *
     * Note: ~<BIT> indicates that <BIT> has value zero
     */
    BCSCTL2 = SELM_0 + DIVM_0 + DIVS_0;

    if (CALBC1_1MHZ != 0xFF) {
        /* Follow recommended flow. First, clear all DCOx and MODx bits. Then
         * apply new RSELx values. Finally, apply new DCOx and MODx bit values.
         */
        DCOCTL = 0x00;
        BCSCTL1 = CALBC1_1MHZ;      /* Set DCO to 1MHz */
        DCOCTL = CALDCO_1MHZ;
    }

    /*
     * Basic Clock System Control 1
     *
     * XT2OFF -- Disable XT2CLK
     * ~XTS -- Low Frequency
     * DIVA_0 -- Divide by 1
     *
     * Note: ~XTS indicates that XTS has value zero
     */
    BCSCTL1 |= XT2OFF + DIVA_0;

    /*
     * Basic Clock System Control 3
     *
     * XT2S_0 -- 0.4 - 1 MHz
     * LFXT1S_2 -- If XTS = 0, XT1 = VLOCLK ; If XTS = 1, XT1 = 3 - 16-MHz crystal or resonator
     * XCAP_1 -- ~6 pF
     */
    BCSCTL3 = XT2S_0 + LFXT1S_2 + XCAP_1;
}


