#include "../Headers/lightModes.h"
#include "HardwareSerial.h"
#include "../Headers/serialCommands.h"

		//getNextValue
		long localTime = 0;			// the last time the output pin was toggled
		int stringPointer = 0;   	//A pointer used for getNextValue function
									//in order to get the next value from string
		bool serialFlag = 0;
		int8_t serialValue = -1;

		//Variables Initialization
		char wifiData = 0;
		char bluetoothData = 0;

/********************************************************************************
 * serialCommandsVariableInit(void)												*
 * 																				*
 * 		Description: Initializes variables of the serial commands				*
 * 		Input: --  																*
 * 		Output:--																*
 ********************************************************************************/
void serialCommandsVariableInit(void)
{
	wifiData = 0;
	bluetoothData = 0;
}

/********************************************************************************
 * void bluetoothCheck(void)													*
 * 																				*
 * 		Description: Checks if a serial command (integer) is received from the 	*
 * 					 bluetooth receiver and if a command is received uses the	*
 * 					 switchModeCases() function									*
 * 		Input: --																*
 * 		Output:--																*
 ********************************************************************************/
void bluetoothCheck(void)
{
	if(Serial2.available() > 0)
	{
		bluetoothData = Serial2.read();			//Reads the incoming data and
												//stores the value in bluetoothData
		uint8_t ia = (uint8_t)(bluetoothData - '0');		//converts a char into int
		
		if(bluetoothCheckDebug==0) Serial.println(ia);
		if(ia<=SWITCH_MODE_CASES_NUMBER)
		{
			serialFlag = true;
			serialValue = ia;
			Serial2.write(ia);
			switchModeCases(ia);
		}
		else if(ia==99)
		{
			void printAvailableCommands();
		}
		else
		{
			Serial2.println("Error, command does not exist");
		}
	}
}

/********************************************************************************
 * void wifiCheck(void)															*
 * 																				*
 * 		Description: Checks if a serial command (integer) is received from the 	*
 * 					 WiFi receiver and if a command is received uses the		*
 * 					 switchModeCases() function									*
 * 		Input: --																*
 * 		Output:--																*
 ********************************************************************************/
void wifiCheck(void)
{
	if(Serial3.available() > 0)
	{
		wifiData = Serial3.read();     			//Reads the incoming data and
												//stores the value in wifiData
		uint8_t ia = (uint8_t)(wifiData - '0');	//converts a char into int
		if(wifiCheckDebug==0) {
			Serial.println("Original value:	" + wifiData);
			Serial.println("Final value:		" + ia);
		}
		if(ia<=SWITCH_MODE_CASES_NUMBER)
		{
			serialFlag = true;
			serialValue = ia;
			switchModeCases(ia);
		}
		else if(ia==99)
		{
			void printAvailableCommands();
		}
		else
		{
			Serial.println("Error, command does not exist");
		}
	}
}