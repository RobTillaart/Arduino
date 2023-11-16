#pragma once
//
//    FILE: Prandom.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.6
// PURPOSE: Arduino library for random numbers with Python Random interface
//          The underlying pseudo-random number generator is a
//          Multiply-with-carry method invented by George Marsaglia.
//     URL: https://github.com/RobTillaart/Prandom
//          https://docs.python.org/3/library/random.html
//          https://www.pcg-random.org/


#include "Arduino.h"

#define PRANDOM_LIB_VERSION                 (F("0.1.6"))


class Prandom
{
public:
  Prandom();
  Prandom(uint32_t s);

  void seed();
  void seed(uint32_t s, uint32_t t = 2);  //  Marsaglia need 2 seeds, but 1 will work too


  //  integer methods
  //
  uint32_t getrandbits(uint8_t n);
  uint32_t randrange(uint32_t stop);
  uint32_t randrange(uint32_t start, uint32_t stop, uint32_t step = 1);
  //  randint is inclusive end value
  uint32_t randint(uint32_t start, uint32_t stop) { return randrange(start, stop + 1); };


  //  real distributions
  //
  float random(const float top = 1.0);
  float uniform(float lo, float hi);
  float triangular(float lo = 0, float hi = 1.0, float mid = 0.5);
  float normalvariate(float mu = 0, float sigma = 1.0);
  float lognormvariate(float mu = 0, float sigma = 1.0);
  float gauss(float mu = 0, float sigma = 1.0);
  float expovariate(float lambda);
  float gammavariate(float alpha, float beta);
  float betavariate(float alpha, float beta);
  float paretovariate(float alpha);
  float weibullvariate(float alpha, float beta);

 
  //  Circular distributions
  //
  //  mu is mean angle in radians
  //  kappa is concentration parameter, 0 -> uniform.
  float vonmisesvariate(float mu, float kappa = 0);


private:

  uint32_t _rndTime();
  uint32_t _rnd(uint32_t n);

  //  Marsaglia 'constants'
  uint32_t _m_w = 1;
  uint32_t _m_z = 2;
  uint32_t __random();
};


//  -- END OF FILE --

