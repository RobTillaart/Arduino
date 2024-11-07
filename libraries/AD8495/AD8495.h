#pragma once
//
//    FILE: AD8495.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2024-11-07
// PURPOSE: Arduino library for AD8495 Thermocouple
//     URL: https://github.com/RobTillaart/AD8495



#include "Arduino.h"


#define AD8495_LIB_VERSION       (F("0.1.0"))


////////////////////////////////////////////////
//
//  BASE CLASS
//
class AD849x
{
public:
  AD849x(int analogPin, int steps, float maxVoltage)
  {
    _apin = analogPin;
    _steps = steps;
    _maxVoltage = maxVoltage;
  };


  float getPrecision()
  {
    return _maxVoltage * (1.0 / _steps);
  };


  float getVoltage(int times = 1)
  {
    float sum = 0;
    if (times < 1) times = 1;
    for (int i = 0; i < times; i++)
    {
      sum += analogRead(_apin) * (1.0 / _steps) * _maxVoltage;
    }
    return sum / times;
  };


  //  for external ADC
  inline float voltageToTemperatureC(float voltage)
  {
    return voltage * _DmV;
  };


  float getTemperatureC(int times = 1)
  {
    float temp = getVoltage(times) * _DmV;
    if (_offset != 0) temp += _offset;
    return temp;
  };


  void setOffset(float offset)
  {
    _offset = offset;
  };


  float getOffset()
  {
    return _offset;
  };


protected:
  int _apin;
  int _steps;
  float _maxVoltage;

  //  degree per millivolt - investigate AN1087 if this is needed
  float _DmV = (1.0 / 5.00e-3);
  float _offset = 0;

  //  TODO?
  //  uint8_t _type = 0;
};


////////////////////////////////////////////////
//
//  DERIVED CLASS
//
class AD8494 : public AD849x
{
public:
  AD8494(int analogPin, int steps, float maxVoltage) 
        : AD849x(analogPin, steps, maxVoltage)
  {
  };
};

class AD8495 : public AD849x
{
public:
  AD8495(int analogPin, int steps, float maxVoltage) 
        : AD849x(analogPin, steps, maxVoltage)
  {
  };
};

class AD8496 : public AD849x
{
public:
  AD8496(int analogPin, int steps, float maxVoltage) 
        : AD849x(analogPin, steps, maxVoltage)
  {
  };
};

class AD8497 : public AD849x
{
public:
  AD8497(int analogPin, int steps, float maxVoltage) 
        : AD849x(analogPin, steps, maxVoltage)
  {
  };
};


//  -- END OF FILE --

