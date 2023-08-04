//
//    FILE: m5angle8.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library for M5 8ANGLE 8x12 bit potentiometers
//     URL: https://github.com/RobTillaart/M5ANGLE8


#include "m5angle8.h"


//  REGISTERS
#define M5ANGLE8_REG_ADDRESS            0xFF
#define M5ANGLE8_REG_VERSION            0xFE
#define M5ANGLE8_REG_BASE_ANA12         0x00
#define M5ANGLE8_REG_BASE_ANA8          0x10
#define M5ANGLE8_REG_SWITCH             0x20
#define M5ANGLE8_REG_RGB                0x30


M5ANGLE8::M5ANGLE8(uint8_t address, TwoWire *wire)
{
  _address = address;
  _wire = wire;
}


#if defined (ESP8266) || defined(ESP32)
bool M5ANGLE8::begin(int dataPin, int clockPin)
{
  if ((dataPin < 255) && (clockPin < 255))
  {
    _wire->begin(dataPin, clockPin);
  } else {
    _wire->begin();
  }
  if (! isConnected()) return false;
  return true;
}
#endif


bool M5ANGLE8::begin()
{
  _wire->begin();
  if (! isConnected()) return false;
  return true;
}


bool M5ANGLE8::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}


bool M5ANGLE8::setAddress(uint8_t address)
{
  _address = address;
  write8(M5ANGLE8_REG_ADDRESS, _address);
  return isConnected();
}


uint8_t M5ANGLE8::getAddress()
{
  return _address;
}


uint8_t M5ANGLE8::getVersion()
{
  return read8(M5ANGLE8_REG_VERSION);
}


////////////////////////////////////////////////
//
//  INPUT PART
//
uint16_t M5ANGLE8::analogRead(uint8_t channel, uint8_t resolution)
{
  if (channel > 7)
  {
    return M5ANGLE8_ERR_CHANNEL;
  }
  if (resolution <= 8)
  {
    return (uint16_t) read8(M5ANGLE8_REG_BASE_ANA8 + channel);
  }
  uint16_t value = read16(M5ANGLE8_REG_BASE_ANA12 + (channel << 1));
  if      (resolution == 11) value >>= 1;
  else if (resolution == 10) value >>= 2;
  else if (resolution == 9)  value >>= 3;
  return value;
}


uint8_t M5ANGLE8::inputSwitch()
{
  return read8(M5ANGLE8_REG_SWITCH);
}


bool M5ANGLE8::writeRGB(uint8_t channel, uint8_t R, uint8_t G, uint8_t B, uint8_t brightness)
{
  if (channel > 7)
  {
    return false;
  }
  if (brightness > 100) brightness = 100;
  write32(M5ANGLE8_REG_RGB + (channel << 2), R, G, B, brightness);
  return true;
}


bool M5ANGLE8::allOff()
{
  for (uint8_t ch = 0; ch < 8; ch++)
  {
    write32(M5ANGLE8_REG_RGB + (ch << 2), 0, 0, 0, 0);
  }
  return true;
}


////////////////////////////////////////////////
//
//  PRIVATE
//
bool M5ANGLE8::write8(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value);
  _error = _wire->endTransmission();
  return (_error == 0);
}


uint8_t M5ANGLE8::read8(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _error = _wire->endTransmission();
  if (_error != 0)
  {
    //  error handling
    return 0;
  }
  if (_wire->requestFrom(_address, (uint8_t)1) != 1)
  {
    //  error handling
    return 0;
  }
  return _wire->read();
}


uint16_t M5ANGLE8::read16(uint8_t reg)
{
  uint16_t value = 0;
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _error = _wire->endTransmission();
  if (_error != 0)
  {
    //  error handling
    return 0;
  }
  if (_wire->requestFrom(_address, (uint8_t)2) != 2)
  {
    //  error handling
    return 0;
  }
  value += _wire->read();
  value <<= 8;
  value += _wire->read();
  return value;
}


bool M5ANGLE8::write32(uint8_t reg, uint8_t R, uint8_t G, uint8_t B, uint8_t brightness)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(R);
  _wire->write(G);
  _wire->write(B);
  _wire->write(brightness);
  _error = _wire->endTransmission();
  return (_error == 0);
}


//  -- END OF FILE --
