#pragma once
//
//    FILE: CountDown.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.3
// PURPOSE: CountDown library for Arduino
//     URL: https://github.com/RobTillaart/CountDown


#include "Arduino.h"

#define COUNTDOWN_LIB_VERSION               (F("0.3.3"))


class CountDown
{
public:
  enum Resolution { MICROS = 'u', MILLIS = 'm', SECONDS = 's', MINUTES = 'M' };

  explicit CountDown(const enum Resolution res = MILLIS);

  void     setResolution(const enum Resolution res = MILLIS);
  enum     Resolution resolution() { return _res; };
  char     getUnits();

  //  one need to set the resolution before calling start(ticks).
  bool     start(uint32_t ticks);
  //  Implicit set resolution to SECONDS.
  bool     start(uint8_t days, uint16_t hours, uint32_t minutes, uint32_t seconds);
  //  Implicit set resolution to MINUTES.
  bool     start(uint8_t days, uint16_t hours, uint32_t minutes);

  void     stop();
  void     cont();
  void     restart();

  uint32_t remaining();
  bool     isRunning();
  bool     isStopped();


private:
  enum State { RUNNING, STOPPED };

  uint32_t        _ticks;
  uint32_t        _remaining;
  enum State      _state;
  enum Resolution _res;
  uint32_t        _startTime;
  void            calcRemaining();
};


//  -- END OF FILE --

