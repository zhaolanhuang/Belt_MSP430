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

	static unsigned char TimeFlag = 0;
	static char BreathTimeIndex = 0;
	IE2 &= ~(UCA0RXIE);
	if(TimeFlag == 0)
	{
	BreathTime[BreathTimeIndex] = Second *10+ Timmer_Cycle;
	TimeFlag = 1;
	}
	else if(TimeFlag == 1)
	{
	BreathTime[BreathTimeIndex] = (Second *10+ Timmer_Cycle) - BreathTime[BreathTimeIndex];
	SendData(BreathTimeIndex);


	if(BreathTimeIndex > ARRAYLEN -2)
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


			BreathTimeIndex = -1;
		}
	BreathTimeIndex++;
	BreathTime[BreathTimeIndex] = Second *10+ Timmer_Cycle;



	}


	IE2 |= (UCA0RXIE);
}
