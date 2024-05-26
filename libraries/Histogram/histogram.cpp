//
//    FILE: Histogram.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2012-11-10
// VERSION: 0.3.7
// PURPOSE: Histogram library for Arduino
//     URL: https://github.com/RobTillaart/Histogram


#include "histogram.h"


Histogram::Histogram(const uint16_t length, float *bounds)
{
  _bounds = bounds;
  _length = length + 1;
  _data = (int32_t *) malloc((_length) * sizeof(int32_t));
  if (_data != NULL)
  {
    clear();
  }
  else
  {
    _length = 0;
  }
  _count = 0;
  _status = HISTO_OK;
  _maxBucket = 2147483647;
}


Histogram::~Histogram()
{
  if (_data != NULL)
  {
    free(_data);
  }
}


//  resets all counters to value (default 0)
uint8_t Histogram::clear(int32_t value)
{
  for (uint16_t i = 0; i < _length; i++)
  {
    _data[i] = value;
  }
  _count = 0;
  _status = HISTO_OK;
  if (value == _maxBucket) _status = HISTO_FULL;
  return _status;
}


uint8_t Histogram::setBucket(const uint16_t index, int32_t value)
{
  _data[index] = value;
  _status = HISTO_OK;
  if (value == _maxBucket) _status = HISTO_FULL;
  return _status;
}


//  adds a new value to the histogram - increasing
uint8_t Histogram::add(const float value)
{
  if (_length == 0)
  {
    _status = HISTO_ERR_LENGTH;
    return _status;
  }
  uint16_t index = find(value);
  if (_data[index] == _maxBucket)
  {
    _status = HISTO_ERR_FULL;
    return _status;
  }
  _data[index]++;
  _count++;
  _status = HISTO_OK;
  if (_data[index] == _maxBucket) _status = HISTO_FULL;
  return _status;
}


//  adds a new value to the histogram - decreasing
uint8_t Histogram::sub(const float value)
{
  if (_length == 0)
  {
    _status = HISTO_ERR_LENGTH;
    return _status;
  }
  uint16_t index = find(value);
  if (_data[index] == -_maxBucket)
  {
    _status = HISTO_ERR_FULL;
    return _status;
  }
  _data[index]--;
  _count++;
  _status = HISTO_OK;
  if (_data[index] == _maxBucket) _status = HISTO_FULL;
  return _status;
}


uint8_t  Histogram::status()
{
  return _status;
}


//  number of buckets
uint16_t Histogram::size()
{
  return _length;
}


//  number of values added to all buckets
uint32_t Histogram::count()
{
  return _count;
}


//  returns the count of a bucket
int32_t Histogram::bucket(const uint16_t index)
{
  if (index > _length) return 0;
  return _data[index];
}


//  returns the relative frequency of a bucket
float Histogram::frequency(const uint16_t index)
{
  if ((_count == 0) || (_length == 0)) return NAN;

  if (index > _length) return 0;   //  differs from PMF()
  return (1.0 * _data[index]) / _count;
}


//  EXPERIMENTAL
//  returns the probability of the bucket of a value
float Histogram::PMF(const float value)
{
  if ((_count == 0) || (_length == 0)) return NAN;

  uint16_t index = find(value);
  return (1.0 * _data[index]) / _count;
}


//  EXPERIMENTAL
//  returns the cumulative probability of
//  values <= value
float Histogram::CDF(const float value)
{
  if ((_count == 0) || (_length == 0)) return NAN;

  //  TODO: could be done in one loop?
  uint16_t index = find(value);
  int32_t  sum = 0;
  for (uint16_t i = 0; i <= index; i++)
  {
    sum += _data[i];
  }
  return (1.0 * sum) / _count;
}


//  EXPERIMENTAL
//  returns the value of the original array for
//  which the CDF is at least probability.
//  must start at 0.
float Histogram::VAL(const float probability)
{
  if ((_count == 0) || (_length == 0)) return NAN;

  float prob = probability;
  if      (prob < 0.0) prob = 0.0;
  else if (prob > 1.0) prob = 1.0;

  prob *= _count;
  int32_t sum = 0;
  for (uint16_t i = 0; i < _length; i++)
  {
    sum += _data[i];
    if ((sum >= prob) && (i < (_length - 1)))
    {
      return _bounds[i];
    }
  }
  return INFINITY;
}


int32_t Histogram::sum()
{
  int32_t _sum = 0;
  for (uint16_t i = 0; i < _length; i++)
  {
    _sum += _data[i];
  }
  return _sum;
}


