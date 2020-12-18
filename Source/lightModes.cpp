/****************************************************************
 * lightModes.ccp - Library for different light modes	 		*
 * Created by D. �kerk, October 15, 2017				 		*
 ****************************************************************/

#include "../Headers/lightModes.h"
//#include "../Headers/mega2560_board.h"
#include <Arduino.h>
#include "../Headers/sensors.h"

class Lights{
	public:
		void setRelayPin(int pin []);
		void randomToggle (void);
		void snakeToggle(void);
		void selectiveToggle(uint8_t []);
		void selectiveToggle(uint8_t, uint8_t);
		void switchSequence(uint8_t);
		void debugSerialPrint(uint8_t); // up to 8 flags can be selected
	private:
		int lightNum; 			// number of lights given the I/O pin array
		int relayArr [];		// array containing the I/O pins
};



uint8_t toggleFlag=255;
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

/********************************************************************************
 *  setRelayArray ()															*
 *  	Description: Sets the relay array with a while cycle. The relay pins 	*
 *  				 MUST be in sequence										*
 *  	Input:	--																*
 *  	Output: --																*
 ********************************************************************************/
void setRelayArray(int auxRelArr [])
{
	lightNum = sizeof(auxRelArr);
	for(int el : auxRelArr)
	{
		relayArr[i] = el;
	}
}

/********************************************************************************
 * switchSequence(uint8_t)														
 * 																				
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
 * 																				
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
*																				
*	Description: Given an exit value "x", randomly toggles one relay at a time	
*	Input: --																	
*	Output: --																	
*********************************************************************************/
void randomToggle()
{
	omniPrintln("Random Toggle Activated");
	relayToggle(0);
	do
	{
	  int r = random(RELAY_ARRAY_MIN_VALUE,RELAY_ARRAY_MAX_VALUE+1);
	  digitalWrite (RelayArray[r], LOW);
	  if (randomToggleDebug==0)
	  {
		  Serial.println("	ON - " + String(r+1) + "	" +
				  analogRead(POT_PIN)+"	" +
				  potInteger(MODES_JUMP,NUMBER_OF_MODES,SINGLE_EDGE_DISCARD));
	  }
	  delay(RANDOM_TOGGLE_ON_DELAY);
	  digitalWrite (RelayArray[r], HIGH);
	  bluetoothCheck();
	  delay(10);
	}
	while (potInteger(MODES_JUMP,NUMBER_OF_MODES, SINGLE_EDGE_DISCARD) == RANDOM || serialValue == RANDOM);
	omniPrintln("Random Toggle OFF");
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
*selectiveToggle(firstOnLight,lastOnLight)										*
*																				*
*	Description: Given an array of booleans, turns ON/OFF in case of 1/0		*
*	Input: (uint8_t,uint8_t)													*
*	Output: --																	*
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