/*
 * Time.c
 *
 *  Created on: 2014-8-23
 *      Author: HP
 */
#include "Time.h"

unsigned int BreathTime[ARRAYLEN]={0};
void Real_Time()
{
	Timmer_Cycle++;
	if (Timmer_Cycle == 10)
	{
		Second++;

		Timmer_Cycle = 0;

	}

}
void CalcBreathTime()
{

	static unsigned char isFirstrespiration = 1;
	static char BreathTimeIndex = 0;
	IE2 &= ~(UCA0RXIE);
	//Begining of first respiration period
	if(isFirstrespiration == 1) 
	{
		BreathTime[BreathTimeIndex] = Second * 10 + Timmer_Cycle;
		isFirstrespiration = 0;
	}
	//End of respiration period, begining of the next respiration period
	//calculate respiration duration, save and send measurement data
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
