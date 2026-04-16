#pragma once
//
//    FILE: TCA6408A.h
//  AUTHOR: Rob Tillaart
//    DATE: 2026-04-13
// VERSION: 0.1.0
// PURPOSE: Arduino library for TCA6408A I2C 8 bits IO expander.
//     URL: https://github.com/RobTillaart/TCA6408A_RT
//


#include "Arduino.h"
#include "Wire.h"


#define TCA6408A_LIB_VERSION         (F("0.1.0"))

//  ERROR CODES
//  values <> 0 are errors.
constexpr int TCA6408A_OK            = 0;
constexpr int TCA6408A_REQUEST_ERROR = -11;


class TCA6408A
{
public:
  TCA6408A(uint8_t address = 0x20, TwoWire *wire = &Wire);

  bool     begin();
  bool     isConnected();
  uint8_t  getAddress();


  //  1 = INPUT 0 = OUTPUT
  void     setPinMode8(uint8_t mask);
  uint8_t  getPinMode8();
  void     setPinMode1(uint8_t pin, uint8_t value);
  uint8_t  getPinMode1(uint8_t pin);

  //  1 = INVERTED, 0 = NORMAL.
  void     setPolarity8(uint8_t mask);
  uint8_t  getPolarity8();
  void     setPolarity1(uint8_t pin, uint8_t value);
  uint8_t  getPolarity1(uint8_t pin);

  //  1 = HIGH, 0 = LOW
  void     digitalWrite8(uint8_t mask);
  uint8_t  digitalRead8();
  void     digitalWrite1(uint8_t pin, uint8_t value);
  uint8_t  digitalRead1(uint8_t pin);

  //       DEBUG
  int      getLastError();


private:
  uint8_t  _address = 0;
  TwoWire* _wire = NULL;

  uint8_t _IOMask = 0;

  int     _error = 0;

  int     writeRegister(uint8_t reg, uint8_t value);
  uint8_t readRegister(uint8_t reg);
};


//  -- END OF FILE --





