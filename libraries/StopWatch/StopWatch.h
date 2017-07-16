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

#define STOPWATCH_LIB_VERSION "0.1.4"

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class StopWatch
{
public:
  enum State      { RESET, RUNNING, STOPPED };
  enum Resolution { MILLIS, MICROS, SECONDS };

  explicit StopWatch(const enum Resolution res = MILLIS);
  void start();
  void stop();
  void reset();

  uint32_t value();
  uint32_t elapsed() const           { return value(); };

  bool isRunning() const             { return _state == StopWatch::RUNNING; };
  enum State state() const           { return _state; };
  enum Resolution resolution() const { return _res; };

private:
  enum State _state;
  enum Resolution _res;

  uint32_t _starttime;
  uint32_t _stoptime;

  uint32_t (*_gettime)(void);
  static uint32_t seconds()          { return millis() / 1000; };
};

#endif
// END OF FILE