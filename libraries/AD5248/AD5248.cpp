//
//    FILE: AD5248.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: Library for I2C digital potentiometer AD5243 + rheostat AD5248
//    DATE: 2023-12-12
//     URL: https://github.com/RobTillaart/AD5248


#include "AD5248.h"


#define AD5248_RDAC0        0x00
#define AD5248_RDAC1        0x80
#define AD5248_RESET        0x40
#define AD5248_SHUTDOWN     0x20

#define AD5243_ADDRESS      0x2F


AD5248::AD5248(uint8_t address, TwoWire *wire)
{
  _address = address;
  _wire = wire;

  //  power on reset => mid position
  _lastValue[0] = _lastValue[1] = AD5248_MIDPOINT;
  _pmCount = 2;
}


bool AD5248::begin()
{
  if (! isConnected()) return false;
  reset();
  return true;
}


bool AD5248::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


uint8_t AD5248::getAddress()
{
  return _address;
}


uint8_t AD5248::reset()
{
  write(0, AD5248_MIDPOINT);
  return write(1, AD5248_MIDPOINT);
}


uint8_t AD5248::zeroAll()
{
  write(0, 0);
  return write(1, 0);
}


uint8_t AD5248::write(const uint8_t rdac, const uint8_t value)
{
  if (rdac >= _pmCount) return AD5248_ERROR;

  uint8_t cmd = (rdac == 0) ? AD5248_RDAC0 : AD5248_RDAC1;
  _lastValue[rdac] = value;
  return send(cmd, value);
}


uint8_t AD5248::read(const uint8_t rdac)
{
  return _lastValue[rdac];
}


uint8_t AD5248::readBackRegister()
{
  _wire->beginTransmission(_address);
  _wire->endTransmission();
  _wire->requestFrom(_address, (uint8_t)1);
  return _wire->read();
}


uint8_t AD5248::midScaleReset(const uint8_t rdac)
{
  if (rdac >= _pmCount) return AD5248_ERROR;

  uint8_t cmd = AD5248_RESET;
  if (rdac == 1) cmd |= AD5248_RDAC1;
  _lastValue[rdac] = AD5248_MIDPOINT;
  return send(cmd, _lastValue[rdac]);
}


//  read datasheet P.??
uint8_t AD5248::shutDown()
{
  uint8_t cmd = AD5248_SHUTDOWN;  //  TODO TEST & VERIFY
  return send(cmd, 0);
}


uint8_t AD5248::pmCount()
{
  return _pmCount;
}


//////////////////////////////////////////////////////////
//
//  PROTECTED
//
uint8_t AD5248::send(const uint8_t cmd, const uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(cmd);
  _wire->write(value);
  return _wire->endTransmission();
}


//////////////////////////////////////////////////////////////
//
//  DERIVED CLASS  AD5243 potentiometer
//
AD5243::AD5243(TwoWire * wire) : AD5248(AD5243_ADDRESS, wire)  //  fixed address
{
  _pmCount = 2;
}


//  -- END OF FILE --

