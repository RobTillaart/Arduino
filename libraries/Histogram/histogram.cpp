//
//    FILE: Histogram.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.3
// PURPOSE: Histogram library for Arduino
//    DATE: 2012-11-10


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
}


Histogram::~Histogram()
{
  if (_data != NULL)
  {
    free(_data);
  }
}


//  resets all counters to value (default 0)
void Histogram::clear(int32_t value)
{
  for (uint16_t i = 0; i < _length; i++)
  {
    _data[i] = value;
  }
  _count = 0;
}


void Histogram::setBucket(const uint16_t index, int32_t value)
{
  _data[index] = value;
}


//  adds a new value to the histogram - increasing
void Histogram::add(const float value)
{
  if (_length > 0)
  {
    uint16_t index = find(value);
    _data[index]++;
    _count++;
  }
  //  return index or count.
}


//  adds a new value to the histogram - decreasing
void Histogram::sub(const float value)
{
  if (_length > 0)
  {
    uint16_t index = find(value);
    _data[index]--;
    _count++;
  }
  //  return index or count.
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


// returns the bucket number for value
// - binary search, more memory ;  faster for #buckets > 20 ?
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


//////////////////////////////////////////////////////////////
//
//  DERIVED CLASS
//

Histogram16::Histogram16(const uint16_t length, float *bounds) : Histogram(length, bounds)
{
}


Histogram8::Histogram8(const uint16_t length, float *bounds) : Histogram(length, bounds)
{
}


//  -- END OF FILE --

