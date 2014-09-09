/*
 * Global.c
 *
 *  Created on: 2014-8-21
 *      Author: HP
 */
#include "Global.h"
unsigned int CountDrawLen = 0;
unsigned int CountShrinkLen = 0;
unsigned int arrayDrawResultLen[ARRAYLEN]={0};
unsigned int arrayShrinkResultLen[ARRAYLEN]={0};
unsigned char Flag = (FLAGMAX-FLAGMIN)/2;//Flag round [FLAGMIN,FLAGMAX].FLAGMIN means Shrinking.FLAGMAX means Drawing.(FLAGMIN,FLAGMAX)means Temping.
unsigned int Temp = 0;//When Flag round (FLAGMIN,FLAGMAX) whatever Shrinking or Drawing Temp++
unsigned int CountDraw = 0;
unsigned int CountShrink = 0;
unsigned short Second = 0;
unsigned int Timmer_Cycle = 0;
unsigned char TransmitMode = 2;
unsigned int BState = IDLE;
unsigned char isInTimmer = 2;
