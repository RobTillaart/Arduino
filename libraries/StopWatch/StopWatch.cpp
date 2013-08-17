// 
//    FILE: StopWatch.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.02
// PURPOSE: Simple StopWatch library for Arduino
//
// The library is based upon millis() and therefor has the same restrictions as millis() has wrt overflow.
//
// HISTORY: 
// 0.1.00 - 2011-01-04 initial version
// 0.1.01 - 2011-01-04 Added better state
// 0.1.02 - 2011-06-15 Added state() + #defines + lib version
// 
// Released to the public domain 
//

#include "StopWatch.h"
#include "wiring.h"

StopWatch::StopWatch()
{
	reset();
}

void StopWatch::reset()
{
	_state = STOPWATCH_RESET;
	_starttime = _stoptime = 0;
}

void StopWatch::start()
{
	if (STOPWATCH_RESET == _state || STOPWATCH_STOPPED == _state)
	{
		_state = STOPWATCH_RUNNING;
		unsigned long t = millis();
		_starttime += t - _stoptime;
		_stoptime = t;
	}
}

unsigned long StopWatch::value()
{
	if (STOPWATCH_RUNNING == _state) _stoptime = millis();
	return _stoptime - _starttime;
}

void StopWatch::stop()
{
	if (STOPWATCH_RUNNING == _state)
	{
		_state = STOPWATCH_STOPPED;
		_stoptime = millis();
	}
}

bool StopWatch::isRunning()
{
	return (STOPWATCH_RUNNING == _state);
}

int StopWatch::state()
{
	return _state;
}

// END OF FILE