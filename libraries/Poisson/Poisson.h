#pragma once
//
//    FILE: Poisson.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2026-05-29
// PURPOSE: Arduino library for Poisson distribution math.
//     URL: https://github.com/RobTillaart/Poisson


#include "Arduino.h"

#define POISSON_LIB_VERSION       (F("0.1.0"))


class Poisson
{
public:
  Poisson()
  {
    _mu = 1;
    _factor = exp(-_mu);
  }

  Poisson(double mu)
  {
    _mu = mu;
    _factor = exp(-_mu);
  }

  //  runtime adjustment.
  void begin(double mu)
  {
    _mu = mu;
    _factor = exp(-_mu);
  }

  //  P(X == k)
  double equal(uint8_t k)
  {
    //  iterative, stable for large values
    double value = exp(-_mu);
    for (int n = 1; n <= k; n++)
    {
      value *= _mu / n;
    }
    return value;
  }

  //  P(X <= k)  CDF(k)
  double smallerEqual(uint8_t k)
  {
    double sum = 0;
    double value = exp(-_mu);
    for (int n = 1; n <= k; n++)
    {
      sum += value;
      value *= _mu / n;
    }
    sum += value;
    return sum;
  }

  //  P(X < k)
  double smaller(uint8_t k)
  {
    double sum = 0;
    double value = exp(-_mu);
    for (int n = 1; n < k; n++)
    {
      sum += value;
      value *= _mu / n;
    }
    sum += value;
    return sum;
  }

  //  P(X >= k)
  double largerEqual(uint8_t k)
  {
     return 1 - smaller(k);
  }

  //  P(X > k)
  double larger(uint8_t k)
  {
     return 1 - smallerEqual(k);
  }

  // P(k1 <= X < k2)
  double between(uint8_t k1, uint8_t k2)
  {
    if ((k2 -1) <= k1) return 0;
    double sum = 0;
    double value = exp(-_mu);
    if (k1 == 0) sum += value;
    for (int n = 1; n < k2; n++)
    {
      value *= _mu / n;
      if (n >= k1) sum += value;
    }
    return sum;

    //  better
    // return smaller(k2) - smallerEqual(k1);
    //  slow
    // double sum = 0;
    // for (int i = k1; i < k2; i++)
    // {
      // sum += equal(i);
    // }
     // return sum;
  }

  double average()
  {
     return _mu;
  }

  double stdev()
  {
     return sqrt(_mu);
  }


private:

  double _mu;
  double _factor;

  uint64_t fac(int n)
  {
    uint64_t val = 1;
    for (int x = 2; x <= n; x++) val *= n;
    return val;
  }

};


//  -- END OF FILE --

