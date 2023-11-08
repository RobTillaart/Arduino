//
//    FILE: m5angle8.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
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
  _reverse = false;
  _error = M5ANGLE8_OK;
}


bool M5ANGLE8::begin()
{
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
//  ANALOG PART
//
uint16_t M5ANGLE8::analogRead(uint8_t channel, uint8_t resolution)
{
  if (channel > 7)
  {
    return M5ANGLE8_ERR_CHANNEL;
  }
  uint16_t value;
  if (resolution > 8)
  {
    value = read16(M5ANGLE8_REG_BASE_ANA12 + (channel << 1));
    if (_reverse == false) value = 4095 - value;
    if (resolution < 12)  value >>= (12 - resolution);
  }
  else
  {
    value = read8(M5ANGLE8_REG_BASE_ANA8 + channel);
    if (_reverse == false) value = 255 - value;
    if (resolution < 8)  value >>= (8 - resolution);
  }
  return value;
}


void M5ANGLE8::setReverse(bool reverse)
{
  _reverse = reverse;
}


bool M5ANGLE8::getReverse()
{
  return _reverse;
}


uint16_t M5ANGLE8::selectorRead(uint8_t channel, uint8_t steps)
{
  uint32_t value = analogRead(channel, 12);
  return (value * steps) >> 12;
}



////////////////////////////////////////////////
//
//  INPUT SWITCH PART
//
uint8_t M5ANGLE8::inputSwitch()
{
  return read8(M5ANGLE8_REG_SWITCH);
}


////////////////////////////////////////////////
//
//  LED PART
//
bool M5ANGLE8::writeRGB(uint8_t channel, uint8_t R, uint8_t G, uint8_t B, uint8_t brightness)
{
  if (channel > 8)
  {
    return false;
  }
  if (brightness > 100) brightness = 100;
  write32(M5ANGLE8_REG_RGB + (channel << 2), R, G, B, brightness);
  return true;
}


bool M5ANGLE8::setAll(uint8_t R, uint8_t G, uint8_t B, uint8_t brightness)
{
  for (uint8_t ch = 0; ch < 9; ch++)
  {
    write32(M5ANGLE8_REG_RGB + (ch << 2), R, G, B, brightness);
  }
  return true;
}


bool M5ANGLE8::allOff()
{
  return setAll(0,0,0,0);
}


bool M5ANGLE8::writeBrightness(uint8_t channel, uint8_t brightness)
{
  if (channel > 8)
  {
    return false;
  }
  if (brightness > 100) brightness = 100;
  write8(M5ANGLE8_REG_RGB + (channel << 2) + 3, brightness);
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
  value += _wire->read() << 8;
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
