#pragma once
//
//    FILE: ShiftOutSlow.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.5
// PURPOSE: Arduino library for shiftOut with build-in delay
//    DATE: 2021-05-11
//     URL: https://github.com/RobTillaart/ShiftOutSlow


#include "Arduino.h"


#define SHIFTOUTSLOW_LIB_VERSION            (F("0.1.5"))


class ShiftOutSlow : public Print
{
public:
  //  bitOrder = { LSBFIRST, MSBFIRST };  defined in Arduino.h
  ShiftOutSlow(const uint8_t dataPin, const uint8_t clockPin, const uint8_t  bitOrder = LSBFIRST);

  //  PRINT INTERFACE
  virtual size_t write(const uint8_t data) override;
  virtual size_t write(const uint8_t *buffer, size_t size) override;

  uint8_t  lastWritten();

  bool     setBitOrder(const uint8_t bitOrder = LSBFIRST);
  uint8_t  getBitOrder();

  //  microSeconds = 0..65535
  void     setDelay(uint16_t microSeconds = 0);
  uint16_t getDelay();


private:
  uint8_t  _clockPin = 0;
  uint8_t  _dataPin  = 0;
  uint8_t  _bitOrder = LSBFIRST;
  uint16_t _delay    = 0;
  uint8_t  _value    = 0;
};


//  -- END OF FILE --

