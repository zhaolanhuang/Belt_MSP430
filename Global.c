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
unsigned char Flag = (FLAGMAX-FLAGMIN)/2;//Flag round [FLAGMIN,FLAGMAX].FLAGMIN means Shrinking.FLAGMAX means Stretching.
unsigned int Temp = 0;
unsigned int CountDraw = 0;
unsigned int CountShrink = 0;
unsigned int Second = 0;
unsigned char Timmer_Cycle = 0;
unsigned char TransmitMode = 2;
unsigned char BState = IDLE;
unsigned char isInTimmer = 2;
unsigned char Tick[2] = {0};
