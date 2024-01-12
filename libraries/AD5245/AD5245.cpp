//
//    FILE: AD5245.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.4.0
// PURPOSE: Arduino library for I2C digital potentiometer AD5245.
//    DATE: 2022-07-31
//     URL: https://github.com/RobTillaart/AD5245


#include "AD5245.h"


#define AD5245_WRITE            0x00
#define AD5245_RESET            0x40
#define AD5245_SHUTDOWN         0x20


AD5245::AD5245(const uint8_t address, TwoWire *wire)
{
  //  address: 0x010110x = 0x2C or 0x2D
  _address = address;
  _wire = wire;
  //  power on reset => mid position
  _lastValue = AD5245_MIDPOINT;
}


bool AD5245::begin()
{
  if ((_address != 0x2C) && (_address != 0x2D)) return false;
  if (! isConnected()) return false;
  reset();
  return true;
}


bool AD5245::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


uint8_t AD5245::reset()
{
  uint8_t cmd = AD5245_RESET;
  _lastValue = AD5245_MIDPOINT;
  return send(cmd, _lastValue);
}


uint8_t AD5245::write(const uint8_t value)
{
  uint8_t cmd = AD5245_WRITE;
  _lastValue = value;
  return send(cmd, value);
}


uint8_t AD5245::read()
{
  return _lastValue;
}


uint8_t AD5245::readDevice()
{
  _wire->requestFrom(_address, (uint8_t)1);
  return _wire->read();
}


//  read datasheet
uint8_t AD5245::shutDown()
{
  uint8_t cmd = AD5245_SHUTDOWN;
  return send(cmd, 0);
}


//////////////////////////////////////////////////////////
//
//  PRIVATE
//
uint8_t AD5245::send(const uint8_t cmd, const uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(cmd);
  _wire->write(value);
  return _wire->endTransmission();
}


//  -- END OF FILE --
