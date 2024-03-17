//
//    FILE: AD5263.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
// PURPOSE: Arduino library for I2C digital potentiometer AD5263 and compatibles.
//    DATE: 2023-10-09
//     URL: https://github.com/RobTillaart/AD5263


#include "AD5263.h"


#define AD5263_RDAC0        0x00
#define AD5263_RDAC1        0x20
#define AD5263_RDAC2        0x40
#define AD5263_RDAC3        0x60
#define AD5263_RESET        0x10
#define AD5263_SHUTDOWN     0x08
#define AD5263_O1_HIGH      0x04
#define AD5263_O2_HIGH      0x02


AD5263::AD5263(const uint8_t address, TwoWire *wire)
{
  _address = address;
  _wire = wire;

  //  power on reset => mid position
  _pmCount = 4;
  for (int i = 0; i < _pmCount; i++)
  {
  _lastValue[i] = AD5263_MIDPOINT;
  }
  _O1 = _O2 = 0;
}


bool AD5263::begin()
{
  if (! isConnected()) return false;
  reset();
  return true;
}


bool AD5263::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


uint8_t AD5263::getAddress()
{
  return _address;
}


uint8_t AD5263::reset()
{
  return setAll(AD5263_MIDPOINT);
}


uint8_t AD5263::zeroAll()
{
  return setAll(0);
}


uint8_t AD5263::setAll(const uint8_t value)
{
  for (int i = 1; i < _pmCount; i++)
  {
    write(i, value);
  }
  return write(0, value, LOW, LOW);
}


uint8_t AD5263::write(const uint8_t rdac, const uint8_t value)
{
  if (rdac >= _pmCount) return AD5263_ERROR;

  //  uint8_t cmd = rdac << 5;  //  saves 12 bytes UNO
  uint8_t cmd = AD5263_RDAC0;
  if (rdac == 1) cmd = AD5263_RDAC1;
  if (rdac == 2) cmd = AD5263_RDAC2;
  if (rdac == 3) cmd = AD5263_RDAC3;

  //  apply the output lines
  cmd = cmd | _O1 | _O2;
  _lastValue[rdac] = value;
  return send(cmd, value);
}


uint8_t AD5263::write(const uint8_t rdac, const uint8_t value, const uint8_t O1, const uint8_t O2)
{
  if (rdac >= _pmCount) return AD5263_ERROR;

  _O1 = (O1 == LOW) ? 0 : AD5263_O1_HIGH;
  _O2 = (O2 == LOW) ? 0 : AD5263_O2_HIGH;

  //  uint8_t cmd = rdac << 5;  //  saves 12 bytes UNO
  uint8_t cmd = AD5263_RDAC0;
  if (rdac == 1) cmd = AD5263_RDAC1;
  if (rdac == 2) cmd = AD5263_RDAC2;
  if (rdac == 3) cmd = AD5263_RDAC3;

  //  apply the output lines
  cmd = cmd | _O1 | _O2;
  _lastValue[rdac] = value;
  return send(cmd, value);
}


uint8_t AD5263::setO1(const uint8_t value)
{
  _O1 = (value == LOW) ? 0 : AD5263_O1_HIGH;
  uint8_t cmd = AD5263_RDAC0 | _O1 | _O2;
  return send(cmd, _lastValue[0]);
}


uint8_t AD5263::setO2(const uint8_t value)
{
  _O2 = (value == LOW) ? 0: AD5263_O2_HIGH;
  uint8_t cmd = AD5263_RDAC0 | _O1 | _O2;
  return send(cmd, _lastValue[0]);
}


uint8_t AD5263::getO1()
{
  return (_O1 > 0);
}


uint8_t AD5263::getO2()
{
  return (_O2 > 0);
}


uint8_t AD5263::read(const uint8_t rdac)
{
  if (rdac >= _pmCount) return 0x00;
  return _lastValue[rdac];
}


uint8_t AD5263::readBackRegister()
{
  _wire->beginTransmission(_address);
  _wire->endTransmission();
  _wire->requestFrom(_address, (uint8_t)1);
  return _wire->read();
}


uint8_t AD5263::midScaleReset(const uint8_t rdac)
{
  if (rdac >= _pmCount) return AD5263_ERROR;

  uint8_t cmd = AD5263_RDAC0;
  if (rdac == 1) cmd = AD5263_RDAC1;
  if (rdac == 2) cmd = AD5263_RDAC2;
  if (rdac == 3) cmd = AD5263_RDAC3;

  cmd |= AD5263_RESET;

  //  apply the output lines
  cmd = cmd | _O1 | _O2;
  _lastValue[rdac] = AD5263_MIDPOINT;
  return send(cmd, AD5263_MIDPOINT);
}


//  read datasheet P.20
uint8_t AD5263::shutDown()
{
  uint8_t cmd = AD5263_SHUTDOWN;  //  TODO TEST & VERIFY
  return send(cmd, 0);
}


uint8_t AD5263::pmCount()
{
  return _pmCount;
}


//////////////////////////////////////////////////////////
//
//  PROTECTED
//
uint8_t AD5263::send(const uint8_t cmd, const uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(cmd);
  _wire->write(value);
  return _wire->endTransmission();
}



//////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
//  None known so far.



//  -- END OF FILE --

