/*
 * SPI.h
 *
 *  Created on: 2013-4-3
 *      Author: Administrator
 */

#ifndef SPI_H_
#define SPI_H_

#define	HARD_SPI	//条件编译，HARD_SPI启用硬件SPI代码
//#define	SOFT_SPI			//条件编译，SOFT_SPI启用软件SPI代码
extern void SPI_CS_High(void);
extern void SPI_CS_Low(void);
extern void SPI_HighSpeed(void);
extern void SPI_LowSpeed(void);
extern void SPI_init(void);
extern unsigned char SPI_TxFrame(unsigned char  *pBuffer, unsigned int   size);
extern unsigned char SPI_RxFrame(unsigned char  *pBuffer, unsigned int size);
extern void SPI_TxISR_Hook();
extern void SPI_RxISR_Hook();
extern unsigned char  SPI_Tx_Size;
extern unsigned char  SPI_Rx_Size;
extern unsigned char  *SPI_Tx_Buffer;
extern unsigned char  *SPI_Rx_Buffer;
//-----定义待发送/接收的字节数-----
extern unsigned char  SPI_Tx_Size;
extern unsigned char  SPI_Rx_Size;
//-----定义发送/接收模式标志-----
extern unsigned char SPI_Rx_Or_Tx ;
#endif /* SPI_H_ */
