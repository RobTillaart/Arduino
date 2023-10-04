//
//    FILE: Max44009.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.6.0
//    DATE: 2010-??-??
// PURPOSE: library for MAX44009 lux sensor Arduino
//     URL: https://github.com/RobTillaart/MAX44009


#include "Max44009.h"

// MAX44007 KEY VALUES
#define MAX44009_MIN_LUX                       (0.045)
#define MAX44009_MAX_LUX                       (188006.0)


Max44009::Max44009(const uint8_t address, TwoWire *wire)
{
  _address = address;
  _data    = 0;
  _error   = MAX44009_OK;
  _wire    = wire;
}


bool Max44009::isConnected()
{
  _wire->beginTransmission(_address);
  _error = _wire->endTransmission();
  return (_error == 0);
}


float Max44009::getLux(void)
{
  uint8_t datahigh = read(MAX44009_LUX_READING_HIGH);
  if (_error != MAX44009_OK)
  {
    _error = MAX44009_ERROR_HIGH_BYTE;
    return _error;
  }
  uint8_t datalow = read(MAX44009_LUX_READING_LOW);
  if (_error != MAX44009_OK)
  {
    _error = MAX44009_ERROR_LOW_BYTE;
    return _error;
  }
  uint8_t exponent = datahigh >> 4;
  if (exponent == 0x0F)
  {
    _error = MAX44009_ERROR_OVERFLOW;
    return _error;
  }

  float lux = convertToLux(datahigh, datalow);
  return lux;
}


int Max44009::getError()
{
  int err = _error;
  _error = MAX44009_OK;
  return err;
}


bool Max44009::setHighThreshold(const float value)
{
  return setThreshold(MAX44009_THRESHOLD_HIGH, value);
}


float Max44009::getHighThreshold(void)
{
  return getThreshold(MAX44009_THRESHOLD_HIGH);
}


bool Max44009::setLowThreshold(const float value)
{
  return setThreshold(MAX44009_THRESHOLD_LOW, value);
}


float Max44009::getLowThreshold(void)
{
  return getThreshold(MAX44009_THRESHOLD_LOW);
}


void Max44009::setThresholdTimer(const uint8_t value)
{
  write(MAX44009_THRESHOLD_TIMER, value);
}


uint8_t Max44009::getThresholdTimer()
{
  return read(MAX44009_THRESHOLD_TIMER);
}


void Max44009::setConfiguration(const uint8_t value)
{
  write(MAX44009_CONFIGURATION, value);
}


uint8_t Max44009::getConfiguration()
{
  return read(MAX44009_CONFIGURATION);
}


void Max44009::setAutomaticMode()
{
  // CDR & TIM cannot be written in automatic mode
  uint8_t config = read(MAX44009_CONFIGURATION);
  config &= ~MAX44009_CFG_MANUAL;
  write(MAX44009_CONFIGURATION, config);
}


void Max44009::setContinuousMode()
{
  uint8_t config = read(MAX44009_CONFIGURATION);
  config |= MAX44009_CFG_CONTINUOUS;
  write(MAX44009_CONFIGURATION, config);
}


void Max44009::clrContinuousMode()
{
  uint8_t config = read(MAX44009_CONFIGURATION);
  config &= ~MAX44009_CFG_CONTINUOUS;
  write(MAX44009_CONFIGURATION, config);
}


void Max44009::setManualMode(uint8_t CDR, uint8_t TIM)
{
  if (CDR !=0) CDR = 1;    //  only 0 or 1 
  if (TIM > 7) TIM = 7;
  uint8_t config = read(MAX44009_CONFIGURATION);
  config |= MAX44009_CFG_MANUAL;
  config &= 0xF0;                     //  clear old CDR & TIM bits
  config |= CDR << 3 | TIM;           //  set new CDR & TIM bits
  write(MAX44009_CONFIGURATION, config);
}


float Max44009::convertToLux(uint8_t datahigh, uint8_t datalow)
{
  uint8_t  exponent = datahigh >> 4;
  uint32_t mantissa = ((datahigh & 0x0F) << 4) + (datalow & 0x0F);
  float lux = ((0x0001 << exponent) * MAX44009_MIN_LUX) * mantissa;
  return lux;
}


///////////////////////////////////////////////////////////
//
//  PRIVATE
//
bool Max44009::setThreshold(const uint8_t reg, const float value)
{
  //  CHECK RANGE OF VALUE
  if ((value < 0.0) || (value > MAX44009_MAX_LUX)) return false;

  uint32_t mantissa = round(value * (1.0 / MAX44009_MIN_LUX));     //  compile time optimized.
  uint8_t exponent = 0;
  while (mantissa > 255)
  {
    mantissa >>= 1;                //  bits get lost
    exponent++;
  };
  mantissa = (mantissa >> 4) & 0x0F;
  exponent <<= 4;
  write(reg, exponent | mantissa);
  return true;
}


float Max44009::getThreshold(uint8_t reg)
{
  uint8_t datahigh = read(reg);
  float lux = convertToLux(datahigh, 0x08);  //  0x08 = correction for lost bits 
  return lux;
}


uint8_t Max44009::read(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _error = _wire->endTransmission();
  if (_error != MAX44009_OK)
  {
    return _data;           //  last value
  }
  if (_wire->requestFrom(_address, (uint8_t) 1) != 1)
  {
    _error = MAX44009_ERROR_WIRE_REQUEST;
    return _data;           //  last value
  }
  _data = _wire->read();
  return _data;
}


void Max44009::write(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value);
  _error = _wire->endTransmission();
}


//  -- END OF FILE --
