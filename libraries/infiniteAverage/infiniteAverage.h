#pragma once
//
//    FILE: infiniteAverage.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.7
// PURPOSE: Calculate the average of a very large number of values.
//     URL: https://github.com/RobTillaart/infiniteAverage


#include "Arduino.h"

#define IAVG_LIB_VERSION            (F("0.1.7"))


class IAVG
{
public:
   IAVG()
   {
     reset();
   };


  void reset()
  {
    _sum = 0;
    _overflow = 0;
    _count = 0;
    //  cannot reset _minimum or maximum;
  };


  void add(float value)
  {
    if (_count == 0)
    { 
      _minimum = value;
      _maximum = value;
    }
    else
    {
      if (value < _minimum) _minimum = value;
      if (value > _maximum) _maximum = value;
    }
    _count++;
    long ov = value;
    _overflow += ov;
    value -= ov;
    _sum += value;
    if (_sum > 1)
    {
      _overflow++;
      _sum -= 1;
    }
    //  scale back factor 2 when overflow comes near
    //  TODO abs(_overflow)
    if ( (_overflow >= _threshold) || (_count >= 4294967000 ) )
    {
      if (_overflow & 1) _sum += 1.0;    //  fix rounding error.
      _count /= 2;
      _overflow /= 2;
      _sum /= 2;
    }
  };


  float average()
  {
    if (_count == 0) return NAN;
    return _sum / _count + (1.0 * _overflow) / _count;
  };


  float maximum()
  {
    if (_count == 0) return NAN;
    return _maximum;
  };


  float minimum()
  {
    if (_count == 0) return NAN;
    return _minimum;
  };


  uint32_t count()
  {
    return _count;
  };


  uint32_t whole()
  {
    return _overflow;
  };


  float decimals()
  {
    return _sum;
  };


  void setDivideThreshold(uint32_t threshold)
  {
    _threshold = threshold;
  }


  uint32_t getDivideThreshold()
  {
    return _threshold;
  }


private:
  float    _sum      = 0;
  float    _minimum  = 0;
  float    _maximum  = 0;
  uint32_t _overflow = 0;
  uint32_t _count    = 0;
  uint32_t _threshold = (1UL << 30);
};


//  -- END OF FILE --

