//
//    FILE: TOPMAX.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
//    DATE: 2023-05-18
// PURPOSE: Arduino library to track top n maxima.
//     URL: https://github.com/RobTillaart/TOPMAX


#include "TOPMAX.h"


TOPMAX::TOPMAX(uint8_t size)
{
  _size = size;
  if (_size < 3) _size = 3;
  _count = 0;
  _arr   = (float *) malloc(_size * sizeof(float));
}


TOPMAX::~TOPMAX()
{
  if (_arr) free(_arr);
}


uint8_t TOPMAX::count()
{
  return _count;
}


uint8_t TOPMAX::size()
{
  return _size;
}


void TOPMAX::reset()
{
  _count = 0;
}


bool TOPMAX::add(float value)
{
  if (_arr == NULL) return false;
  //  initial
  if (_count == 0)
  {
    _arr[_count] = value;
    _count++;
    return true;
  }

  //  not all elements filled.
  if (_count < _size)
  {
    int i = _count - 1;
    while ((i >= 0) && (value < _arr[i]))
    {
      _arr[i + 1] = _arr[i];
      i--;
    }
    _arr[i + 1] = value;
    _count++;
    return true;
  }

  //  too small (or equal)
  if (value <= _arr[0]) return false;

  //  insert
  int i = 1;
  while ((i < _size) && (value > _arr[i]))
  {
    _arr[i - 1] = _arr[i];
    i++;
  }
  _arr[i - 1] = value;
  return true;
}


bool TOPMAX::fill(float value)
{
  if (_arr == NULL) return false;
  for (int i = 0; i < _size; i++)
  {
    _arr[i] = value;
  }
  _count = _size;
  return true;
}


float TOPMAX::getValue(uint8_t index)
{
  if ((_arr == NULL) || (index >= _count)) return NAN;
  return _arr[_count - 1 - index];
}


////////////////////////////////////////////////////
//
//  DERIVED
//
TOPMAXext::TOPMAXext(uint8_t size) : TOPMAX(size)
{
  _tag = (uint32_t *) malloc(_size * sizeof(uint32_t));
}


TOPMAXext::~TOPMAXext()
{
  if (_tag) free(_tag);
}


bool TOPMAXext::add(float value, uint32_t tag)
{
  if (_arr == NULL) return false;
  if (_tag == NULL) return false;
  //  initial
  if (_count == 0)
  {
    _arr[_count] = value;
    _tag[_count] = tag;
    _count++;
    return true;
  }

  //  not all elements filled.
  if (_count < _size)
  {
    int i = _count - 1;
    while ((i >= 0) && (value < _arr[i]))
    {
      _arr[i + 1] = _arr[i];
      _tag[i + 1] = _tag[i];
      i--;
    }
    _arr[i + 1] = value;
    _tag[i + 1] = tag;
    _count++;
    return true;
  }

  //  too small (or equal)
  if (value <= _arr[0]) return false;

  //  insert
  int i = 1;
  while ((i < _size) && (value > _arr[i]))
  {
    _arr[i - 1] = _arr[i];
    _tag[i - 1] = _tag[i];
    i++;
  }
  _arr[i - 1] = value;
  _tag[i - 1] = tag;
  return true;
}


bool TOPMAXext::fill(float value, uint32_t tag)
{
  if (_arr == NULL) return false;
  if (_tag == NULL) return false;
  for (int i = 0; i < _size; i++)
  {
    _arr[i] = value;
    _tag[i] = tag;
  }
  _count = _size;
  return true;
}


uint32_t TOPMAXext::getTag(uint8_t index)
{
  if ((_tag == NULL) || (index >= _count)) return 0xFFFFFFFF;
  return _tag[_count - 1 - index];
}


//  -- END OF FILE --

