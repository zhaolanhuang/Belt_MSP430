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
	if (Timmer_Cycle == 1000000/TIMMER_PERIOD)
	{
		Second++;
		Timmer_Cycle = 0;

	}

}
void CalcBreathTime()
{

	static unsigned char TimeFlag = 0;
	static unsigned char BreathTimeIndex = 0;
	IE2 &= ~(UCA0RXIE);
	if(TimeFlag == 0)
	{
	BreathTime[BreathTimeIndex] = Second *10+ Timmer_Cycle/200;
	}
	if(TimeFlag == 1)
	{
	BreathTime[BreathTimeIndex] = (Second *10+ Timmer_Cycle/200) - BreathTime[BreathTimeIndex];
	BreathTimeIndex++;

	SendData();


	if(BreathTimeIndex > ARRAYLEN -1)
		{
		IE2 &= ~(UCA0RXIE);
		#ifdef SAVE

		int i;
		for(i = 0;i<ARRAYLEN ;i++)
		{
			Push(&BreathTime[i]);
			Push(&arrayDrawResultLen[i]);
			Push(&arrayShrinkResultLen[i]);
		}

		#endif


			BreathTimeIndex = 0;
		}


	}
	TimeFlag++;
	if (TimeFlag>1) TimeFlag = 0;
	IE2 |= (UCA0RXIE);
}
