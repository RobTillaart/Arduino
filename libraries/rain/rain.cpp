//
//    FILE: rain.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2021-12-03
// PURPOSE: Arduino library for a rain sensor
//     URL: https://github.com/RobTillaart/RAIN
//          https://www.tinytronics.nl/shop/nl/sensoren/vloeistof/regensensor


#include "rain.h"

RAIN::RAIN(uint8_t port)
{
  _port       = port;
  _maxVoltage = 5;
  _maxSteps   = 1023;
}


bool RAIN::begin(float maxVoltage, uint16_t maxSteps)
{
  _maxVoltage = maxVoltage;
  _maxSteps   = maxSteps;
  _mVstep = _maxVoltage / _maxSteps;
  read();
  return true;
}


float RAIN::raw(uint8_t times)
{
  if (times == 0) times = 1;
  float sum = 0;
  for (int i = 0; i < times; i++)
  {
    sum += analogRead(_port);
  }
  if (times > 1) sum /= times;
  return sum;
}


float RAIN::read(uint8_t times)
{
  _voltage = raw(times) * _mVstep;
  return _voltage;
}


float RAIN::percentage()
{
  return _voltage * 100.0 / _maxVoltage;
}


bool RAIN::setLevel(uint8_t nr, float voltage)
{
  if (nr == 0) return false;
  if (nr > 4) return false;
  _level[nr] = voltage;
  return true;
}


uint8_t RAIN::getLevel()
{
  for (int index = 4; index > 0; index--)
  {
    if (_voltage >= _level[index]) return index;
  }
  return 0;
}


//  -- END OF FILE --

