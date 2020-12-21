/****************************************************************
 * lightModes.ccp - Library for different light modes	 		*
 * Created by D. �kerk, October 15, 2017				 		*
 ****************************************************************/

#include "../Headers/lightModes.h"
#include <Arduino.h>
#include "../Headers/sensors.h"


uint8_t toggleFlag=255;
	#define SEQ_JUMP			(MAX_BIT_VALUE/NUMBER_OF_RELAYS)
	#define MODES_JUMP			((MAX_BIT_VALUE+1)/NUMBER_OF_MODES)

Lights(){
	delaySnake = 140;
	delayRelay = 50;
	delayRandom = 170;
}

/********************************************************************************
 *  delayInit (snakeDelay, relayDelay, randomDelay)
 *  	Description: set the delay for each light mode
 *  	Input:	int, int, int
 *  	Output: --
 ********************************************************************************/
delayInit(int snake, int relay, int random){
	delaySnake = snake;
	delayRelay = relay;
	delayRandom = random;
}

/********************************************************************************
 *  setRelayPins (array)
 *  	Description: Sets the relay pins
 *  	Input:	int [ ]
 *  	Output: --
 ********************************************************************************/
void setRelayPins(int auxRelArr [])
{
	lightNum = sizeof(auxRelArr);
	for(int el : auxRelArr)
	{
		relayArr[i] = el;
	}
}

/********************************************************************************
* omniPrint(msg)
* 		Description: Prints text to all serial devices (PC, Bluetooth etc.)
* 		Input: String or uint8_t
* 		Output:--
********************************************************************************/
void omniPrint(String msg)
{
	Serial.print (msg);
	Serial1.print (msg);
	Serial2.print (msg);
	//Serial3.print (msg);
}

void omniPrint(uint8_t msg)
{
	Serial.print (msg);
	Serial1.print (msg);
	Serial2.print (msg);
	//Serial3.print (msg);
}

/********************************************************************************
* omniPrintln(msg)
*
* 		Description: Prints text to all serial devices (PC, Bluetooth etc.)
* 		Input: String or uint8_t
* 		Output:--
********************************************************************************/
void omniPrintln(String msg)
{
	Serial.println (msg);
	Serial1.println (msg);
	Serial2.println (msg);
	//Serial3.println (msg);
}

void omniPrintln()
{
	Serial.println ();
	Serial1.println ();
	Serial2.println ();
	//Serial3.println ();
}

/********************************************************************************
 * printAvailableCommands(void)						
 * 		Description: Prints all available serial commands
 * 		Input: --
 * 		Output:--
 ********************************************************************************/
void printAvailableCommands()
{
	omniPrintln("Available serial commands:");
	omniPrintln();
	omniPrintln("General commands:");
	omniPrintln("	1 - on");
	omniPrintln("	2 - random");
	omniPrintln("	3 - snake");
	omniPrintln("	4 - off");
	omniPrintln("	5 - couch");
	omniPrintln("	6 - bed");
	omniPrintln("	7 - alcohol");
	omniPrintln("	8 - desk");
	omniPrintln();
	omniPrintln("Debug commands:");
	omniPrintln("	dbgON");
	omniPrintln("	dbgOFF");
	omniPrintln("	tg1");
//	omniPrintln("	sqc");
}

/********************************************************************************
 * boardPin(void)
 * 		Description: Prints all pins and their job
 * 		Input: --
 * 		Output:--
 ********************************************************************************/
void boardPin(void)
{
	omniPrintln("This is the board scheme:");
	for (auto el: relayArray)
	{
		omniPrint(el);
		omniPrint(" ");
	}
	omniPrintln();
}

/********************************************************************************
 * switchSequence(uint8_t)
 * 		Description: Given an integer turns sequentially the lights	ON/OFF
 * 		Input: uint8_t
 * 		Output:--
 ********************************************************************************/
void switchSequence(uint8_t j)
{
	uint8_t i = 1;
	omniPrintln("Switch Sqc");
	if (switchSequenceDebug == 0) Serial.print("	");
	while (i <= RELAY_TOTAL_NUMBER)
	{
		if (i<j) {
			digitalWrite (relayArr[i-1], LOW);
			if (switchSequenceDebug == 0)
				Serial.print(String(i) +" ");
		}
		if (i>=j) {
			digitalWrite (relayArr[i-1], HIGH);
			if (switchSequenceDebug == 0) 
				Serial.print("- ");
		}
		i++;
	}
	if (switchSequenceDebug == 0) Serial.println();
}

/********************************************************************************
 * relayToggle(uint8_t)
 * 		Description: Turns all n relay ON (0) or all OFF (1)
 * 		Input: uint8_t 0 or 1
 * 		Output:--
 ********************************************************************************/
