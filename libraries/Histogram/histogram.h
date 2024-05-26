#pragma once
//
//    FILE: Histogram.h
//  AUTHOR: Rob Tillaart
//    DATE: 2012-11-10
// VERSION: 0.3.7
// PURPOSE: Histogram library for Arduino
//     URL: https://github.com/RobTillaart/Histogram


#include "Arduino.h"


#define HISTOGRAM_LIB_VERSION       (F("0.3.6"))

//  return STATUS add(), sub(), clear(), setBucket();
#define HISTO_OK                     0x00    //  idem
#define HISTO_FULL                   0x01    //  just got full
#define HISTO_ERR_FULL               0xFF    //  over- underflow
#define HISTO_ERR_LENGTH             0xFE    //  constructor issue.


class Histogram
{
public:
  Histogram(const uint16_t length, float * bounds);
  ~Histogram();

  uint8_t  clear(int32_t value = 0);
  uint8_t  add(const float value);
  uint8_t  sub(const float value);

  virtual uint8_t setBucket(const uint16_t index, int32_t value = 0);

  //  returns last known status
  uint8_t  status();

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
  int32_t  sum();


  uint16_t find(const float value);
  uint16_t findMin();
  uint16_t findMax();
  uint16_t countLevel(const int32_t level);
  uint16_t countAbove(const int32_t level);
  uint16_t countBelow(const int32_t level);


  ///////////////////////////////////////////////////
  //
  //  experimental
  //
  float    saturation();

  //  use with care
  int32_t  getMaxBucket();
  void     setMaxBucket(int32_t value);


protected:
  float *   _bounds;
  int32_t * _data;
  uint16_t  _length;
  uint32_t  _count;
  int32_t   _maxBucket;
  uint8_t   _status;
};


//////////////////////////////////////////////////////////////
//
// DERIVED CLASS
//
class Histogram16 : public Histogram
{
public:
  Histogram16(const uint16_t length, float * bounds);
  ~Histogram16();

  uint8_t setBucket(const uint16_t index, int16_t value = 0);

protected:
  int16_t * _data;
};


class Histogram8 : public Histogram
{
public:
  Histogram8(const uint16_t length, float * bounds);
  ~Histogram8();

  uint8_t setBucket(const uint16_t index, int8_t value = 0);

protected:
  int8_t * _data;
};


//  -- END OF FILE --

