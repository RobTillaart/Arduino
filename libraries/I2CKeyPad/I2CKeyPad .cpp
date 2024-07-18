//
//    FILE: I2CKeyPad.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.5.0
// PURPOSE: Arduino library for 4x4 KeyPad connected to an I2C PCF8574
//     URL: https://github.com/RobTillaart/I2CKeyPad


#include "I2CKeyPad.h"


I2CKeyPad::I2CKeyPad(const uint8_t deviceAddress, TwoWire *wire)
{
  _lastKey = I2C_KEYPAD_NOKEY;
  _address = deviceAddress;
  _wire    = wire;
  _mode    = I2C_KEYPAD_4x4;
  _debounceThreshold = 0;
  _lastTimeRead      = 0;
}


bool I2CKeyPad::begin()
{
  //  enable interrupts
  _read(0xF0);
  return isConnected();
}


bool I2CKeyPad::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}


uint8_t I2CKeyPad::getKey()
{
  uint32_t now = millis();
  if (_debounceThreshold > 0)
  {
    if (now - _debounceThreshold < _lastTimeRead)
    {
      return I2C_KEYPAD_THRESHOLD;
    }
  }

  uint8_t key = 0;
  if      (_mode == I2C_KEYPAD_5x3) key = _getKey5x3();
  else if (_mode == I2C_KEYPAD_6x2) key = _getKey6x2();
  else if (_mode == I2C_KEYPAD_8x1) key = _getKey8x1();
  else                              key = _getKey4x4();  //  default.

  if (key == I2C_KEYPAD_FAIL) return key;  //  propagate error.
  //  valid keys + NOKEY
  _lastKey = key;
  _lastTimeRead = now;
  return key;
}


uint8_t I2CKeyPad::getLastKey()
{
  return _lastKey;
}


//  to check "press any key"
bool I2CKeyPad::isPressed()
{
  uint8_t a = _read(0xF0);
  if (a == 0xFF) return false;
  return (a != 0xF0);
}


uint8_t I2CKeyPad::getChar()
{
  uint8_t key = getKey();
  if (key != I2C_KEYPAD_THRESHOLD)
  {
    return _keyMap[key];
  }
  return I2C_KEYPAD_THRESHOLD;
}


uint8_t I2CKeyPad::getLastChar()
{
  return _keyMap[_lastKey];
}


void I2CKeyPad::loadKeyMap(char * keyMap)
{
  _keyMap = keyMap;
}


void I2CKeyPad::setKeyPadMode(uint8_t mode)
{
  if ((mode == I2C_KEYPAD_5x3) ||
      (mode == I2C_KEYPAD_6x2) ||
      (mode == I2C_KEYPAD_8x1))
  {
    _mode = mode;
    return;
  }
  _mode = I2C_KEYPAD_4x4;
}


uint8_t I2CKeyPad::getKeyPadMode()
{
  return _mode;
}


void I2CKeyPad::setDebounceThreshold(uint16_t value)
{
  _debounceThreshold = value;
}


uint16_t I2CKeyPad::getDebounceThreshold()
{
  return _debounceThreshold;
}


uint32_t I2CKeyPad::getLastTimeRead()
{
  return _lastTimeRead;
}


//////////////////////////////////////////////////////
//
//  PROTECTED
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
  //  key = row + 4 x column
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

  //  4 columns as input pull up, 4 rows as output
  uint8_t cols = _read(0x0F);
  //  check if single line has gone low.
  if (cols == 0x0F)      return I2C_KEYPAD_NOKEY;
  else if (cols == 0x0E) key += 0;
  else if (cols == 0x0D) key += 4;
  else if (cols == 0x0B) key += 8;
  else if (cols == 0x07) key += 12;
  else return I2C_KEYPAD_FAIL;

  return key;   //  0..15
}


//  not tested
uint8_t I2CKeyPad::_getKey5x3()
{
  //  key = row + 5 x column
  uint8_t key = 0;

  //  mask = 5 rows as input pull up, 3 columns as output
  uint8_t rows = _read(0xF8);
  //  check if single line has gone low.
  if (rows == 0xF8)      return I2C_KEYPAD_NOKEY;
  else if (rows == 0xF0) key = 0;
  else if (rows == 0xE8) key = 1;
  else if (rows == 0xD8) key = 2;
  else if (rows == 0xB8) key = 3;
  else if (rows == 0x78) key = 4;
  else return I2C_KEYPAD_FAIL;

  // 3 columns as input pull up, 5 rows as output
  uint8_t cols = _read(0x07);
  // check if single line has gone low.
  if (cols == 0x07)      return I2C_KEYPAD_NOKEY;
  else if (cols == 0x06) key += 0;
  else if (cols == 0x05) key += 5;
  else if (cols == 0x03) key += 10;
  else return I2C_KEYPAD_FAIL;

  return key;   //  0..14
}


//  not tested
uint8_t I2CKeyPad::_getKey6x2()
{
  //  key = row + 6 x column
  uint8_t key = 0;

  //  mask = 6 rows as input pull up, 2 columns as output
  uint8_t rows = _read(0xFC);
  //  check if single line has gone low.
  if (rows == 0xFC)      return I2C_KEYPAD_NOKEY;
  else if (rows == 0xF8) key = 0;
  else if (rows == 0xF4) key = 1;
  else if (rows == 0xEC) key = 2;
  else if (rows == 0xDC) key = 3;
  else if (rows == 0xBC) key = 4;
  else if (rows == 0x7C) key = 5;
  else return I2C_KEYPAD_FAIL;

  //  2 columns as input pull up, 6 rows as output
  uint8_t cols = _read(0x03);
  //  check if single line has gone low.
  if (cols == 0x03)      return I2C_KEYPAD_NOKEY;
  else if (cols == 0x02) key += 0;
  else if (cols == 0x01) key += 6;
  else return I2C_KEYPAD_FAIL;

  return key;   //  0..11
}


//  not tested
uint8_t I2CKeyPad::_getKey8x1()
{
  //  key = row
  uint8_t key = 0;

  //  mask = 8 rows as input pull up, 0 columns as output
  uint8_t rows = _read(0xFF);
  //  check if single line has gone low.
  if (rows == 0xFF)      return I2C_KEYPAD_NOKEY;
  else if (rows == 0xFE) key = 0;
  else if (rows == 0xFD) key = 1;
  else if (rows == 0xFB) key = 2;
  else if (rows == 0xF7) key = 3;
  else if (rows == 0xEF) key = 4;
  else if (rows == 0xDF) key = 5;
  else if (rows == 0xBF) key = 6;
  else if (rows == 0x7F) key = 7;
  else return I2C_KEYPAD_FAIL;

  return key;   //  0..7
}


//  -- END OF FILE --

