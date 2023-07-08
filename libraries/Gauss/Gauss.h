#pragma once
//
//    FILE: Gauss.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: Library for the Gauss probability math.
//    DATE: 2023-07-06


#include "Arduino.h"
#include "MultiMap.h"

#define GAUSS_LIB_VERSION       (F("0.1.1"))


class Gauss
{
public:
  Gauss()
  {
    _mean = 0;
    _stddev = 1;
    _reciprokeSD = 1;
  }

  //  stddev should be positive.
  bool begin(float mean = 0, float stddev = 1)
  {
    _mean = mean;
    _stddev = stddev;  //  should be positive
    _reciprokeSD = 1.0 / _stddev;
    return (stddev > 0);
  }


  float getMean()
  {
    return _mean;
  }


  float getStdDev()
  {
    return _stddev;
  }


  float P_smaller(float value)
  {
    if (_stddev == 0) return NAN;
    //  normalize(value)
    return _P_smaller((value - _mean) * _reciprokeSD);
  }


  float P_larger(float value)
  {
    return 1.0 - P_smaller(value);
  }


  float P_between(float p, float q)
  {
    if (_stddev == 0) return NAN;
    if (p >= q) return 0;
    return P_smaller(q) - P_smaller(p);
  }


  float P_equal(float value)
  {
    if (_stddev == 0) return NAN;
    float n = (value - _mean) * _reciprokeSD;
    float c = _reciprokeSD * (1.0 / sqrt(TWO_PI));
    return c * exp(-0.5 * n * n);
  }


  float stddevs(float value)
  {
    return normalize(value);
  }


  float normalize(float value)
  {
    return (value - _mean) * _reciprokeSD;
  }


  float bellCurve(float value)
  {
    return P_equal(value);
  }



private:

  float _P_smaller(float x)
  {
    //  NORM.DIST(mean, stddev, x, true)
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

    //  0..60000  uint16_t = 68 bytes less
    float __z[] = {
      0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7,
      0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5,
      1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3,
      2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0, 4,0,
      5.0, 6.0
    };

    //  a dedicated MultiMap could exploit the fact that
    //  the __z[] array is largely equidistant.
    //  that could remove the __z[] array (almost) completely.
    if (x < 0) return 1.0 - multiMap<float>(-x, __z, __gauss, 34);
    return multiMap<float>(x, __z, __gauss, 34);
  }

  float _mean = 0;
  float _stddev = 1;       //  not needed as _reciprokeSD holds same info?
  float _reciprokeSD = 1;
};


//  -- END OF FILE --

