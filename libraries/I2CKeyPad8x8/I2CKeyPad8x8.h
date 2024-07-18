#pragma once
//
//    FILE: I2CKeyPad8x8.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
// PURPOSE: Arduino library for 8x8 or smaller KeyPad connected to an I2C PCF8575.
//     URL: https://github.com/RobTillaart/I2CKeyPad


#include "Arduino.h"
#include "Wire.h"


#define I2C_KEYPAD8x8_LIB_VERSION         (F("0.3.0"))

#define I2C_KEYPAD8x8_NOKEY               64
#define I2C_KEYPAD8x8_FAIL                65
#define I2C_KEYPAD8x8_THRESHOLD           255

class I2CKeyPad8x8
{
public:
  I2CKeyPad8x8(const uint8_t deviceAddress, TwoWire *wire = &Wire);

  //  call Wire.begin() first!
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

  //  value in milliseconds, max 65535 ms
  void     setDebounceThreshold(uint16_t value = 0);
  uint16_t getDebounceThreshold();
  uint32_t getLastTimeRead();


protected:
  uint8_t  _address;
  uint8_t  _lastKey;
  uint16_t _read(uint16_t mask);
  uint16_t _debounceThreshold;
  uint32_t _lastTimeRead;

  uint8_t  _getKey8x8();

  TwoWire* _wire;

  char *   _keyMap = NULL;

};


//  -- END OF FILE --

