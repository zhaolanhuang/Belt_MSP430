/*
 * Data.h
 *
 *  Created on: 2014-9-3
 *      Author: HP
 */

#ifndef DATA_H_
#define DATA_H_
#include "Global.h"
#include "Bluetooth.h"
#include "memorizer.h"
#include "UART/UART_Event.h"
/*
Using Word R/W Mode
堆栈式操作
Stack-liked operation
第一页前两个字作为当前数据指针位置
The first two words of the first page are reserved for stack top pointer
*/
#define PAGEBASE 0
#define OFFSETBASE 1
extern unsigned int pageIndex;//当前页索引,range [0,4095] Current page index
extern unsigned int pageOffsetIndex;//页内偏移,range [0,127] current page offset per word
void Push(unsigned int *data);
unsigned char Pop(unsigned int *data);
extern void SaveData();//保存ARRAYLEN组呼吸数据
extern void SendData(unsigned char _index);
extern void SavePointer();
extern void ReadPointer();
extern void FlushFlash();
#endif /* DATA_H_ */
