//
//    FILE: Histogram.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.6
// PURPOSE: Histogram library for Arduino
//    DATE: 2012-11-10
//
// Released to the public domain
//
// HISTORY:
// 0.1.0 - 2012-11-10 initial version
// 0.1.1 - 2012-11-10 added PMF() and CDF()
// 0.1.2 - 2012-12-23 changed float to double; some comments
// 0.1.3 - 2013-09-29 testing a lot & refactoring
// 0.1.4 - 2015-03-06 stricter interface
// 0.1.5 - 2017-07-16 refactor, support for > 256 buckets; prevent alloc errors
// 0.1.6 - 2017-07-27 revert double to float (issue #33)
//
// Released to the public domain
//

#include "histogram.h"

Histogram::Histogram(const int16_t len, float *bounds)
{
  _bounds = bounds;
  _len = len + 1;
  _data = (int32_t *) malloc((_len) * sizeof(int32_t));
  if (_data) clear();
  else _len = 0;
  _cnt = 0;
}

Histogram::~Histogram()
{
  if (_data) free(_data);
}

// resets all counters
void Histogram::clear()
{
  for (int16_t i = 0; i < _len; i++) _data[i] = 0;
  _cnt = 0;
}

// adds a new value to the histogram - increasing
void Histogram::add(const float f)
{
  if (_len > 0)
  {
    _data[find(f)]++;
    _cnt++;
  }
}

// adds a new value to the histogram - decreasing
void Histogram::sub(const float f)
{
  if (_len > 0)
  {
    _data[find(f)]--;
    _cnt++;
  }
}

// returns the count of a bucket
int32_t Histogram::bucket(const int16_t idx)
{
  if (idx > _len) return 0;
  return _data[idx];
}

// returns the relative frequency of a bucket
float Histogram::frequency(const int16_t idx)
{
  if (_cnt == 0 || _len == 0) return NAN;

  if (idx > _len) return 0;   // diff with PMF
  return (1.0 * _data[idx]) / _cnt;
}

// EXPERIMENTAL
// returns the probability of the bucket of a value
float Histogram::PMF(const float val)
{
  if (_cnt == 0 || _len == 0) return NAN;

  int16_t idx = find(val);
  return (1.0 * _data[idx]) / _cnt;
}

// EXPERIMENTAL
// returns the cummulative probability of
// values <= value
float Histogram::CDF(const float val)
{
  if (_cnt == 0 || _len == 0) return NAN;

  int16_t idx = find(val);
  int32_t sum = 0;
  for (int16_t i = 0; i <= idx; i++)
  {
    sum += _data[i];
  }
  return (1.0 * sum) / _cnt;
}

// EXPERIMENTAL
// returns the value of the original array for
// which the CDF is at least prob.
float Histogram::VAL(const float prob)
{
  if (_cnt == 0 || _len == 0) return NAN;
  float p = prob;
  if (p < 0.0) p = 0.0;
  if (p > 1.0) p = 1.0;

  float probability = p * _cnt;
  int32_t sum = 0;
  for (int16_t i = 0; i < _len; i++)
  {
    sum += _data[i];
    if (sum >= probability && (i <(_len-1)) ) return _bounds[i];
  }
  return INFINITY;
}

// returns the bucket number for value val
int16_t Histogram::find(const float val)
{
  if (_len <= 0) return -1;

  for (int16_t i = 0; i < (_len-1); i++)
  {
    if (_bounds[i] >= val) return i;
  }
  return _len-1;  // len?
  // int16_t i = 0;
  // while ((i < (_len-1)) && (_bounds[i] < val)) i++;
  // return i;
}

// END OF FILE