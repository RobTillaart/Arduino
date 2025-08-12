#pragma once
//
//    FILE: SMC.h
//  AUTHOR: Rob Tillaart
//    DATE: 2025-02-23
// VERSION: 0.1.0
// PURPOSE: Arduino library for a Sliding Mode Controller (SMC).
//     URL: https://github.com/RobTillaart/SMC
//


#include "Arduino.h"


#define SMC_LIB_VERSION         (F("0.1.0"))

//  MODE
#define SMC_LINEAR              0
#define SMC_EXPONENTIAL         1
#define SMC_SIMPLE              2


class SMC
{
public:
  SMC()
  {
    _mode = 0;  //  LINEAR
  };

  void begin(float setPoint, float maxValue, float weight1, float weight2)
  {
    _setPoint = setPoint;
    _maxValue = maxValue;
    _weight1 = weight1;
    _weight2 = weight2;
  };


  //  returns 0..100%
  float outValuePercentage(float inValue)
  {
    if (_offset != 0)
    {
      inValue -= _offset;
    }
    _error = _setPoint - inValue;

    //  SIMPLE mode doesn't need delta error.
    if (_mode == SMC_SIMPLE)
    {
      // (_weight1 < 0) error = -error???
      if (_error >= 0) return 100.0;
      //  to investigate "cooling" ?
      //  if .... return -100;
      return 0.0;
    }

    //  LINEAR and EXPONENTIAL need delta error.
    float delta = _error - _prevError;
    _prevError = _error;
    float s = (_weight1 * _error) + (_weight2 * delta);
    if (_mode == SMC_LINEAR)
    {
      if (s > 0) return 100.0;
      //  to investigate "cooling" ?
      //  if .... return -100;
      return 0.0;
    }
    if (_mode == SMC_EXPONENTIAL)
    {
      float rv = 100.0 * (1.0 / (1.0 + exp(-s)));
      // if (rv >= 100.0) return 100.0;
      // if (rv <= 0.0)   return 0;
      return rv;
    }

    //  no mode, should not happen.
    return 0.0;
  };

  //  returns 0..maxValue
  float outValue(float inValue)
  {
    return _maxValue * 0.01 * outValuePercentage(inValue);
  };


  //       0 = SMC_LINEAR
  //       1 = SMC_EXPONENTIAL
  //       2 = SMC_SIMPLE
  void setMode(uint8_t mode)
  {
    if (mode > SMC_SIMPLE) return;
    _mode = mode;
  };

  uint8_t getMode()
  {
    return _mode;
  };

  void setSetPoint(float setPoint)
  {
    _setPoint = setPoint;
  };

  float getSetPoint()
  {
    return _setPoint;
  };

  void setMaxValue(float maxValue)
  {
    _maxValue = maxValue;
  };

  float getMaxValue()
  {
    return _maxValue;
  };

  void setWeights(float weight1, float weight2)
  {
    _weight1 = weight1;
    _weight2 = weight2;
  };

  float getWeight1()
  {
    return _weight1;
  };

  float getWeight2()
  {
    return _weight2;
  };


  void setOffset(float offset)
  {
    _offset = offset;
  };

  float getOffset()
  {
    return _offset;
  };


private:
  float    _setPoint = 0;   //  level one wants (SOLL)
  float    _maxValue = 0;   //  signal strength
  float    _weight1 = 0;    //  weight delta1 = error - setPoint
  float    _weight2 = 0;    //  weight delta2 = error - previous error
  float    _offset = 0;     //  offset the equilibrium.
  float    _error = 0;
  float    _prevError = 0;
  uint8_t  _mode = 0;       //  linear or exponential
};


//  -- END OF FILE --





