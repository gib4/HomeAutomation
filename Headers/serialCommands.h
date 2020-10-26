

#ifndef SERIALCOMMANDS_H
#define SERIALCOMMANDS_H

#include <Arduino.h>
#include "../Headers/SoftwareSerial.h"

//Public:
	//Debug Variables
	#define bluetoothCheckDebug 1
	#define wifiCheckDebug		0

	//Variables:
	extern bool serialFlag;
	extern int8_t serialValue;

	//Functions:
	extern void printAvailableCommands(void);
	extern void serialCommandsVariableInit(void);
	extern void bluetoothCheck(void);
	extern void wifiCheck(void);
	extern void omniPrint(String);
	extern void omniPrint(uint8_t);
	extern void omniPrintln(String);
	extern void omniPrintln(void);
	extern void boardPinInfoPrint(void);

//Private:
	//Serial Setup
	#define BLUETOOTH_TRX		14,15
	#define LCD_TRX				16,17
	#define PC_TRX				18,19

	//Variables
		extern char bluetoothData;
		extern char wifiData;

		// set up the LCD's number of columns and rows:
		#define rs 	12
		#define en	11
		#define d4	5
		#define d5	4
		#define d6	3
		#define d7	2

#endif	/*SERIALCOMMANDS_H*/
