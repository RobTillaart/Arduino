#pragma once
//
//    FILE: FastShiftIn.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.1
// PURPOSE: Fast ShiftIn for 74HC165 register, AVR optimized
//    DATE: 2013-09-29
//     URL: https://github.com/RobTillaart/FastShiftIn


#include "Arduino.h"


#define FASTSHIFTIN_LIB_VERSION         (F("0.3.1"))


class FastShiftIn
{
public:
  //  bitOrder = { LSBFIRST, MSBFIRST };
  FastShiftIn(uint8_t dataIn, uint8_t clockPin, uint8_t bitOrder = LSBFIRST);

  int     read(void);
  int     lastRead(void);

  bool    setBitOrder(uint8_t bitOrder);
  uint8_t getBitOrder(void);

  //  overrule bitOrder (most optimized).
  int     readLSBFIRST(void);
  int     readMSBFIRST(void);

private:
  uint8_t _bitOrder;
  int     _value;
  
#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)

  volatile uint8_t *_dataInRegister;
  uint8_t _dataInBit;

  volatile uint8_t *_clockRegister;
  uint8_t _clockBit;

#else

  uint8_t _dataPinIn;
  uint8_t _clockPin;

#endif
};


// -- END OF FILE --

