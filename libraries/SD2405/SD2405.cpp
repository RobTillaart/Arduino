//
//    FILE: SD2405.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for I2C SD2405 RTC and compatibles.
// VERSION: 0.1.1
//    DATE: 2022-03-17
//     URL: https://github.com/RobTillaart/SD2405


#include "SD2405.h"


/////////////////////////////////////////////////////////
//
//  CONSTRUCTOR
//
SD2405::SD2405(TwoWire *wire)
{
  _wire     = wire;
  _address  = 0x32;  //  fixed.
  _lastRead = 0;
  for (int i = 0; i < 7; i++)
  {
    _reg[i] = 0;
  }
}


int SD2405::begin()
{
  if (! isConnected() ) return SD2405_ERROR_CONNECT;
  return SD2405_OK;
}


bool SD2405::isConnected()
{
  _wire->beginTransmission(_address);
  _rv = _wire->endTransmission();
  return (_rv == 0);
}


uint8_t SD2405::getAddress()
{
  return _address;
}


/////////////////////////////////////////////////////////
//
//  CORE
//
int SD2405::read()
{
  _wire->beginTransmission(_address);
  _wire->write(SD2405_SECONDS);
  _rv = _wire->endTransmission();
  if (_rv != 0) return SD2405_ERROR_I2C;

  if (_wire->requestFrom(_address, (uint8_t)7) != 7)
  {
    return SD2405_ERROR_I2C;
  }
  for (int i = 0; i < 7; i++)
  {
    _reg[i] = bcd2dec(_wire->read());
  }
  _reg[0] &= 0x7F;
  _reg[2] &= 0x3F;
  _lastRead = millis();

  return SD2405_OK;
}


int SD2405::write()
{
  _wire->beginTransmission(_address);
  _wire->write(SD2405_SECONDS);
  _wire->write(_reg[0] | 0x80);  //  stop clock
  for (int i = 1; i < 7; i++)
  {
    _wire->write(dec2bcd(_reg[i]));
  }
  _rv = _wire->endTransmission();
  if (_rv != 0) return SD2405_ERROR_I2C;

  _wire->beginTransmission(_address);
  _wire->write(SD2405_SECONDS);
  _wire->write(_reg[0] & 0x7f);  //  start clock
  _rv = _wire->endTransmission();
  if (_rv != 0) return SD2405_ERROR_I2C;

  return SD2405_OK;
}


uint32_t SD2405::lastRead()
{
  return _lastRead;
}


/////////////////////////////////////////////////////////
//
//  GETTERS
//
uint8_t SD2405::seconds() { return _reg[0]; }
uint8_t SD2405::minutes() { return _reg[1]; }
uint8_t SD2405::hours()   { return _reg[2]; }
uint8_t SD2405::weekDay() { return _reg[3]; }
uint8_t SD2405::day()     { return _reg[4]; }
uint8_t SD2405::month()   { return _reg[5]; }
uint8_t SD2405::year()    { return _reg[6]; }


/////////////////////////////////////////////////////////
//
//  SETTERS
//
void SD2405::setSeconds(uint8_t value) { _reg[0] = value; }
void SD2405::setMinutes(uint8_t value) { _reg[1] = value; }
void SD2405::setHours(uint8_t value)   { _reg[2] = value; }
void SD2405::setWeekDay(uint8_t value) { _reg[3] = value; }
void SD2405::setDay(uint8_t value)     { _reg[4] = value; }
void SD2405::setMonth(uint8_t value)   { _reg[5] = value; }
void SD2405::setYear(uint8_t value)    { _reg[6] = value; }


/////////////////////////////////////////////////////////
//
//  LOW LEVEL
//
int SD2405::readRegister(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _rv = _wire->endTransmission();
  if (_rv != 0) return SD2405_ERROR_I2C;

  if (_wire->requestFrom(_address, (uint8_t)1) != 1)
  {
    return SD2405_ERROR_I2C;
  }
  return _wire->read();
}


int SD2405::writeRegister(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value);
  _rv = _wire->endTransmission();
  if (_rv != 0) return SD2405_ERROR_I2C;
  return SD2405_OK;
}


/////////////////////////////////////////////////////////
//
//  PRIVATE
//

uint8_t SD2405::dec2bcd(uint8_t value)
{
  return value + 6 * (value / 10);
}


uint8_t SD2405::bcd2dec(uint8_t value)
{
  return value - 6 * (value >> 4);
}



//
//  SRAM 12 bytes, register 0x14-0x1F
//  index = 0x00..0x0B == 0..11
//  note: no boundary check
int SD2405::SRAMwrite8(uint8_t index, uint8_t value)
{
  uint8_t position = SD2405_SRAM_BASE + index;
  return writeRegister(position, value);
}

int SD2405::SRAMwrite16(uint8_t index, uint16_t value)
{
  uint8_t position = SD2405_SRAM_BASE + index;
  writeRegister(position, value >> 8);
  return writeRegister(position + 1, value & 0xFF);
}

int SD2405::SRAMwrite32(uint8_t index, uint32_t value)
{
  uint32_t val = value;
  uint8_t position = SD2405_SRAM_BASE + index;
  for (int i = 0; i < 4; i++)
  {
    writeRegister(position + i, val & 0xFF);
    val >>= 8;
  }
  return SD2405_OK;
}

uint8_t SD2405::SRAMread8(uint8_t index)
{
  uint8_t position = SD2405_SRAM_BASE + index;
  return readRegister(position);
}

uint16_t SD2405::SRAMread16(uint8_t index)
{
  uint8_t position = SD2405_SRAM_BASE + index;
  uint16_t val = readRegister(position);
  val <<= 8;
  val += readRegister(position + 1);
  return val;
}

uint32_t SD2405::SRAMread32(uint8_t index)
{
  uint32_t val = 0;
  uint8_t position = SD2405_SRAM_BASE + index;
  for (int i = 3; i >= 0; i--)
  {
    val <<= 8;
    val += readRegister(position + i);
  }
  return val;
}


//  -- END OF FILE --

