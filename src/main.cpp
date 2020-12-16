/*************************************************************
 * HomeAutomation.cpp
 *
 *  Created on: 15 ott 2017
 *      Author: D. �kerk
 ************************************************************/

#include <Arduino.h>
#include <HardwareSerial.h>
// #include "lightModes.h"
// #include "Headers/mega2560_board.h"
// #include "Headers/sensors.h"
// #include "Headers/serialCommands.h"



//#include <Headers/LiquidCrystal.h>

//Impulse BUTTON SET-UP

uint8_t state = HIGH;      // the current state of the output pin
uint8_t previous = LOW;    // the previous reading from the input pin



void setup()
{
  delay(ANTI_RELAY_FLICKER_DELAY);
  Serial.begin(115200);			//PC
  Serial1.begin(9600);
  Serial2.begin(9600);			//LCD or Bluetooth
  //Serial3.begin(9600);			//WiFi

  sensorsReset();
  omniPrintln("Revision 0.3.5 - 08 February 2018");
  omniPrintln();
  printAvailableCommands();
  //printAvailableCommands(BLUETOOTH_TRX);
  //lcd.begin (16, 2);

  //defines the PINs to INPUT or OUTPUT
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  pinMode(RELAY_3, OUTPUT);
  pinMode(RELAY_4, OUTPUT);
  pinMode(RELAY_5, OUTPUT);
  pinMode(RELAY_6, OUTPUT);
  pinMode(RELAY_7, OUTPUT);
  pinMode(RELAY_8, OUTPUT);
  pinMode(RELAY_9, OUTPUT);
  pinMode(RELAY_10, OUTPUT);
  pinMode(RELAY_11, OUTPUT);
  pinMode(RELAY_12, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);      	//defines Button
  pinMode(POT_PIN, INPUT);         	//defines Potentiometer as INPUT
  char myRelayArray [] = {RELAY_1,RELAY_2,RELAY_3,RELAY_4,RELAY_5,RELAY_6,
		  	  	  	RELAY_7,RELAY_8, RELAY_9, RELAY_10,RELAY_11,RELAY_12};
  setRelayArray(myRelayArray);
  relayToggle(0);					//in case of a reset assures that
  	  	  	  	  	  	  	  	  	//the lights won't turn on themselves
}

void loop ()
{
	//DOOR BUTTON
	uint8_t buttonStateControl = doorButtonRead();

	if (serialFlag == false)
	{
		if (buttonStateControl == 0)
		{
			prevButtonStateControl= buttonStateControl;
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
}