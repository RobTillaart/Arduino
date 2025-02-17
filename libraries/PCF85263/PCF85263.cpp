//
//    FILE: PCF85263.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-02-17
// VERSION: 0.1.0
// PURPOSE: Arduino library for the PCF85263 RTC.
//     URL: https://github.com/RobTillaart/PCF85263



#include "PCF85263.h"


PCF85263::PCF85263(TwoWire *wire)
{
  _wire     = wire;
  _error    = 0;
  _lastRead = 0;
}


int PCF85263::begin()
{
  //  reset variables
  _error = 0;
  _lastRead = 0;
  if (! isConnected())
  {
    return false;
  }
  return true;
}


bool PCF85263::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}


uint8_t PCF85263::getAddress()
{
  return _address;
}


/////////////////////////////////////////////////////////
//
//  CORE
//
int PCF85263::readDateTime()
{
  _wire->beginTransmission(_address);
  _wire->write(PCF85263_SECONDS);
  _rv = _wire->endTransmission();
  if (_rv != 0) return PCF85263_ERROR_I2C;

  if (_wire->requestFrom(_address, (uint8_t)7) != 7)
  {
    return PCF85263_ERROR_I2C;
  }
  for (int i = 0; i < 7; i++)
  {
    _reg[i] = bcd2dec(_wire->read());
  }
  _lastRead = millis();

  return PCF85263_OK;
}


int PCF85263::writeDateTime()
{
  stopRTC();
  int _rv = PCF85263_OK;
  _wire->beginTransmission(_address);
  _wire->write(PCF85263_SECONDS);
  for (int i = 0; i < 7; i++)
  {
    _wire->write(dec2bcd(_reg[i]));
  }
  _rv = _wire->endTransmission();
  if (_rv != 0) _rv = PCF85263_ERROR_I2C;
  startRTC();
  return _rv;
}


uint32_t PCF85263::lastRead()
{
  return _lastRead;
}


/////////////////////////////////////////////////////////
//
//  GETTERS
//
uint8_t PCF85263::seconds() { return _reg[0] & 0x7F; }
uint8_t PCF85263::minutes() { return _reg[1] & 0x7F; }
uint8_t PCF85263::hours()   { return _reg[2] & 0x3F; }
uint8_t PCF85263::weekDay() { return _reg[3] & 0x3F; }
uint8_t PCF85263::day()     { return _reg[4] & 0x07; }
uint8_t PCF85263::month()   { return _reg[5] & 0x1F; }
uint8_t PCF85263::year()    { return _reg[6] & 0xFF; }


/////////////////////////////////////////////////////////
//
//  SETTERS
//
void PCF85263::setSeconds(uint8_t value) { _reg[0] = value; }
void PCF85263::setMinutes(uint8_t value) { _reg[1] = value; }
void PCF85263::setHours(uint8_t value)   { _reg[2] = value; }
void PCF85263::setWeekDay(uint8_t value) { _reg[3] = value; }
void PCF85263::setDay(uint8_t value)     { _reg[4] = value; }
void PCF85263::setMonth(uint8_t value)   { _reg[5] = value; }
void PCF85263::setYear(uint8_t value)    { _reg[6] = value; }


/////////////////////////////////////////////////////////
//
//  FUNCTION
//
void PCF85263::setRTCmode(uint8_t mode)
{
  if (mode > 1) return;
  uint8_t mask = readRegister(PCF85263_FUNCTION);
  mask &= 0xEF;
  if (mode == 1) mask |= 0x10;
  writeRegister(PCF85263_FUNCTION, mask);
}

void PCF85263::startRTC()
{
  writeRegister(PCF85263_STOP_ENABLE, 0);
}

void PCF85263::stopRTC()
{
  writeRegister(PCF85263_STOP_ENABLE, 1);
}


/////////////////////////////////////////////////////////
//
//  LOW LEVEL
//
int PCF85263::readRegister(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _rv = _wire->endTransmission();
  if (_rv != 0) return PCF85263_ERROR_I2C;

  if (_wire->requestFrom(_address, (uint8_t)1) != 1)
  {
    return PCF85263_ERROR_I2C;
  }
  return _wire->read();
}

int PCF85263::writeRegister(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value);
  _rv = _wire->endTransmission();
  if (_rv != 0) return PCF85263_ERROR_I2C;
  return PCF85263_OK;
}

int PCF85263::getLastI2Cstate()
{
  return _rv;
}


/////////////////////////////////////////////////////////
//
//  PRIVATE
//

uint8_t PCF85263::dec2bcd(uint8_t value)
{
  return value + 6 * (value / 10);
}


uint8_t PCF85263::bcd2dec(uint8_t value)
{
  return value - 6 * (value >> 4);
}




//  -- END OF FILE --

