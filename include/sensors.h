/*
 * sensors.h
 *
 *  Created on: 16 ott 2017
 *      Author: Denis
 */

#ifndef SENSORS_H
#define SENSORS_H
#include <Arduino.h>

//Public:
	//Microphone
		extern uint8_t doubleClapFlag;
		extern bool clapFlag;
		extern uint8_t internalClapFlag;

	//Buttons
		extern uint8_t prevButtonStateControl;

	//Methods
		extern uint8_t potInteger(uint16_t,uint8_t, uint8_t);
		extern uint8_t doorButtonRead(void);
		extern void micDoubleClapDetection(void);
		extern void sensorsReset(void);

//Private:
	//Debug variables
		#define doorButtonReadDebug 			1
		#define micDoubleClapDetectionDebug		1
		#define potIntegerDebug					1

	//Hardware
		#define MAX_BIT_VALUE		(1024 - 1)
		#define NUMBER_OF_MODES 	4
		#define NUMBER_OF_RELAYS	13

	//Microphone
		#define MIC_DEBOUNCE_TIME 200   // the debounce time, increase if the output flickers
		#define MIC_MAX_SECOND_CLAP_WAIT_TIME 	1500
		#define MIC_TRIGGER						390


	//ADC Sensibility Percents
		#define SINGLE_EDGE_DISCARD			SINGLE_EDGE_DISCARD_10

		#define SINGLE_EDGE_DISCARD_5		5
		#define SINGLE_EDGE_DISCARD_8		8
		#define SINGLE_EDGE_DISCARD_10		10
		#define SINGLE_EDGE_DISCARD_15		15
#endif /* SENSORS_H */
