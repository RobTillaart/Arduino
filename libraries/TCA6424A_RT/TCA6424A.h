#pragma once
//
//    FILE: TCA6424A.h
//  AUTHOR: Rob Tillaart
//    DATE: 2026-04-13
// VERSION: 0.1.0
// PURPOSE: Arduino library for TCA6424A I2C 16 bits IO expander.
//     URL: https://github.com/RobTillaart/TCA6424A_RT
//


#include "Arduino.h"
#include "Wire.h"


#define TCA6424A_LIB_VERSION         (F("0.1.0"))

//  ERROR CODES
//  values <> 0 are errors.
constexpr int TCA6424A_OK            = 0;
constexpr int TCA6424A_REQUEST_ERROR = -11;


class TCA6424A
{
public:
  TCA6424A(uint8_t address = 0x20, TwoWire *wire = &Wire);

  bool     begin();
  bool     isConnected();
  uint8_t  getAddress();


  //  1 = INPUT 0 = OUTPUT
  void     setPinMode24(uint32_t mask);
  uint32_t getPinMode24();
  void     setPinMode1(uint8_t pin, uint8_t value);
  uint8_t  getPinMode1(uint8_t pin);

  //  1 = INVERTED, 0 = NORMAL.
  void     setPolarity24(uint32_t mask);
  uint32_t getPolarity24();
  void     setPolarity1(uint8_t pin, uint8_t value);
  uint8_t  getPolarity1(uint8_t pin);

  //  1 = HIGH, 0 = LOW
  void     digitalWrite24(uint32_t mask);
  uint32_t digitalRead24();
  void     digitalWrite1(uint8_t pin, uint8_t value);
  uint8_t  digitalRead1(uint8_t pin);

  //       DEBUG
  int      getLastError();


private:
  uint8_t  _address = 0;
  TwoWire* _wire = NULL;

  uint32_t _IOMask = 0;
  int      _error = 0;

  int      writeRegister(uint8_t reg, uint32_t value);
  uint32_t readRegister(uint8_t reg);
};


//  -- END OF FILE --





