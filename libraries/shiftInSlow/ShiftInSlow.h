#pragma once
//
//    FILE: ShiftInSlow.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
// PURPOSE: Arduino library for shiftIn with build-in delay
//    DATE: 2021-05-11
//     URL: https://github.com/RobTillaart/ShiftInSlow


#include "Arduino.h"


#define SHIFTINSLOW_LIB_VERSION           (F("0.1.3"))


class ShiftInSlow
{
public:
  //  bitOrder = { LSBFIRST, MSBFIRST }; defined in Arduino.h.
  ShiftInSlow(const uint8_t dataPin, const uint8_t clockPin, const uint8_t  bitOrder = LSBFIRST);

  int      read();
  int      lastRead();

  bool     setBitOrder(const uint8_t bitOrder = LSBFIRST);
  uint8_t  getBitOrder();
  
  void     setDelay(uint16_t microseconds = 0);
  uint16_t getDelay();


private:
  uint8_t  _clockPin = 0;
  uint8_t  _dataPin  = 0;
  uint8_t  _bitOrder = LSBFIRST;
  uint16_t _delay    = 0;
  uint8_t  _value    = 0;
};


//  -- END OF FILE --

