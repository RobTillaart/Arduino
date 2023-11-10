#pragma once
//
//    FILE: MATRIX7219.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
//    DATE: 2023-07-28
// PURPOSE: Arduino Library for 8x8 LED MATRIX MAX7219
//     URL: https://github.com/RobTillaart/MATRIX7219


#include "Arduino.h"


#define MATRIX7219_LIB_VERSION        (F("0.1.2"))


class MATRIX7219
{
public:
  MATRIX7219(uint8_t dataPin, uint8_t selectPin, uint8_t clockPin, uint8_t matrices = 1);

  uint8_t  getMatrixCount();
  void     begin();

  //  bright = 0..15
  void     setBrightness(uint8_t bright = 2);
  void     displayOff();
  void     displayOn();
  void     displayTest(bool on = false);

  void     clear();
  //  row   = 1..8
  //  value = 0..255
  void     setRow(uint8_t row, uint8_t value, uint8_t matrix);

  void     setInvert(bool invert);
  bool     getInvert();
  void     setReverse(bool reverse);
  bool     getReverse();
  void     setSwap(bool swap);
  bool     getSwap();

protected:

  void     _write(uint8_t b);
  void     _writeZero();         //  optimized  writing of all 0
  uint8_t  _reverse8(uint8_t in);


#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)

  volatile uint8_t *_dataOutRegister;
  uint8_t _dataOutBit;

  volatile uint8_t *_clockRegister;
  uint8_t _clockBit;

#endif

  uint8_t  _dataPin;
  uint8_t  _selectPin;
  uint8_t  _clockPin;
  uint8_t  _matrices;

  bool     _invert  = false;
  bool     _reverse = false;
  bool     _swap    = false;
};



///////////////////////////////////////////////////////////////
//
//  DERIVED MATRIX7221 CLASS
//
class MATRIX7221 : public MATRIX7219
{
public:
  MATRIX7221(uint8_t dataPin, uint8_t selectPin, uint8_t clockPin, uint8_t matrices = 1);
};


//  -- END OF FILE --

