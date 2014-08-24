/*
 * Time.c
 *
 *  Created on: 2014-8-23
 *      Author: HP
 */
#include "Time.h"
#include "Bluetooth.h"
#include "UART/UART_Global.h"
unsigned short BreathTime[5]={0};
void Real_Time()
{

	Timmer_Cycle++;
	if (Timmer_Cycle == 1000000/TIMMER_PERIOD)
	{
		Second++;
		Timmer_Cycle = 0;
		//UART_SendString("TEST+\0");

	//	if(BState == Test)
	//	{

	//	}
	}

}
void CalcBreathTime()
{
	static unsigned char TimeFlag = 0;
	static unsigned char BreathTimeIndex = 0;
	if(TimeFlag == 0)
	{
	BreathTime[BreathTimeIndex] = Second *1000+ Timmer_Cycle;
	}
	if(TimeFlag == 1)
	{
	BreathTime[BreathTimeIndex] = (Second *1000+ Timmer_Cycle) - BreathTime[BreathTimeIndex];
	BreathTimeIndex++;
	}
	TimeFlag++;
	if (TimeFlag>1) TimeFlag = 0;
}
