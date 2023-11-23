#pragma once
//
//    FILE: TSL235R.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.5
//    DATE: 2020-05-29
// PURPOSE: library for the TSL235R light to frequency convertor
//     URL: https://github.com/RobTillaart/TSL235R


#define TSL235R_LIB_VERSION             (F("0.1.5"))

#include "Arduino.h"

#if not defined(TSL235_DEFAULT_VOLTAGE)
#define TSL235_DEFAULT_VOLTAGE    5.0
#endif

class TSL235R
{
public:

  TSL235R(float voltage = TSL235_DEFAULT_VOLTAGE);

  //  Hz == pulses in one second.
  //        could be calculated from shorter/longer measurement.
  float    irradiance(uint32_t Hz);
  float    irradiance(uint32_t pulses, uint32_t milliseconds);
  float    irradiance_HS(uint32_t pulses, uint32_t microseconds);
  float    getFactor();

  void     setWavelength(uint16_t wavelength = 635);
  uint16_t getWavelength();
  float    getWaveLengthFactor();

  void     setVoltage(float voltage = TSL235_DEFAULT_VOLTAGE);
  float    getVoltage();
  float    getVoltageFactor();


private:
  uint16_t _waveLength       = 635;
  float    _waveLengthFactor = 1.0;
  float    _voltageFactor    = 1.0;
  float    _voltage;
  float    _factor;

  void     calculateFactor();
  float    calculateWaveLengthFactor(uint16_t _waveLength);
  float    multiMap(float value, float * _in, float * _out, uint8_t size);
};


//  -- END OF FILE --

