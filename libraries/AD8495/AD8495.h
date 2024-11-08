#pragma once
//
//    FILE: AD8495.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2024-11-07
// PURPOSE: Arduino library for AD8495 Thermocouple
//     URL: https://github.com/RobTillaart/AD8495



#include "Arduino.h"


#define AD8495_LIB_VERSION       (F("0.1.1"))


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
    _maxVoltage = maxVoltage;
    _LSB = _maxVoltage / steps;
  };


  float getPrecision()
  {
    return _LSB;
  };


  float getVoltage(int times = 1)
  {
    float sum = 0;
    if (times < 1) times = 1;
    for (int i = 0; i < times; i++)
    {
      sum += analogRead(_apin) * _LSB;
      //  yield();
    }
    if (times > 1) sum /= times;
    return sum;
  };


  //  for external ADC
  inline float voltageToTemperatureC(float voltage)
  {
    return voltage * _DegreePerMilliVolt;
  };


  float getTemperatureC(int times = 1)
  {
    float temp = getVoltage(times) * _DegreePerMilliVolt;
    if (_offset != 0) temp += _offset;
    return temp;
  };


  float getTemperatureF(int times = 1)
  {
    return getTemperatureC(times) * 1.8 + 32.0;
  }


  void setOffset(float offset = 0)
  {
    _offset = offset;
  };


  float getOffset()
  {
    return _offset;
  };


  float getSetPointVoltage(float temperature)
  {
    return temperature / _DegreePerMilliVolt;
  };


protected:
  int   _apin;
  float _maxVoltage;
  float _LSB;

  //  degree per millivolt - investigate AN1087 if this is needed
  float _DegreePerMilliVolt = (1.0 / 5.00e-3);
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

