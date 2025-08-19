//
//    FILE: MAX14661.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-29
// VERSION: 0.3.0
// PURPOSE: Arduino library for MAX14661 16 channel I2C multiplexer
//     URL: https://github.com/RobTillaart/MAX14661



#include "MAX14661.h"


//
//  REGISTERS
//
#define MAX14661_DIR0       0x00
#define MAX14661_DIR1       0x01
#define MAX14661_DIR2       0x02
#define MAX14661_DIR3       0x03
#define MAX14661_SHDW0      0x10
#define MAX14661_SHDW1      0x11
#define MAX14661_SHDW2      0x12
#define MAX14661_SHDW3      0x13
#define MAX14661_CMD_A      0x14
#define MAX14661_CMD_B      0x15


MAX14661::MAX14661(const uint8_t deviceAddress, TwoWire *wire)
{
  _address = deviceAddress;
  _wire    = wire;
  _error   = MAX14661_OK;
}


bool MAX14661::begin()
{
  _error = MAX14661_OK;
  if ((_address < 76) || (_address > 79))
  {
    _error = MAX14661_ERR_ADDRESS;
    return false;
  }
  return isConnected();
}


bool MAX14661::isConnected()
{
  _wire->beginTransmission(_address);
  _error = _wire->endTransmission();
  //  set MAX14661_ERR_I2C (nope)
  return ( _error == 0);
}


uint8_t MAX14661::getAddress()
{
  return _address;
}


/////////////////////////////////////////////////////////
//
//  PAIR INTERFACE
//
bool MAX14661::connectPair(uint8_t pair)
{
  if (pair > 7)
  {
    _error = MAX14661_ERR_CHANNEL;
    return false;
  }
  uint8_t channel = pair * 2;  //  select A channel
  uint8_t reg = MAX14661_DIR0;
  if (channel > 7)
  {
    reg = MAX14661_DIR1;
    channel -= 8;
  }
  //  Handle switch A
  uint8_t mask = readRegister(reg);
  //  test _error?
  mask |= (1 << channel);
  writeRegister(reg, mask);
  //  test _error?

  //  Handle switch B
  reg += 2;
  channel = channel + 1;  //  select B channel
  mask = readRegister(reg);
  //  test _error?
  mask |= (1 << channel);
  writeRegister(reg, mask);
  //  test _error?
  return true;
}


bool MAX14661::disconnectPair(uint8_t pair)
{
  if (pair > 7)
  {
    _error = MAX14661_ERR_CHANNEL;
    return false;
  }
  uint8_t channel = pair * 2;  //  select A channel
  uint8_t reg = MAX14661_DIR0;
  if (channel > 7)
  {
    reg = MAX14661_DIR1;
    channel -= 8;
  }
  //  Handle switch A
  uint8_t mask = readRegister(reg);
  //  test _error?
  mask &= ~(1 << channel);
  writeRegister(reg, mask);
  //  test _error?

  //  Handle switch B
  reg += 2;
  channel = channel + 1;  //  select B channel
  mask = readRegister(reg);
  //  test _error?
  mask &= ~(1 << channel);
  writeRegister(reg, mask);
  //  test _error?
  return true;
}


bool MAX14661::isConnectedPair(uint8_t pair)
{
  if (pair > 7)
  {
    _error = MAX14661_ERR_CHANNEL;
    return false;
  }
  uint8_t channel = pair * 2;  //  select A channel
  uint8_t reg = MAX14661_DIR0;
  if (channel > 7)
  {
    reg = MAX14661_DIR1;
    channel -= 8;
  }
  //  Handle switch A
  uint8_t mask = readRegister(reg);
  //  test _error?
  return (mask & (1 << channel)) > 0;
}


bool MAX14661::disconnectAllPairs()
{
  return disconnectAll();
}


/////////////////////////////////////////////////////////
//
//  SHADOW INTERFACE
//
void MAX14661::shadowClear()
{
  setShadowChannelMaskA(0x0000);
  setShadowChannelMaskB(0x0000);
}


void MAX14661::activateShadow()
{
  //  table 2: Copy shadows registers to switches
  writeRegister(MAX14661_CMD_A, 0x11);
  //  test _error?
  writeRegister(MAX14661_CMD_B, 0x11);
  //  test _error?
  //  return bool
}


