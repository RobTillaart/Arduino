#pragma once
//
//    FILE: TEMT6000.h
//  AUTHOR: Rob Tillaart
//    DATE: 2024-11-26
// VERSION: 0.1.1
// PURPOSE: Arduino library for TEMT6000 light / LUX sensor.
//     URL: https://github.com/RobTillaart/TEMT6000
//          https://forum.arduino.cc/t/temt6000-light-sensor-resistor/1239046


#include "Arduino.h"


#define TEMT6000_LIB_VERSION              (F("0.1.1"))

class TEMT6000
{
public:
  TEMT6000(uint8_t pin, float volts, uint16_t steps)
  {
    _resistor = 1e4;
    _pin = pin;
    _volts = volts;
    _steps = steps;
    _voltsPerStep = volts / steps;
  }

  void setResistor(uint16_t resistor)
  {
    _resistor = resistor;
  }

  uint16_t getResistor()
  {
    return _resistor;
  }

  uint16_t readRaw(uint8_t times = 1)
  {
    uint16_t raw = 0;
    for (int i = 0; i < times; i++)
    {
      raw += analogRead(_pin);
    }
    if (times > 1) raw /= times;
    return raw;
  }

  float readLUX(uint8_t times = 1)
  {
    uint16_t raw = readRaw(times);
    float volts = raw * _voltsPerStep;
    float current = volts / _resistor;
    //  1 LUX = 2 micro ampere (inverted)
    //  2 uA is based upon fig 3 in datasheet.
    return current / 2e-6;  
  }

  float readLUX(uint8_t times, float angleDegrees)
  {
    //  check range..
    if ((angleDegrees < 0.0) || (angleDegrees > 89.0))
    {
      return -1;
    }
    float lux = readLUX(times);
    float factor = cos(angleDegrees * (PI / 180.0));
    return lux / factor; 
  }


protected:
  uint8_t  _pin;
  uint16_t _resistor;
  float    _volts;
  uint16_t _steps;
  float    _voltsPerStep;

};


//  -- END OF FILE --

