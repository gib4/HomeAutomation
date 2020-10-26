/****************************************************************
 * sensors.ccp - defines all sensors and values			 		*
 * Created by D. Škerk, October 15, 2017				 		*
 ****************************************************************/

#include "../Headers/sensors.h"

#include <Time.h>
#include <Arduino.h>

#include "../Headers/lightModes.h"
#include "../Headers/mega2560_board.h"
#include "../Headers/serialCommands.h"

//LOCAL VARIABLES
	//Clap Variables
		 int currentMicInputValue = 0;
		 uint8_t clapCount = 0;
		 uint8_t micFlag = 0;
		 uint8_t doubleClapFlag = 0;
		 uint8_t internalClapFlag = 0;
		 bool clapFlag = 0;
		 unsigned long previousMillis = 0;
		 unsigned long currentMillis = 0;
	//Button Variables
		 uint8_t prevButtonState = LOW;
		 uint8_t prevButtonStateControl = HIGH;
	//potInteger Variables
	 	 uint16_t currentPotAnalogValue = 0;
	 	 uint16_t previousPotAnalogValue = 0;
		 uint8_t previousPotDigitalValue = 0;

/********************************************************************************
 *  sensorReset(void)															*
 *  	Description: Resets the values to 0 of all sensor-related variables		*
 *  	Input:	--																*
 *  	Output: --																*
 ********************************************************************************/
void sensorsReset(void)
{
	 currentMicInputValue = 0;
	 clapCount = 0;
	 micFlag = 0;
	 previousMillis = 0;
	 currentMillis = 0;
	 prevButtonState = LOW;
	 currentPotAnalogValue = 0;
	 previousPotAnalogValue = 0;
	 previousPotDigitalValue = 0;
	 doubleClapFlag = 0;
}


/********************************************************************************
 *  potInteger (jump, multiplier, edgePercentDiscard)							*
 *  	Description: Converts the potentiometer value into "multiplier" cases	*
 *  				 edgePercentDiscard is a percent value that discards the 	*
 *  				 values on the edges to compensate the fluctuations of the	*
 *  				 value.	The value influences the upper and lower bound.		*
 *  	Input:	uint16_t jump, uint8_t multiplier, uint8_t edgePercentDiscard	*
 *  	Output: uint8_t from potentiometer value to Mode number					*
 ********************************************************************************/

uint8_t potInteger(uint16_t jump, uint8_t multiplier, uint8_t edgeDiscard)
{
	currentPotAnalogValue = analogRead(POT_PIN);
	if(potIntegerDebug==0)	Serial.println(currentPotAnalogValue);
	if(currentPotAnalogValue < (previousPotAnalogValue-edgeDiscard)
			|| currentPotAnalogValue > (previousPotAnalogValue+edgeDiscard))
	{
		for(uint8_t i = 0; i< multiplier; i++)
		{
			if((currentPotAnalogValue >= (i*jump))
					&& (currentPotAnalogValue < ((i+1)*jump)))
			{
				previousPotAnalogValue = currentPotAnalogValue;
				previousPotDigitalValue = i+1;
				return previousPotDigitalValue;
			}
		}
	}
	return previousPotDigitalValue;
}


/********************************************************************************
 *  uint8_t doorButtonRead (void)												*
 *  	Description: Checks button state and returns a value					*
 *  	Input:	--																*
 *  	Output: o = ON, 1 = OFF, 255 = error occured during	reading				*
 ********************************************************************************/
uint8_t doorButtonRead(void)
{

	uint8_t buttonState = digitalRead (BUTTON_PIN);
	if (buttonState == HIGH)
	{

		if(prevButtonState!=buttonState)
		{
			Serial.println ("buttonState = ON");
			//SerialLCD.println ("buttonState = ON");
		}
		prevButtonState = buttonState;
		return 0;
	}
	else
	{
		if(prevButtonState!=buttonState)
			{
			Serial.println ("buttonState = OFF");
			//SerialLCD.println ("buttonState = OFF");
			}
		prevButtonState = buttonState;
		return 1;
	}
}


/********************************************************************************
 * boolean micDoubleClapDetection(void)											*
 *  	Description: Checks if a double clap was detected. During listening 	*
 *  				 changes uint8_t micFlag to 1 (1 clap), 2 (2 claps)			*
 *  				 or 0 (to reset the counter value)							*
 *  	Input:	--																*
 *  	Output: --																*
 ********************************************************************************/
 void micDoubleClapDetection(void)
 {
	 currentMicInputValue = analogRead(MIC_PIN);
 	 if ((currentMicInputValue >= MIC_TRIGGER) && (micFlag == 0))
 	 {
 		 previousMillis = millis();
 		 micFlag = 1;
 		 Serial.println("Waiting second clap...");
 		 //SerialLCD.print("Waiting second clap...");
 		 if(micDoubleClapDetectionDebug==0) Serial.println("		" + String(currentMicInputValue));
 	 }
 	 else if ((currentMicInputValue >= MIC_TRIGGER) && (micFlag == 1) && (millis() - previousMillis > MIC_DEBOUNCE_TIME))
 	 {
 		 micFlag = 2;
 		 doubleClapFlag = 0;
 		 Serial.println("Claps detected!	" + String() +" ms");
 		 //SerialLCD.println("Claps detected!	" + String() +" ms");
 		 if(micDoubleClapDetectionDebug==0) Serial.println("		" + String(currentMicInputValue));
 		 internalClapFlag = true;
 	 }
 	 else if (((millis() - previousMillis) > MIC_MAX_SECOND_CLAP_WAIT_TIME) && micFlag!=0)
 	 {
 		 micFlag = 0;
 		 if(micFlag==1)	 Serial.println("No second clap no party...");
 		 doubleClapFlag = 1;
 	 }

 	if(doubleClapFlag==0)
 	{
 		if(internalClapFlag==0)
 			{
 			//digitalWrite (13,HIGH);
 			internalClapFlag = 1;
 			}
 		else if(internalClapFlag==1)
 			{
 			//digitalWrite (13,LOW);
 			internalClapFlag = 0;
 			}
 	}
 }
