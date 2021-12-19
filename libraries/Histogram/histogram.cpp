//
//    FILE: Histogram.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.1
// PURPOSE: Histogram library for Arduino
//    DATE: 2012-11-10
//
//  HISTORY:
//  0.1.0   2012-11-10  initial version
//  0.1.1   2012-11-10  added PMF() and CDF()
//  0.1.2   2012-12-23  changed float to double; some comments
//  0.1.3   2013-09-29  testing a lot & refactoring
//  0.1.4   2015-03-06  stricter interface
//  0.1.5   2017-07-16  refactor, support for > 256 buckets; prevent alloc() errors
//  0.1.6   2017-07-27  revert double to float (issue #33)
//  0.2.0   2020-06-12  #pragma once, removed pre 1.0 support
//  0.2.1   2020-12-24  Arduino-CI + unit tests
//  0.3.0   2021-11-02  update build-CI, add badges
//                      refactor readability
//                      add parameter for clear(value = 0)
//                      add findMin(), findMax()
//                      add countAbove(), countLevel(), countBelow().
//                      add setBucket(),
//                      change length to uint16_t ==> 65534
//  0.3.1   2021-12-19  update library.json, license, minor edits


#include "histogram.h"


Histogram::Histogram(const uint16_t length, float *bounds)
{
  _bounds = bounds;
  _length = length + 1;
  _data = (int32_t *) malloc((_length) * sizeof(int32_t));
  if (_data) clear();
  else _length = 0;
  _count = 0;
}


Histogram::~Histogram()
{
  if (_data) free(_data);
}


// resets all counters to value (default 0)
void Histogram::clear(int32_t value)
{
  for (uint16_t i = 0; i < _length; i++) _data[i] = value;
  _count = 0;
}


// adds a new value to the histogram - increasing
void Histogram::add(const float value)
{
  if (_length > 0)
  {
    uint16_t index = find(value);
    _data[index]++;
    _count++;
  }
  // could return index or count.
}


// adds a new value to the histogram - decreasing
void Histogram::sub(const float value)
{
  if (_length > 0)
  {
    uint16_t index = find(value);
    _data[index]--;
    _count++;
  }
  // could return index or count.
}


// returns the count of a bucket
int32_t Histogram::bucket(const uint16_t index)
{
  if (index > _length) return 0;
  return _data[index];
}


// returns the relative frequency of a bucket
float Histogram::frequency(const uint16_t index)
{
  if ((_count == 0) || (_length == 0)) return NAN;

  if (index > _length) return 0;   // differs from PMF()
  return (1.0 * _data[index]) / _count;
}


// EXPERIMENTAL
// returns the probability of the bucket of a value
float Histogram::PMF(const float value)
{
  if ((_count == 0) || (_length == 0)) return NAN;

  uint16_t index = find(value);
  return (1.0 * _data[index]) / _count;
}


// EXPERIMENTAL
// returns the cumulative probability of
// values <= value
float Histogram::CDF(const float value)
{
  if ((_count == 0) || (_length == 0)) return NAN;

  // TODO: could be done in one loop?
  uint16_t index = find(value);
  int32_t  sum = 0;
  for (uint16_t i = 0; i <= index; i++)
  {
    sum += _data[i];
  }
  return (1.0 * sum) / _count;
}


// EXPERIMENTAL
// returns the value of the original array for
// which the CDF is at least prob(ability).
float Histogram::VAL(const float prob)
{
  if ((_count == 0) || (_length == 0)) return NAN;

  float p = prob;
  if (p < 0.0) p = 0.0;
  if (p > 1.0) p = 1.0;

  float probability = p * _count;
  int32_t sum = 0;
  for (uint16_t i = 0; i < _length; i++)
  {
    sum += _data[i];
    if (sum >= probability && (i < (_length - 1)) )
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


// returns the bucket number for value
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


// returns the (first) index of the bucket with minimum value.
uint16_t Histogram::findMin()
{
  if (_length <= 0) return -1;

  uint16_t index = 0;
  for (uint16_t i = 1; i < _length; i++)
  {
    if (_data[i] < _data[index]) index = i;
  }
  return index;
}


// returns the (first) index of the bucket with maximum value.
uint16_t Histogram::findMax()
{
  if (_length <= 0) return -1;

  uint16_t index = 0;
  for (uint16_t i = 1; i < _length; i++)
  {
    if (_data[i] > _data[index]) index = i;
  }
  return index;
}


// returns the number of buckets above a certain level.
uint16_t Histogram::countLevel(const int32_t level)
{
  if (_length <= 0) return -1;

  uint16_t buckets = 0;
  for (uint16_t i = 0; i < _length; i++)
  {
    if (_data[i] == level) buckets++;
  }
  return buckets;
}


// returns the number of buckets above a certain level.
uint16_t Histogram::countAbove(const int32_t level)
{
  if (_length <= 0) return -1;

  uint16_t buckets = 0;
  for (uint16_t i = 0; i < _length; i++)
  {
    if (_data[i] > level) buckets++;
  }
  return buckets;
}


// returns the number of buckets below a certain level.
uint16_t Histogram::countBelow(const int32_t level)
{
  if (_length <= 0) return -1;

  uint16_t buckets = 0;
  for (uint16_t i = 0; i < _length; i++)
  {
    if (_data[i] < level) buckets++;
  }
  return buckets;
}


//////////////////////////////////////////////////////////////
//
// DERIVED CLASS
//

Histogram16::Histogram16(const uint16_t length, float *bounds) : Histogram(length, bounds)
{
};


Histogram8::Histogram8(const uint16_t length, float *bounds) : Histogram(length, bounds)
{
};

// -- END OF FILE --

