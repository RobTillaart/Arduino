#ifndef StopWatch_h
#define StopWatch_h
// 
//    FILE: StopWatch.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Simple StopWatch library for Arduino
// HISTORY: See StopWatch.cpp
//     URL: http://www.arduino.cc/playground/Code/StopWatchClass
//
// Released to the public domain 
//


#define STOPWATCH_LIB_VERSION "0.1.02"

#define STOPWATCH_RESET 0
#define STOPWATCH_RUNNING 1
#define STOPWATCH_STOPPED 2

class StopWatch 
{
public:
	StopWatch();
	void start();
	void stop(); 
	void reset();
	unsigned long value();
	bool isRunning();
	int state();

private:
	int _state;
	unsigned long _starttime;
	unsigned long _stoptime;
};

#endif
// END OF FILE