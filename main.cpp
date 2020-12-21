/*
 * HomeAutomation.cpp
 *
 *  Created on: 15 ott 2017
 *      Author: D. �kerk
 */

#include <libraries/arduino/Arduino.h>
#include "HardwareSerial.h"
#include "Headers/lightModes.h"
#include "Headers/mega2560_board.h"
#include "Headers/sensors.h"
#include "Headers/serialCommands.h"
//#include <Headers/LiquidCrystal.h>

//Impulse BUTTON SET-UP

uint8_t state = HIGH;      // the current state of the output pin
uint8_t previous = LOW;    // the previous reading from the input pin

	 //DELAYS
	 #define ANTI_RELAY_FLICKER_DELAY	500

void setup()
{
  	delay(ANTI_RELAY_FLICKER_DELAY);
  	Serial.begin(115200);			//PC
  	Serial1.begin(9600);
  	Serial2.begin(9600);			//LCD or Bluetooth
  	Serial3.begin(9600);			//WiFi

  	sensorsReset();
  	omniPrintln("Revision 0.3.5 - 08 February 2020");
  	omniPrintln();
  	printAvailableCommands();
  	//printAvailableCommands(BLUETOOTH_TRX);
  	//lcd.begin (16, 2);
	int light_array_pins [] = {23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45};
	int input_array_pins [] = {53, A1}; //button, potentiometer, A0 mic
  	//defines the PINs to INPUT or OUTPUT
  	for (auto el : light_array_pins){
		pinMode(el,OUTPUT);
  	}
  	for (auto el : input_array_pins){
		pinMode(el,INPUT);
  	}

	setRelayArray(light_array_pins);
	relayToggle(0);					//in case of a reset assures that
										//the lights won't turn on themselves
}

//PREBUILT LIGHT PATTERNS
uint8_t lightsStateArray1 [] {0,0,1, 1,1,1, 0,1,1, 1,0,0};
uint8_t corners [] {1,0,0, 1,0,0, 1,0,0, 1,0,0};

/********************************************************************************
 * switchModeCases(uint8_t)														
 * 																				
 * 		Description: Given an integer from 1 to 8 give the corresponding mode	
 * 		Input: uint8_t from 1 to 8												
 * 		Output:--																
 ********************************************************************************/
void switchModeCases(uint8_t j) {
  delay(500);
  switch (j) {

	case ON:
		relayToggle(0);
		break;
	case RANDOM:
		randomToggle();
		break;
	case SNAKE:
		snakeToggle();
		break;
	case OFF:
		relayToggle(1);
		break;
	case COUCH:
		selectiveToggle(8,10);
		break;
	case BED:
		selectiveToggle(6,7);
		break;
	case ALCOHOL:
		selectiveToggle(lightsStateArray1);
		break;
	case DESK:
		selectiveToggle();
		break;
	default:
		relaytoggle(1);
  }
}

void loop ()
{
	//DOOR BUTTON
	uint8_t buttonStateControl = doorButtonRead();

	if (serialFlag == false)
	{
		if (buttonStateControl == 0)
		{
			prevButtonStateControl = buttonStateControl;
			switchModeCases(potInteger(MODES_JUMP, NUMBER_OF_MODES,
												SINGLE_EDGE_DISCARD));
		}
		else if (buttonStateControl == 1)
		{
			prevButtonStateControl = buttonStateControl;
			switchSequence(potInteger(SEQ_JUMP, NUMBER_OF_RELAYS,
												SINGLE_EDGE_DISCARD));
		}
	}
	else if (prevButtonStateControl != buttonStateControl)
	{
		serialFlag = false;
		internalClapFlag = false;
		serialValue = -1;
	}
	/*
	else
	{
		 sensorsReset();
	}
	*/

	//SERIAL READ
	bluetoothCheck();
	wifiCheck();
	//serialRead();

	//MICROPHONE
	//micDoubleClapDetection();
}