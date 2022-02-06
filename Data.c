/*
 * Data.c
 * 
 * This file implements high-level operations of data storage and trasmission, including:
 * - a LIFO stack on AT45DB081 NOR-Flash for data storage
 * - a function for sending data through Bluetooth-serial
 * 
 *  Created on: 2014-9-3
 *      Author: HP
 */

#include "Data.h"
// Total 4096 Pages, every page has 256 bytes (128 words)
// The first two words of the first page are reserved for stack top pointer
unsigned int pageIndex = 0;
unsigned int pageOffsetIndex = OFFSETBASE + 1;

/**
 * Push a word (2 bytes) to stack
 * @param data pointer of the word to be pushed
 */
void Push(unsigned int *data)
{
	static unsigned char times = 0;
	write_16(pageIndex,pageOffsetIndex,1,data);
	pageOffsetIndex++;
	if(pageOffsetIndex > 127)
	{
		pageOffsetIndex = 0;
		pageIndex++;
	}
	if(pageIndex>4095)
	{
		pageIndex = 0;
		pageOffsetIndex = OFFSETBASE+1;
	}
	times++;
	if (times == 3)
	{
		SavePointer();
		times = 0;
	}

}
/** Pop a word from the stack
 * @param data pointer for saving poped word
 * @return 0 for success, 1 for empty stack
 */
unsigned char Pop(unsigned int *data)
{
	static unsigned char times = 0;
	read_16(pageIndex,pageOffsetIndex,1,data);
	if(pageIndex == 0 && pageOffsetIndex == OFFSETBASE+1)
	{
	//	pageIndex = 4095;
	//	pageOffsetIndex = 127;
		SavePointer();
		return 1;

	}
	if(pageOffsetIndex == 0)
	{
		pageOffsetIndex = 127;

			pageIndex--;
	}

	else
	{
		pageOffsetIndex--;

	}
	times++;
	if (times == 3)
	{
		SavePointer();
		times = 0;
	}
	return 0;
	//SavePointer();


}

/**
 * Save breathing time and the corresponding belt stretch/shrinkage length
 * caused by inhaling/exhaling
 */
void SaveData()
{
	int i;
	for(i = 0;i<ARRAYLEN ;i++)
	{
		Push(&BreathTime[i]);
		Push(&arrayDrawResultLen[i]);
		Push(&arrayShrinkResultLen[i]);
	}
	SavePointer();
}

/*
	Reset the stack top pointer
 */
void FlushFlash()
{
	pageIndex = 0;
	pageOffsetIndex = OFFSETBASE + 1;
	SavePointer();
}

/*
	Save current stack top point to flash
 */
void SavePointer()
{
	write_16(0,0,1,&pageIndex);
	write_16(0,1,1,&pageOffsetIndex);
}

/**
 * Read stack top pointer from flash
 */
void ReadPointer()
{
	read_16(0,0,1,&pageIndex);
	read_16(0,1,1,&pageOffsetIndex);
}

/**
 * Transmit respiration data through Bluetooth serial
 * @param _index the buffer index of data to be transmitted
 */
void SendData(unsigned char _index)
{
	unsigned char temp,i;
	unsigned int itemp;

	//Bluetooth state: ready for transmission
	if(BState == BTRANSMIT)
	{

		//REALTIME MODE: Transmit current respiration data
		if(TransmitMode == REALTIME)
		{

			i = _index;
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

			UART_SendString(strREADY);
		}

		//HISTORY MODE: Pop and transmit all data saved in the flash
		else if (TransmitMode == HISTORY)
		{
			if(pageIndex == 0 && pageOffsetIndex == OFFSETBASE+1)
			{
				UART_SendString("EMPTY+");
				TransmitMode = REALTIME;
				return;
			}

			while(!Pop(&itemp))
			{

				temp = itemp & 0x00ff;
				Tx_FIFO_WriteChar(temp);
				temp = (itemp >>8)& 0x00ff;
				Tx_FIFO_WriteChar(temp);
				i++;
				if(i == 3)
				{
					UART_SendString(strREADY);
					i = 0;
				}
			}
			UART_SendString("EMPTY-");
			TransmitMode = REALTIME;
		}
	}


}
