/*
 * UART_Event.h
 *
 *  Created on: 2013-3-18
 *      Author: Administrator
 */

#ifndef UART_EVENT_H_
#define UART_EVENT_H_
extern const unsigned char strREADY[];
extern const unsigned char strSTAMP[];
extern void UART_OnTx(void);
extern void UART_OnRx(void);
extern void UART_SendString(const  unsigned char *Ptr); //给上位机发送字符串


#endif /* UART_EVENT_H_ */
