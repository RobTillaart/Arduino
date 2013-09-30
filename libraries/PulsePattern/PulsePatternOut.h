#ifndef Histogram_h
#define PulsePatternOut_h
// 
//    FILE: PulsePatternOut.h
//  AUTHOR: Rob dot Tillaart at gmail dot com  
// PURPOSE: PulsePatternOut library for Arduino
//          sends out a pulse pattern over a digital pin
// HISTORY: See PulsePatternOut.cpp
//
// Released to the public domain
//

#include <inttypes.h>

#define PULSEPATTERNOUT_LIB_VERSION "0.0.1"

#define STOPPED 0
#define RUNNING 1


class PulsePatternOut 
{
	public:
	PulsePatternOut(uint8_t pin);
	~PulsePatternOut();
	void init(uint16_t * ar, uint8_t size, uint8_t level);
	void start();
	void stop();
	bool isRunning();
	void worker();
	
protected:

	void stopTimer();
	void setTimer(uint16_t cc);
	
	uint16_t * _ar;
	uint8_t _size;
	uint8_t _pin;
	volatile uint8_t _level;
	volatile uint8_t _state;
	volatile uint8_t _cnt;
};

#endif
// END OF FILE