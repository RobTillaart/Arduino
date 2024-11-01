#pragma once
//
//    FILE: FastShiftInOut.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
// PURPOSE: Arduino library for (AVR) optimized shiftInOut (simultaneously)
//     URL: https://github.com/RobTillaart/FastShiftInOut


#include "Arduino.h"


#define FASTSHIFTINOUT_LIB_VERSION        (F("0.2.1"))

//  uncomment next line to get SPEED OPTIMIZED CODE
//  #define FASTSHIFTINOUT_AVR_LOOP_UNROLLED    1


class FastShiftInOut
{
public:
  //  bitOrder = { LSBFIRST, MSBFIRST };
  FastShiftInOut(uint8_t dataIn, uint8_t dataOut, uint8_t clockPin, uint8_t bitOrder = LSBFIRST);

  //  reads and writes simultaneously
  uint8_t write(uint8_t data);

  uint8_t lastWritten(void);
  uint8_t lastRead(void);

  bool    setBitOrder(uint8_t bitOrder);
  uint8_t getBitOrder(void);

  //  overrule bitOrder (most optimized).
  uint8_t writeLSBFIRST(uint8_t data);
  uint8_t writeMSBFIRST(uint8_t data);

private:
  uint8_t _bitOrder;
  int     _lastValue;
  int     _lastRead;

#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)

  volatile uint8_t *_dataInRegister;
  uint8_t _dataInBit;

  volatile uint8_t *_dataOutRegister;
  uint8_t _dataOutBit;

  volatile uint8_t *_clockRegister;
  uint8_t _clockBit;

#else

  uint8_t _dataPinIn;
  uint8_t _dataPinOut;
  uint8_t _clockPin;

#endif
};


//  -- END OF FILE --

