/****************************************************************
 * lightModes.h - light modes header							*
 * Created by D. �kerk, October 15, 2017				 		*
 ****************************************************************/

#ifndef LIGHTMODES_H_
#define LIGHTMODES_H_

#include <Arduino.h>
#include "lightModes.h"
#include "mega2560_board.h"
#include "sensors.h"
#include "serialCommands.h"

//DEBUG values
	#define relayToggleDebug 	1
	#define randomToggleDebug 	1
	#define snakeToggleDebug	1
	#define switchSequenceDebug	1
	#define selectiveRelayDebug	1

/****************************************************************************************
 * switchModeCases(uint8_t)                                                          	*
 ****************************************************************************************/
	#define ON 		1
	#define RANDOM	2
	#define SNAKE	3
	#define OFF		4
	#define COUCH 	5
	#define BED		6
	#define ALCOHOL	7
	#define DESK	8

	#define SWITCH_MODE_CASES_NUMBER 8

/**************************************************************************************
 * snakeToggle()                                                              		  *
 **************************************************************************************/

	#define PROGRESSION_DELAY		140
	extern void snakeToggle(void);

/**************************************************************************************
 * relayToggle                                                                        *
 **************************************************************************************/

	#define DELAY_TOGGLE_SEQUENCE 	50
	extern void relayToggle(uint8_t);

/**************************************************************************************
 * randomToggle                                                                        *
 **************************************************************************************/
	#define RANDOM_TOGGLE_ON_DELAY	170
	extern void randomToggle(void);

/*****************************************************************************************
 * Given an integer (j) the method selects the equivalent mode case                      *
 *****************************************************************************************/
	#define MODES_JUMP			((MAX_BIT_VALUE+1)/NUMBER_OF_MODES)
	extern void switchModeCases(uint8_t);

/****************************************************************************************
 * relayToggle(uint8_t)																	*
 * 																						*
 * 		Description: Given an integer (j) the method turns on every led till the j one  *
 * 		Input: uint8_t from 0 to RELAY_ARRAY_MAX_VALUE									*
 * 		Output:--																		*
 ****************************************************************************************/
	#define SEQ_JUMP			(MAX_BIT_VALUE/NUMBER_OF_RELAYS)
	extern void switchSequence(uint8_t);

/**************************************************************************************
 * selectiveToggle                                                                        *
 **************************************************************************************/
	extern void selectiveToggle(uint8_t []);
	extern void selectiveToggle(uint8_t, uint8_t);

	//Patterns
	extern uint8_t lightsStateArray1 [];
	extern uint8_t lightsStateArray2 [];
	extern uint8_t lightsStateArray3 [];


#endif /*LIGHTMODES_H_ */
