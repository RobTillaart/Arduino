#pragma once
//
//    FILE: Vibration.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2024-04-24
// PURPOSE: Arduino library for a vibration / tilt sensor e.g. SW-420, SW-18010P.
//     URL: https://github.com/RobTillaart/Vibration


#include "Arduino.h"

#define VIBRATION_LIB_VERSION                 (F("0.1.1"))


class VibrationSensor
{
public:
  explicit VibrationSensor(uint8_t analogPin)
  {
    _analogPin = analogPin;
  }


  bool begin()
  {
    // what to do here?
    return true;
  }


  float zeroCount(uint32_t duration, uint16_t noise = 10)
  {
    uint16_t count = 0;
    uint16_t total = 0;
    uint32_t start = millis();
    do
    {
      if (analogRead(_analogPin) <= noise) count++;
      total++;
    }
    while ((millis() - start) < duration);
    return 100.0 * count / total;
  }


  float average(uint32_t duration)
  {
    float sum = 0;
    uint32_t samples = 0;
    uint32_t start = millis();
    do
    {
      sum += analogRead(_analogPin);
      samples++;
    }
    while ((millis() - start) < duration);
    if (samples > 1) sum /= samples;
    return sum;
  }


  uint16_t poll(uint32_t duration)
  {
    uint16_t maxValue = 0;
    uint32_t start = millis();
    do
    {
      uint16_t val = analogRead(_analogPin);
      if (val > maxValue) maxValue = val;
    }
    while ((millis() - start) < duration);
    return maxValue;
  }


protected:
  uint8_t _analogPin;
  uint16_t _noiseLevel = 0;  //  to be detected automatically.
};


/*

interrupt count / timing?

analog for signal strength?

*/


//  -- END OF FILE --

