#pragma once
//
//    FILE: ADG2128.h
//  AUTHOR: Rob Tillaart
//    DATE: 2025-02-28
// VERSION: 0.1.0
// PURPOSE: Arduino library for ADG2128 8x12 (cross-point) matrix switch with I2C.
//     URL: https://github.com/RobTillaart/ADG2128
//


#include "Arduino.h"
#include "Wire.h"


#define ADG2128_LIB_VERSION             (F("0.1.0"))

#define ADG2128_DEFAULT_ADDRESS         0x70

//  ERROR CODES
//  values <> 0 are errors.
#define ADG2128_OK                      0x00
#define ADG2128_CRC_ERROR               0x01
#define ADG2128_NOT_READY               0x10
#define ADG2128_REQUEST_ERROR           0x11


class ADG2128
{
public:
  ADG2128(uint8_t address = ADG2128_DEFAULT_ADDRESS, TwoWire *wire = &Wire);

  bool     begin();
  bool     isConnected();
  uint8_t  getAddress();


  //  SWITCH
  void     on(uint8_t row, uint8_t col);
  void     off(uint8_t row, uint8_t col);
  bool     isOn(uint8_t row, uint8_t col);
  uint8_t  isOnMask(uint8_t col);  //  get a whole column at once as bit mask.

  //  WRAPPERS.
  void     on(uint8_t sw)   { on(sw / 12, sw % 12); };
  void     off(uint8_t sw)  { off(sw / 12, sw % 12); };
  uint8_t  isOn(uint8_t sw) { return isOn(sw / 12, sw % 12); };


  //  MODE
  //  default direct (transparent) mode
  void     setMode(bool latched = false);
  bool     isLatchedMode();
  bool     isDirectMode();


  //       RESET
  void     setResetPin(uint8_t resetPin);
  //       reset ==> all switches off, registers ==> 0.
  void     pulseResetPin();


  //       DEBUG
  int      getLastError();


private:
  uint8_t  _address = 0x2A;
  TwoWire* _wire;

  int      _send(uint8_t pins, uint8_t value);
  int      _readback(uint8_t value);

  int      _error;
  uint8_t  _mode;
  uint8_t  _reset;
};


//  -- END OF FILE --





