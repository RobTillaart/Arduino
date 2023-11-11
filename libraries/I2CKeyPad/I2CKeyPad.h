#pragma once
//
//    FILE: I2CKeyPad.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.4.0
// PURPOSE: Arduino library for 4x4 KeyPad connected to an I2C PCF8574
//     URL: https://github.com/RobTillaart/I2CKeyPad


#include "Arduino.h"
#include "Wire.h"


#define I2C_KEYPAD_LIB_VERSION    (F("0.4.0"))

#define I2C_KEYPAD_NOKEY          16
#define I2C_KEYPAD_FAIL           17

//  experimental
#define I2C_KEYPAD_4x4            44
#define I2C_KEYPAD_5x3            53
#define I2C_KEYPAD_6x2            62
#define I2C_KEYPAD_8x1            81


class I2CKeyPad
{
public:
  I2CKeyPad(const uint8_t deviceAddress, TwoWire *wire = &Wire);

  //  call Wire.begin() first!
  bool    begin();

  //  get raw key's 0..15
  uint8_t getKey();
  uint8_t getLastKey();

  bool    isPressed();
  bool    isConnected();

  //  get 'translated' keys
  //  user must load KeyMap, there is no check.
  uint8_t getChar();
  uint8_t getLastChar();
  void    loadKeyMap(char * keyMap);   //  char[19]

  //  mode functions - experimental
  void    setKeyPadMode(uint8_t mode = I2C_KEYPAD_4x4);
  uint8_t getKeyPadMode();


protected:
  uint8_t _address;
  uint8_t _lastKey;
  uint8_t _mode;
  uint8_t _read(uint8_t mask);
  uint8_t _getKey4x4();

  //  experimental - could be public ?!
  uint8_t _getKey5x3();
  uint8_t _getKey6x2();
  uint8_t _getKey8x1();

  TwoWire* _wire;

  char *  _keyMap = NULL;
};


//  -- END OF FILE --

