#pragma once
//
//    FILE: TRAFO.h
//  AUTHOR: Rob Tillaart
//    DATE: 2026-03-13
// VERSION: 0.1.0
// PURPOSE: Arduino library for AC line voltage and frequency measurement.
//     URL: https://github.com/RobTillaart/TRAFO
//


#include "Arduino.h"


#define TRAFO_LIB_VERSION         (F("0.1.0"))


class TRAFO
{
public:
  TRAFO() {};

  bool begin(int32_t (* readADC)(), uint32_t steps, float maxVoltage)
  {
    _readADC = readADC;
    _steps = steps;
    _zeroPoint = steps / 2;  //  reasonable initial value
    _voltsPerStep = maxVoltage / steps;

    detectFrequency();
    return true;
  };


  //  based upon https://github.com/RobTillaart/ACS712
  //  at least 10 Hz.
  float detectFrequency(uint8_t times = 1)
  {
    if (times < 1) times = 1;
    int32_t minimum = 0;
    int32_t maximum = 0;
    minimum = maximum = _readADC();

    uint32_t timeOut = 100000;
    uint32_t start = micros();
    while (micros() - start < timeOut)
    {
      int32_t value = _readADC();
      if      (value < minimum) minimum = value;
      else if (value > maximum) maximum = value;
    }
    _zeroPoint = (minimum + maximum) / 2;

    //  calculate quarter points
    //  using quarter points is less noise prone
    //  than using one single midpoint
    int32_t Q1 = (3 * minimum + maximum ) / 4;
    int32_t Q3 = (minimum + 3 * maximum ) / 4;

    //  10x passing Quantile points
    //  wait for the right moment to start
    //  to prevent endless loop a timeOut is checked.
    timeOut = timeOut * times;
    start = micros();
    //  ride the wave to Q1 point.
    while ((_readADC() >  Q1) && ((micros() - start) < timeOut));
    while ((_readADC() <= Q3) && ((micros() - start) < timeOut));
    start = micros();
    //  do times waves
    for (int i = 0; i < times; i++)
    {
      while ((_readADC() >  Q1) && ((micros() - start) < timeOut));
      while ((_readADC() <= Q3) && ((micros() - start) < timeOut));
    }
    float tenWaves = micros() - start;
    //  calculate frequency
    _frequency = (times * 1e6) / tenWaves;
    if (_microsAdjust != 1.0)
    {
      _frequency *= _microsAdjust;
    }
    _period = 1000000 / _frequency;
    return _frequency;
  };


  //  timing for measureFrequency
  void setMicrosAdjust(float factor = 1.0f)
  {
    _microsAdjust = factor;
  };


  float getRMS()
  {
    float sum = 0;
    uint32_t count = 0;
    uint32_t start = micros();
    while (micros() - start < _period)
    {
      float raw = _readADC();
      sum = sum + (raw - _zeroPoint) * (raw - _zeroPoint);
      count++;
    }
    float rms = sqrt(sum / count) * _voltsPerStep;
    return rms;
  };


  int32_t getADC()
  {
    return _readADC();
  };


  int32_t getZeroPoint()
  {
    return _zeroPoint;
  };


private:
  int32_t  (* _readADC)();
  uint32_t _steps;
  float    _voltsPerStep;

  float    _frequency;
  uint32_t _period;
  float    _microsAdjust = 1.0f;
  int32_t  _zeroPoint;
};



//  -- END OF FILE --





