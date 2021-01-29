//
//    FILE: I2CKeyPad.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
// PURPOSE: Arduino libray for 4x4 KeyPad connected to an I2C PCF8574
//     URL: https://github.com/RobTillaart/I2CKeyPad
//
//  HISTORY:
//  0.0.1  2019-10-01  initial version
//  0.1.0  2020-06-26  first release
//  0.1.1  2020-07-05  fix compilation for ESP32
//  0.1.2  2020-12-27  arduino-ci + unit test

#include "I2CKeyPad.h"

I2CKeyPad::I2CKeyPad()
{
}

#if defined(ESP8266) || defined(ESP32)
bool I2CKeyPad::begin(uint8_t sda, uint8_t scl, uint8_t address)
{
  Wire.begin(sda, scl);
  _lastKey = I2C_KEYPAD_NOKEY;
  _address = address;
  return isConnected();
}
#endif

bool I2CKeyPad::begin(uint8_t address)
{
  Wire.begin();
  _lastKey = I2C_KEYPAD_NOKEY;
  _address = address;
  return isConnected();
}

uint8_t I2CKeyPad::getKey()
{
  // key = row + 4 x col
  uint8_t key = 0;

  // mask = 4 rows as input-pullup, 4 colomns as output
  uint8_t rows = _read(0xF0);
  // check if single line has gone low.
  if (rows == 0xF0)      return I2C_KEYPAD_NOKEY;
  else if (rows == 0xE0) key = 0;
  else if (rows == 0xD0) key = 1;
  else if (rows == 0xB0) key = 2;
  else if (rows == 0x70) key = 3;
  else return I2C_KEYPAD_FAIL;

  // 4 columns as input-pullup, 4 rows as output
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

// to check "press any key"
bool I2CKeyPad::isPressed()
{
  uint8_t a = _read(0xF0);
  if (a == 0xFF) return false;
  return (a != 0xF0);
}

bool I2CKeyPad::isConnected()
{
  Wire.beginTransmission(_address);
  return (Wire.endTransmission() == 0);
}

uint8_t I2CKeyPad::_read(uint8_t mask)
{
  Wire.beginTransmission(_address);
  Wire.write(mask);
  if (Wire.endTransmission() != 0)
  {
    // set com error
    return 0xFF;
  }
  Wire.requestFrom(_address, (uint8_t)1);
  return Wire.read();
}

// -- END OF FILE --
