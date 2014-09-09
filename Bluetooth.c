/*
 * Bluetooth.c
 *
 *  Created on: 2014-8-23
 *      Author: HP
 */
#include "Bluetooth.h"
#include "UART/UART_init.h"


void Bluetooth_Init()
{
	USCI_A0_init();
}

