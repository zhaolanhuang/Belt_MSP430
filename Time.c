/*
 * Time.c
 *
 *  Created on: 2014-8-23
 *      Author: HP
 */
#include "Time.h"

unsigned int BreathTime[ARRAYLEN]={0};

/**
 * Soft RTC
 * Called every 100 ms.
 */
void Real_Time()
{
	Timmer_Cycle++;
	if (Timmer_Cycle == 10)
	{
		Second++;

		Timmer_Cycle = 0;

	}

}

/**
 * Called by count.c/ResultCalc at every beginning of inhalation
 * Calculate the duration of each respiratory period, then save and send the measurement data
 */
void CalcBreathTime()
{

	static unsigned char isFirstrespiration = 1;
	static char BreathTimeIndex = 0;
	IE2 &= ~(UCA0RXIE);
	//Begining of the first respiratory period
	if(isFirstrespiration == 1) 
	{
		BreathTime[BreathTimeIndex] = Second * 10 + Timmer_Cycle;
		isFirstrespiration = 0;
	}
	//End of a respiratory period, begining of the next respiratory period
	else
	{
		BreathTime[BreathTimeIndex] = (Second * 10 + Timmer_Cycle) - BreathTime[BreathTimeIndex];
		SendData(BreathTimeIndex);

		#ifdef SAVE
			Push(&BreathTime[BreathTimeIndex]);
			Push(&arrayDrawResultLen[BreathTimeIndex]);
			Push(&arrayShrinkResultLen[BreathTimeIndex]);
		#endif

		BreathTimeIndex++;
		if (BreathTimeIndex >ARRAYLEN-1) BreathTimeIndex = 0;
		BreathTime[BreathTimeIndex] = Second *10+ Timmer_Cycle;



	}


	IE2 |= (UCA0RXIE);
}
