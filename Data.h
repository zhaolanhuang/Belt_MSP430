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
��ջʽ����
��һҳǰ��������Ϊ��ǰ����ָ��λ��
*/
#define PAGEBASE 0
#define OFFSETBASE 1
extern unsigned int pageIndex;//��ǰҳ����,range [0,4095]
extern unsigned int pageOffsetIndex;//ҳ��ƫ��,range [0,127]
void Push(unsigned int *data);
unsigned char Pop(unsigned int *data);
extern void SaveData();//����ARRAYLEN���������
extern void SendData(unsigned char _index);
extern void SavePointer();
extern void ReadPointer();
extern void FlushFlash();
#endif /* DATA_H_ */
