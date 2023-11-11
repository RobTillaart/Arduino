#pragma once
//
//    FILE: I2CKeyPad8x8.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: Arduino library for 8x8 or smaller KeyPad connected to an I2C PCF8575.
//     URL: https://github.com/RobTillaart/I2CKeyPad


#include "Arduino.h"
#include "Wire.h"


#define I2C_KEYPAD8x8_LIB_VERSION         (F("0.2.0"))

#define I2C_KEYPAD8x8_NOKEY               64
#define I2C_KEYPAD8x8_FAIL                65


class I2CKeyPad8x8
{
public:
  I2CKeyPad8x8(const uint8_t deviceAddress, TwoWire *wire = &Wire);

  bool     begin();
  bool     isConnected();

  //  get raw key's 0..65
  uint8_t  getKey();
  uint8_t  getLastKey();
  bool     isPressed();


  //  get 'translated' keys
  //  user must load KeyMap, there is no check.
  uint8_t  getChar();
  uint8_t  getLastChar();
  void     loadKeyMap(char * keyMap);   //  char[65]


protected:
  uint8_t  _address;
  uint8_t  _lastKey;
  uint16_t _read(uint16_t mask);

  TwoWire* _wire;

  char *   _keyMap = NULL;
};


//  -- END OF FILE --

