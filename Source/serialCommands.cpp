#include "../Headers/lightModes.h"
#include "../Headers/LiquidCrystal.h"
#include "HardwareSerial.h"
#include "../Headers/serialCommands.h"


	LiquidCrystal lcd (rs, en, d4, d5, d6, d7);

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
* omniPrint(char msg)															*
* 																				*
* 		Description: Prints text to all serial devices (PC, LCD, Bluetooth)		*
* 		Input: char																*
* 		Output:--																*
********************************************************************************/
void omniPrint(String msg)
{
	Serial.print (msg);
	Serial1.print (msg);
	Serial2.print (msg);
	//Serial3.print (msg);
	lcd.print (msg);
}

/********************************************************************************
* omniPrint(uint8_t msg)														*
* 																				*
* 		Description: Prints text to all serial devices (PC, LCD, Bluetooth)		*
* 		Input: uint8_t															*
* 		Output:--																*
********************************************************************************/
void omniPrint(uint8_t msg)
{
	Serial.print (msg);
	Serial1.print (msg);
	Serial2.print (msg);
	//Serial3.print (msg);
	lcd.print (msg);
}

/********************************************************************************
* omniPrintln(char msg)															*
* 																				*
* 		Description: Prints text to all serial devices (PC, LCD, Bluetooth)		*
* 		Input: char																*
* 		Output:--																*
********************************************************************************/
void omniPrintln(String msg)
{
	Serial.println (msg);
	Serial1.println (msg);
	Serial2.println (msg);
	//Serial3.println (msg);
	lcd.print (msg);
}

void omniPrintln()
{
	Serial.println ();
	Serial1.println ();
	Serial2.println ();
	//Serial3.println ();
}

/********************************************************************************
 * printAvailableCommands(void)													*
 * 																				*
 * 		Description: Prints all available serial commands	  					*
 * 		Input: --  																*
 * 		Output:--																*
 ********************************************************************************/
void printAvailableCommands()
{
	omniPrintln("Available serial commands:");
	omniPrintln();
	omniPrintln("General commands:");
	omniPrintln("	on");
	omniPrintln("	off");
	omniPrintln("	random");
	omniPrintln("	snake");
	omniPrintln("	couch");
	omniPrintln("	bed");
	omniPrintln("	alcohol");
	omniPrintln();
	omniPrintln("Debug commands:");
	omniPrintln("	dbgon");
	omniPrintln("	tg1");
//	omniPrintln("	sqc");
}

/********************************************************************************
 * boardPin(void)														*
 * 																				*
 * 		Description: Prints all pins and their job			  					*
 * 		Input: --  																*
 * 		Output:--																*
 ********************************************************************************/
void boardPin(void)
{
	omniPrintln("Hello, this is the board scheme:");
	uint8_t i = 0;
	while(i<=RELAY_ARRAY_MAX_VALUE)
	{
		//CONTROL
		printf("/n Element is %c",relayArr[i]);
		i++;
	}
}


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
		Serial.println(ia);
		if(bluetoothCheckDebug==0) Serial.println(bluetoothData);
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
		if(wifiCheckDebug==0) Serial.println("Original value:	" + wifiData);
		Serial.println("Final value:		" + ia);
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


/********************************************************************************
 * getNextValue (String str, String separator, int index)						*
 * 																				*
 * 		Description: 	Get the next index from the previous one using the 		*
 * 						separator. When you want to continue trough the same	*
 * 						string simply put the third param (index) to -1 		*
 * 		Input: (String, String, int)											*
 * 		Output: String															*
 ********************************************************************************/

String getNextValue (String str, String separator, int index)
{
 if (index != -1)
	 {
	 stringPointer = index;
	 }
 int8_t nextIndex = str.indexOf(separator, stringPointer+1);
 String sub = str.substring(stringPointer, nextIndex);
 stringPointer = nextIndex;
 return sub;
}


/********************************************************************************
 * serialRead(void)																*
 * 																				*
 * 		Description: Reads the serial commands sent to arduino 					*
 * 					 Returns values from 0 to 6 (253 is returned if the command	*
 * 					 does not exist or is mispelled)							*
 * 		Input: --																*
 * 		Output:uint8_t 															*
 ********************************************************************************/

/*
void serialRead(void)
{
  if (Serial.available())
  {
    String pn = Serial.readString();
    Serial.println("Command received: " + pn);
    String com = getNextValue(pn, " ", 0);
  	if (com == "tgl")
    {
  	  	String c = getNextValue(pn, ",", -1);
  	      while (c.toInt() != -1)
  	      {
  	    	  relayToggle(c.substring(1).toInt());
  	          c = getNextValue(pn, ",", -1);
  	      }
    }
    else
    Serial.println("Error, command does not exist");
  }
}
*/
