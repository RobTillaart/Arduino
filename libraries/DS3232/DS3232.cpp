//
//    FILE: DS3232.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for DS3232 RTC (minimalistic)
// VERSION: 0.4.1
//    DATE: 2011-01-21
//     URL: https://github.com/RobTillaart/DS3232


#include "DS3232.h"


/////////////////////////////////////////////////////////
//
//  CONSTRUCTOR
//
DS3231::DS3231(TwoWire *wire)
{
  _wire     = wire;
  _address  = 0x68;  //  fixed.
  _type     = 3231;
  _lastRead = 0;
  for (int i = 0; i < 7; i++)
  {
    _reg[i] = 0;
  }
}


int DS3231::begin()
{
  if (! isConnected() ) return DS3232_ERROR_CONNECT;
  return DS3232_OK;
}


bool DS3231::isConnected()
{
  _wire->beginTransmission(_address);
  _rv = _wire->endTransmission();
  return (_rv == 0);
}


uint8_t DS3231::getAddress()
{
  return _address;
}


uint16_t DS3231::getType()
{
  return _type;
}


/////////////////////////////////////////////////////////
//
//  CORE
//
int DS3231::read()
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


int DS3231::write()
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


uint32_t DS3231::lastRead()
{
  return _lastRead;
}


/////////////////////////////////////////////////////////
//
//  GETTERS
//
uint8_t DS3231::seconds() { return _reg[0]; }
uint8_t DS3231::minutes() { return _reg[1]; }
uint8_t DS3231::hours()   { return _reg[2]; }
uint8_t DS3231::weekDay() { return _reg[3]; }
uint8_t DS3231::day()     { return _reg[4]; }
uint8_t DS3231::month()   { return _reg[5]; }
uint8_t DS3231::year()    { return _reg[6]; }


/////////////////////////////////////////////////////////
//
//  SETTERS
//
void DS3231::setSeconds(uint8_t value) { _reg[0] = value; }
void DS3231::setMinutes(uint8_t value) { _reg[1] = value; }
void DS3231::setHours(uint8_t value)   { _reg[2] = value; }
void DS3231::setWeekDay(uint8_t value) { _reg[3] = value; }
void DS3231::setDay(uint8_t value)     { _reg[4] = value; }
void DS3231::setMonth(uint8_t value)   { _reg[5] = value; }
void DS3231::setYear(uint8_t value)    { _reg[6] = value; }


/////////////////////////////////////////////////////////
//
//  TEMPERATURE
//
float DS3231::getTemperature()
{
  float temperature = (int8_t)readRegister(DS3232_TEMPERATURE);
  int   fraction = readRegister(DS3232_TEMPERATURE + 1);
  if (fraction != 0) temperature += (fraction >> 6) * 0.25;
  return temperature;
}


/////////////////////////////////////////////////////////
//
//  LOW LEVEL
//
int DS3231::readRegister(uint8_t reg)
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


int DS3231::writeRegister(uint8_t reg, uint8_t value)
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

uint8_t DS3231::dec2bcd(uint8_t value)
{
  return value + 6 * (value / 10);
}


uint8_t DS3231::bcd2dec(uint8_t value)
{
  return value - 6 * (value >> 4);
}


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//


/////////////////////////////////////////////////////////////////////////////
//
//  DS3232
//
DS3232::DS3232(TwoWire *wire) : DS3231(wire)
{
  _type = 3232;
}


//
//  SRAM 236 bytes, register 0x14-0xFF
//  index = 0x00..0xEB == 0..235
//  note: no boundary check
int DS3232::SRAMwrite8(uint8_t index, uint8_t value)
{
  uint8_t position = DS3232_SRAM_BASE + index;
  return writeRegister(position, value);
}

int DS3232::SRAMwrite16(uint8_t index, uint16_t value)
{
  uint8_t position = DS3232_SRAM_BASE + index;
  writeRegister(position, value >> 8);
  return writeRegister(position + 1, value & 0xFF);
}

int DS3232::SRAMwrite32(uint8_t index, uint32_t value)
{
  uint32_t val = value;
  uint8_t position = DS3232_SRAM_BASE + index;
  for (int i = 0; i < 4; i++)
  {
    writeRegister(position + i, val & 0xFF);
    val >>= 8;
  }
  return DS3232_OK;
}

uint8_t DS3232::SRAMread8(uint8_t index)
{
  uint8_t position = DS3232_SRAM_BASE + index;
  return readRegister(position);
}

uint16_t DS3232::SRAMread16(uint8_t index)
{
  uint8_t position = DS3232_SRAM_BASE + index;
  uint16_t val = readRegister(position);
  val <<= 8;
  val += readRegister(position + 1);
  return val;
}

uint32_t DS3232::SRAMread32(uint8_t index)
{
  uint32_t val = 0;
  uint8_t position = DS3232_SRAM_BASE + index;
  for (int i = 3; i >= 0; i--)
  {
    val <<= 8;
    val += readRegister(position + i);
  }
  return val;
}


//  -- END OF FILE --

