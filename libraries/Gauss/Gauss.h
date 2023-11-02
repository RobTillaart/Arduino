#pragma once
//
//    FILE: Gauss.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
// PURPOSE: Library for the Gauss probability math.
//    DATE: 2023-07-06


#include "Arduino.h"

#define GAUSS_LIB_VERSION       (F("0.2.1"))


class Gauss
{
public:
  Gauss()
  {
    _mean = 0;
    _reciprokeSD = 1;  //  math optimization.
  }

  //  stddev should be positive.
  bool begin(float mean = 0, float stddev = 1)
  {
    _mean = mean;
    if (stddev == 0) _reciprokeSD = NAN;
    else _reciprokeSD = 1.0 / stddev;
    return (stddev > 0);
  }


  float getMean()
  {
    return _mean;
  }


  float getStdDev()
  {
    return 1.0 / _reciprokeSD;
  }


  float P_smaller(float value)
  {
    if (_reciprokeSD == NAN) return NAN;
    return _P_smaller((value - _mean) * _reciprokeSD);
  }


  float P_larger(float value)
  {
    return 1.0 - P_smaller(value);
  }


  float P_between(float p, float q)
  {
    if (_reciprokeSD == NAN) return NAN;
    if (p >= q) return 0;
    return P_smaller(q) - P_smaller(p);
  }


  float P_outside(float p, float q)
  {
    return 1.0 - P_between(p, q);
  }


  float P_equal(float value)
  {
    if (_reciprokeSD == NAN) return NAN;
    float n = (value - _mean) * _reciprokeSD;
    //  gain of ~10% if we allocate a global var for 'constant' c
    float c = _reciprokeSD * (1.0 / sqrt(TWO_PI));
    return c * exp(-0.5 * (n * n));
  }


  float stddevs(float value)
  {
    return normalize(value);
  }


  float normalize(float value)
  {
    return (value - _mean) * _reciprokeSD;
  }


  float denormalize(float value)
  {
    return value / _reciprokeSD + _mean;
  }


  float bellCurve(float value)
  {
    return P_equal(value);
  }


  float CDF(float value)
  {
    return P_smaller(value);
  }



private:

  float _P_smaller(float x)
  {
    //  NORM.DIST(mean, stddev, x, true)
    //  these points correspond with
    //  0.0 .. 3.0 in steps of 0.1 followed by 4.0, 5.0 and 6.0 
    float __gauss[] = {
      0.50000000, 0.53982784, 0.57925971, 0.61791142,
      0.65542174, 0.69146246, 0.72574688, 0.75803635,
      0.78814460, 0.81593987, 0.84134475, 0.86433394,
      0.88493033, 0.90319952, 0.91924334, 0.93319280,
      0.94520071, 0.95543454, 0.96406968, 0.97128344,
      0.97724987, 0.98213558, 0.98609655, 0.98927589,
      0.99180246, 0.99379033, 0.99533881, 0.99653303,
      0.99744487, 0.99813419, 0.99865010, 0.99996833,
      0.99999971, 1.00000000
    };

    bool neg = false;
    if (x < 0)
    {
      neg = true;
      x = -x;
    }

    if (x >= 6.0)
    {
      if (neg) return 0.0;
      return 1.0;
    }

    if (x <= 3.0)
    {
      int idx  = x * 10;
      float rv = __gauss[idx] + ((x * 10) - idx) * (__gauss[idx+1] - __gauss[idx]);
      if (neg) return 1.0 - rv;
      return rv;
    }

    //  3.0 .. 6.0
    int xint = x;
    int idx  = 27 + xint;
    float rv = __gauss[idx] + (x - xint) * (__gauss[idx+1] - __gauss[idx]);
    if (neg) return 1.0 - rv;
    return rv;
  }

  float _mean = 0;
  //  reciprokeSD = 1.0 / stddev is faster in most math (MUL vs DIV)
  float _reciprokeSD = 1;
};


//  -- END OF FILE --