void relayToggle (uint8_t control){

	//if true turn ON
    if(control == 0) {
    	//lcd.print("All OFF");
        if(toggleFlag!=control) Serial.println ("All off");
    	//start FOR cycle that sequentially writes all relays value to HIGH
        for (int i = RELAY_ARRAY_MAX_VALUE; i>=RELAY_ARRAY_MIN_VALUE; i--)
        {
            delay(DELAY_TOGGLE_SEQUENCE);
            if (relayToggleDebug == 0)
            	Serial.println("	off - " + String(i+1)+ "		" +
            		analogRead(POT_PIN)+"		" +
					potInteger(MODES_JUMP,NUMBER_OF_MODES, SINGLE_EDGE_DISCARD));
            digitalWrite(RelayArray[i], HIGH);
        }
    }

    //if false turn OFF
    else if (control == 1) {
    	//lcd.print("All ON");
    	if(toggleFlag!=control)Serial.println ("All on");
        //start FOR cycle that sequentially writes all relays value to LOW)
        for (int i = RELAY_ARRAY_MIN_VALUE; i<=RELAY_ARRAY_MAX_VALUE; i++)
        {
            delay(DELAY_TOGGLE_SEQUENCE);
            if (relayToggleDebug == 0)
            	{
            	Serial.println("	ON - " + String(i+1)+ "		  " +
            			analogRead(POT_PIN)+"		" +
						potInteger(MODES_JUMP,NUMBER_OF_MODES,SINGLE_EDGE_DISCARD));
            	}
            digitalWrite(RelayArray[i], LOW);
        }
    }
    toggleFlag=control;
 }

/********************************************************************************
 * snakeToggle ()																
 * 																				
 * 		Description: Snake light method											
 * 		Requirements: sensors.h													
 * 		Input: --																
 * 		Output:--																
 ********************************************************************************/
void snakeToggle(void){
  uint8_t i = 0;
  omniPrintln ("Snake started");
  do{
	  	int n = i - 2;
		if(i > RELAY_ARRAY_MAX_VALUE)
		{
		  i=0;
		}
		if(n==-1)
		{
		  n = RELAY_ARRAY_MAX_VALUE;
		}
		else if(n==-2)
		{
		  n = RELAY_ARRAY_MAX_VALUE-1;
		}
		else if(n==-3)
		{
		  n = RELAY_ARRAY_MAX_VALUE-2;
		}
		digitalWrite(RelayArray[i], LOW);
		delay(50);
		digitalWrite(RelayArray[n], HIGH);
		if (snakeToggleDebug==0)
		{
			Serial.print("		off - " + String(n)+ "  	|	 on - " + String(i));
			Serial.println();
			/*
			Serial.print("	");
			for(uint8_t x=0; x<=RELAY_ARRAY_MAX_VALUE; x++)
			{
				if(x==n || x==i)	Serial.print("* ");
				else				Serial.print("- ");
			}
			Serial.println();
			*/
		}
		bluetoothCheck();
		delay(PROGRESSION_DELAY);
		i++;

  }
  while (potInteger(MODES_JUMP,NUMBER_OF_MODES, SINGLE_EDGE_DISCARD) == SNAKE || serialValue == SNAKE);
}

/********************************************************************************
*randomToggle()																	
*	Description: Given an exit value "x", randomly toggles one relay at a 
*	Input: --
*	Output: --
*********************************************************************************/
void randomToggle()
{
	omniPrintln("Random Toggle Activated");
	relayToggle(0);
	do {
		int r = random(0,lightNum);
		digitalWrite (relayArr[r], LOW);
		if (randomToggleDebug==0)
		{
			Serial.println("	ON - " + String(r+1) + "	" +
					analogRead(POT_PIN)+"	" +
					potInteger(MODES_JUMP,NUMBER_OF_MODES,SINGLE_EDGE_DISCARD));
		}
		delay(delayRandom);
		digitalWrite (relayArr[r], HIGH);
		bluetoothCheck();
		delay(10);
	}
	while (potInteger(MODES_JUMP,NUMBER_OF_MODES, SINGLE_EDGE_DISCARD)== RANDOM...
	|| serialValue == RANDOM);
}

/********************************************************************************
*selectiveToggle(bool [])														
*																				
*	Description: Given an array of booleans, turns ON/OFF in case of 1/0		
*	Input: bool [RELAY_TOTAL_NUMBER] lightStateArray							
*	Output: --																	
*********************************************************************************/
void selectiveToggle(uint8_t localLightStateArray [])
{
	relayToggle(0);
	for (int i = 0; i<RELAY_TOTAL_NUMBER; i++)
	{
		if (localLightStateArray [i] != 0,1) localLightStateArray [i] = 0;
		digitalWrite(RelayArray[i],localLightStateArray [i]);
	}
}

/********************************************************************************
*selectiveToggle(firstOnLight,lastOnLight)
*	Description: Given an array of booleans, turns ON/OFF in case of 1/0
*	Input: (uint8_t,uint8_t)
*	Output: --
*********************************************************************************/
void selectiveToggle(uint8_t initial, uint8_t final)
{
	relayToggle(0);
	for (int i = initial; i<final; i++)
	{
		if		(i<initial)					digitalWrite(RelayArray[i],HIGH);
		else if	(i>=initial && i<=final)	digitalWrite(RelayArray[i],LOW);
		else								digitalWrite(RelayArray[i],HIGH);
	}
}

/********************************************************************************
*debugSerialPrint(flag)
*	Description: if flag is set to true will print debug values through all
*				 serial ports
*	Input: bool
*	Output: --
*********************************************************************************/
void debugSerialPrint(bool dFlag){
	bool relayToggleDebug 		= dFlag;
	bool randomToggleDebug 		= dFlag;
	bool snakeToggleDebug		= dFlag;
	bool switchSequenceDebug	= dFlag;
	bool selectiveRelayDebug	= dFlag;
}