//
//    FILE: RunningMedian.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.9
// PURPOSE: RunningMedian library for Arduino


#include "RunningMedian.h"


RunningMedian::RunningMedian(const uint8_t size)
{
  _size = size;
  if (_size < MEDIAN_MIN_SIZE) _size = MEDIAN_MIN_SIZE;
#if !RUNNING_MEDIAN_USE_MALLOC
  if (_size > MEDIAN_MAX_SIZE) _size = MEDIAN_MAX_SIZE;
#endif

#if RUNNING_MEDIAN_USE_MALLOC
  _values = (float *) malloc(_size * sizeof(float));
  _sortIdx  = (uint8_t *) malloc(_size * sizeof(uint8_t));
#endif
  clear();
}


RunningMedian::~RunningMedian()
{
  #if RUNNING_MEDIAN_USE_MALLOC
  free(_values);
  free(_sortIdx);
  #endif
}


//  resets all internal counters
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


//  adds a new value to the data-set
//  or overwrites the oldest if full.
void RunningMedian::add(float value)
{
  _values[_index++] = value;
  if (_index >= _size) _index = 0; //  wrap around
  if (_count < _size) _count++;
  _sorted = false;
}


float RunningMedian::getMedian()
{
  if (_count == 0) return NAN;

  if (_sorted == false) sort();

  if (_count & 0x01)  //  is it odd sized?
  {
    return _values[_sortIdx[_count / 2]];
  }
  return (_values[_sortIdx[_count / 2]] + _values[_sortIdx[_count / 2 - 1]]) / 2;
}


float RunningMedian::getQuantile(float quantile)
{
  if (_count == 0) return NAN;

  if ((quantile < 0) || (quantile > 1)) return NAN;

  if (_sorted == false) sort();

  const float index = (_count - 1) * quantile;
  const uint8_t lo  = floor(index);
  const uint8_t hi  = ceil(index);
  const float qs    = _values[_sortIdx[lo]];
  const float h     = (index - lo);

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

//  when filling the array for first time
  if (_count < nMedians) nMedians = _count;

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


//  nMedians is the spread, or the middle N
//  this version compensated for bias #22

float RunningMedian::getMedianAverage(uint8_t nMedians)
{
  //  handle special cases.
  if ((_count == 0) || (nMedians == 0)) return NAN;
  if (_count == 1) return _values[0];
  if (_count == 2) return (_values[0] + _values[1]) * 0.5;

  //  nMedians can not be larger than current nr of elements.
  if (_count <= nMedians) return getAverage();

  //  _count is at least 3 from here

  //  Eliminate the bias when the nMedians would fall slightly
  //  to the left or right of the centre.
  //  If count and nMedians are not both odd or both even reduce
  //  the spread by 1 to make them the same.
  //  If nMedians becomes 0 correct this. to 2.
  if ((_count & 0x01) != (nMedians & 0x01))
  {
     --nMedians;
     //  nmedians can not become 0
     if (nMedians == 0) nMedians = 2;
  }

  uint8_t start = (_count - nMedians) / 2;
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
  if (pos >= _count)  //  faster than %
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


//  n can be max <= half the (filled) size
float RunningMedian::predict(const uint8_t n)
{
  uint8_t mid = _count / 2;
  if ((_count == 0) || (n >= mid)) return NAN;

  float med = getMedian();  //  takes care of sorting !
  if (_count & 0x01)        //  odd # elements
  {
    return max(med - _values[_sortIdx[mid - n]], _values[_sortIdx[mid + n]] - med);
  }
  //  even # elements
  float f1 = (_values[_sortIdx[mid - n]] + _values[_sortIdx[mid - n - 1]]) / 2;
  float f2 = (_values[_sortIdx[mid + n]] + _values[_sortIdx[mid + n - 1]]) / 2;
  return max(med - f1, f2 - med) / 2;
}


void RunningMedian::setSearchMode(uint8_t searchMode)
{
  if (searchMode == 1) _searchMode = 1;
  else _searchMode = 0;
}


uint8_t RunningMedian::getSearchMode()
{
  return _searchMode;
}


////////////////////////////////////////////////////////////
//
//  PRIVATE
//

//  insertion sort - _searchMode = linear or binary.

void RunningMedian::sort()
{
  uint16_t lo   = 0;
  uint16_t hi   = 0;
  uint16_t mi   = 0;
  uint16_t temp = 0;

  for (uint16_t i = 1; i < _count; i++)
  {
    temp = _sortIdx[i];
    float f = _values[temp];

    //  handle special case f is smaller than all elements first.
    //  only one compare needed, improves linear search too.
    if (f <= _values[_sortIdx[0]])
    {
      hi = 0;
    }
    else
    {
      if (_searchMode == 0)
      {
        hi = i;
        //  find insertion point with linear search
        while ((hi > 0) && (f < _values[_sortIdx[hi - 1]]))
        {
          hi--;
        }
      }
      else if (_searchMode == 1)
      {
        //  find insertion point with binary search
        lo = 0;
        hi = i;
        //  be aware there might be duplicates
        while (hi - lo > 1)
        {
          mi = (lo + hi) / 2;
          if (f < _values[_sortIdx[mi]])
          {
            hi = mi;
          }
          else
          {
            lo = mi;
          }
        }
      }
    }

    //  move elements to make space
    uint16_t k = i;
    while (k > hi)
    {
      _sortIdx[k] = _sortIdx[k - 1];
      k--;
    }

    //  insert at right spot.
    _sortIdx[k] = temp;

  }
  _sorted = true;

  // //  verify sorted
  // for (int i = 0; i < _count; i++)
  // {
    // if (i%5 == 0) Serial.println();
    // Serial.print("\t");
    // Serial.print(_values[_sortIdx[i]]);
  // }
  // Serial.println("\n");
}



/*
 split version of pre-0.3.7 sort - bit faster

void RunningMedian::sort()
{
  // insertSort
  for (uint16_t i = 1; i < _count; i++)
  {
    uint16_t hi = i;
    uint16_t temp = _sortIdx[hi];
    float f = _values[temp];
    while ((hi > 0) && (f < _values[_sortIdx[hi - 1]]))
    {
      hi--;
    }

    //  move elements to make space
    uint16_t k = i;
    while (k > hi)
    {
      _sortIdx[k] = _sortIdx[k - 1];
      k--;
    }

    //  insert at right spot.
    _sortIdx[k] = temp;
  }
  _sorted = true;
  //  //  verify sorted
  // for (int i = 0; i < _count; i++)
  // {
    // if (i%5 == 0) Serial.println();
    // Serial.print("\t");
    // Serial.print(_values[_sortIdx[i]]);
  // }
  // Serial.println("\n");
}
*/


/*
//  straightforward insertion sort - PRE-0.3.7
void RunningMedian::sort()
{
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

  //  //  verify sorted
  // for (int i = 0; i < _count; i++)
  // {
    // if (i%5 == 0) Serial.println();
    // Serial.print("\t");
    // Serial.print(_values[_sortIdx[i]]);
  // }
  // Serial.println("\n");
}
*/


//  -- END OF FILE --

