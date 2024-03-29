//修改自 G2 pocket lab code for CCS6.2 示例
//Adapted from DEMO G2 pocket lab code for CCS6.2
/*
 * UART_Global.c
 * 说明：UART的FIFO库函数
 *  Created on: 2013-3-18
 *      Author: Administrator
 */
#include "UART_Global.h"

unsigned char Rx_FIFO[RX_FIFO_SIZE]={0};		//UART接收FIFO数组
unsigned char Rx_FIFO_DataNum=0;					//UART接收FIFO的“空满”指示变量
unsigned char Rx_FIFO_IndexR=0;						//UART接收FIFO的模拟“读指针”变量
unsigned char Rx_FIFO_IndexW=0;						//UART接收FIFO的模拟“写指针”变量

unsigned char Tx_FIFO[TX_FIFO_SIZE]={0};		//UART发送FIFO数组
unsigned char Tx_FIFO_DataNum=0;					//UART发送FIFO的“空满”指示变量
unsigned char Tx_FIFO_IndexR=0;						//UART发送FIFO的模拟“读指针”变量
unsigned char Tx_FIFO_IndexW=0;						//UART发送FIFO的模拟“写指针”变量
