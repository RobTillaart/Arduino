#pragma once
//
//    FILE: FastShiftInOut.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library for (AVR) optimized shiftInOut (simultaneously)
//     URL: https://github.com/RobTillaart/FastShiftInOut


#include "Arduino.h"

#define FASTSHIFTINOUT_LIB_VERSION        (F("0.1.0"))


class FastShiftInOut
{
public:
  //  bitOrder = { LSBFIRST, MSBFIRST };
  FastShiftInOut(uint8_t dataIn, uint8_t dataOut, uint8_t clockPin, uint8_t bitOrder = LSBFIRST);

  //  reads and writes simultaneously
  uint8_t write(uint8_t data);
  uint8_t lastWritten(void);

  bool    setBitOrder(uint8_t bitOrder);
  uint8_t getBitOrder(void);

  // overrule bitOrder (most optimized).
  uint8_t writeLSBFIRST(uint8_t data);
  uint8_t writeMSBFIRST(uint8_t data);

private:
  uint8_t _bitOrder;
  int     _value;

  uint8_t _dataPinIn;
  volatile uint8_t *_dataIn;

  uint8_t _dataPinOut;
  volatile uint8_t *_dataOut;

  uint8_t _clockPin;
  volatile uint8_t *_clockOut;
};


// -- END OF FILE --
