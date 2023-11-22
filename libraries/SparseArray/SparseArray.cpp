//
//    FILE: SparseArray.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
//    DATE: 2022-07-17
// PURPOSE: Arduino library for sparse arrays of floats
//     URL: https://github.com/RobTillaart/SparseArray


#include "SparseArray.h"


SparseArray::SparseArray(uint16_t sz)
{
  _count = 0;
  _size  = sz;
  if ( _size > SPARSEARRAY_MAX_SIZE)
  {
    _size = SPARSEARRAY_MAX_SIZE;
  }
  _x     = (uint16_t *) malloc(sz * sizeof(uint16_t));
  _value = (float *)    malloc(sz * sizeof(float));
  //  catch malloc error
  if (_x && _value) return;
  //  if malloc error set size to zero.
  _size = 0;
}


SparseArray::~SparseArray()
{
  if (_x) free(_x);
  if (_value) free(_value);
}


uint16_t SparseArray::size()
{
  return _size;
}


uint16_t SparseArray::count()
{
  return _count;
}


void SparseArray::clear()
{
  _count = 0;
}


float SparseArray::sum()
{
  float _sum = 0;
  for (uint16_t i = 0; i < _count; i++)
  {
    _sum += _value[i];
  }
  return _sum;
}


bool SparseArray::set(uint16_t x, float value)
{
  int32_t pos = findPos(x);
  //  existing element
  if (pos > -1)
  {
    _value[pos] = value;
    if (_value[pos] == 0.0) removeElement(pos);
    return true;
  }

  //  does not exist => new element ?
  return newElement(x, value);
}


bool SparseArray::add(uint16_t x, float value)
{
  int32_t pos = findPos(x);
  //  existing element
  if (pos > -1)
  {
    _value[pos] += value;
    if (_value[pos] == 0.0) removeElement(pos);
    return true;
  }

  //  does not exist => new element ?
  return newElement(x, value);
}


float SparseArray::get(uint16_t x)
{
  int32_t pos = findPos(x);
  if (pos > -1)
  {
    return _value[pos];
  }
  return 0;
}


void SparseArray::boundingSegment(uint16_t &minX, uint16_t &maxX)
{
  uint16_t _minx = 65535, _maxx = 0;
  for (uint16_t i = 0; i < _count; i++)
  {
    if (_x[i] < _minx) _minx = _x[i];
    if (_x[i] > _maxx) _maxx = _x[i];
  }
  minX = _minx;
  maxX = _maxx;
}


//////////////////////////////////////////////////////
//
//  PRIVATE
//
int32_t SparseArray::findPos(uint16_t x)
{
  //  linear search - not optimized.
  for (uint16_t i = 0; i < _count; i++)
  {
    if (_x[i] == x)
    {
      return (int32_t)i;
    }
  }
  return -1;
}


void SparseArray::removeElement(uint16_t pos)
{
  _count--;
  //  move last element
  //  efficiency (keep sorted) is no requirement.
  if (pos == _count) return;
  _x[pos]     = _x[_count];
  _value[pos] = _value[_count];
}


bool SparseArray::newElement(uint16_t x, float value)
{
  if (value == 0.0) return true;
  if (_count >= _size) return false;
  _x[_count]     = x;
  _value[_count] = value;
  _count++;
  return true;
}


//  -- END OF FILE --

