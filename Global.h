/*
 * Global.h
 *
 *  Created on: 2014-8-21
 *      Author: HP
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_
#include "Data.h"
#include "Interrupt.h"
#include "Count.h"
#include "Init.h"
#include "Time.h"
#include "Bluetooth.h"
#define DTRIGGER
//#define TEST
#define SAVE
#define TIMMER_PERIOD 500//TIMMER_PERIOD/1000 (ms)
#define FLAGMAX 5
#define FLAGMIN 0
#define ARRAYLEN 5
extern unsigned int CountDrawLen;
extern unsigned int CountShrinkLen;
extern unsigned int arrayDrawResultLen[ARRAYLEN];
extern unsigned int arrayShrinkResultLen[ARRAYLEN];
extern unsigned int BreathTime[ARRAYLEN];
extern unsigned char Flag;//Flag round [FLAGMIN,FLAGMAX].FLAGMIN means Shrinking.FLAGMAX means Drawing.(FLAGMIN,FLAGMAX)means Temping.
extern unsigned int Temp;//When Flag round (FLAGMIN,FLAGMAX) whatever Shrinking or Drawing Temp++
extern unsigned int CountDraw;
extern unsigned int CountShrink;
extern unsigned short Second;
extern unsigned int Timmer_Cycle;
extern unsigned char isInTimmer;//0 no,1 yes
#define REALTIME 1
#define HISTORY 0
#define IDLE 0
#define CONNECTED 1
#define BTRANSMIT 2
#define BTEST 3
#define SEND 4
#define PRESEND 5
extern unsigned char TransmitMode;
extern unsigned int BState;
#endif /* GLOBAL_H_ */
