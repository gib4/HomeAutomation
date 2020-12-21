/****************************************************************
 * lightModes.h - light modes header							*
 * Created by D. �kerk, October 15, 2017				 		*
 ****************************************************************/

#ifndef LIGHTMODES_H_
#define LIGHTMODES_H_

#include <Arduino.h>
#include "sensors.h"
#include "serialCommands.h"

class Lights{
	public:
		void setRelayPins(int []);
		void delayInit(int, int, int);
		void randomToggle ();
		void snakeToggle();
		void selectiveToggle(uint8_t []);
		void selectiveToggle(uint8_t, uint8_t);
		void switchSequence(uint8_t);
		
		// Print 
		void printAvailableCommands();
		void debugSerialPrint(bool); // up to 8 flags can be selected
		void omniPrint(String);
		void omniPrintln(String);
		void omniPrint(uint8_t);
		void omniPrintln(uint8_t);
		void boardPin ();

		enum modes:{ON, RANDOM, SNAKE, OFF, COUCH, BED, ALCOHOL, DESK}
		#define SWITCH_MODE_CASES_NUMBER 8

	private:
		extern int relayArr[];			// array containing the I/O pins
		extern int lightNum; 			// number of lights given the I/O pin array
		extern int delaySnake;
		extern int delayRelay;
		extern int delayRandom;
		bool relayToggleDebug 	= false;
		bool randomToggleDebug 	= false;
		bool snakeToggleDebug	= false;
		bool switchSequenceDebug	= false;
		bool selectiveRelayDebug	= false;
};

#endif /*LIGHTMODES_H_ */