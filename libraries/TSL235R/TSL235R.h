#pragma once
//
//    FILE: TSL235R.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: library fot the TSL235R light to frequency convertor


#define TSL235R_LIB_VERSION     (F("0.1.0"))

#include "Arduino.h"


class TSL235R
{
public:

  TSL235R(float voltage = 5.0);

  float    irradiance(uint32_t Hz);
  float    irradiance(uint32_t pulses, uint32_t milliseconds);
  float    getFactor()           { return _factor; };

  void     setWavelength(uint16_t wavelength = 635);
  uint16_t getWavelength()       { return _waveLength; }
  float    getWaveLengthFactor() { return _waveLengthFactor; }

  void     setVoltage(float voltage = 5.0);
  float    getVoltage()          { return _voltage; };
  float    getVoltageFactor()    { return _voltageFactor; };

private:
  uint16_t _waveLength       = 635;
  float    _waveLengthFactor = 1.0;
  float    _voltage          = 5.0;
  float    _voltageFactor    = 1.0;
  float    _factor           = 1.2;

  void     calculateFactor();
  float    calcWLF(uint16_t _waveLength);
  float    multiMap(float val, float * _in, float * _out, uint8_t size);
};


// -- END OF FILE --
