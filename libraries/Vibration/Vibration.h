#pragma once
//
//    FILE: Vibration.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
//    DATE: 2024-04-24
// PURPOSE: Arduino library for a vibration / tilt sensor e.g. SW-420, SW-18010P.
//     URL: https://github.com/RobTillaart/Vibration


#include "Arduino.h"

#define VIBRATION_LIB_VERSION                 (F("0.2.1"))


class VibrationSensor
{
public:
  explicit VibrationSensor(uint8_t analogPin)
  {
    _analogPin = analogPin;
    _samples = 0;
    _maxValue = 0;
    _zeroCount = 0;
    _sum = 0;
    _noiseLevel = 10;
  }


  bool begin()
  {
    //  what to do here?
    return true;
  }


  void setNoiseLevel(uint16_t noise = 10)
  {
    _noiseLevel = noise;
  }


  uint16_t getNoiseLevel()
  {
    return _noiseLevel;
  }


  uint32_t measure(uint32_t duration, bool reset = true)
  {
    if (reset)
    {
      _samples = 0;
      _maxValue = 0;
      _zeroCount = 0;
      _sum = 0;
    }
    uint32_t start = micros();
    do
    {
      uint16_t value = analogRead(_analogPin);
      _sum += value;
      if (value <= _noiseLevel) _zeroCount++;
      if (value > _maxValue) _maxValue = value;
      _samples++;
    }
    while ((micros() - start) < duration);
    return _samples;
  }


  float zeroCount()
  {
    return (100.0 * _zeroCount) / _samples;
  }


  uint32_t sampleCount()
  {
    return _samples;
  }


  float average()
  {
    if (_samples == 1) return _sum;
    return (1.0 * _sum) / _samples;
  }


  uint16_t maxValue()
  {
    return _maxValue;
  }


  uint32_t sum()
  {
    return _sum;
  }


protected:
  uint8_t  _analogPin;
  uint16_t _noiseLevel;

  uint32_t _samples;
  uint16_t _maxValue;
  uint16_t _zeroCount;
  uint32_t _sum;
};


/*

interrupt count / timing?

analog for signal strength?

*/


//  -- END OF FILE --

