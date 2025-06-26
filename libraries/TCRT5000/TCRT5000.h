#pragma once
//
//    FILE: TCRT5000.h
//  AUTHOR: Rob Tillaart
//    DATE: 2025-02-23
// VERSION: 0.1.0
// PURPOSE: Arduino library for the TCRT5000 reflective optical sensor (IR).
//     URL: https://github.com/RobTillaart/TCRT5000
//


#include "Arduino.h"


#define TCRT5000_LIB_VERSION              (F("0.1.0"))

#ifndef TCRT5000_DEFAULT_THRESHOLD
#define TCRT5000_DEFAULT_THRESHOLD        500
#endif


class TCRT5000
{
public:
  TCRT5000(uint8_t analogPin)
  {
    _pin = analogPin;
  }

  int read()
  {
    _lastRead = analogRead(_pin);
    return _lastRead;
  }

  int lastRead()
  {
    return _lastRead;
  }

  void setThreshold(int threshold)
  {
    _threshold = threshold;
  }

  int getThreshold()
  {
    return _threshold;
  }

  bool aboveThreshold()
  {
    return this->read() > _threshold;
  }

  bool belowThreshold()
  {
    return this->read() <= _threshold;
  }

private:
  uint8_t  _pin;
  int      _threshold = TCRT5000_DEFAULT_THRESHOLD;
  int      _lastRead = 0;
};


//  -- END OF FILE --





