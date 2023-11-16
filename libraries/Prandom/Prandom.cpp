//
//    FILE: Prandom.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.6
// PURPOSE: Arduino library for random number generation with Python random interface
//     URL: https://github.com/RobTillaart/Prandom
//
//  code based upon Python implementation although some small
//  optimizations and tweaks were needed to get it working.


#include "Prandom.h"


Prandom::Prandom()
{
  seed();
}


Prandom::Prandom(uint32_t s)
{
  seed(s);
}


void Prandom::seed()
{
  //  no argument ==> time based.
  seed(_rndTime());
}


void Prandom::seed(uint32_t s, uint32_t t)
{
  //  set Marsaglia constants, prevent 0 as value
  if (s == 0) s = 1;
  if (t == 0) t = 2;
  _m_w = s;
  _m_z = t;
}


uint32_t Prandom::getrandbits(uint8_t n)
{
  uint8_t shift = min(31, n - 1);
  return _rnd(1UL << shift);
}


uint32_t Prandom::randrange(uint32_t stop)
{
  return _rnd(stop);
}


uint32_t Prandom::randrange(uint32_t start, uint32_t stop, uint32_t step)
{
  if (step == 1) return start + _rnd(stop - start);
  return start + step * _rnd((stop - start + step - 1) / step);
}


//  returns value between 0 and top which defaults to 1.0
//          the parameter does not exist in Python
//  note:   not all possible (0xFFFFFFFF) values are used
//          function has an uniform distribution.
float Prandom::random(const float top)
{
  if (top == 0) return 0;
  float f = (top * __random()) / 0xFFFFFFFF;
  return f;
}


float Prandom::uniform(float lo, float hi)
{
  if (lo == hi) return lo;
  return lo + random(hi - lo);
}


float Prandom::triangular(float lo, float hi, float mid)
{
  if (lo == hi) return lo;
  float val = random();

  if (val > mid)
  {
    val = 1 - val;
    mid = 1 - mid;
    float t = hi;
    hi = lo;
    lo = t;
  }
  return lo + (hi - lo) * sqrt(val * mid);
}


//  minor optimization.
float Prandom::normalvariate(float mu, float sigma)
{
  //  const float NV_MAGICCONST = 4 * exp(-0.5)/sqrt(2.0);
  const float NV_MAGICCONST = 2 * exp(-0.5) / sqrt(2.0);

  float u1, u2, z;
  while (true)
  {
    u1 = random();
    u2 = 1 - random();
    z = NV_MAGICCONST * (u1 - 0.5) / u2 ;
    //  if ((z * z / 4) <= -log(u2)) break;
    if ((z * z) <= -log(u2)) break;
  }
  return z * sigma + mu;
}


float Prandom::lognormvariate(float mu, float sigma)
{
  return exp(normalvariate(mu, sigma));
}


//  implemented slightly differently
float Prandom::gauss(float mu, float sigma)
{
  static bool generate = false;
  static float next = 0;
  float z = 0;

  generate = !generate;
  if (generate == false)
  {
    z = next;
  }
  else
  {
    float x2pi = random(TWO_PI);
    float g2rad = sqrt( -2.0 * log(1.0 - random()));
    z = cos(x2pi) * g2rad;
    next = sin(x2pi) * g2rad;
  }
  return z * sigma + mu;
};


float Prandom::expovariate(float lambda)
{
  return  -log(1.0 - random()) / lambda;
}


//  alpha & beta > 0
float Prandom::gammavariate(float alpha, float beta)
{
  const float LOG4 = log(4);
  const float SG_MAGICCONST = 1.0 + log(4.5);

  if (alpha > 1.0)
  {
    //  #  Uses R.C.H. Cheng, "The generation of Gamma
    //  #  variables with non-integral shape parameters",
    //  #  Applied Statistics, (1977), 26, No. 1, p71-74

    float ainv = sqrt(2.0 * alpha - 1.0);
    float bbb = alpha - LOG4;
    float ccc = alpha + ainv;

    float u1, u2, v, x, z, r;
    while (true)
    {
      u1 = random();
      if (u1 < 1e-7) continue;
      if (u1 > 0.9999999) continue;  //  needed?

      u2 = 1.0 - random();
      v = log(u1 / (1.0 - u1)) / ainv;
      x = alpha * exp(v);
      z = u1 * u1 * u2;
      r = bbb + ccc * v - x;
      if ( ( (r + SG_MAGICCONST - 4.5 * z) >= 0.0) ||
           (r >= log(z)) )
      {
        return x * beta;
      }
    }
  }
  else if (alpha == 1.0)
  {
    return -log(1.0 - random()) * beta;
  }
  else   //  alpha in 0..1
  {
    //  #  Uses ALGORITHM GS of Statistical Computing - Kennedy & Gentle

    float u, b, p, x, u1;
    while (true)
    {
      u = random();
      b = (EULER + alpha) / EULER;
      p = b * u;
      if ( p <= 1.0) x = pow(p, (1.0 / alpha));
      else           x = -log((b - p) / alpha);
      u1 = random();
      if (p > 1.0)
      {
        if (u1 <= pow(x, (alpha - 1.0))) break;
      }
      else
      {
        if (u1 <= exp(-x)) break;
      }
    }
    return x * beta;
  }
}


float Prandom::betavariate(float alpha, float beta)
{
  float y = gammavariate(alpha, 1.0);
  if (y == 0) return 0.0;
  return y / (y + gammavariate(beta, 1.0));
};


float Prandom::paretovariate(float alpha)
{
  float u = 1 - random();
  return pow(u, (-1.0 / alpha));
}


float Prandom::weibullvariate(float alpha, float beta)
{
  float u = 1 - random();
  return  alpha * pow(-log(u), 1.0 / beta);
}


float Prandom::vonmisesvariate(float mu, float kappa)
{
  if (kappa <= 1e-6) return TWO_PI * random();

  float s = 0.5 / kappa;
  float r = s + sqrt(1.0 + s * s);

  float u1, u2, u3, z, d, q, f, theta;

  do
  {
    u1 = random();
    z = cos(PI * u1);
    d = z / (r + z);
    u2 = random();
  } while ( ( u2 >= 1.0 - d * d ) && (u2 > (1.0 - d) * exp(d)) );

  q = 1.0 / r;
  f = (q + z) / (1.0 + q * z);

  u3 = random();

  if (u3 > 0.5) theta = mu + acos(f);
  else theta = mu - acos(f);

  while (theta < 0) theta += TWO_PI;
  while (theta > TWO_PI) theta -= TWO_PI;

  return theta;
}


////////////////////////////////////////////////////////////////////////////
//
//  PRIVATE
//
uint32_t Prandom::_rndTime()
{
  return (micros() + (micros() >> 2) ) ^ (millis());
}


//  TODO how to guarantee it uniform between 0 .. n-1
uint32_t Prandom::_rnd(uint32_t n)
{
  //  float formula works fastest but it looses precision for large values of n
  //  as floats have only 23 bit mantissa
  uint32_t val = __random();
  if (n > 0x003FFFFF) return val % n;     //  distribution will fail here
  return (n * 1.0 * val) / 0xFFFFFFFF;
}


//  An example of a simple pseudo-random number generator is the
//  Multiply-with-carry method invented by George Marsaglia.
//  two initializers (not null)
uint32_t Prandom::__random()
{
  _m_z = 36969L * (_m_z & 65535L) + (_m_z >> 16);
  _m_w = 18000L * (_m_w & 65535L) + (_m_w >> 16);
  return (_m_z << 16) + _m_w;  /* 32-bit result */
}


//  -- END OF FILE --

