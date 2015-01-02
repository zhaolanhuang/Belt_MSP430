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
		Temp++;
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
		Temp++;
	}
}
void ResultCalc()
{
	static unsigned char Flag_Past= (FLAGMAX-FLAGMIN)/2;	//变量值出函数时需保留
	unsigned int ShrinkResultLen = 0;
	unsigned int DrawResultLen = 0;
	static unsigned char isCount = 0;
	if (Flag == FLAGMAX && Flag_Past == FLAGMIN)//Shrink Over
	{
		
		ShrinkResultLen = CountShrinkLen + Temp - (FLAGMAX - FLAGMIN - 1);
		if(isCount == 1)
		{
			SaveShrinkToArray(ShrinkResultLen);
		}

		CalcBreathTime();
		isCount = 1;
		CountShrinkLen = 0;
		CountDrawLen = CountDrawLen + (FLAGMAX - FLAGMIN - 1);
		Temp = 0;
		CountShrink++;


	}
	else if (Flag == FLAGMIN && Flag_Past == FLAGMAX)//Draw Over
	{
		
		DrawResultLen = CountDrawLen + Temp- (FLAGMAX - FLAGMIN - 1);
		if(isCount == 1)
		{
			SaveDrawToArray(DrawResultLen);
		}

		CountDrawLen = 0;
		CountShrinkLen = CountShrinkLen + (FLAGMAX - FLAGMIN - 1);
		Temp = 0;
		CountDraw++;

	}
	else if (Flag == FLAGMIN && Flag_Past == FLAGMIN)//Shrinking
	{
		CountShrinkLen++;

	}
	else if (Flag == FLAGMAX && Flag_Past == FLAGMAX)//Shrinking
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
