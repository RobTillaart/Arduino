#pragma once
//
//    FILE: FastShiftIn.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.4
// PURPOSE: Fast ShiftIn for 74HC165 register, AVR optimized
//    DATE: 2013-09-29
//     URL: https://github.com/RobTillaart/FastShiftIn


#include "Arduino.h"


#define FASTSHIFTIN_LIB_VERSION         (F("0.3.4"))


class FastShiftIn
{
public:
  //  bitOrder = { LSBFIRST, MSBFIRST };
  FastShiftIn(uint8_t dataIn, uint8_t clockPin, uint8_t bitOrder = LSBFIRST);

  uint16_t read(void);
  uint16_t read16(void);
  uint32_t read24(void);
  uint32_t read32(void);
  uint32_t lastRead(void);

  //  Experimental 0.3.4
  void     read(uint8_t * array, uint8_t size);

  //  returns false if bitOrder out of range.
  bool     setBitOrder(uint8_t bitOrder);
  uint8_t  getBitOrder(void);

  //  overrule bitOrder (most optimized).
  uint8_t  readLSBFIRST(void);
  uint8_t  readMSBFIRST(void);

private:
  uint8_t  _bitOrder;
  uint32_t _lastValue;

#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)

  volatile uint8_t *_dataInRegister;
  uint8_t  _dataInBit;

  volatile uint8_t *_clockRegister;
  uint8_t  _clockBit;

#else

  uint8_t  _dataPinIn;
  uint8_t  _clockPin;

#endif
};


//  -- END OF FILE --