//  returns the bucket number for value
//  - binary search, more memory ;  faster for #buckets > 20 ?
// uint16_t Histogram::find(const float value)
// {
  // if (_length <= 0) return -1;

  // uint16_t low = 0, high = _length;
  // uint16_t mid;
  // while (high - low > 1)
  // {
    // mid = (low + high)/2;
    // if (_bounds[mid] > value)
    // {
      // high = mid;
    // }
    // else
    // {
      // low = mid;
    // }
  // }
  // if (_bounds[mid] > value) return mid;
  // return _length - 1;
// }


//  returns the bucket number for value
//  must start at 0.
uint16_t Histogram::find(const float value)
{
  if (_length <= 0) return -1;

  for (uint16_t i = 0; i < (_length - 1); i++)
  {
    if (_bounds[i] >= value)
    {
      return i;
    }
  }
  return _length - 1;
}


//  returns the (first) index of the bucket with minimum value.
uint16_t Histogram::findMin()
{
  if (_length <= 0) return -1;
  uint16_t index = 0;
  uint16_t n = _length;
  while (n > 1)
  {
    n--;
    if (_data[n] <  _data[index]) index = n;
  }
  return index;
}


//  returns the (first) index of the bucket with maximum value.
uint16_t Histogram::findMax()
{
  if (_length <= 0) return -1;
  uint16_t index = 0;
  uint16_t n = _length;
  while (n > 1)
  {
    n--;
    if (_data[n] >  _data[index]) index = n;
  }
  return index;
}


//  returns the number of buckets with an exact level.
uint16_t Histogram::countLevel(const int32_t level)
{
  if (_length <= 0) return -1;

  uint16_t buckets = 0;
  uint16_t n = _length;
  while (n > 0)
  {
    n--;
    if (_data[n] == level) buckets++;
  }
  return buckets;
}


//  returns the number of buckets above a certain level.
uint16_t Histogram::countAbove(const int32_t level)
{
  if (_length <= 0) return -1;

  uint16_t buckets = 0;
  uint16_t n = _length;
  while (n > 0)
  {
    n--;
    if (_data[n] > level) buckets++;
  }
  return buckets;
}


//  returns the number of buckets below a certain level.
uint16_t Histogram::countBelow(const int32_t level)
{
  if (_length <= 0) return -1;

  uint16_t buckets = 0;
  uint16_t n = _length;
  while (n > 0)
  {
    n--;
    if (_data[n] < level) buckets++;
  }
  return buckets;
}



///////////////////////////////////////////////////
//
//  experimental
//
//  use with care
float Histogram::saturation()
{
  return (1.0 * _count) / _length;
}


//  experimental use with care
int32_t Histogram::getMaxBucket()
{
  return _maxBucket;
}


void Histogram::setMaxBucket(int32_t value)
{
  _maxBucket = value;
}


//////////////////////////////////////////////////////////////
//
//  DERIVED CLASS - HISTOGRAM16
//
Histogram16::Histogram16(const uint16_t length, float *bounds) : Histogram(length, bounds)
{
  _bounds = bounds;
  _length = length + 1;
  _data = (int16_t *) malloc((_length) * sizeof(int16_t));
  if (_data != NULL)
  {
    clear();
  }
  else
  {
    _length = 0;
  }
  _count = 0;
  _status = HISTO_OK;
  _maxBucket = 32767;
}


Histogram16::~Histogram16()
{
  if (_data) free(_data);
}


uint8_t Histogram16::setBucket(const uint16_t index, int16_t value)
{
  _data[index] = value;
  _status = HISTO_OK;
  if (value == _maxBucket) _status = HISTO_FULL;
  return _status;
}


//////////////////////////////////////////////////////////////
//
//  DERIVED CLASS - HISTOGRAM8
//
Histogram8::Histogram8(const uint16_t length, float *bounds) : Histogram(length, bounds)
{
  _bounds = bounds;
  _length = length + 1;
  _data = (int8_t *) malloc((_length) * sizeof(int8_t));
  if (_data != NULL)
  {
    clear();
  }
  else
  {
    _length = 0;
  }
  _count = 0;
  _status = HISTO_OK;
  _maxBucket = 127;
}


Histogram8::~Histogram8()
{
  if (_data) free(_data);
}


uint8_t Histogram8::setBucket(const uint16_t index, int8_t value)
{
  _data[index] = value;
  _status = HISTO_OK;
  if (value == _maxBucket) _status = HISTO_FULL;
  return _status;
}


//  -- END OF FILE --

