#pragma once
//
//    FILE: ShiftOutSlow.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library for shiftOut with build-in delay
//    DATE: 2021-05-11
//     URL: https://github.com/RobTillaart/ShiftOutSlow
//


#include "Arduino.h"


#define SHIFTOUTSLOW_LIB_VERSION (F("0.1.0"))


class ShiftOutSlow : public Print
{
public:
  // bitorder = { LSBFIRST, MSBFIRST };
  ShiftOutSlow(const uint8_t dataPin, const uint8_t clockPin, const uint8_t  bitOrder = LSBFIRST);

  size_t   write(const uint8_t data);
  uint8_t  lastWritten(void) { return _value; };

  bool     setBitOrder(const uint8_t bitOrder);
  uint8_t  getBitOrder(void) { return _bitOrder; };
  
  void     setDelay(uint16_t d) { _delay = d; };
  uint16_t getDelay() { return _delay; };


private:
  uint8_t  _clockPin = 0  ;
  uint8_t  _dataPin  = 0;
  uint8_t  _bitOrder = LSBFIRST;
  uint16_t _delay    = 0;
  uint8_t  _value    = 0;
};

// -- END OF FILE --
