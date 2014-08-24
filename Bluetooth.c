/*
 * Bluetooth.c
 *
 *  Created on: 2014-8-23
 *      Author: HP
 */
#include "Bluetooth.h"
#include "UART/UART_init.h"
enum BluetoothState BState = Idle;
unsigned char TransmitMode = 2;
void Bluetooth_Init()
{
	USCI_A0_init();
}