////////////////////////////////////////////////////////////


void MAX14661::setShadowChannelMaskA(uint16_t mask)
{
  writeRegister(MAX14661_SHDW0, mask & 0xFF);
  //  test _error?
  writeRegister(MAX14661_SHDW1, mask >> 8);
  //  test _error?
  //  return bool...
}


uint16_t MAX14661::getShadowChannelMaskA()
{
  uint16_t mask = readRegister(MAX14661_SHDW1) << 8;
  mask |= readRegister(MAX14661_SHDW0);
  return mask;
}


void MAX14661::setShadowChannelMaskB(uint16_t mask)
{
  writeRegister(MAX14661_SHDW2, mask & 0xFF);
  //  test _error?
  writeRegister(MAX14661_SHDW3, mask >> 8);
  //  test _error?
  //  return bool...
}


uint16_t MAX14661::getShadowChannelMaskB()
{
  uint16_t mask = readRegister(MAX14661_SHDW3) << 8;
  mask |= readRegister(MAX14661_SHDW2);
  return mask;
}


////////////////////////////////////////////////////////////


bool MAX14661::openShadowChannelA(uint8_t channel)
{
  if (channel > 15)
  {
    _error = MAX14661_ERR_CHANNEL;
    return false;
  }
  uint8_t ch = channel;
  uint8_t reg = MAX14661_SHDW0;
  if (ch > 7)
  {
    reg = MAX14661_SHDW1;
    ch -= 8;
  }
  uint8_t mask = readRegister(reg);
  //  test _error?
  mask |= (1 << ch);
  writeRegister(reg, mask);
  //  test _error?
  return true;
}


bool MAX14661::closeShadowChannelA(uint8_t channel)
{
  if (channel > 15)
  {
    _error = MAX14661_ERR_CHANNEL;
    return false;
  }
  uint8_t ch = channel;
  uint8_t reg = MAX14661_SHDW0;
  if (ch > 7)
  {
    reg = MAX14661_SHDW1;
    ch -= 8;
  }
  uint8_t mask = readRegister(reg);
  //  test _error?
  mask &= ~(1 << ch);
  writeRegister(reg, mask);
  //  test _error?
  return true;
}


bool MAX14661::isOpenShadowChannelA(uint8_t channel)
{
  if (channel > 15)
  {
    _error = MAX14661_ERR_CHANNEL;
    return false;
  }
  uint8_t ch = channel;
  uint8_t reg = MAX14661_SHDW0;
  if (ch > 7)
  {
    reg = MAX14661_SHDW1;
    ch -= 8;
  }
  uint8_t mask = readRegister(reg);
  //  test _error?
  return (mask & (1 << ch)) > 0;
}


bool MAX14661::openShadowChannelB(uint8_t channel)
{
  if (channel > 15)
  {
    _error = MAX14661_ERR_CHANNEL;
    return false;
  }
  uint8_t ch = channel;
  uint8_t reg = MAX14661_SHDW0;
  if (ch > 7)
  {
    reg = MAX14661_SHDW1;
    ch -= 8;
  }
  uint8_t mask = readRegister(reg);
  mask |= (1 << ch);
  //  test _error?
  writeRegister(reg, mask);
  //  test _error?
  return true;
}


bool MAX14661::closeShadowChannelB(uint8_t channel)
{
  if (channel > 15)
  {
    _error = MAX14661_ERR_CHANNEL;
    return false;
  }
  uint8_t ch = channel;
  uint8_t reg = MAX14661_SHDW2;
  if (ch > 7)
  {
    reg = MAX14661_SHDW3;
    ch -= 8;
  }
  uint8_t mask = readRegister(reg);
  mask &= ~(1 << ch);
  //  test _error?
  writeRegister(reg, mask);
  //  test _error?
  return true;
}


bool MAX14661::isOpenShadowChannelB(uint8_t channel)
{
  if (channel > 15)
  {
    _error = MAX14661_ERR_CHANNEL;
    return false;
  }
  uint8_t ch = channel;
  uint8_t reg = MAX14661_SHDW2;
  if (ch > 7)
  {
    reg = MAX14661_SHDW3;
    ch -= 8;
  }
  uint8_t mask = readRegister(reg);
  //  test _error?
  return (mask & (1 << ch)) > 0;
}


