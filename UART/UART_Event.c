//修改自 G2 pocket lab code for CCS6.2 示例
//Adapted from DEMO G2 pocket lab code for CCS6.2
/*
 * UART_Event.c
 * 功能：全面处理与上位机通信的相关事宜
 * 
 * Tx/Rx ISR handlers of UART_A0
 * Communicate with smart phone or PC through Bluetooth serial
 * 
 *  Created on: 2013-3-18
 *      Author: Administrator
 *  
 */
#include "MSP430G2553.h"
#include "UART_Global.h"
#include "UART_FIFO.h"
#include "UART_Event.h"
//-----对于硬件有关的代码宏定义处理-----

//-----预存入ROM中的显示代码-----
const unsigned char strERR[] = "ERR+\0";
const unsigned char strACKQ[] = "ACKQ+\0";
const unsigned char strREADY[] = "READY+\0";
const unsigned char strSTAMP[] = "STAMP+\0";
void Command_match();  // 字符匹配命令函数
/******************************************************************************************************
 * 名       称：UART_OnTx()
 * 功       能：UART的Tx事件处理函数
 * 入口参数：无
 * 出口参数：无
 * 说       明：Tx_FIFO里有数据就将数据移到Tx Buffer寄存器中去
 * 范       例：无
 ******************************************************************************************************/
/**
 * Tx ISR handler of UART
 * Transmit all data in the Tx FIFO to Bluetooth-Client
 */
void UART_OnTx(void)
{
	unsigned char Temp;
	if(Tx_FIFO_DataNum>0)
	{
		Tx_FIFO_ReadChar(&Temp);	//调用FIFO库函数
		UCA0TXBUF= Temp;
	}
}
/******************************************************************************************************
 * 名       称：UART_OnRx()
 * 功       能：UART的Rx事件处理函数
 * 入口参数：无
 * 出口参数：无
 * 说       明：对接收到的数据，区别对待进行处理
 * 范       例：无
 ******************************************************************************************************/
/**
 * Rx ISR handler of UART
 * Receive commands from Bluetooth client
 */
void UART_OnRx(void)
{
	unsigned char Temp = 0;
	Temp=UCA0RXBUF;			// 预存下Tx Buffer数据

	//Match the end of Command
	if(Temp == '+')				// 如果是回车，表明可以做个”了断“了
	{
		if(Rx_FIFO_DataNum > 0)	//FIFO里有数据，则进行数据判断
		{
			IE2 &= ~(UCA0RXIE);
			//Determine which command is received
			Command_match();		//判断是什么命令
			Rx_FIFO_Clear();				//清空FIFO
			IE2 |= (UCA0RXIE);
		}


	}
	//-----既不是回车也不是退格，那就正常存命令数据-----
	else
	{
		if(!Rx_FIFO_WriteChar(Temp))
			{
				UART_SendString(strERR);
				Rx_FIFO_Clear();
				Rx_FIFO_WriteChar(Temp)
				return;
			}
		
	}
}
/******************************************************************************************************
 * 名       称：UART_SendString()
 * 功       能：用UART发送一个字符串
 * 入口参数：*Ptr：字符串首地址
 * 出口参数：无
 * 说       明：字符串如果很长，超过Tx_FIFO长度，则会发生阻塞CPU
 * 范       例：无
 ******************************************************************************************************/
/**
 * Send string to client
 * @param Ptr pointer of the string
 */
void UART_SendString(const unsigned char *Ptr) //给上位机发送字符串
{

	while(*Ptr)
	{

	    //__delay_cycles(100);//延时 等待蓝牙模块响应
		if(Tx_FIFO_WriteChar(*Ptr) == 1)
		{
			Ptr++;
		}

	}

	Tx_FIFO_Clear();
}
/******************************************************************************************************
 * 名       称：Command_match()
 * 功       能：对接收到的命令数据进行匹配，根据匹配结果控制LED并回显处理结果
 * 入口参数：无
 * 出口参数：无
 * 说       明：共4种预先约定的命令字
 * 范       例：无
 ******************************************************************************************************/
/**
 * Determine which command is received
 *
 * Command Word:
 * 'RST': Disable the data transmission
 * 'TXD0': Enable data transmission and switch to HISTORY mode for sending all stored data
 * 'TXD1': Enable data transmission and switch to REALTIME mode for sending current data
 *
 * Acknowledge:
 * 'ACKQ': Command executed successfully
 * 'ERR': Unknown command
 * 
 */
void Command_match()  // 字符匹配命令
{
	if(Rx_FIFO[0] == 'R' && Rx_FIFO[1] == 'S' && Rx_FIFO[2] == 'T')
	{
		BState = IDLE;
		UART_SendString(strACKQ);
		
		return;
	}
	if(Rx_FIFO[0] == 'T' && Rx_FIFO[1] == 'X' && Rx_FIFO[2] == 'D')
			{

				if(Rx_FIFO[3] == '0')
				{
					BState = BTRANSMIT;
					TransmitMode = HISTORY;
					UART_SendString(strACKQ);
					return;
				}
				else if(Rx_FIFO[3] == '1')
				{
					BState = BTRANSMIT;
					TransmitMode = REALTIME;
					UART_SendString(strACKQ);
					return;
				}
				else
				{
					UART_SendString(strERR);
					return;
				}
			}

	return;
}


