#pragma once
//
//    FILE: FastShiftOut.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.2
// PURPOSE: shiftout that implements the Print interface
//    DATE: 2013-08-22
//     URL: https://github.com/RobTillaart/FastShiftOut
//

#include "Arduino.h"
#include "Print.h"

#define FASTSHIFTOUT_LIB_VERSION (F("0.2.2"))

class FastShiftOut : public Print
{
public:
  // bitorder = { LSBFIRST, MSBFIRST };
  FastShiftOut(const uint8_t datapin, const uint8_t clockpin, const uint8_t bitOrder = LSBFIRST);
  size_t  write(const uint8_t data);
  uint8_t lastWritten(void) { return _value; };

  bool    setBitOrder(const uint8_t bitOrder);
  uint8_t getBitOrder(void) { return _bitorder; };

  // overrule bitorder (most optimized).
  size_t  writeLSBFIRST(const uint8_t data);
  size_t  writeMSBFIRST(const uint8_t data);

private:
  uint8_t _bitorder;
  int     _value;

  uint8_t _databit;
  volatile uint8_t *_dataout;

  uint8_t _clockbit;
  volatile uint8_t *_clockout;
};

// -- END OF FILE --
