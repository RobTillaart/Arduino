#pragma once
//
//    FILE: Histogram.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.3
// PURPOSE: Histogram library for Arduino
//    DATE: 2012-11-10


#include "Arduino.h"

#define HISTOGRAM_LIB_VERSION       (F("0.3.3"))


class Histogram
{
public:
  Histogram(const uint16_t length, float *bounds);
  ~Histogram();

  void  clear(int32_t value = 0);
  void  setBucket(const uint16_t index, int32_t value = 0);
  void  add(const float value);
  void  sub(const float value);

  //  number of buckets
  uint16_t size();

  //  number of values added to all buckets
  uint32_t count();

  //  number of values added to single bucket
  int32_t  bucket(const uint16_t index);

  float    frequency(const uint16_t index);
  float    PMF(const float value);
  float    CDF(const float value);
  float    VAL(const float probability);

  uint16_t find(const float value);
  uint16_t findMin();
  uint16_t findMax();
  uint16_t countLevel(const int32_t level);
  uint16_t countAbove(const int32_t level);
  uint16_t countBelow(const int32_t level);


protected:
  float *   _bounds;
  int32_t * _data;
  uint16_t  _length;
  uint32_t  _count;
};


//////////////////////////////////////////////////////////////
//
// DERIVED CLASS
//
class Histogram16 : public Histogram
{
public:
  Histogram16(const uint16_t length, float *bounds);
  ~Histogram16();
protected:
  int16_t * _data;
};


class Histogram8 : public Histogram
{
public:
  Histogram8(const uint16_t length, float *bounds);
  ~Histogram8();
protected:
  int8_t * _data;
};


//  -- END OF FILE --

