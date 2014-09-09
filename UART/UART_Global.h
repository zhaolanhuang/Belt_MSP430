/*
 * UART_Global.h
 * 说明：UART的FIFO库函数头文件
 *  Created on: 2013-3-18
 *      Author: Administrator
 */

#ifndef UART_GLOBAL_H_
#define UART_GLOBAL_H_
#include "../Bluetooth.h"
#include "../Global.h"
#define RX_FIFO_SIZE 16		//接收缓冲区大小宏定义
#define TX_FIFO_SIZE 64		//发送缓冲区大小宏定义

extern  unsigned char Rx_FIFO[RX_FIFO_SIZE];
extern  unsigned char Rx_FIFO_DataNum;
extern  unsigned char Rx_FIFO_IndexR;
extern  unsigned char Rx_FIFO_IndexW;

extern  unsigned char Tx_FIFO[TX_FIFO_SIZE];
extern  unsigned char Tx_FIFO_DataNum;
extern  unsigned char Tx_FIFO_IndexR;
extern  unsigned char Tx_FIFO_IndexW;

#endif /* UART_GLOBAL_H_ */
