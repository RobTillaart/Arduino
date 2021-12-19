//
//    FILE: I2CKeyPad.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.1
// PURPOSE: Arduino library for 4x4 KeyPad connected to an I2C PCF8574
//     URL: https://github.com/RobTillaart/I2CKeyPad
//
//  HISTORY:
//  0.0.1  2019-10-01  initial version
//  0.1.0  2020-06-26  first release
//  0.1.1  2020-07-05  fix compilation for ESP32
//  0.1.2  2020-12-27  Arduino-CI + unit test
//
//  0.2.0  2021-05-06  MultiWire ... (breaking interface)
//  0.2.1  2021-05-06  add _read(0xF0) to begin() to enable PCF8574
//                     interrupts. (#5 thanks to JohnMac1234)
//  0.3.0  2021-11-04  add key mapping functions.
//  0.3.1  2021-12-19  update library.json, license, minor edits


#include "I2CKeyPad.h"


I2CKeyPad::I2CKeyPad(const uint8_t deviceAddress, TwoWire *wire)
{
  _lastKey = I2C_KEYPAD_NOKEY;
  _address = deviceAddress;
  _wire    = wire;
}


#if defined(ESP8266) || defined(ESP32)
bool I2CKeyPad::begin(uint8_t sda, uint8_t scl)
{
  _wire->begin(sda, scl);
  //  enable interrupts
  _read(0xF0);
  return isConnected();
}
#endif


bool I2CKeyPad::begin()
{
  _wire->begin();
  //  enable interrupts
  _read(0xF0);
  return isConnected();
}


uint8_t I2CKeyPad::getKey()
{
  return _getKey4x4();
}


//  to check "press any key"
bool I2CKeyPad::isPressed()
{
  uint8_t a = _read(0xF0);
  if (a == 0xFF) return false;
  return (a != 0xF0);
}


bool I2CKeyPad::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}


void I2CKeyPad::loadKeyMap(char * keyMap)
{
  _keyMap = keyMap;
}


//////////////////////////////////////////////////////
//
//  PRIVATE
//
uint8_t I2CKeyPad::_read(uint8_t mask)
{
  //  improve the odds that IO will not interrupted.
  yield();

  _wire->beginTransmission(_address);
  _wire->write(mask);
  if (_wire->endTransmission() != 0)
  {
    //  set communication error
    return 0xFF;
  }
  _wire->requestFrom(_address, (uint8_t)1);
  return _wire->read();
}


uint8_t I2CKeyPad::_getKey4x4()
{
  //  key = row + 4 x col
  uint8_t key = 0;

  //  mask = 4 rows as input pull up, 4 columns as output
  uint8_t rows = _read(0xF0);
  //  check if single line has gone low.
  if (rows == 0xF0)      return I2C_KEYPAD_NOKEY;
  else if (rows == 0xE0) key = 0;
  else if (rows == 0xD0) key = 1;
  else if (rows == 0xB0) key = 2;
  else if (rows == 0x70) key = 3;
  else return I2C_KEYPAD_FAIL;

  // 4 columns as input pull up, 4 rows as output
  uint8_t cols = _read(0x0F);
  // check if single line has gone low.
  if (cols == 0x0F)      return I2C_KEYPAD_NOKEY;
  else if (cols == 0x0E) key += 0;
  else if (cols == 0x0D) key += 4;
  else if (cols == 0x0B) key += 8;
  else if (cols == 0x07) key += 12;
  else return I2C_KEYPAD_FAIL;

  _lastKey = key;

  return key;   // 0..15
}


// -- END OF FILE --

