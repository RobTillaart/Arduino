#pragma once
//
//    FILE: FastShiftIn.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
// PURPOSE: Fast ShiftIn for 74HC165 register, AVR optimized
//    DATE: 2013-09-29
//     URL: https://github.com/RobTillaart/FastShiftIn
//

#include "Arduino.h"

#define FASTSHIFTIN_LIB_VERSION (F("0.2.1"))

class FastShiftIn
{
public:
  // bitorder = { LSBFIRST, MSBFIRST };
  FastShiftIn(const uint8_t datapin, const uint8_t clockpin, const uint8_t bitOrder = LSBFIRST);
  int read(void);

  // overrule bitorder (most optimized).
  int readLSBFIRST(void);
  int readMSBFIRST(void);

private:
  uint8_t _bitorder;
  int _value;

  uint8_t _databit;
  volatile uint8_t *_datain;

  uint8_t _clockbit;
  volatile uint8_t *_clockin;
};

// -- END OF FILE --
