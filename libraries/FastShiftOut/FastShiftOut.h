#pragma once
//
//    FILE: FastShiftOut.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.2
// PURPOSE: shiftOut class that implements the Print interface
//    DATE: 2013-08-22
//     URL: https://github.com/RobTillaart/FastShiftOut


#include "Arduino.h"
#include "Print.h"

#define FASTSHIFTOUT_LIB_VERSION        (F("0.3.2"))


class FastShiftOut : public Print
{
public:
  // bitOrder = { LSBFIRST, MSBFIRST };
  FastShiftOut(uint8_t dataOut, uint8_t clockPin, uint8_t bitOrder = LSBFIRST);

  size_t  write(uint8_t data);
  //  experimental
  //  size_t write(const uint8_t \*buffer, size_t size);
  uint8_t lastWritten(void);

  bool    setBitOrder(uint8_t bitOrder);
  uint8_t getBitOrder(void);

  // overrule bitOrder (most optimized).
  size_t  writeLSBFIRST(uint8_t data);
  size_t  writeMSBFIRST(uint8_t data);

private:
  uint8_t _bitOrder;
  int     _lastValue;


#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)

  volatile uint8_t *_dataOutRegister;
  uint8_t _dataOutBit;

  volatile uint8_t *_clockRegister;
  uint8_t _clockBit;

#else

  uint8_t _dataPinOut;
  uint8_t _clockPin;

#endif
};


// -- END OF FILE --
