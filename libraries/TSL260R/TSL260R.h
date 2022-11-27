#pragma once
//
//    FILE: TSL260R.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2022-11-25
// PURPOSE: library for the TSL260R IR to voltage convertor


#define TSL260R_LIB_VERSION             (F("0.1.1"))

#include "Arduino.h"


class TSL260R
{
public:

  //  for internal ADC
  TSL260R(uint8_t pin, uint16_t maxADC, float voltage);
  //  for external ADC
  TSL260R();

  //  use internal ADC, defined in constructor
  //  uses a single analogRead() => defined by constructor.
  float    irradiance();
  //  use external (or internal) ADC voltage.
  //  e.g to average multiple analogRead() calls
  float    irradiance(float voltage);

  //  range: 800 - 1150 ==> 940 = default.
  void     setWaveLength(uint16_t waveLength = 940);
  uint16_t getWaveLength();
  float    getWaveLengthFactor();

  //  useful for debugging too
  float    calculateWaveLengthFactor(uint16_t waveLength);


protected:
  uint8_t  _pin;
  float    _voltagePerStep;
  uint16_t _waveLength;
  float    _waveLengthFactor;
  //       _aa and _bb are defined in constructor;
  //       need getter / setter to adjust values runtime
  float    _aa;
  float    _bb;
  float    multiMap(float value, float * _in, float * _out, uint8_t size);
};


///////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
class TSL261R : public TSL260R
{
public:
  TSL261R();
  TSL261R(uint8_t pin, uint16_t maxADC, float voltage);
};


class TSL262R : public TSL260R
{
public:
  TSL262R();
  TSL262R(uint8_t pin, uint16_t maxADC, float voltage);
};


// -- END OF FILE --


