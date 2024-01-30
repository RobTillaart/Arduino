//
//    FILE: MAX471.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2024-01-30
// PURPOSE: Arduino library for MAX471 current sensor.
//     URL: https://github.com/RobTillaart/MAX471_RT


#include "MAX471.h"


/////////////////////////////////////////////////////////////////////////////
//
//  CONSTRUCTOR
//
MAX471::MAX471(uint8_t currentPin, uint8_t voltagePin)
{
  _currentPin = currentPin;
  _voltagePin = voltagePin;
  _signPin    = 255;
  _current    = 0;
  _voltage    = 0;
}


MAX471::MAX471(uint8_t currentPin, uint8_t voltagePin, uint8_t signPin)
{
  _currentPin = currentPin;
  _voltagePin = voltagePin;
  _signPin    = signPin;
  _current    = 0;
  _voltage    = 0;
  pinMode(_signPin, INPUT_PULLUP);
}


void MAX471::begin(float maxVoltage, uint16_t maxSteps)
{
  _units = maxVoltage / maxSteps;
}


float MAX471::readCurrent(uint8_t times)
{
  if (times == 0) times = 1;
  uint8_t _times = times;
  float sum = 0;
  while (_times--)
  {
    sum += analogRead(_currentPin) ;
  }
  _current = sum * _units / times;
  if (_signPin != 255) 
  {
    if (digitalRead(_signPin) == HIGH)
    {
      _current *= -1;
    }
  }
  return _current;
}


float MAX471::readCurrentMilliAmpere(uint8_t times)
{
  return readCurrent(times) * 1000;
}


float MAX471::readVoltage(uint8_t times)
{
  if (times == 0) times = 1;
  uint8_t _times = times;
  float sum = 0;
  while (_times--)
  {
    sum += analogRead(_voltagePin);
  }
  _voltage = sum * _units / times;
  return _voltage;
}


float MAX471::readVoltageMilliVolts(uint8_t times)
{
  return readVoltage(times) * 1000;
}


float MAX471::calcPower()
{
  return _current * _voltage;
}


float MAX471::calcPowerMilliWatt()
{
  return _current * _voltage * 1000;
}


//  -- END OF FILE --

