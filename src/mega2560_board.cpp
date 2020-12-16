/*
 * mega2560_board.cpp
 *
 *  Created on: 01 nov 2017
 *      Author: Denis
 */
#include <Arduino.h>
#include "../Headers/mega2560_board.h"

//Variables Initialization
#define RELAY_ARRAY_MAX_VALUE 	RELAY_TOTAL_NUMBER-1
#define RELAY_ARRAY_MIN_VALUE 	0

	char RelayArray[] = {0,0,0,0,0,0,0,0,0,0,0,0};


/********************************************************************************
 *  setRelayArray ()															*
 *  	Description: Sets the relay array with a while cycle. The relay pins 	*
 *  				 MUST be in sequence										*
 *  	Input:	--																*
 *  	Output: --																*
 ********************************************************************************/

void setRelayArray(char auxiliaryRelayArray [])
{
	for(uint8_t i = 0; i<=RELAY_TOTAL_NUMBER; i++)
	{
		RelayArray[i] = auxiliaryRelayArray[i];
	}
}

