/*
 * Interrupt.c
 *
 *  Created on: 2014-8-20
 *      Author: HP
 */
#include "Interrupt.h"
#include "Count.h"
#include "Time.h"

/**
 * TA0 ISR for motion detection of optical scale
 */
#pragma vector = TIMER0_A0_VECTOR
__interrupt void TA0_ISR(void)
{

	_DINT();
	TACCTL0 &= ~CCIE;//Stop Timer
	TA1CCTL0 &= ~CCIE;
	isInTimmer = 1;
	TA0CTL &= ~TAIFG;
	TACCTL0 &= ~CCIFG;

	//IO Scan
	P1_IODect();
	_DINT();
	TACCTL0 |= CCIE;
	TA1CCTL0 |= CCIE;
	isInTimmer = 0;
	_EINT();
}

/**
 * TA1 ISR for Soft RTC 
 */
#pragma vector = TIMER1_A0_VECTOR
__interrupt void TA1_ISR(void)
{

	_DINT();
	TACCTL0 &= ~CCIE;//Stop Timer
	TA1CCTL0 &= ~CCIE;
	isInTimmer = 1;
	TA0CTL &= ~TAIFG;
	TACCTL0 &= ~CCIFG;
	Real_Time();
	_DINT();
	TACCTL0 |= CCIE;
	TA1CCTL0 |= CCIE;
	isInTimmer = 0;
	_EINT();
}

/**
 * Edge detection of encoder output
 * 
 */
void P1_IODect()
{
	static unsigned char P13_Now=0;	//变量值出函数时需保留

	unsigned char P13_Past=0;

	P13_Past=P13_Now;

	
	// Edge detection of P1.3 (Output channel of encoder)
	if((P1IN&BIT3) == BIT3) 	P13_Now= 1;
		else		P13_Now = 0;
	
// deprecated: we used D-trigger for detecting the moving direction
#ifndef DTRIGGER

#endif

#ifdef DTRIGGER
	// Edge from encoder output detected, means that the scale is moving.
	// Also means that the belt is stretching (inhaling) or shrinking (exhaling)
	// Each detected edge stands for scale motion of 0.07 mm
	if((P13_Now==1)&&(P13_Past==0) || (P13_Now==0)&&(P13_Past==1))
	{
		//D-Trigger output is high-level, the belt is shrinking
		if((P1IN&BIT4) == BIT4)
		#ifdef TEST
					CountShrinkLen++;
		#else
					FlagSub();
		#endif
		//D-Trigger output is low-level, the belt is stretching
		else
		#ifdef TEST
					CountDrawLen++;
		#else
					FlagPlus();
		#endif

	}
#endif
}

