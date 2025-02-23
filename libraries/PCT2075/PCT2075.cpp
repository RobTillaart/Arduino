//
//    FILE: PCT2075.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-02-11
// VERSION: 0.1.1
// PURPOSE: Arduino library for I2C PCT2075 temperature sensor / thermal watchdog.
//     URL: https://github.com/RobTillaart/PCT2075


#include "PCT2075.h"


//  REGISTERS
#define PCT2075_TEMPERATURE         0x00
#define PCT2075_CONFIGURATION       0x01
#define PCT2075_HYSTERESIS          0x02
#define PCT2075_OVER_TEMPERATURE    0x03
#define PCT2075_IDLE_REGISTER       0x04


PCT2075::PCT2075(const uint8_t address, TwoWire * wire)
{
  _address = address;
  _wire = wire;
}

bool PCT2075::begin()
{
  if (! isConnected()) return false;
  return true;
}

bool PCT2075::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


uint8_t PCT2075::getAddress()
{
  return _address;
}


/////////////////////////////////////////////////////////
//
//  CONFIGURATION
//
void PCT2075::setConfiguration(uint8_t mask)
{
  _write8(PCT2075_CONFIGURATION, mask);
}

uint8_t PCT2075::getConfiguration()
{
  return _read8(PCT2075_CONFIGURATION);
}

void PCT2075::setOSFQUE(uint8_t value)
{
  if (value > 3)
  {
    _error = PCT2075_PARAM_ERROR;
    return;  //  bool false? to indicate error
  }
  uint8_t mask = _read8(PCT2075_CONFIGURATION);
  mask &= 0xE7;
  mask |= (value << 3);
  _write8(PCT2075_CONFIGURATION, mask);
}

void PCT2075::setOSPolarityLOW()
{
  uint8_t mask = _read8(PCT2075_CONFIGURATION);
  mask &= 0xFB;
  _write8(PCT2075_CONFIGURATION, mask);
}

void PCT2075::setOSPolarityHIGH()
{
  uint8_t mask = _read8(PCT2075_CONFIGURATION);
  mask |= 0x04;
  _write8(PCT2075_CONFIGURATION, mask);
}

void PCT2075::setOSComparatorMode()
{
  uint8_t mask = _read8(PCT2075_CONFIGURATION);
  mask &= 0xFD;
  _write8(PCT2075_CONFIGURATION, mask);
}

void PCT2075::setOSInterruptMode()
{
  uint8_t mask = _read8(PCT2075_CONFIGURATION);
  mask |= 0x02;
  _write8(PCT2075_CONFIGURATION, mask);
}

void PCT2075::wakeUp()
{
  uint8_t mask = _read8(PCT2075_CONFIGURATION);
  mask &= 0xFE;
  _write8(PCT2075_CONFIGURATION, mask);
}

void PCT2075::shutDown()
{
  uint8_t mask = _read8(PCT2075_CONFIGURATION);
  mask |= 0x01;
  _write8(PCT2075_CONFIGURATION, mask);
}


/////////////////////////////////////////////////////////
//
//  TEMPERATURE
//
float PCT2075::getTemperature()
{
  int16_t raw = _read16(PCT2075_TEMPERATURE);
  float temp = raw * (0.125 / 32.0);  // 32 to get from 16 bit => 11 bit.
  return temp;
}


//  OPERATING MODE - OS pin => datasheet section 7
void PCT2075::setHysteresis(float temp)
{
  uint16_t raw = int16_t(temp * 512.0);
  _write16(PCT2075_HYSTERESIS, raw);
}

float PCT2075::getHysteresis()
{
  int16_t raw = _read16(PCT2075_HYSTERESIS);
  float temp = raw * (1.0 / 512.0);
  return temp;
}

void PCT2075::setOverTemperature(float temp)
{
  uint16_t raw = int16_t(temp * 512.0);
  _write16(PCT2075_OVER_TEMPERATURE, raw);
}

float PCT2075::getOverTemperature()
{
  int16_t raw = _read16(PCT2075_OVER_TEMPERATURE);
  float temp = raw * (1.0 / 512.0);
  return temp;
}


//  SAMPLE FREQUENCY
void PCT2075::setSampleDelay(uint8_t steps)
{
  if (steps > 31) steps = 31;
  _write8(PCT2075_IDLE_REGISTER, steps);
}

uint8_t PCT2075::getSampleDelay()
{
  int8_t raw = _read8(PCT2075_IDLE_REGISTER);
  return raw;
}

uint16_t PCT2075::lastError()
{
  return _error;
}


uint16_t PCT2075::_read8(uint8_t reg)
{
  _error = PCT2075_OK;
  //  improve the odds that IO will not interrupted.
  yield();

  _wire->beginTransmission(_address);
  _wire->write(reg);
  if (_wire->endTransmission() != 0)
  {
    _error = PCT2075_I2C_ERROR;
    return 0xFFFF;
  }
  if (1 != _wire->requestFrom(_address, (uint8_t)1))
  {
    _error = PCT2075_I2C_ERROR;
    return 0xFFFF;
  }
  uint8_t value = _wire->read();
  return value;
}


uint16_t PCT2075::_read16(uint8_t reg)
{
  _error = PCT2075_OK;
  //  improve the odds that IO will not interrupted.
  yield();

  _wire->beginTransmission(_address);
  _wire->write(reg);
  if (_wire->endTransmission() != 0)
  {
    _error = PCT2075_I2C_ERROR;
    return 0xFFFF;
  }
  if (2 != _wire->requestFrom(_address, (uint8_t)2))
  {
    _error = PCT2075_I2C_ERROR;
    return 0xFFFF;
  }
  uint16_t value = _wire->read();
  value <<= 8;
  value += _wire->read();
  return value;
}


uint16_t PCT2075::_write8(uint8_t reg, uint8_t value)
{
  _error = PCT2075_OK;
  //  improve the odds that IO will not interrupted.
  yield();

  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value);
  if (_wire->endTransmission() != 0)
  {
    _error = PCT2075_I2C_ERROR;
  }
  return _error;
}


uint16_t PCT2075::_write16(uint8_t reg, uint16_t value)
{
  _error = PCT2075_OK;
  //  improve the odds that IO will not interrupted.
  yield();

  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value >> 8);
  _wire->write(value & 0xFF);
  if (_wire->endTransmission() != 0)
  {
    _error = PCT2075_I2C_ERROR;
  }
  return _error;
}


//  -- END OF FILE --

