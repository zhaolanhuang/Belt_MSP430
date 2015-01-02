/*
 * Count.c
 *
 *  Created on: 2014-8-21
 *      Author: HP
 */
#include "Count.h"

void FlagPlus()
{
	//Tick[0]++;
	if (Flag >= FLAGMAX)
	{
		Flag = FLAGMAX;
		ResultCalc();

	}
	else
	{
		Flag++;
	}
}
void FlagSub()
{
	//Tick[1]++;
	if (Flag <=FLAGMIN)
	{
		Flag =FLAGMIN;
		ResultCalc();
	}
	else
	{
		Flag--;
	}
}
void ResultCalc()
{
	static unsigned char Flag_Past= (FLAGMAX-FLAGMIN)/2;	//变量值出函数时需保留
	unsigned int ShrinkResultLen = 0;
	unsigned int DrawResultLen = 0;
	static unsigned char isCount = 0;

	//Shrink Over
	//End of exhaling, beginning of inhaling
	if (Flag == FLAGMAX && Flag_Past == FLAGMIN)
	{
		
		ShrinkResultLen = CountShrinkLen + (FLAGMAX - FLAGMIN);
		if(isCount == 1)
		{
			SaveShrinkToArray(ShrinkResultLen);
		}

		CalcBreathTime();
		isCount = 1;
		CountShrinkLen = 0;


	}

	//Draw Over
	//End of inhaling, beginning of exhaling
	else if (Flag == FLAGMIN && Flag_Past == FLAGMAX)
	{
		
		DrawResultLen = CountDrawLen + (FLAGMAX - FLAGMIN);
		if(isCount == 1)
		{
			SaveDrawToArray(DrawResultLen);
		}

		CountDrawLen = 0;

	}
	else if (Flag == FLAGMIN && Flag_Past == FLAGMIN)//Shrinking
	{
		CountShrinkLen++;

	}
	else if (Flag == FLAGMAX && Flag_Past == FLAGMAX)//Drawing
	{
		CountDrawLen++;

	}
	Flag_Past = Flag;

}
void SaveDrawToArray(const unsigned int _DrawResultLen)
{
	static unsigned char indexDrawResultLen = 0;
	if (indexDrawResultLen >ARRAYLEN-1) indexDrawResultLen = 0;
	arrayDrawResultLen[indexDrawResultLen] = _DrawResultLen;
	indexDrawResultLen++;

}
void SaveShrinkToArray(const unsigned int _ShrinkResultLen)
{
	static unsigned char indexShrinkResultLen = 0;
	if (indexShrinkResultLen >ARRAYLEN-1) indexShrinkResultLen = 0;
	arrayShrinkResultLen[indexShrinkResultLen] = _ShrinkResultLen;
	indexShrinkResultLen++;

}
