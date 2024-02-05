//
//    FILE: DS3232.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for DS3232 RTC (minimalistic)
// VERSION: 0.3.0
//    DATE: 2011-01-21
//     URL: https://github.com/RobTillaart/DS3232


#include "DS3232.h"


/////////////////////////////////////////////////////////
//
//  CONSTRUCTOR
//
DS3232::DS3232(TwoWire *wire)
{
  _wire     = wire;
  _address  = 0x68;  //  fixed.
  _type     = 3232;
  _lastRead = 0;
  for (int i = 0; i < 7; i++)
  {
    _reg[i] = 0;
  }
}


int DS3232::begin()
{
  if (! isConnected() ) return DS3232_ERROR_CONNECT;
  return DS3232_OK;
}


bool DS3232::isConnected()
{
  _wire->beginTransmission(_address);
  _rv = _wire->endTransmission();
  return (_rv == 0);
}


uint8_t DS3232::getAddress()
{
  return _address;
}


uint16_t DS3232::getType()
{
  return _type;
}


/////////////////////////////////////////////////////////
//
//  CORE
//
int DS3232::read()
{
  _wire->beginTransmission(_address);
  _wire->write(DS3232_SECONDS);
  _rv = _wire->endTransmission();
  if (_rv != 0) return DS3232_ERROR_I2C;

  if (Wire.requestFrom(_address, (uint8_t)7) != 7)
  {
    return DS3232_ERROR_I2C;
  }
  for (int i = 0; i < 7; i++)
  {
    _reg[i] = bcd2dec(_wire->read());
  }
  _reg[0] &= 0x7F;
  _reg[2] &= 0x3F;
  _lastRead = millis();

  return DS3232_OK;
}


int DS3232::write()
{
  _wire->beginTransmission(_address);
  _wire->write(DS3232_SECONDS);
  _wire->write(_reg[0] | 0x80);  //  stop clock
  for (int i = 1; i < 7; i++)
  {
    _wire->write(dec2bcd(_reg[i]));
  }
  _rv = Wire.endTransmission();
  if (_rv != 0) return DS3232_ERROR_I2C;

  _wire->beginTransmission(_address);
  _wire->write(DS3232_SECONDS);
  _wire->write(_reg[0] & 0x7f);  //  start clock
  _rv = Wire.endTransmission();
  if (_rv != 0) return DS3232_ERROR_I2C;

  return DS3232_OK;
}


uint32_t DS3232::lastRead()
{
  return _lastRead;
}


/////////////////////////////////////////////////////////
//
//  GETTERS
//
uint8_t DS3232::seconds() { return _reg[0]; }
uint8_t DS3232::minutes() { return _reg[1]; }
uint8_t DS3232::hours()   { return _reg[2]; }
uint8_t DS3232::weekDay() { return _reg[3]; }
uint8_t DS3232::day()     { return _reg[4]; }
uint8_t DS3232::month()   { return _reg[5]; }
uint8_t DS3232::year()    { return _reg[6]; }


/////////////////////////////////////////////////////////
//
//  SETTERS
//
void DS3232::setSeconds(uint8_t value) { _reg[0] = value; }
void DS3232::setMinutes(uint8_t value) { _reg[1] = value; }
void DS3232::setHours(uint8_t value)   { _reg[2] = value; }
void DS3232::setDay(uint8_t value)     { _reg[4] = value; }
void DS3232::setMonth(uint8_t value)   { _reg[5] = value; }
void DS3232::setYear(uint8_t value)    { _reg[6] = value; }


/////////////////////////////////////////////////////////
//
//  LOW LEVEL
//
int DS3232::readRegister(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _rv = _wire->endTransmission();
  if (_rv != 0) return DS3232_ERROR_I2C;

  if (Wire.requestFrom(_address, (uint8_t)1) != 1)
  {
    return DS3232_ERROR_I2C;
  }
  return _wire->read();
}


int DS3232::writeRegister(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value);
  _rv = Wire.endTransmission();
  if (_rv != 0) return DS3232_ERROR_I2C;
  return DS3232_OK;
}


/////////////////////////////////////////////////////////
//
//  PRIVATE
//

uint8_t DS3232::dec2bcd(uint8_t value)
{
  return value + 6 * (value / 10);
}


uint8_t DS3232::bcd2dec(uint8_t value)
{
  return value - 6 * (value >> 4);
}


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//


/////////////////////////////////////////////////////////////////////////////
//
//  DS3231
//
DS3231::DS3231(TwoWire *wire) : DS3232(wire)
{
  _type = 3231;
}


//  -- END OF FILE --

