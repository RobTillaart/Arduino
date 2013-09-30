#ifndef StopWatch_h
#define StopWatch_h
// 
//    FILE: StopWatch.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Simple StopWatch library for Arduino
// HISTORY: See StopWatch.cpp
//     URL: http://playground.arduino.cc/Code/StopWatchClass
//
// Released to the public domain
//

#define STOPWATCH_LIB_VERSION "0.1.03"

#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

class StopWatch 
{
public:
    enum State { RESET, RUNNING, STOPPED };
    enum Resolution { MILLIS, MICROS, SECONDS };
    StopWatch(enum Resolution res = MILLIS);
    void start();
    void stop(); 
    void reset();
    unsigned long value();
    unsigned long elapsed() { return value(); };
    bool isRunning();
    enum State state();
    enum Resolution resolution() { return _res; };

private:
    enum State _state;
    enum Resolution _res;
    unsigned long _starttime;
    unsigned long _stoptime;
    unsigned long (*_gettime)(void);
    static unsigned long seconds() { return millis()/1000; };
};

#endif
// END OF FILE