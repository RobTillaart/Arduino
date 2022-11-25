#pragma once
//
//    FILE: StopWatch.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.3
// PURPOSE: Arduino Library implementing a stopwatch including seconds, milliseconds microseconds
// HISTORY: See StopWatch.cpp
//     URL: https://github.com/RobTillaart/StopWatch_RT
//          http://playground.arduino.cc/Code/StopWatchClass
//


#include "Arduino.h"


#define STOPWATCH_LIB_VERSION             (F("0.3.3"))


//  NOTE: adjust divider can fix timing inaccuracies (to some extend)
#ifndef STOPWATCH_SECONDS_DIVIDER
#define STOPWATCH_SECONDS_DIVIDER         1000
#endif

#ifndef STOPWATCH_MINUTES_DIVIDER
#define STOPWATCH_MINUTES_DIVIDER         60000
#endif


class StopWatch: public Printable
{
public:
  enum State      { RESET, RUNNING, STOPPED };
  enum Resolution { MICROS, MILLIS, SECONDS, MINUTES};

  explicit StopWatch(const enum Resolution resolution = MILLIS);
  void     start();
  void     stop();
  void     reset();
  //  elapsed() made const as printTo expect a const object.
  uint32_t elapsed() const;

  bool     isRunning();
  enum     State state() { return _state; };
  void     setResolution(const enum Resolution resolution);
  enum     Resolution resolution() { return _resolution; };

  //  PRINTABLE
  size_t printTo(Print& p) const;


private:
  enum State      _state;
  enum Resolution _resolution;

  uint32_t _starttime;
  uint32_t _stoptime;

  uint32_t (*_gettime)(void);
  static uint32_t _micros()     { return micros(); };   //  wrapper for ESP proc.
  static uint32_t _millis()     { return millis(); };
  static uint32_t seconds()     { return millis() / STOPWATCH_SECONDS_DIVIDER; };
  static uint32_t minutes()     { return millis() / STOPWATCH_MINUTES_DIVIDER; };
};


//  -- END OF FILE --

