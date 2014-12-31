/*
 * UART_Event.c
 * ���ܣ�ȫ�洦������λ��ͨ�ŵ��������
 *  Created on: 2013-3-18
 *      Author: Administrator
 */
#include "MSP430G2553.h"
#include "UART_Global.h"
#include "UART_FIFO.h"
#include "UART_Event.h"
//-----����Ӳ���йصĴ���궨�崦��-----

//-----Ԥ����ROM�е���ʾ����-----
const unsigned char strERR[] = "ERR+\0";
const unsigned char strACKQ[] = "ACKQ+\0";
const unsigned char strREADY[] = "READY+\0";
const unsigned char strSTAMP[] = "STAMP+\0";
void Command_match();  // �ַ�ƥ�������
/******************************************************************************************************
 * ��       �ƣ�UART_OnTx()
 * ��       �ܣ�UART��Tx�¼�������
 * ��ڲ�������
 * ���ڲ�������
 * ˵       ����Tx_FIFO�������ݾͽ������Ƶ�Tx Buffer�Ĵ�����ȥ
 * ��       ������
 ******************************************************************************************************/
void UART_OnTx(void)
{
	unsigned char Temp;
	if(Tx_FIFO_DataNum>0)
	{
		Tx_FIFO_ReadChar(&Temp);	//����FIFO�⺯��
		UCA0TXBUF= Temp;
	}
}
/******************************************************************************************************
 * ��       �ƣ�UART_OnRx()
 * ��       �ܣ�UART��Rx�¼�������
 * ��ڲ�������
 * ���ڲ�������
 * ˵       �����Խ��յ������ݣ�����Դ����д���
 * ��       ������
 ******************************************************************************************************/
void UART_OnRx(void)
{
	unsigned char Temp = 0;
	Temp=UCA0RXBUF;			// Ԥ����Tx Buffer����

	if(Temp == '+')				// ����ǻس������������������˶ϡ���
	{
		if(Rx_FIFO_DataNum > 0)	//FIFO�������ݣ�����������ж�
		{
			IE2 &= ~(UCA0RXIE);
			Command_match();		//�ж�������ʲô
			Rx_FIFO_Clear();				//���FIFO
			IE2 |= (UCA0RXIE);
		}
							//���ɶ���ݶ�û�У������˸��س���
	//		UART_SendString(String1);  	//��ʾ������ʾ��
	//		UART_SendString(String2);	//��ʾ������ʾ��

	}
	//-----�Ȳ��ǻس�Ҳ�����˸��Ǿ���������������-----
	else
	{
		if(Rx_FIFO_DataNum >= RX_FIFO_SIZE)
			{
				UART_SendString(strERR);
				Rx_FIFO_Clear();
				return;
			}
		Rx_FIFO_WriteChar(Temp); 			//����дFIFO
	}
}
/******************************************************************************************************
 * ��       �ƣ�UART_SendString()
 * ��       �ܣ���UART����һ���ַ���
 * ��ڲ�����*Ptr���ַ����׵�ַ
 * ���ڲ�������
 * ˵       �����ַ�������ܳ�������Tx_FIFO���ȣ���ᷢ������CPU
 * ��       ������
 ******************************************************************************************************/
void UART_SendString(const unsigned char *Ptr) //����λ�������ַ���
{

	while(*Ptr)
	{

	    //__delay_cycles(100);//��ʱ �ȴ�����ģ����Ӧ
		if(Tx_FIFO_WriteChar(*Ptr) == 1)
		{
			Ptr++;
		}

	}

	Tx_FIFO_Clear();
}
/******************************************************************************************************
 * ��       �ƣ�Command_match()
 * ��       �ܣ��Խ��յ����������ݽ���ƥ�䣬����ƥ��������LED�����Դ�����
 * ��ڲ�������
 * ���ڲ�������
 * ˵       ������4��Ԥ��Լ���������֣�LED1_ON,LED1_OFF,LED2_ON,LED2_OFF
 * ��       ������
 ******************************************************************************************************/
void Command_match()  // �ַ�ƥ������
{
	if(Rx_FIFO[0] == 'R' && Rx_FIFO[1] == 'S' && Rx_FIFO[2] == 'T')
	{
		//UART_SendString(strACKQ);
		BState = IDLE;
		return;
	}
	if(Rx_FIFO[0] == 'T' && Rx_FIFO[1] == 'X' && Rx_FIFO[2] == 'D')
			{

				if(Rx_FIFO[3] == '0')
				{
					BState = BTRANSMIT;
					TransmitMode = HISTORY;
				//	UART_SendString(strACKQ);
					return;
				}
				else if(Rx_FIFO[3] == '1')
				{
					BState = BTRANSMIT;
					TransmitMode = REALTIME;
				//	UART_SendString(strACKQ);
					return;
				}
				else
				{
				//	UART_SendString(strERR);
					return;
				}
			}
/*	if(Rx_FIFO[0] == 'T' && Rx_FIFO[1] == 'E' && Rx_FIFO[2] == 'S'&& Rx_FIFO[3] == 'T')
	{
		BState = BTEST;
		return;
	}
	if(BState == IDLE)
	{
		if(Rx_FIFO[0] == 'R' && Rx_FIFO[1] == 'E' && Rx_FIFO[2] == 'Q')
		{
		//	UART_SendString(strACKQ);
		//	BState = CONNECTED;
			BState = SEND;
		}
		else
		{
			UART_SendString(strERR);
		}
		return;
	}
	if(BState == CONNECTED)
	{
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
		else
		{
			UART_SendString(strERR);
			return;
		}
	}
	if(BState == PRESEND)
	{
		if(Rx_FIFO[0] == 'A' && Rx_FIFO[1] == 'C' && Rx_FIFO[2] == 'K' && Rx_FIFO[3] == 'Q')

		{
			if(TransmitMode == REALTIME)
			{
				UART_SendString("HELLO+\0");
				return;
			}
			BState = SEND;
			return;
		}
		if(Rx_FIFO[0] == 'E' && Rx_FIFO[1] == 'N' && Rx_FIFO[2] == 'D' && Rx_FIFO[3] == 'T')

		{
			BState = CONNECTED;
			UART_SendString(strACKQ);
			return;
		}
		UART_SendString(strERR);
		return;
	}*/
	//UART_SendString(strERR);
	return;
}


