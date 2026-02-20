//
//    FILE: MAX30205.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-02-19
// VERSION: 0.1.1
// PURPOSE: Arduino library for MAX30205
//     URL: https://github.com/RobTillaart/MAX30205



#include "MAX30205.h"

//  register constants
const int MAX30205_REG_TEMPERATURE = 0x00;
const int MAX30205_REG_CONFIG      = 0x01;
const int MAX30205_REG_HYSTERESIS  = 0x02;
const int MAX30205_REG_OVERTEMP    = 0x04;  //  aka OverTemp ShutDown

//  other constants
const float MAX30205_LSB = 0.00390625f;


MAX30205::MAX30205(uint8_t address, TwoWire *wire)
{
  _address     = address;
  _wire        = wire;
  _error       = MAX30205_OK;
  _lastRead    = 0;
  _temperature = 0.0f;
}


bool MAX30205::begin()
{
  //  reset variables
  _error       = MAX30205_OK;
  _lastRead    = 0;
  _temperature = 0.0f;

  if (! isConnected())
  {
    return false;
  }
  return true;
}


bool MAX30205::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}


uint8_t MAX30205::getAddress()
{
  return _address;
}


/////////////////////////////////////////////
//
//  READ
//
bool MAX30205::read()
{
  Serial.println(".");
  uint16_t raw = readRegister(MAX30205_REG_TEMPERATURE, 2);
  if (_error != MAX30205_OK)
  {
    //  other error value? -999.0f;
    return false;
  }
  _lastRead = millis();
  _temperature = int16_t(raw) * MAX30205_LSB;
  return true;
}

float MAX30205::getTemperature()
{
  return _temperature;
}

float MAX30205::getAccuracy()
{
  if (_temperature < 15.0) return 0.5;
  if (_temperature < 35.8) return 0.3;
  if (_temperature < 37.0) return 0.2;
  if (_temperature < 39.0) return 0.1;
  if (_temperature < 41.8) return 0.2;
  if (_temperature < 45.0) return 0.3;
  //  > 45C
  return 0.5;
}


/////////////////////////////////////////////
//
//  CONFIGURATION
//  datasheet page 12, 13
void MAX30205::setConfig(uint8_t mask)
{
  writeRegister(MAX30205_REG_CONFIG, mask, 1);
}

uint8_t MAX30205::getConfig()
{
  uint8_t raw = readRegister(MAX30205_REG_CONFIG, 1);
  return raw;
}

//  TODO optimize.
void MAX30205::shutDown()
{
  uint8_t raw = getConfig();
  if ((raw & 0x01) == 0x01) return;
  setConfig(raw | 0x01);
}

void MAX30205::wakeUp()
{
  uint8_t raw = getConfig();
  if ((raw & 0x01) == 0x00) return;
  setConfig(raw & ~0x01);
}

void MAX30205::setModeInterrupt()
{
  uint8_t raw = getConfig();
  if ((raw & 0x02) == 0x02) return;
  setConfig(getConfig() | 0x02);
}

void MAX30205::setModeComparator()
{
  uint8_t raw = getConfig();
  if ((raw & 0x02) == 0x00) return;
  setConfig(getConfig() & ~0x02);
}

void MAX30205::setPolarity(uint8_t polarity)
{
  uint8_t raw = getConfig();
  if (polarity == 0) setConfig(raw & ~0x04);
  else               setConfig(raw | 0x04);
}

void MAX30205::setFaultQueLevel(uint8_t level)
{
  if (level > 3) return;
  uint8_t raw = getConfig();
  uint8_t previous = raw;
  raw = raw & 0xE7;  //  clear bits
  raw = raw | (level << 3);
  if (raw != previous) setConfig(raw);
}

void MAX30205::setDataFormat(uint8_t range)
{
  if (range > 1) return;
  uint8_t raw = getConfig();
  uint8_t previous = raw;
  raw = raw & ~(1 << 5);  //  clear bits
  if (range == 1) raw = raw | (1 << 5);
  if (raw != previous) setConfig(raw);
}

void MAX30205::setTimeout(uint8_t timeout)
{
  if (timeout > 1) return;
  uint8_t raw = getConfig();
  uint8_t previous = raw;
  raw = raw & ~(1 << 6);  //  clear bits
  if (timeout == 1) raw = raw | (1 << 6);
  if (raw != previous) setConfig(raw);
}

void MAX30205::setModeContinuous()
{
}

void MAX30205::setModeOneShot()
{
  //  datasheet page 13
  //  might be optimizable in one call.
  //  must be in shutdown mode
  uint8_t raw = getConfig();
  if ((raw & 0x01) == 0x00)  //  if not in shutdown?
  {
    //  shutdown!
    raw = raw | 0x01;
    setConfig(raw);
  }
  //  one shot
  raw = raw | 0x80;
  setConfig(raw);
}



/////////////////////////////////////////////
//
//  HYSTERESIS & OVERTEMP
//
bool MAX30205::setHysteresis(float Celsius)
{
  //  TODO neg values?
  uint16_t raw = Celsius / MAX30205_LSB;
  writeRegister(MAX30205_REG_HYSTERESIS, raw, 2);
  return (_error == MAX30205_OK);
}

float MAX30205::getHysteresis()
{
  uint16_t raw = readRegister(MAX30205_REG_HYSTERESIS, 2);
  return int16_t(raw) * MAX30205_LSB;
}

bool MAX30205::setOverTemperature(float Celsius)
{
  //  TODO neg values?
  uint16_t raw = Celsius / MAX30205_LSB;
  writeRegister(MAX30205_REG_OVERTEMP, raw, 2);
  return (_error == MAX30205_OK);
}

float MAX30205::getOverTemperature()
{
  uint16_t raw = readRegister(MAX30205_REG_OVERTEMP, 2);
  return int16_t(raw) * MAX30205_LSB;
}


/////////////////////////////////////////////
//
//  DEBUG
//
uint32_t MAX30205::lastRead()
{
  return _lastRead;
}


uint16_t MAX30205::lastError()
{
  uint16_t e = _error;
  _error = MAX30205_OK;
  return e;
}


///////////////////////////////////////////////
//
//  PRIVATE
//

uint16_t MAX30205::writeRegister(uint8_t reg, uint16_t value, uint8_t bytes)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  //  CHECK
  if (bytes == 2) _wire->write(value >> 8);
  _wire->write(value &0xFF);
  _error = _wire->endTransmission();
  return _error;
}


uint16_t MAX30205::readRegister(uint8_t reg, uint8_t bytes)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _error = _wire->endTransmission();
  if (_error != MAX30205_OK)
  {
    return _error;
  }
  uint8_t n = _wire->requestFrom(_address, bytes);
  if (n == 0)
  {
    _error = MAX30205_NOT_READY;
    return _error;
  }
  if (n < bytes)
  {
    _error = MAX30205_REQUEST_ERROR;
    return _error;
  }

  uint16_t raw = _wire->read();
  if (n == 2)
  {
    raw <<= 8;
    raw |= _wire->read();
  }
  return _error;
}



//  -- END OF FILE --

