#ifndef Histogram_h
#define Histogram_h
//
//    FILE: Histogram.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.5
// PURPOSE: Histogram library for Arduino
//    DATE: 2012-11-10
//
// Released to the public domain
//

#include <stdlib.h>
#include <math.h>
#include <inttypes.h>

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define HISTOGRAM_LIB_VERSION "0.1.6"

class Histogram
{
public:
  Histogram(const int16_t len, float *bounds);
  ~Histogram();

  void  clear();
  void  add(const float val);
  void  sub(const float val);

  // number of buckets
  inline int16_t size() { return _len; };

  // number of values added to all buckets
  inline uint32_t count() { return _cnt; };
  // number of values added to single bucket
  int32_t bucket(const int16_t idx);

  float   frequency(const int16_t idx);
  float   PMF(const float val);
  float   CDF(const float val);
  float   VAL(const float prob);
  int16_t find(const float f);

protected:
  float *   _bounds;
  int32_t * _data;
  int16_t   _len;
  uint32_t  _cnt;
};

#endif
// END OF FILE