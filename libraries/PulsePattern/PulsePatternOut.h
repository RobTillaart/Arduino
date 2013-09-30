#ifndef Histogram_h
#define PulsePatternOut_h
// 
//    FILE: PulsePatternOut.h
//  AUTHOR: Rob dot Tillaart at gmail dot com  
// PURPOSE: PulsePatternOut library for Arduino
//          sends a pulse pattern to a digital pin (continuously)
// HISTORY: See PulsePatternOut.cpp
//
// Released to the public domain
//

#include <inttypes.h>

#define PULSEPATTERNOUT_LIB_VERSION "0.0.3"

#define NOTINIT -1
#define STOPPED 0
#define RUNNING 1

class PulsePatternOut 
{
	public:
	PulsePatternOut();
	
	void init(uint8_t pin, uint16_t * ar, uint8_t size, uint8_t level);
	void start();
	void stop();
	bool isRunning();
	
private:
	void worker();
	
	void stopTimer();
	void setTimer(uint16_t cc);
	
	uint16_t * _ar;
	uint8_t _size;
	uint8_t _pin;
	volatile uint8_t _level;
	volatile int8_t _state;
	volatile uint8_t _cnt;
};

static PulsePatternOut PPO;

#endif
// END OF FILE