/*
 * mega2560_board.h
 *
 *  Created on: 15 ott 2017
 *      Author: Denis
 */

#ifndef MEGA2560_BOARD_H
#define MEGA2560_BOARD_H

#include "../Headers/LiquidCrystal.h"
/*****************************************************************************************
 * HARDWARE SET-UP                                                       				 *
 *****************************************************************************************/
	//Relay digital pins
	 #define RELAY_1 	23
	 #define RELAY_2 	25
	 #define RELAY_3 	27
	 #define RELAY_4 	29
	 #define RELAY_5 	31
	 #define RELAY_6 	33
	 #define RELAY_7 	35
	 #define RELAY_8 	37
	 #define RELAY_9 	39
	 #define RELAY_10 	41
	 #define RELAY_11 	43
	 #define RELAY_12 	45

	//Sensors PINs
	 #define MIC_PIN 		A0          //microphone analog pin
	 #define BUTTON_PIN 	53         	//button near potentiometer
	 #define POT_PIN 		A1          //potentiometer

	 //DELAYS
	 #define ANTI_RELAY_FLICKER_DELAY	500

//public:
	//VARIABLES
		extern char RelayArray[];

		//LCD
		const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
		//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

	//METHODS
		extern void setRelayArray(char[]);

//private:
	 //const uint8_t relayArraySize1 = sizeof(RelayArray);
	 #define RELAY_TOTAL_NUMBER		12


#endif /* MEGA2560_BOARD_H */
