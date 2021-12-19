#pragma once
//
//    FILE: I2CKeyPad.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.1
// PURPOSE: Arduino library for 4x4 KeyPad connected to an I2C PCF8574
//     URL: https://github.com/RobTillaart/I2CKeyPad


#include "Arduino.h"
#include "Wire.h"


#define I2C_KEYPAD_LIB_VERSION    (F("0.3.1"))

#define I2C_KEYPAD_NOKEY          16
#define I2C_KEYPAD_FAIL           17


class I2CKeyPad
{
public:
  I2CKeyPad(const uint8_t deviceAddress, TwoWire *wire = &Wire);

#if defined(ESP8266) || defined(ESP32)
  bool    begin(uint8_t sda, uint8_t scl);
#endif
  bool    begin();

  //  get raw key's 0..15
  uint8_t getKey();
  uint8_t getLastKey()   { return _lastKey; };

  bool    isPressed();  
  bool    isConnected();

  //  get 'translated' keys
  //  user must load KeyMap self, there is no check.
  uint8_t getChar()      { return _keyMap[getKey()]; };
  uint8_t getLastChar()  { return _keyMap[_lastKey]; };
  void    loadKeyMap(char * keyMap);   // char[19]


protected:
  uint8_t _address;
  uint8_t _lastKey;
  uint8_t _read(uint8_t mask);
  uint8_t _getKey4x4();

  TwoWire* _wire;
  
  char *  _keyMap = NULL;
};


// -- END OF FILE --

