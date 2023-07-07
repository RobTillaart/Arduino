#pragma once
//
//    FILE: Gauss.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Library for the Gauss probability math.
//    DATE: 2023-07-06


#include "Arduino.h"
#include "MultiMap.h"

#define GAUSS_LIB_VERSION       (F("0.1.0"))


class Gauss
{
public:
  Gauss()
  {
    _mean = 0;
    _stddev = 1;
  }

  bool begin(float mean, float stddev)
  {
    _mean = mean;
    _stddev = abs(stddev);
    return true;
  }


  float P_smaller(float value)
  {
    if (_stddev == 0) return NAN;
    return _P_smaller((value - _mean) / _stddev);
  }


  float P_larger(float value)
  {
    return 1.0 - P_smaller(value);
    //  if (_stddev == 0) return NAN;
    //  optimize math division?
    //  return _P_larger((value - _mean) / _stddev);
  }


  float P_between(float p, float q)
  {
    if (p >= q) return 0;
    return P_smaller(q) - P_smaller(p);
  }


  float P_equal(float value)
  {
    if (_stddev == 0) return NAN;
    float n = (value - _mean)/_stddev;
    float c = 1.0 / (_stddev * sqrt(TWO_PI));
    return c * exp(-0.5 * n * n);
  }


  float stddevs(float value)
  {
    return normalize(value);
  }


  float normalize(float value)
  {
    return (value - _mean)/_stddev;
  }


  float bellCurve(float value)
  {
    return P_equal(value);
  }



private:

  float _P_smaller(float x)
  {
    //  TODO improve accuracy or reduce points.
    float __gauss[] = {
      0.5000, 0.5398, 0.5793, 0.6179, 0.6554, 0.6915, 0.7257, 0.7580,
      0.7881, 0.8159, 0.8413, 0.8643, 0.8849, 0.9032, 0.9192, 0.9332,
      0.9452, 0.9554, 0.9641, 0.9713, 0.9772, 0.9821, 0.9861, 0.9893,
      0.9918, 0.9938, 0.9953, 0.9965, 0.9974, 0.9981, 0.9987, 1.0000
    };
    float __z[] = {
      0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7,
      0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5,
      1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3,
      2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0, 10.0
    };

    if (x < 0) return 1.0 - multiMap<float>(-x, __z, __gauss, 32);
    return multiMap<float>(x, __z, __gauss, 32);
  }

  float _mean = 0;
  float _stddev = 1;
};


//  -- END OF FILE --
