#pragma once
//
//    FILE: StopWatch.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.2
// PURPOSE: Arduino Library implementing a stopwatch including seconds, milliseconds microseconds
// HISTORY: See StopWatch.cpp
//     URL: https://github.com/RobTillaart/StopWatch_RT
//          http://playground.arduino.cc/Code/StopWatchClass
//

#include "Arduino.h"

#define STOPWATCH_LIB_VERSION (F("0.2.2"))

  // note - adjust divider can fix timing inaccuracies (to some extend)
#ifndef STOPWATCH_SECONDS_DIVIDER
#define STOPWATCH_SECONDS_DIVIDER 1000
#endif

#ifndef STOPWATCH_MINUTES_DIVIDER
#define STOPWATCH_MINUTES_DIVIDER 60000
#endif

class StopWatch
{
public:
  enum State      { RESET, RUNNING, STOPPED };
  enum Resolution { MICROS, MILLIS, SECONDS, MINUTES};

  explicit StopWatch(const enum Resolution res = MILLIS);
  void start();
  void stop();
  void reset();
  uint32_t elapsed();

  bool isRunning() { return _state == StopWatch::RUNNING; };
  enum State state() { return _state; };
 
  void setResolution(const enum Resolution res);
  enum Resolution resolution() { return _res; };

  // value will become obsolete in the future, elapsed() is more descriptive
  uint32_t value() { return elapsed(); };

private:
  enum State _state;
  enum Resolution _res;

  uint32_t _starttime;
  uint32_t _stoptime;

  uint32_t (*_gettime)(void);
  static uint32_t _micros()     { return micros(); };   // wrapper for ESP proc.
  static uint32_t _millis()     { return millis(); };
  static uint32_t seconds()     { return millis() / STOPWATCH_SECONDS_DIVIDER; };
  static uint32_t minutes()     { return millis() / STOPWATCH_MINUTES_DIVIDER; };
};

// -- END OF FILE --
