/*
 * UART_Event.c
 * 功能：全面处理与上位机通信的相关事宜
 *  Created on: 2013-3-18
 *      Author: Administrator
 */
#include "MSP430G2553.h"
#include "UARt_Global.h"
#include "UART_FIFO.h"
#include "UART_Event.h"
//-----对于硬件有关的代码宏定义处理-----

//-----预存入ROM中的显示代码-----



void Command_match();  // 字符匹配命令函数
/******************************************************************************************************
 * 名       称：UART_OnTx()
 * 功       能：UART的Tx事件处理函数
 * 入口参数：无
 * 出口参数：无
 * 说       明：Tx_FIFO里有数据就将数据移到Tx Buffer寄存器中去
 * 范       例：无
 ******************************************************************************************************/
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
void UART_OnRx(void)
{
	unsigned char Temp = 0;
	Temp=UCA0RXBUF;			// 预存下Tx Buffer数据

	if(Temp == '+')				// 如果是回车，表明可以做个”了断“了
	{
		if(Rx_FIFO_DataNum > 0)	//FIFO里有数据，则进行数据判断
		{
		//	IE2 &= ~(UCA0RXIE);
			Command_match();		//判断命令是什么
			Rx_FIFO_Clear();				//清空FIFO
		//	IE2 |= (UCA0RXIE);
		}
							//如果啥数据都没有（光敲了个回车）
	//		UART_SendString(String1);  	//显示命令提示符
	//		UART_SendString(String2);	//显示命令提示符

	}
	//-----既不是回车也不是退格，那就正常存命令数据-----
	else
	{
		if(Rx_FIFO_DataNum >= RX_FIFO_SIZE)
			{
				UART_SendString("ERR+\0");
				Rx_FIFO_Clear();
				return;
			}
		Rx_FIFO_WriteChar(Temp); 			//正常写FIFO
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
void UART_SendString(const unsigned char *Ptr) //给上位机发送字符串
{
	while(*Ptr)
	{

	//	__delay_cycles(100);//延时 等待蓝牙模块响应
		Tx_FIFO_WriteChar(*Ptr++);
	}
	//Tx_FIFO_Clear();
}
/******************************************************************************************************
 * 名       称：Command_match()
 * 功       能：对接收到的命令数据进行匹配，根据匹配结果控制LED并回显处理结果
 * 入口参数：无
 * 出口参数：无
 * 说       明：共4种预先约定的命令字：LED1_ON,LED1_OFF,LED2_ON,LED2_OFF
 * 范       例：无
 ******************************************************************************************************/
void Command_match()  // 字符匹配命令
{
	if(Rx_FIFO[0] == 'R' && Rx_FIFO[1] == 'S' && Rx_FIFO[2] == 'T')
	{
		UART_SendString("ACKQ+\0");
		BState = Idle;
		return;
	}
	if(Rx_FIFO[0] == 'T' && Rx_FIFO[1] == 'E' && Rx_FIFO[2] == 'S'&& Rx_FIFO[3] == 'T')
	{
		BState = Test;
	}
	if(BState == Idle)
	{
		if(Rx_FIFO[0] == 'R' && Rx_FIFO[1] == 'E' && Rx_FIFO[2] == 'Q')
		{
			UART_SendString("ACKQ+\0");
			BState = Connected;
		}
		else
		{
			UART_SendString("ERR+\0");
		}
		return;
	}
	if(BState == Connected)
	{
		if(Rx_FIFO[0] == 'T' && Rx_FIFO[1] == 'X' && Rx_FIFO[2] == 'D')
		{

			if(Rx_FIFO[3] == '0')
			{
				BState = Transmit;
				TransmitMode = HISTORY;
				UART_SendString("READY+\0");
				return;
			}
			else if(Rx_FIFO[3] == '1')
			{
				BState = Transmit;
				TransmitMode = REALTIME;
				UART_SendString("READY+\0");
				return;
			}
			else
			{
				UART_SendString("ERR+\0");
				return;
			}

		}
		else
		{
			UART_SendString("ERR+\0");
			return;
		}
	}
	if(BState == Transmit)
	{
		if(Rx_FIFO[0] == 'A' && Rx_FIFO[1] == 'C' && Rx_FIFO[2] == 'K' && Rx_FIFO[3] == 'Q')

		{
			if(TransmitMode == REALTIME)
			{
				UART_SendString("HELLO+\0");
				return;
			}
		}
		if(Rx_FIFO[0] == 'E' && Rx_FIFO[1] == 'N' && Rx_FIFO[2] == 'D' && Rx_FIFO[3] == 'T')

		{
			BState = Connected;
			UART_SendString("ACKQ+\0");
			return;
		}
		UART_SendString("ERR+\0");
		return;
	}
}


