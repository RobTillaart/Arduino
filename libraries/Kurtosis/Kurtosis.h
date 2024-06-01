#pragma once
//
//    FILE: Kurtosis.h
//  AUTHOR: Rob Tillaart
//    DATE: 2024-05-21
// VERSION: 0.1.2
// PURPOSE: Arduino library for calculating skewness and kurtosis of a dataset.
//     URL: https://github.com/RobTillaart/Kurtosis
//
//  code based upon https://www.johndcook.com/blog/skewness_kurtosis/
//  documentation   https://en.wikipedia.org/wiki/Kurtosis
//
//  Experimental


#define KURTOSIS_LIB_VERSION        "0.1.2"


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
      //  optimized: F3M2 ~1%
      double F3M2 = 3 * M2;
      M4 += delta_n2 * (term1 * (_count * (_count - 3) + 3) + F3M2 * 2) - 4 * delta_n1 * M3;
      M3 += delta_n1 * (term1 * (_count - 2) - F3M2);
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
    };


    //////////////////////////////////////////////////////////////
    //
    //  ADDING DISTRIBUTIONS
    //
    //  Optimization applied to original code.
    //  - divisions replaced by multiplication
    //    - prevent "overflow in divider" without using uint64_t.
    //    - slightly faster when no hardware float support.
    //  - ab = a.count * b.count; is used 5 times.
    //  - more are possible, e.g. aa, bb.
    friend Kurtosis operator + (Kurtosis a, Kurtosis b)
    {
      Kurtosis combined;

      combined._count = a._count + b._count;

      double delta  = b.M1 - a.M1;
      double delta2 = delta * delta;
      double delta3 = delta * delta2;
      double delta4 = delta2 * delta2;

      double invcnt = 1.0 / combined._count;
      double ab = a._count * b._count;

      combined.M1 = (a._count * a.M1 + b._count * b.M1) * invcnt;

      combined.M2 = a.M2 + b.M2 + delta2 * ab * invcnt;

      combined.M3 = a.M3 + b.M3 + delta3 * ab * (a._count - b._count) * invcnt * invcnt;

      combined.M3 += 3.0 * delta * (a._count * b.M2 - b._count * a.M2) * invcnt;

      combined.M4 = a.M4 + b.M4 + delta4 * ab * (a._count * a._count - ab + b._count * b._count)
                    * invcnt * invcnt * invcnt;

      combined.M4 += 6.0 * delta2 * (a._count * a._count * b.M2 + b._count * b._count * a.M2) * invcnt * invcnt +
                    4.0 * delta * (a._count * b.M3 - b._count * a.M3) * invcnt;

      return combined;
    }


    Kurtosis& operator += (const Kurtosis& rhs)
    {
      Kurtosis combined = *this + rhs;
      *this = combined;
      return *this;
    }


//////////////////////////////////////////////////////////////
//
//  DEBUG
//
    void dump()
    {
      Serial.println(_count);
      Serial.println(M1);
      Serial.println(M2);
      Serial.println(M3);
      Serial.println(M4);
    }


  private:
    uint32_t _count;
    double M1, M2, M3, M4;
    double _variance = 0.0;
};


//  -- END OF FILE --
