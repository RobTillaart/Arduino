//
//    FILE: RunningAverage.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.4.2
//    DATE: 2015-July-10
// PURPOSE: Arduino library to calculate the running average by means of a circular buffer
//     URL: https://github.com/RobTillaart/RunningAverage
//
// The library stores N individual values in a circular buffer,
// to calculate the running average.
//
//  HISTORY:
//  0.1.00  2011-01-30  initial version
//  0.1.01  2011-02-28  fixed missing destructor in .h
//  0.2.00  2012-??-??  Yuval Naveh added trimValue (found on web)
//          http://stromputer.googlecode.com/svn-history/r74/trunk/Arduino/Libraries/RunningAverage/RunningAverage.cpp
//  0.2.01  2012-11-21  refactored
//  0.2.02  2012-12-30  refactored trimValue -> fillValue
//  0.2.03  2013-11-31  getElement
//  0.2.04  2014-07-03  added memory protection
//  0.2.05  2014-12-16  changed float -> double
//  0.2.06  2015-03-07  all size uint8_t
//  0.2.07  2015-03-16  added getMin() and getMax() functions (Eric Mulder)
//  0.2.08  2015-04-10  refactored getMin() and getMax() implementation
//  0.2.09  2015-07-12  refactor const + constructor
//  0.2.10  2015-09-01  added getFastAverage() and refactored getAverage()
//                      http://forum.arduino.cc/index.php?topic=50473
//  0.2.11  2015-09-04  added getMaxInBuffer() getMinInBuffer() request (Antoon)
//  0.2.12  2016-12-01  added GetStandardDeviation() GetStandardError() BufferIsFull()  (V0v1kkk)
//  0.2.13  2017-07-26  revert double to float - issue #33;
//                      refactored a bit; marked some TODO's; all function names to camelCase
//  0.2.14  2020-01-15  added getValue(n) to retrieve elements in order of addition - see issue #132
//  0.2.15  2020-01-17  fix overflow in getValue - see issue #139
//  0.2.16  2020-04-16  improve _sum - see issue #149 (bourkemcrobbo)
//  0.3.0   2020-04-16  main refactor
//  0.3.1   2020-06-19  fix library.json; minor refactor
//  0.3.2   2021-01-15  add add() + license + refactor
//  0.4.0   2021-05-18  increase size above 256 elements (16 bit version)
//  0.4.1   2021-11-22  updated buil-CI, readme, badges
//                      add getAverageLast() functions.
//  0.4.2   2021-12-28  license, minor edits


#include "RunningAverage.h"


RunningAverage::RunningAverage(const uint16_t size)
{
  _size = size;
  _partial = _size;
  _array = (float*) malloc(_size * sizeof(float));
  if (_array == NULL) _size = 0;
  clear();
}


RunningAverage::~RunningAverage()
{
  if (_array != NULL) free(_array);
}


// resets all counters
void RunningAverage::clear()
{
  _count = 0;
  _index = 0;
  _sum = 0.0;
  _min = NAN;
  _max = NAN;
  for (uint16_t i = _size; i > 0; )
  {
    _array[--i] = 0.0; // keeps addValue simpler
  }
}


// adds a new value to the data-set
void RunningAverage::addValue(const float value)
{
  if (_array == NULL)
  {
    return;
  }

  _sum -= _array[_index];
  _array[_index] = value;
  _sum += _array[_index];
  _index++;

  if (_index == _partial) _index = 0;  // faster than %

  // handle min max
  if (_count == 0) _min = _max = value;
  else if (value < _min) _min = value;
  else if (value > _max) _max = value;

  // update count as last otherwise if ( _count == 0) above will fail
  if (_count < _partial) _count++;
}


// returns the average of the data-set added so far, NAN if no elements.
float RunningAverage::getAverage()
{
  if (_count == 0)
  {
    return NAN;
  }

  _sum = 0;
  for (uint16_t i = 0; i < _count; i++)
  {
    _sum += _array[i];
  }
  return _sum / _count;   // multiplication is faster ==> extra admin
}


// the larger the size of the internal buffer the greater the gain wrt getAverage()
float RunningAverage::getFastAverage() const
{
  if (_count == 0)
  {
    return NAN;
  }

  return _sum / _count;   // multiplication is faster ==> extra admin
}


// returns the minimum value in the buffer
float RunningAverage::getMinInBuffer() const
{
  if (_count == 0)
  {
    return NAN;
  }

  float _min = _array[0];
  for (uint16_t i = 1; i < _count; i++)
  {
    if (_array[i] < _min) _min = _array[i];
  }
  return _min;
}


