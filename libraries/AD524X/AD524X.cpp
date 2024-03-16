//
//    FILE: AD524X.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.5.1
// PURPOSE: I2C digital potentiometer AD5241 AD5242
//    DATE: 2013-10-12
//     URL: https://github.com/RobTillaart/AD524X


#include "AD524X.h"


#define AD524X_RDAC0        0x00
#define AD524X_RDAC1        0x80
#define AD524X_RESET        0x40
#define AD524X_SHUTDOWN     0x20
#define AD524X_O1_HIGH      0x10
#define AD524X_O2_HIGH      0x08


AD524X::AD524X(const uint8_t address, TwoWire *wire)
{
  //  address: 0x01011xx = 0x2C - 0x2F
  _address = address;
  _wire = wire;

  //  power on reset => mid position
  _lastValue[0] = _lastValue[1] = AD524X_MIDPOINT;
  _O1 = _O2 = 0;
  _pmCount = 2;
}


bool AD524X::begin()
{
  if (! isConnected()) return false;
  reset();
  return true;
}


bool AD524X::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


uint8_t AD524X::getAddress()
{
  return _address;
}


uint8_t AD524X::reset()
{
  write(0, AD524X_MIDPOINT, LOW, LOW);
  return write(1, AD524X_MIDPOINT);
}


uint8_t AD524X::zeroAll()
{
  write(0, 0, LOW, LOW);
  return write(1, 0);
}


uint8_t AD524X::write(const uint8_t rdac, const uint8_t value)
{
  if (rdac >= _pmCount) return AD524X_ERROR;

  uint8_t cmd = (rdac == 0) ? AD524X_RDAC0 : AD524X_RDAC1;
  //  apply the output lines
  cmd = cmd | _O1 | _O2;
  _lastValue[rdac] = value;
  return send(cmd, value);
}


uint8_t AD524X::write(const uint8_t rdac, const uint8_t value, const uint8_t O1, const uint8_t O2)
{
  if (rdac >= _pmCount) return AD524X_ERROR;

  _O1 = (O1 == LOW) ? 0 : AD524X_O1_HIGH;
  _O2 = (O2 == LOW) ? 0 : AD524X_O2_HIGH;

  uint8_t cmd = (rdac == 0) ? AD524X_RDAC0 : AD524X_RDAC1;
  //  apply the output lines
  cmd = cmd | _O1 | _O2;
  _lastValue[rdac] = value;
  return send(cmd, value);
}


uint8_t AD524X::setO1(const uint8_t value)
{
  _O1 = (value == LOW) ? 0 : AD524X_O1_HIGH;
  uint8_t cmd = AD524X_RDAC0 | _O1 | _O2;
  return send(cmd, _lastValue[0]);
}


uint8_t AD524X::setO2(const uint8_t value)
{
  _O2 = (value == LOW) ? 0: AD524X_O2_HIGH;
  uint8_t cmd = AD524X_RDAC0 | _O1 | _O2;
  return send(cmd, _lastValue[0]);
}


uint8_t AD524X::getO1()
{
  return (_O1 > 0);
}


uint8_t AD524X::getO2()
{
  return (_O2 > 0);
}


uint8_t AD524X::read(const uint8_t rdac)
{
  return _lastValue[rdac];
}


uint8_t AD524X::readBackRegister()
{
  _wire->beginTransmission(_address);
  _wire->endTransmission();
  _wire->requestFrom(_address, (uint8_t)1);
  return _wire->read();
}


uint8_t AD524X::midScaleReset(const uint8_t rdac)
{
  if (rdac >= _pmCount) return AD524X_ERROR;

  uint8_t cmd = AD524X_RESET;
  if (rdac == 1) cmd |= AD524X_RDAC1;
  cmd = cmd | _O1 | _O2;
  _lastValue[rdac] = AD524X_MIDPOINT;
  return send(cmd, _lastValue[rdac]);
}


//  read datasheet P.15
uint8_t AD524X::shutDown()
{
  uint8_t cmd = AD524X_SHUTDOWN;  //  TODO TEST & VERIFY
  return send(cmd, 0);
}


uint8_t AD524X::pmCount()
{
  return _pmCount;
}


//////////////////////////////////////////////////////////
//
//  PROTECTED
//
uint8_t AD524X::send(const uint8_t cmd, const uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(cmd);
  _wire->write(value);
  return _wire->endTransmission();
}


//////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES  AD5241 AD5242
//
AD5241::AD5241(const uint8_t address, TwoWire *wire) : AD524X(address, wire)
{
  _pmCount = 1;
}


uint8_t AD5241::write(const uint8_t value)
{
  //  apply the output lines
  uint8_t cmd = AD524X_RDAC0 | _O1 | _O2;
  _lastValue[0] = value;
  return send(cmd, value);
}


uint8_t AD5241::write(const uint8_t value, const uint8_t O1, const uint8_t O2)
{
  _O1 = (O1 == LOW) ? 0 : AD524X_O1_HIGH;
  _O2 = (O2 == LOW) ? 0 : AD524X_O2_HIGH;

  //  apply the output lines
  uint8_t cmd = AD524X_RDAC0 | _O1 | _O2;
  _lastValue[0] = value;
  return send(cmd, value);
}


uint8_t AD5241::write(const uint8_t rdac, const uint8_t value)
{
  if (rdac >= _pmCount) return AD524X_ERROR;
  return AD5241::write(value);
}


uint8_t AD5241::write(const uint8_t rdac, const uint8_t value, const uint8_t O1, const uint8_t O2)
{
  if (rdac >= _pmCount) return AD524X_ERROR;
  return AD5241::write(value, O1, O2);
}


AD5242::AD5242(const uint8_t address, TwoWire *wire) : AD524X(address, wire)
{
  _pmCount = 2;
}


//////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES  AD5280 AD5282
//
AD5280::AD5280(const uint8_t address, TwoWire *wire) : AD524X(address, wire)
{
  _pmCount = 1;
}


uint8_t AD5280::write(const uint8_t value)
{
  //  apply the output lines
  uint8_t cmd = AD524X_RDAC0 | _O1 | _O2;
  _lastValue[0] = value;
  return send(cmd, value);
}


uint8_t AD5280::write(const uint8_t value, const uint8_t O1, const uint8_t O2)
{
  _O1 = (O1 == LOW) ? 0 : AD524X_O1_HIGH;
  _O2 = (O2 == LOW) ? 0 : AD524X_O2_HIGH;

  //  apply the output lines
  uint8_t cmd = AD524X_RDAC0 | _O1 | _O2;
  _lastValue[0] = value;
  return send(cmd, value);
}


uint8_t AD5280::write(const uint8_t rdac, const uint8_t value)
{
  if (rdac >= _pmCount) return AD524X_ERROR;
  return AD5280::write(value);
}


uint8_t AD5280::write(const uint8_t rdac, const uint8_t value, const uint8_t O1, const uint8_t O2)
{
  if (rdac >= _pmCount) return AD524X_ERROR;
  return AD5280::write(value, O1, O2);
}


AD5282::AD5282(const uint8_t address, TwoWire *wire) : AD524X(address, wire)
{
  _pmCount = 2;
}


//  -- END OF FILE --

