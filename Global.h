/*
 * Global.h
 *
 *  Created on: 2014-8-21
 *      Author: HP
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#define TEST
#define TIMMER_PERIOD 1000//TIMMER_PERIOD/1000 (ms)
#define FLAGMAX 1
#define FLAGMIN 0
extern unsigned int CountDrawLen;
extern unsigned int CountShrinkLen;
extern unsigned int arrayDrawResultLen[5];
extern unsigned int arrayShrinkResultLen[5];
extern unsigned char Flag;//Flag round [FLAGMIN,FLAGMAX].FLAGMIN means Shrinking.FLAGMAX means Drawing.(FLAGMIN,FLAGMAX)means Temping.
extern unsigned int Temp;//When Flag round (FLAGMIN,FLAGMAX) whatever Shrinking or Drawing Temp++
extern unsigned int CountDraw;
extern unsigned int CountShrink;
extern unsigned short Second;
extern unsigned int Timmer_Cycle;

#endif /* GLOBAL_H_ */
