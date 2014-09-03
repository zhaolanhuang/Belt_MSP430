/*
 * Data.c
 *
 *  Created on: 2014-9-3
 *      Author: HP
 */

#include "Data.h"
unsigned int page = 0;
unsigned int pageOffset = 0;
void Push(unsigned int *data)
{
	write_16(page,pageOffset,1,data);
	pageOffset++;
	if(pageOffset > 127)
	{
		pageOffset = 0;
		page++;
	}
	if(page>4095)
	{
		page = 0;
		pageOffset = OFFSETBASE+1;
	}
	SavePointer();

}
void Pop(unsigned int *data)
{
	read_16(page,pageOffset,1,data);
	if(page == 0 && pageOffset == OFFSETBASE+1)
	{
		page = 4095;
		pageOffset = 127;
		SavePointer();
		return;

	}
	if(pageOffset == 0)
	{
		pageOffset = 127;

			page--;
	}

	else
	{
		pageOffset--;
	}
	SavePointer();


}
void SaveData()
{
	int i;
	for(i = 0;i<ARRAYLEN;i++)
	{
		Push(&BreathTime[i]);
		Push(&arrayDrawResultLen[i]);
		Push(&arrayShrinkResultLen[i]);
	}
}
void SavePointer()
{
	write_16(0,0,1,&page);
	write_16(0,1,1,&pageOffset);
}
void ReadPointer()
{
	read_16(0,0,1,&page);
	read_16(0,1,1,&pageOffset);
}
void SendData()
{
	char temp,i;
	if(BState == Transmit)
	{
	for(i=0;i<5;i++)
	{
		temp = BreathTime[i] & 0x00ff;
		Tx_FIFO_WriteChar(temp);
		temp = (BreathTime[i]>>8) & 0x00ff;
		Tx_FIFO_WriteChar(temp);
		temp = arrayDrawResultLen[i] & 0x00ff;
		Tx_FIFO_WriteChar(temp);
		temp = (arrayDrawResultLen[i]>>8) & 0x00ff;
		Tx_FIFO_WriteChar(temp);
		temp = arrayShrinkResultLen[i] & 0x00ff;
		Tx_FIFO_WriteChar(temp);
		temp = (arrayShrinkResultLen[i]>>8) & 0x00ff;
		Tx_FIFO_WriteChar(temp);
	}
	}

}
