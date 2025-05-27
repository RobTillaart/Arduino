#pragma once
//
//    FILE: infiniteAverage.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.8
// PURPOSE: Calculate the average of a very large number of values.
//     URL: https://github.com/RobTillaart/infiniteAverage


#include "Arduino.h"

#define IAVG_LIB_VERSION            (F("0.1.8"))


class IAVG
{
public:
   IAVG()
   {
     reset();
   };


  void reset()
  {
    _decimal = 0;
    _whole = 0;
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
    _whole += ov;
    value -= ov;
    _decimal += value;
    if (_decimal > 1)
    {
      _whole++;
      _decimal -= 1;
    }
    //  scale back factor 2 when overflow comes near
    //  TODO abs(_whole)
    if ( (_whole >= _threshold) || (_count >= 4294967000 ) )
    {
      _count /= 2;
      _decimal /= 2;
      if (_whole & 1) _decimal += 0.5;  //  fix rounding error.
      _whole /= 2;
    }
  };


  float average()
  {
    if (_count == 0) return NAN;
    return _decimal / _count + (1.0 * _whole) / _count;
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
    return _whole;
  };


  float decimals()
  {
    return _decimal;
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
  uint32_t _whole = 0;
  float    _decimal  = 0;

  float    _minimum  = 0;
  float    _maximum  = 0;
  uint32_t _count    = 0;
  //  threshold for scaling back.
  uint32_t _threshold = (1UL << 30);
};


//  -- END OF FILE --

