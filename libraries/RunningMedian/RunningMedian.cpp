//
//    FILE: RunningMedian.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.3
// PURPOSE: RunningMedian library for Arduino
//
//  HISTORY:
//  0.1.00  2011-02-16  initial version
//  0.1.01  2011-02-22  added remarks from CodingBadly
//  0.1.02  2012-03-15  added
//  0.1.03  2013-09-30  added _sorted flag, minor refactor
//  0.1.04  2013-10-17  added getAverage(uint8_t) - kudo's to Sembazuru
//  0.1.05  2013-10-18  fixed bug in sort; removes default constructor; dynamic memory
//  0.1.06  2013-10-19  faster sort, dynamic arrays, replaced sorted float array with indirection array
//  0.1.07  2013-10-19  add correct median if _count is even.
//  0.1.08  2013-10-20  add getElement(), add getSottedElement() add predict()
//  0.1.09  2014-11-25  float to double (support ARM)
//  0.1.10  2015-03-07  fix clear
//  0.1.11  2015-03-29  undo 0.1.10 fix clear
//  0.1.12  2015-07-12  refactor constructor + const
//  0.1.13  2015-10-30  fix getElement(n) - kudos to Gdunge
//  0.1.14  2017-07-26  revert double to float - issue #33
//  0.1.15  2018-08-24  make runningMedian Configurable #110
//  0.2.0   2020-04-16  refactor.
//  0.2.1   2020-06-19  fix library.json
//  0.2.2   2021-01-03  add Arduino-CI + unit tests
//  0.3.0   2021-01-04  malloc memory as default storage
//  0.3.1   2021-01-16  Changed size parameter to 255 max
//  0.3.2   2021-01-21  replaced bubbleSort by insertionSort 
//                      --> better performance for large arrays.
//  0.3.3   2021-01-22  better insertionSort (+ cleanup test code)


#include "RunningMedian.h"


RunningMedian::RunningMedian(const uint8_t size)
{
  _size = size;
  if (_size < MEDIAN_MIN_SIZE) _size = MEDIAN_MIN_SIZE;
  // if (_size > MEDIAN_MAX_SIZE) _size = MEDIAN_MAX_SIZE;

#ifdef RUNNING_MEDIAN_USE_MALLOC
  _values = (float *) malloc(_size * sizeof(float));
  _sortIdx  = (uint8_t *) malloc(_size * sizeof(uint8_t));
#endif
  clear();
}


RunningMedian::~RunningMedian()
{
  #ifdef RUNNING_MEDIAN_USE_MALLOC
  free(_values);
  free(_sortIdx);
  #endif
}


// resets all internal counters
void RunningMedian::clear()
{
  _count = 0;
  _index = 0;
  _sorted = false;
  for (uint8_t i = 0; i < _size; i++)
  {
    _sortIdx[i] = i;
  }
}


// adds a new value to the data-set
// or overwrites the oldest if full.
void RunningMedian::add(float value)
{
  _values[_index++] = value;
  if (_index >= _size) _index = 0; // wrap around
  if (_count < _size) _count++;
  _sorted = false;
}


float RunningMedian::getMedian()
{
  if (_count == 0) return NAN;

  if (_sorted == false) sort();

  if (_count & 0x01)  // is it odd sized?
  {
    return _values[_sortIdx[_count / 2]];
  }
  return (_values[_sortIdx[_count / 2]] + _values[_sortIdx[_count / 2 - 1]]) / 2;
}


float RunningMedian::getQuantile(float q)
{
  if (_count == 0) return NAN;
  
  if ((q < 0) || (q > 1)) return NAN;

  if (_sorted == false) sort();
  
  const float id = (_count - 1) * q;
  const uint8_t lo = floor(id);
  const uint8_t hi = ceil(id);
  const float qs = _values[_sortIdx[lo]];
  const float h  = (id - lo);

  return (1.0 - h) * qs + h * _values[_sortIdx[hi]];
}


float RunningMedian::getAverage()
{
  if (_count == 0) return NAN;

  float sum = 0;
  for (uint8_t i = 0; i < _count; i++)
  {
    sum += _values[i];
  }
  return sum / _count;
}


float RunningMedian::getAverage(uint8_t nMedians)
{
  if ((_count == 0) || (nMedians == 0)) return NAN;

  if (_count < nMedians) nMedians = _count;     // when filling the array for first time
  uint8_t start = ((_count - nMedians) / 2);
  uint8_t stop = start + nMedians;

  if (_sorted == false) sort();

  float sum = 0;
  for (uint8_t i = start; i < stop; i++)
  {
    sum += _values[_sortIdx[i]];
  }
  return sum / nMedians;
}


float RunningMedian::getElement(const uint8_t n)
{
  if ((_count == 0) || (n >= _count)) return NAN;

  uint8_t pos = _index + n;
  if (pos >= _count) // faster than %
  {
    pos -= _count;
  }
  return _values[pos];
}


float RunningMedian::getSortedElement(const uint8_t n)
{
  if ((_count == 0) || (n >= _count)) return NAN;

  if (_sorted == false) sort();
  return _values[_sortIdx[n]];
}


// n can be max <= half the (filled) size
float RunningMedian::predict(const uint8_t n)
{
  uint8_t mid = _count / 2;
  if ((_count == 0) || (n >= mid)) return NAN;

  float med = getMedian();  // takes care of sorting !
  if (_count & 0x01)        // odd # elements
  {
    return max(med - _values[_sortIdx[mid - n]], _values[_sortIdx[mid + n]] - med);
  }
  // even # elements
  float f1 = (_values[_sortIdx[mid - n]] + _values[_sortIdx[mid - n - 1]]) / 2;
  float f2 = (_values[_sortIdx[mid + n]] + _values[_sortIdx[mid + n - 1]]) / 2;
  return max(med - f1, f2 - med) / 2;
}


void RunningMedian::sort()
{
  // insertSort 
  for (uint16_t i = 1; i < _count; i++)
  {
    uint16_t z = i;
    uint16_t temp = _sortIdx[z];
    while ((z > 0) && (_values[temp] < _values[_sortIdx[z - 1]]))
    {
      _sortIdx[z] = _sortIdx[z - 1];
      z--;
    }
    _sortIdx[z] = temp;
  }
  _sorted = true;
}

// -- END OF FILE --
