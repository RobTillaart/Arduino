//
//    FILE: MCP3424.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library for 18 bit ADC I2C MCP3424 and compatibles.
//     URL: https://github.com/RobTillaart/MCP3424


#include "MCP3424.h"


/////////////////////////////////////////////////////////////////////////////
//
//  CONSTRUCTOR
//
MCP3424::MCP3424(uint8_t address, TwoWire *wire)
{
  _address = address;
  _wire = wire;

  _maxChannels = 4;  //  hack to support other devices from the series.
  _channel = 0;

  _gain = 1;
  _bits = 12;
  _mode = 0;  //  CONTINUOUS
  _config = 0x10;
}


bool MCP3424::begin()
{
  return isConnected();
}


bool MCP3424::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


uint8_t MCP3424::getAddress()
{
  return _address;
}


uint8_t MCP3424::getMaxChannels()
{
  return _maxChannels;
}


int32_t MCP3424::read()
{
  //  return 12345;  //  TEST CODE
  return readRaw();
}


float MCP3424::readVolts()
{
  //  TODO
  //  pre calculate float _factor = 15.625e-6 * pow(2, (_bits - 12))/ _gain;
  return read() * 15.625e-6 * pow(2, (_bits - 12))/ _gain;
}


float MCP3424::readMilliVolts()
{
  return read() * 15.625e-3 * pow(2, (_bits - 12))/ _gain;
}


float MCP3424::readMicroVolts()
{
  return read() * 15.625e0 * pow(2, (_bits - 12))/ _gain;
}


//  TODO move to derived class with more than one channel?
bool MCP3424::setChannel(uint8_t channel)
{
  if (channel >= _maxChannels)
  {
    return false;
  }
  if (_channel != channel)
  {
    _channel = channel;
    _config &= 0x1F;  //  channel = 0
    if (channel == 1) _config |= 0x20;
    if (channel == 2) _config |= 0x40;
    if (channel == 3) _config |= 0x60;
  }
  writeConfig();
  return true;
}


//  TODO move to derived class with more than one channel?
uint8_t MCP3424::getChannel()
{
  return _channel;
}


bool MCP3424::setGain(uint8_t gain)
{
  if ((gain != 1) && (gain != 2) && (gain != 4) && (gain != 8))
  {
    return false;
  }
  if (_gain != gain)
  {
    _gain = gain;
    _config &= 0xFC;  //  gain == 1
    if (_gain == 2) _config |= 0x01;
    if (_gain == 4) _config |= 0x02;
    if (_gain == 8) _config |= 0x03;
    writeConfig();
  }
  return true;
}


uint8_t MCP3424::getGain()
{
  return _gain;
}


bool MCP3424::setResolution(uint8_t bits)
{
  if ((bits != 12) && (bits != 14) && (bits != 16) && (bits != 18))
  {
    return false;
  }
  if (_bits != bits)
  {
    _bits = bits;
    _config &= 0xF3;  //  bits == 12
    if (_bits == 14) _config |= 0x04;
    if (_bits == 16) _config |= 0x08;
    if (_bits == 18) _config |= 0x0C;
    writeConfig();
  }
  return true;
}


uint8_t MCP3424::getResolution()
{
  return _bits;
}


void MCP3424::setContinuousMode()
{
  _config &= ~0x10;
  writeConfig();
}


void MCP3424::setSingleShotMode()
{
  _config |= 0x10;
  writeConfig();
}


uint8_t MCP3424::getMode()
{
  return (_config & 0x10);
}


/////////////////////////////////////////////////////////////////////////////
//
//  PRIVATE
//
int MCP3424::writeConfig()
{
  _wire->beginTransmission(_address);
  _wire->write(_config);
  return _wire->endTransmission();
}


//  status bit/byte is not read.
int32_t MCP3424::readRaw()
{
  int32_t rv = 0;

  //  not optimized compacted code.
  if (_bits == 18)
  {
    if (_wire->requestFrom(_address, (uint8_t)3) != 3)
    {
      //  _error = PCF8574_I2C_ERROR;
      return 0;
    }
    rv += _wire->read();
    rv <<= 8;
    rv += _wire->read();
    rv <<= 8;
    rv += _wire->read();
    //  handle sign bit.
    if (rv & 0x00020000) rv |= 0xFF000000;
    return rv;
  }

  //  12, 14, 16 bit
  if (_wire->requestFrom(_address, (uint8_t)2) != 2)
  {
    //  _error = PCF8574_I2C_ERROR;
    return 0;
  }
  rv += _wire->read();
  rv <<= 8;
  rv += _wire->read();
  //  handle sign bit not needed.
  return rv;
}


//  -- END OF FILE --

