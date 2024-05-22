//
//    FILE: Max44007.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
//    DATE: 2022-01-04
// PURPOSE: library for Max44007 lux sensor Arduino
//     URL: https://github.com/RobTillaart/MAX44007


#include "Max44007.h"


//  MAX44007 KEY VALUES
#define MAX44007_MIN_LUX                       (0.025)
#define MAX44007_MAX_LUX                       (104448.0)


Max44007::Max44007(const uint8_t address, TwoWire *wire)
{
  _address = address;
  _data    = 0;
  _error   = MAX44007_OK;
  _wire    = wire;
}


bool Max44007::isConnected()
{
  _wire->beginTransmission(_address);
  _error = _wire->endTransmission();
  return (_error == 0);
}


uint8_t Max44007::getAddress()
{
  return _address;
}


float Max44007::getLux(void)
{
  uint8_t datahigh = read(MAX44007_LUX_READING_HIGH);
  if (_error != MAX44007_OK)
  {
    _error = MAX44007_ERROR_HIGH_BYTE;
    return _error;
  }
  uint8_t datalow = read(MAX44007_LUX_READING_LOW);
  if (_error != MAX44007_OK)
  {
    _error = MAX44007_ERROR_LOW_BYTE;
    return _error;
  }
  uint8_t exponent = datahigh >> 4;
  if (exponent == 0x0F)
  {
    _error = MAX44007_ERROR_OVERFLOW;
    return _error;
  }

  float lux = convertToLux(datahigh, datalow);
  return lux;
}


int Max44007::getError()
{
  int err = _error;
  _error = MAX44007_OK;
  return err;
}


bool Max44007::setHighThreshold(const float value)
{
  return setThreshold(MAX44007_THRESHOLD_HIGH, value);
}


float Max44007::getHighThreshold(void)
{
  return getThreshold(MAX44007_THRESHOLD_HIGH);
}


bool Max44007::setLowThreshold(const float value)
{
  return setThreshold(MAX44007_THRESHOLD_LOW, value);
}


float Max44007::getLowThreshold(void)
{
  return getThreshold(MAX44007_THRESHOLD_LOW);
}


void Max44007::setThresholdTimer(const uint8_t value)
{
  write(MAX44007_THRESHOLD_TIMER, value);
}


uint8_t Max44007::getThresholdTimer()
{
  return read(MAX44007_THRESHOLD_TIMER);
}


void Max44007::setConfiguration(const uint8_t value)
{
  write(MAX44007_CONFIGURATION, value);
}


uint8_t Max44007::getConfiguration()
{
  return read(MAX44007_CONFIGURATION);
}


void Max44007::setAutomaticMode()
{
  //  CDR & TIM cannot be written in automatic mode
  uint8_t config = read(MAX44007_CONFIGURATION);
  config &= ~MAX44007_CFG_MANUAL;
  write(MAX44007_CONFIGURATION, config);
}


void Max44007::setContinuousMode()
{
  uint8_t config = read(MAX44007_CONFIGURATION);
  config |= MAX44007_CFG_CONTINUOUS;
  write(MAX44007_CONFIGURATION, config);
}


void Max44007::clrContinuousMode()
{
  uint8_t config = read(MAX44007_CONFIGURATION);
  config &= ~MAX44007_CFG_CONTINUOUS;
  write(MAX44007_CONFIGURATION, config);
}


void Max44007::setManualMode(uint8_t CDR, uint8_t TIM)
{
  if (CDR !=0) CDR = 1;    //  only 0 or 1
  if (TIM > 7) TIM = 7;
  uint8_t config = read(MAX44007_CONFIGURATION);
  config |= MAX44007_CFG_MANUAL;
  config &= 0xF0;                     //  clear old CDR & TIM bits
  config |= CDR << 3 | TIM;           //  set new CDR & TIM bits
  write(MAX44007_CONFIGURATION, config);
}


int Max44007::getCurrentDivisorRatio()
{
  uint8_t CDR = read(MAX44007_CONFIGURATION) & 0x08;
  return CDR >> 3;
}


int Max44007::getIntegrationTime()
{
  uint8_t TIM = read(MAX44007_CONFIGURATION) & 0x07;
  return 800 >> TIM;
}


//  datahigh = [eeee mmmm]
//  datalow  = [     mmmm]
float Max44007::convertToLux(uint8_t datahigh, uint8_t datalow)
{
  uint8_t  exponent = datahigh >> 4;
  uint32_t mantissa = ((datahigh & 0x0F) << 4) + (datalow & 0x0F);
  float lux = ((0x0001 << exponent) * MAX44007_MIN_LUX) * mantissa;
  return lux;
}


///////////////////////////////////////////////////////////
//
//  PRIVATE
//
bool Max44007::setThreshold(const uint8_t reg, const float value)
{
  //  CHECK RANGE OF VALUE
  if ((value < 0.0) || (value > MAX44007_MAX_LUX)) return false;

  //  compile time optimized.
  uint32_t mantissa = round(value * (1.0 / MAX44007_MIN_LUX));
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


float Max44007::getThreshold(uint8_t reg)
{
  uint8_t datahigh = read(reg);
  //  0x08 = correction for lost bits
  float lux = convertToLux(datahigh, 0x08);
  return lux;
}


uint8_t Max44007::read(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _error = _wire->endTransmission();
  if (_error != MAX44007_OK)
  {
    return _data;           //  last value
  }
  if (_wire->requestFrom(_address, (uint8_t) 1) != 1)
  {
    _error = MAX44007_ERROR_WIRE_REQUEST;
    return _data;           //  last value
  }
  _data = _wire->read();
  return _data;
}


void Max44007::write(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value);
  _error = _wire->endTransmission();
}


//  -- END OF FILE --
