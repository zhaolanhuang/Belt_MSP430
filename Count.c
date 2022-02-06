/*
 * Count.c
 *
 * Implement the recognition of respiratory cycles
 * The Function FlagPlus or FlagSub is called when the belt is stretching or shrinking
 * Inside them is a soft hysteresis mechanism (quasi a Schmitt trigger) for debounce
 *  Created on: 2014-8-21
 *      Author: HP
 */

#include "Count.h"

/**
 * Called when the belt is stretching (i.e. possible exhalation)
 */
void FlagPlus()
{
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

/**
 * Called when the belt is shrinking (i.e. possible inhalation)
 */
void FlagSub()
{
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

/**
 * Caculate and record respiration time and the corresponding stretch/shrinkage length
 * 
 * Called when the length of belt stretch/shrinkage is greater than 0.35 mm (determined by FLATMIN/-MAX)
 * The changing length smaller than 0.35 mm is counted as jitter.
 */
void ResultCalc()
{
	static unsigned char Flag_Past= (FLAGMAX-FLAGMIN)/2;	//变量值出函数时需保留
	unsigned int ShrinkResultLen = 0;
	unsigned int DrawResultLen = 0;
	static unsigned char isCount = 0;

	//Shrinkage Over
	//End of exhalation, beginning of inhalation
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

	//Stretch Over
	//End of inhalation, beginning of exhalation
	else if (Flag == FLAGMIN && Flag_Past == FLAGMAX)
	{
		
		DrawResultLen = CountDrawLen + (FLAGMAX - FLAGMIN);
		if(isCount == 1)
		{
			SaveDrawToArray(DrawResultLen);
		}

		CountDrawLen = 0;

	}
	else if (Flag == FLAGMIN && Flag_Past == FLAGMIN)//Belt Shrinking, exhaling
	{
		CountShrinkLen++;

	}
	else if (Flag == FLAGMAX && Flag_Past == FLAGMAX)//Belt Stretching, inhaling
	{
		CountDrawLen++;

	}
	Flag_Past = Flag;

}

/**
 * Save belt stretch length of inhalation of one respiratory cycle to a circular buffer
 * @param _DrawResultLen belt stretch length of inhalation
 */
void SaveDrawToArray(const unsigned int _DrawResultLen)
{
	static unsigned char indexDrawResultLen = 0;
	if (indexDrawResultLen >ARRAYLEN-1) indexDrawResultLen = 0;
	arrayDrawResultLen[indexDrawResultLen] = _DrawResultLen;
	indexDrawResultLen++;

}

/**
 * Save belt shrinkage length of exhalation of one respiratory cycle to a circular buffer
 * @param _ShrinkResultLen belt shrinkage length of exhalation
 */
void SaveShrinkToArray(const unsigned int _ShrinkResultLen)
{
	static unsigned char indexShrinkResultLen = 0;
	if (indexShrinkResultLen >ARRAYLEN-1) indexShrinkResultLen = 0;
	arrayShrinkResultLen[indexShrinkResultLen] = _ShrinkResultLen;
	indexShrinkResultLen++;

}
