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
/*
Using Word R/W Mode
堆栈式操作
第一页前两个字作为当前数据指针位置
*/
#define PAGEBASE 0
#define OFFSETBASE 1
extern unsigned int page;//当前页索引,range [0,4095]
extern unsigned int pageOffset;//页内偏移,range [0,127]
void Push(unsigned int *data);
void Pop(unsigned int *data);
void SaveData();//保存ARRAYLEN组呼吸数据
void SendData();
void SavePointer();
void ReadPointer();
#endif /* DATA_H_ */
