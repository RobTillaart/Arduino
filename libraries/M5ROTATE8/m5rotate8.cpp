//
//    FILE: m5rotate8.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.4.0
// PURPOSE: Arduino library for M5 8ROTATE 8x rotary encoders
//     URL: https://github.com/RobTillaart/M5ROTATE8


#include "m5rotate8.h"

//  FIRMWARE V1 REGISTERS
#define M5ROTATE8_REG_ADDRESS               0xFF
#define M5ROTATE8_REG_VERSION               0xFE
#define M5ROTATE8_REG_BASE_ABS              0x00
#define M5ROTATE8_REG_BASE_REL              0x20
#define M5ROTATE8_REG_BASE_RESET            0x40
#define M5ROTATE8_REG_BASE_BUTTON_VALUE     0x50
#define M5ROTATE8_REG_SWITCH                0x60
#define M5ROTATE8_REG_RGB                   0x70

//  FIRMWARE V2 REGISTERS
#define M5ROTATE8_REG_BASE_BUTTON_TOGGLE    0x58
#define M5ROTATE8_REG_ENCODER_MASK          0x61
#define M5ROTATE8_REG_BUTTON_MASK           0x62



M5ROTATE8::M5ROTATE8(uint8_t address, TwoWire *wire)
{
  _address = address;
  _wire = wire;
}


bool M5ROTATE8::begin()
{
  if (! isConnected()) return false;
  return true;
}


bool M5ROTATE8::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}


bool M5ROTATE8::setAddress(uint8_t address)
{
  if ((address < 8) || (address > 119)) return false;
  _address = address;
  write8(M5ROTATE8_REG_ADDRESS, _address);
  return isConnected();
}


uint8_t M5ROTATE8::getAddress()
{
  return _address;
}


uint8_t M5ROTATE8::getVersion()
{
  return read8(M5ROTATE8_REG_VERSION);
}


//
//  ROTARY ENCODER PART
//
int32_t M5ROTATE8::getAbsCounter(uint8_t channel)
{
  return read32(M5ROTATE8_REG_BASE_ABS + (channel << 2));
}


bool M5ROTATE8::setAbsCounter(uint8_t channel, int32_t value)
{
  return write32(M5ROTATE8_REG_BASE_ABS + (channel << 2), value);
}


int32_t M5ROTATE8::getRelCounter(uint8_t channel)
{
  return read32(M5ROTATE8_REG_BASE_REL + (channel << 2));
}


bool M5ROTATE8::getKeyPressed(uint8_t channel)
{
  if (channel > 7)
  {
    return false;
  }
  return (0 == read8(M5ROTATE8_REG_BASE_BUTTON_VALUE + channel));
}


bool M5ROTATE8::resetCounter(uint8_t channel)
{
  if (channel > 7)
  {
    return false;
  }
  write8(M5ROTATE8_REG_BASE_RESET + channel, 1);
  return true;
}


void M5ROTATE8::resetAll()
{
  for (int channel = 0; channel < 8; channel++)
  {
    write8(M5ROTATE8_REG_BASE_RESET + channel, 1);
  }
}


//
//  INPUT SWITCH PART
//
uint8_t M5ROTATE8::inputSwitch()
{
  return read8(M5ROTATE8_REG_SWITCH);
}


//
//  LED PART
//
bool M5ROTATE8::writeRGB(uint8_t channel, uint8_t R, uint8_t G, uint8_t B)
{
  if (channel > 8)
  {
    return false;
  }
  write24(M5ROTATE8_REG_RGB + (channel * 3), R, G, B);
  return true;
}


uint32_t M5ROTATE8::readRGB(uint8_t channel)
{
  return read24(M5ROTATE8_REG_RGB + (channel * 3));
}


bool M5ROTATE8::setAll(uint8_t R, uint8_t G, uint8_t B)
{
  for (uint8_t ch = 0; ch < 9; ch++)
  {
    write24(M5ROTATE8_REG_RGB + (ch * 3), R, G, B);
  }
  return true;
}


bool M5ROTATE8::allOff()
{
  return setAll(0, 0, 0);
}



//
//  FIRMWARE V2
//
bool M5ROTATE8::setButtonToggleCount(uint8_t channel, uint8_t value)
{
  if (channel > 7)
  {
    return false;
  }
  return write8(M5ROTATE8_REG_BASE_BUTTON_TOGGLE + channel, value);
}


uint8_t M5ROTATE8::getButtonToggleCount(uint8_t channel)
{
  if (channel > 7)
  {
    return 0;
  }
  return read8(M5ROTATE8_REG_BASE_BUTTON_TOGGLE + channel);
}


//  0 = no change, 1 = changed
uint8_t M5ROTATE8::getEncoderChangeMask()
{
  return read8(M5ROTATE8_REG_ENCODER_MASK);
}


//  0 = not pressed, 1 = pressed (inverted the datasheetV2 specification)
//  seems more logical
uint8_t M5ROTATE8::getButtonChangeMask()
{
  //  invert register to be more logical IMHO.
  return read8(M5ROTATE8_REG_BUTTON_MASK) ^ 0xFF;
}


//////////////////////////////////////////////////////////////////////////////
//
//  PRIVATE
//
bool M5ROTATE8::write8(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value);
  _error = _wire->endTransmission();
  return (_error == 0);
}


uint8_t M5ROTATE8::read8(uint8_t reg)
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


bool M5ROTATE8::write24(uint8_t reg, uint8_t R, uint8_t G, uint8_t B)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(R);
  _wire->write(G);
  _wire->write(B);
  _error = _wire->endTransmission();
  return (_error == 0);
}


uint32_t M5ROTATE8::read24(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _error = _wire->endTransmission();
  if (_error != 0)
  {
    //  error handling
    return 0;
  }
  if (_wire->requestFrom(_address, (uint8_t)3) != 3)
  {
    //  error handling
    return 0;
  }
  uint32_t value = 0;
  value += _wire->read();
  value <<= 8;
  value += _wire->read();
  value <<= 8;
  value += _wire->read();
  return value;
}


bool M5ROTATE8::write32(uint8_t reg, uint32_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value & 0xFF);
  value >>= 8;
  _wire->write(value & 0xFF);
  value >>= 8;
  _wire->write(value & 0xFF);
  value >>= 8;
  _wire->write(value);
  _error = _wire->endTransmission();
  return (_error == 0);
}


uint32_t M5ROTATE8::read32(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _error = _wire->endTransmission();
  if (_error != 0)
  {
    //  error handling
    return 0;
  }
  if (_wire->requestFrom(_address, (uint8_t)4) != 4)
  {
    //  error handling
    return 0;
  }
  uint32_t value = 0;
  value += (_wire->read());
  value += (((uint32_t)_wire->read()) << 8 );
  value += (((uint32_t)_wire->read()) << 16);
  value += (((uint32_t)_wire->read()) << 24);
  return value;
}


//  -- END OF FILE --
