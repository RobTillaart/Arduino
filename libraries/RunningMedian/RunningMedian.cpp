//
//    FILE: RunningMedian.cpp
//  AUTHOR: Rob.Tillaart at gmail.com
// VERSION: 0.1.15
// PURPOSE: RunningMedian library for Arduino
//
// HISTORY:
// 0.1.00 - 2011-02-16 initial version
// 0.1.01 - 2011-02-22 added remarks from CodingBadly
// 0.1.02 - 2012-03-15 added
// 0.1.03 - 2013-09-30 added _sorted flag, minor refactor
// 0.1.04 - 2013-10-17 added getAverage(uint8_t) - kudo's to Sembazuru
// 0.1.05 - 2013-10-18 fixed bug in sort; removes default constructor; dynamic memory
// 0.1.06 - 2013-10-19 faster sort, dynamic arrays, replaced sorted float array with indirection array
// 0.1.07 - 2013-10-19 add correct median if _cnt is even.
// 0.1.08 - 2013-10-20 add getElement(), add getSottedElement() add predict()
// 0.1.09 - 2014-11-25 float to double (support ARM)
// 0.1.10 - 2015-03-07 fix clear
// 0.1.11 - 2015-03-29 undo 0.1.10 fix clear
// 0.1.12 - 2015-07-12 refactor constructor + const
// 0.1.13 - 2015-10-30 fix getElement(n) - kudos to Gdunge
// 0.1.14 - 2017-07-26 revert double to float - issue #33
// 0.1.15 - 2018-08-24 make runningMedian Configurable #110
//
// Released to the public domain
//

#include "RunningMedian.h"

RunningMedian::RunningMedian(const uint8_t size)
{
  _size = constrain(size, MEDIAN_MIN_SIZE, MEDIAN_MAX_SIZE);

#ifdef RUNNING_MEDIAN_USE_MALLOC
  _ar = (float *) malloc(_size * sizeof(float));
  _p = (uint8_t *) malloc(_size * sizeof(uint8_t));
#endif

  clear();
}

RunningMedian::~RunningMedian()
{
#ifdef RUNNING_MEDIAN_USE_MALLOC
  free(_ar);
  free(_p);
#endif
}

// resets all counters
void RunningMedian::clear()
{
  _cnt = 0;
  _idx = 0;
  _sorted = false;
  for (uint8_t i = 0; i < _size; i++) _p[i] = i;
}

// adds a new value to the data-set
// or overwrites the oldest if full.
void RunningMedian::add(float value)
{
  _ar[_idx++] = value;
  if (_idx >= _size) _idx = 0; // wrap around
  if (_cnt < _size) _cnt++;
  _sorted = false;
}

float RunningMedian::getMedian()
{
  if (_cnt == 0) return NAN;

  if (_sorted == false) sort();

  if (_cnt & 0x01) return _ar[_p[_cnt/2]];
  else return (_ar[_p[_cnt/2]] + _ar[_p[_cnt/2 - 1]]) / 2;
}

#ifdef RUNNING_MEDIAN_ALL
float RunningMedian::getAverage()
{
  if (_cnt == 0) return NAN;

  float sum = 0;
  for (uint8_t i=0; i< _cnt; i++) sum += _ar[i];
  return sum / _cnt;
}

float RunningMedian::getAverage(uint8_t nMedians)
{
  if ((_cnt == 0) || (nMedians == 0)) return NAN;

  if (_cnt < nMedians) nMedians = _cnt;     // when filling the array for first time
  uint8_t start = ((_cnt - nMedians) / 2);
  uint8_t stop = start + nMedians;

  if (_sorted == false) sort();

  float sum = 0;
  for (uint8_t i = start; i < stop; i++) sum += _ar[_p[i]];
  return sum / nMedians;
}

float RunningMedian::getElement(const uint8_t n)
{
  if ((_cnt == 0) || (n >= _cnt)) return NAN;

  uint8_t pos = _idx + n;
  if (pos >= _cnt) // faster than %
  {
    pos -= _cnt;
  }
  return _ar[pos];
}

float RunningMedian::getSortedElement(const uint8_t n)
{
  if ((_cnt == 0) || (n >= _cnt)) return NAN;

  if (_sorted == false) sort();
  return _ar[_p[n]];
}

// n can be max <= half the (filled) size
float RunningMedian::predict(const uint8_t n)
{
  if ((_cnt == 0) || (n >= _cnt/2)) return NAN;

  float med = getMedian();  // takes care of sorting !
  if (_cnt & 0x01)
  {
    return max(med - _ar[_p[_cnt/2-n]], _ar[_p[_cnt/2+n]] - med);
  }
  else
  {
    float f1 = (_ar[_p[_cnt/2 - n]] + _ar[_p[_cnt/2 - n - 1]])/2;
    float f2 = (_ar[_p[_cnt/2 + n]] + _ar[_p[_cnt/2 + n - 1]])/2;
    return max(med - f1, f2 - med)/2;
  }
}
#endif

void RunningMedian::sort()
{
  // bubble sort with flag
  for (uint8_t i = 0; i < _cnt-1; i++)
  {
    bool flag = true;
    for (uint8_t j = 1; j < _cnt-i; j++)
    {
      if (_ar[_p[j-1]] > _ar[_p[j]])
      {
        uint8_t t = _p[j-1];
        _p[j-1] = _p[j];
        _p[j] = t;
        flag = false;
      }
    }
    if (flag) break;
  }
  _sorted = true;
}

// END OF FILE