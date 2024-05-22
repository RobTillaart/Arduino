#pragma once
//
//    FILE: Kurtosis.h
//  AUTHOR: Rob Tillaart
//    DATE: 2024-05-21
// VERSION: 0.1.0
// PURPOSE: Arduino library for calculating skewness and kurtosis of a dataset.
//     URL: https://github.com/RobTillaart/Kurtosis
//
//  code based upon https://www.johndcook.com/blog/skewness_kurtosis/
//  documentation   https://en.wikipedia.org/wiki/Kurtosis


#define KURTOSIS_LIB_VERSION        "0.1.0"


class Kurtosis
{
  public:
    Kurtosis()
    {
      reset();
    };

    void reset()
    {
      _count = 0;
      M1 = M2 = M3 = M4 = 0.0;
    };

    void add(double x)
    {
      uint32_t n1 = _count;
      _count++;

      //  determine distance to the mean (so far) M1.
      double delta = x - M1;
      //  calculate the weighted addition for M1 to the mean.
      double delta_n1 = delta / _count;
      //  TODO calculate the square of the weighted addition (?)
      double delta_n2 = delta_n1 * delta_n1;
      //  TODO 
      double term1 = delta * delta_n1 * n1;

      //  optimized: remove 3 float operations. ~10% gain.
      M1 += delta_n1;
      M4 += delta_n2 * (term1 * (_count * (_count - 3) + 3) + 6 * M2) - 4 * delta_n1 * M3;
      M3 += delta_n1 * (term1 * (_count - 2) - 3 * M2);
      M2 += term1;
    };

    uint32_t count()
    {
      return _count;
    };

    double mean()
    {
      return M1;
    };

    double variance()
    {
      //  cache the variance as it is used for stddev too.
      static uint32_t lc = 0;
      if (_count > lc)
      {
        lc = _count;
        _variance = M2 / (_count - 1.0);
      }
      return _variance;
    };

    double stddev()
    {
      return sqrt( variance() );
    };

    double skewness()
    {
      //  optimized: replaced a DIV by a MUL
      return sqrt(double(_count)) * M3 * pow(M2, -1.5);
    };

    double kurtosis()
    {
      return double(_count) * M4 / (M2 * M2) - 3.0;
    }

  private:
    uint32_t _count;
    double M1, M2, M3, M4;
    double _variance = 0.0;
};

//  -- END OF FILE --
