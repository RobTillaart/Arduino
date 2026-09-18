#pragma once
//
//    FILE: runTime.h
//  AUTHOR: Rob Tillaart
//    DATE: 2026-09-16
// VERSION: 0.1.0
// PURPOSE: Arduino library to measure cumulative series of run times.
//     URL: https://github.com/RobTillaart/runTime
//


#include "Arduino.h"


#define RUNTIME_LIB_VERSION         (F("0.1.0"))


class runTime: public Printable
{
public:
  runTime()
  {
    reset();
  }

  //  CONTROL
  void start()
  {
    if (_isRunning == false)
    {
      _startTime = millis();
      _runCount++;
      _isRunning = true;
    }
  }

  void stop()
  {
    update();
    _isRunning = false;
  }

  void update()
  {
    if (_isRunning == true)
    {
      uint32_t now = millis();
      _remainder += (now - _startTime);
      _runTime += (_remainder / 1000);
      _remainder %= 1000;
      _startTime = now;
    }
  }

  void reset(uint32_t startValue = 0)
  {
    _runTime = startValue;
    _remainder = 0;
    _runCount = 0;
    _isRunning = false;
  }

  bool isRunning()
  {
    return _isRunning;
  }


  //  MEASUREMENT
  uint32_t seconds() const
  {
    if (_isRunning)
    {
      return _runTime + (millis() - _startTime) / 1000;
    }
    return _runTime;
  }

  float minutes()
  {
    return seconds() * (1.0 / 60.0);
  }

  float hours()
  {
    return seconds() * (1.0 / 3600.0);
  }

  float days()
  {
    return seconds() * (1.0 / 86400.0);
  }

  uint32_t runCount()
  {
    return _runCount;
  }


  //  STATISTICS
  float averageSeconds()
  {
    if (_runCount == 0) return 0;
    return (1.0 * seconds()) / _runCount;
  }

  float averageMinutes()
  {
    if (_runCount == 0) return 0;
    return (1.0 * minutes()) / _runCount;
  }

  float averageHours()
  {
    if (_runCount == 0) return 0;
    return (1.0 * hours()) / _runCount;
  }

  float averageDays()
  {
    if (_runCount == 0) return 0;
    return (1.0 * days()) / _runCount;
  }

  //  PRINTABLE
  //  layout could be DDDD:HH:MM:SS
  size_t printTo(Print& p) const override
  {
    uint32_t ti = seconds();
    size_t n = p.print(ti);
    n += p.print(" s.");
    return n;
  }

private:
  bool     _isRunning;
  uint32_t _startTime;      //  milliseconds
  uint32_t _runTime;        //  seconds
  uint32_t _remainder;      //  milliseconds
  uint32_t _runCount;       //  idem
};


//  -- END OF FILE --