// returns the maximum value in the buffer
float RunningAverage::getMaxInBuffer() const
{
  if (_count == 0)
  {
    return NAN;
  }

  float _max = _array[0];
  for (uint16_t i = 1; i < _count; i++)
  {
    if (_array[i] > _max) _max = _array[i];
  }
  return _max;
}


// returns the value of an element if exist, NAN otherwise
float RunningAverage::getElement(uint16_t index) const
{
  if (_count == 0)
  {
    return NAN;
  }

  return _array[index];
}


// Return standard deviation of running average.
// If buffer is empty or has only one element, return NAN.
float RunningAverage::getStandardDeviation() const
{
  // see issue #13
  // need float _stddev = -1;
  //    + patch add() and clear() to reset _stddev to -1;
  // if (_stddev != -1) return _stddev;
  if (_count <= 1) return NAN;

  float temp = 0;
  float average = getFastAverage();
  for (uint16_t i = 0; i < _count; i++)
  {
    temp += pow((_array[i] - average), 2);
  }
  temp = sqrt(temp/(_count - 1));
  return temp;
  // see issue #13
  // _stddev = temp;  // cache the calculate value
  // return _stddev;
}


// Return standard error of running average.
// If buffer is empty or has only one element, return NAN.
float RunningAverage::getStandardError() const
{
  float temp = getStandardDeviation();
  if (temp == NAN) return NAN;

  float n;
  if (_count >= 30) n = _count;
  else n = _count - 1;
  temp = temp/sqrt(n);

  return temp;
}


// fill the average with the same value number times. (weight)
// This is maximized to size times.
// no need to fill the internal buffer over 100%
void RunningAverage::fillValue(const float value, const uint16_t number)
{
  clear();
  uint16_t s = number;
  if (s > _size) s = _size;
  for (uint16_t i = s; i > 0; i--)
  {
    addValue(value);
  }
}

// https://github.com/RobTillaart/RunningAverage/issues/13
// - substantially faster version off fillValue()
// - adds to program size
// void RunningAverage::fillValue(const float value, const uint16_t number)
// {
  // uint16_t s = number;
  // if (s > _size) s = _size;
  // for (uint16_t idx = 0; idx < s; idx++)
  // {
    // _array[idx] = value;
  // }
  // _index = s;
  // if (_index == _partial) _index = 0;  // faster than %
  // _min = value;
  // _max = value;
  // _count = s;
  // _sum = s * value;
// }


float RunningAverage::getValue(const uint16_t position)
{
  if (_count == 0)
  {
    return NAN;
  }
  if (position >= _count)
  {
    return NAN;  // cannot ask more than is added
  }

  uint16_t _pos = position + _index;
  if (_pos >= _count) _pos -= _count;
  return _array[_pos];
}


void RunningAverage::setPartial(const uint16_t partial)
{
  _partial = partial;
  if ((_partial == 0) || (_partial > _size)) _partial = _size;
  clear();
}


////////////////////////////////////////////////////////////////
//
// 0.4.1 added.
//
float RunningAverage::getAverageLast(uint16_t count)
{
  uint16_t cnt = count;
  if (cnt > _count) cnt = _count;
  if (cnt == 0) return NAN;

  uint16_t idx = _index;
  float _sum = 0;
  for (uint16_t i = 0; i < cnt; i++)
  {
    if (idx == 0) idx = _size;
    idx--;
    _sum +=_array[idx];
  }
  return _sum / cnt;
}


float RunningAverage::getMinInBufferLast(uint16_t count)
{
  uint16_t cnt = count;
  if (cnt > _count) cnt = _count;
  if (cnt == 0) return NAN;

  uint16_t idx = _index;
  if (idx == 0) idx = _size;
  idx--;
  float _min = _array[idx];
  for (uint16_t i = 0; i < cnt; i++)
  {
    if (_array[idx] < _min) _min = _array[idx];
    if (idx == 0) idx = _size;
    idx--;
  }
  return _min;
}


float RunningAverage::getMaxInBufferLast(uint16_t count)
{
  uint16_t cnt = count;
  if (cnt > _count) cnt = _count;
  if (cnt == 0) return NAN;

  uint16_t idx = _index;
  if (idx == 0) idx = _size;
  idx--;
  float _max = _array[idx];
  for (uint16_t i = 0; i < cnt; i++)
  {
    if (_array[idx] > _max) _max = _array[idx];
    if (idx == 0) idx = _size;
    idx--;
  }
  return _max;
}


// -- END OF FILE --