/////////////////////////////////////////////////////////
//
//  MUX INTERFACE
//
void MAX14661::MUXA(uint8_t channel)
{
  uint8_t ch = channel;
  if (channel > 15) ch = 0x10;
  writeRegister(MAX14661_CMD_A, ch);
}


uint8_t MAX14661::getMUXA()
{
  uint8_t ch = readRegister(MAX14661_CMD_A);
  if ((ch & 0x10) == 0) return (ch & 0x0F);
  return 255;
}


void MAX14661::MUXB(uint8_t channel)
{
  uint8_t ch = channel;
  if (channel > 15) ch = 0x10;
  writeRegister(MAX14661_CMD_B, ch);
}


uint8_t MAX14661::getMUXB()
{
  uint8_t ch = readRegister(MAX14661_CMD_B);
  if ((ch & 0x10) == 0) return (ch & 0x0F);
  return 255;
}


/////////////////////////////////////////////////////////
//
//  FULL CONTROL
//
bool MAX14661::connectA(uint8_t channel)
{
  if (channel > 15)
  {
    _error = MAX14661_ERR_CHANNEL;
    return false;
  }
  uint8_t ch = channel;
  uint8_t reg = MAX14661_DIR0;
  if (ch > 7)
  {
    reg = MAX14661_DIR1;
    ch -= 8;
  }
  uint8_t mask = readRegister(reg);
  mask |= (1 << ch);
  writeRegister(reg, mask);
  return true;
}


bool MAX14661::connectB(uint8_t channel)
{
  if (channel > 15)
  {
    _error = MAX14661_ERR_CHANNEL;
    return false;
  }
  uint8_t ch = channel;
  uint8_t reg = MAX14661_DIR2;
  if (ch > 7)
  {
    reg = MAX14661_DIR3;
    ch -= 8;
  }
  uint8_t mask = readRegister(reg);
  mask |= (1 << ch);
  writeRegister(reg, mask);
  return true;
}


bool MAX14661::disconnectA(uint8_t channel)
{
  if (channel > 15)
  {
    _error = MAX14661_ERR_CHANNEL;
    return false;
  }
  uint8_t ch = channel;
  uint8_t reg = MAX14661_DIR0;
  if (ch > 7)
  {
    reg = MAX14661_DIR1;
    ch -= 8;
  }
  uint8_t mask = readRegister(reg);
  mask &= ~(1 << ch);
  writeRegister(reg, mask);
  return true;
}


bool MAX14661::disconnectB(uint8_t channel)
{
  if (channel > 15)
  {
    _error = MAX14661_ERR_CHANNEL;
    return false;
  }
  uint8_t ch = channel;
  uint8_t reg = MAX14661_DIR2;
  if (ch > 7)
  {
    reg = MAX14661_DIR3;
    ch -= 8;
  }
  uint8_t mask = readRegister(reg);
  mask &= ~(1 << ch);
  writeRegister(reg, mask);
  return true;
}


bool MAX14661::disconnectAll()
{
  _wire->beginTransmission(_address);
  _wire->write(MAX14661_DIR0);
  _wire->write(0x00);
  _wire->write(0x00);
  _wire->write(0x00);
  _wire->write(0x00);
  _error = _wire->endTransmission();
  return true;
}


/////////////////////////////////////////////////////////
//
//  LOW LEVEL CONTROL
//
uint8_t MAX14661::readRegister(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _error = _wire->endTransmission();
  if (_error != 0)
  {
    _error = MAX14661_ERR_I2C_READ;
    return 0;
  }
  if (_wire->requestFrom(_address, (uint8_t)1) != 1)
  {
    _error = MAX14661_ERR_I2C_REQUEST;
    return 0;
  }
  _error = MAX14661_OK;
  return _wire->read();
}


int MAX14661::writeRegister(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value);
  _error = _wire->endTransmission();
  //  set MAX14661_ERR_I2C
  return _error;
}


int MAX14661::lastError()
{
  int e = _error;
  _error = MAX14661_OK;
  return e;
}


//  -- END OF FILE --

