#pragma once
//
//    FILE: TSW10.h
//  AUTHOR: Rob Tillaart
//    DATE: 2026-05-22
// VERSION: 0.1.0
// PURPOSE: Arduino library for TSW10 analog turbidity sensor.
//     URL: https://github.com/RobTillaart/TSW10
//


#include "Arduino.h"


#define TSW10_LIB_VERSION         (F("0.1.0"))


class TSW10
{
public:
  TSW10(uint8_t analogPin);

  bool     begin(float voltage, uint16_t maxSteps);

  //       READ
  float    getVoltage(int times = 1);
  float    getNTU(int times = 1);
  //  can be used with an external ADC
  float    volts2NTU(float volts);

  uint32_t lastRead();

private:
  uint8_t  _apin;
  float    _VoltsPerStep;

  uint32_t _lastRead;
};


//  -- END OF FILE --


