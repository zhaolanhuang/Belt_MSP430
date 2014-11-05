/*
 * Interrupt.c
 *
 *  Created on: 2014-8-20
 *      Author: HP
 */
#include "Interrupt.h"
#include "Count.h"
#include "Time.h"
#pragma vector = TIMER0_A0_VECTOR
__interrupt void TA0_ISR(void)
{

	_DINT();
	TACCTL0 &= ~CCIE;//Stop Timmer
	isInTimmer = 1;
	TA0CTL &= ~TAIFG;
	TACCTL0 &= ~CCIFG;
	//Real_Time();

	P1_IODect();//IO扫描

	TACCTL0 |= CCIE;
	isInTimmer = 0;
	_EINT();
}
#pragma vector = TIMER1_A0_VECTOR
__interrupt void TA1_ISR(void)
{

	_DINT();
	Real_Time();
	TA1CTL &= ~TAIFG;
	TA1CCTL0 &= ~CCIFG;
	_EINT();
}
void P1_IODect()
{
	static unsigned char P13_Now=0;	//变量值出函数时需保留

	unsigned char P13_Past=0;

	P13_Past=P13_Now;

	//-----查询IO的输入寄存器-----

	if((P1IN&BIT3) == BIT3) 	P13_Now= 1;
		else		P13_Now = 0;
	//-----前一次高电平、后一次低电平，说明按键按下-----

#ifndef DTRIGGER
	if((P1IN&BIT4) == BIT4)
	{
		if((P13_Now==1)&&(P13_Past==0))
#ifndef TEST
			FlagPlus();
#else
			CountDrawLen++;
#endif
		if((P13_Now==0)&&(P13_Past==1))
#ifndef TEST
			FlagSub();
#else
			CountShrinkLen++;
#endif
	}
	else
	{
		if((P13_Now==1)&&(P13_Past==0))
#ifndef TEST
			FlagSub();
#else
			CountShrinkLen++;
#endif
		if((P13_Now==0)&&(P13_Past==1))
#ifndef TEST
			FlagPlus();
#else
			CountDrawLen++;
#endif
	}
#endif

#ifdef DTRIGGER
	if((P13_Now==1)&&(P13_Past==0) || (P13_Now==0)&&(P13_Past==1))
	{
		if((P1IN&BIT4) == BIT4)
#ifdef TEST
			CountShrinkLen++;
#else
			FlagSub();
#endif
		else
#ifdef TEST
			CountDrawLen++;
#else
			FlagPlus();
#endif

	}
#endif
}

