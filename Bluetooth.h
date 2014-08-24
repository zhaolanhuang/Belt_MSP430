/*
 * Bluetooth.h
 *
 *  Created on: 2014-8-23
 *      Author: HP
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_
#include "Global.h"
#include "UART/UART_init.h"
#define REALTIME 1
#define HISTORY 0
extern enum BluetoothState{Connected,Transmit,Idle,Test};
extern enum BluetoothState BState;
extern unsigned char TransmitMode;
void Bluetooth_Init();

#endif /* BLUETOOTH_H_ */
