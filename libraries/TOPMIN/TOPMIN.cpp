//
//    FILE: TOPMIN.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
//    DATE: 2023-05-18
// PURPOSE: Arduino library to track top n minima.
//     URL: https://github.com/RobTillaart/TOPMIN


#include "TOPMIN.h"


TOPMIN::TOPMIN(uint8_t size)
{
  _size = size;
  if (_size < 3) _size = 3;
  _count = 0;
  _arr   = (float *) malloc(_size * sizeof(float));
}


TOPMIN::~TOPMIN()
{
  if (_arr) free(_arr);
}


uint8_t TOPMIN::count()
{
  return _count;
}


uint8_t TOPMIN::size()
{
  return _size;
}


void TOPMIN::reset()
{
  _count = 0;
}


bool TOPMIN::add(float value)
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
    while ((i >= 0) && (value > _arr[i]))
    {
      _arr[i + 1] = _arr[i];
      i--;
    }
    _arr[i + 1] = value;
    _count++;
    return true;
  }

  //  too small (or equal)
  if (value >= _arr[0]) return false;

  //  insert
  int i = 1;
  while ((i < _size) && (value < _arr[i]))
  {
    _arr[i - 1] = _arr[i];
    i++;
  }
  _arr[i - 1] = value;
  return true;
}


bool TOPMIN::fill(float value)
{
  if (_arr == NULL) return false;
  for (int i = 0; i < _size; i++)
  {
    _arr[i] = value;
  }
  _count = _size;
  return true;
}


float TOPMIN::getValue(uint8_t index)
{
  if ((_arr == NULL) || (index >= _count)) return NAN;
  return _arr[_count - 1 - index];
}


////////////////////////////////////////////////////
//
//  DERIVED
//
TOPMINext::TOPMINext(uint8_t size) : TOPMIN(size)
{
  _tag = (uint32_t *) malloc(_size * sizeof(uint32_t));
}


TOPMINext::TOPMINext()
{
  if (_tag) free(_tag);
}


bool TOPMINext::add(float value, uint32_t tag)
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
    while ((i >= 0) && (value > _arr[i]))
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
  if (value >= _arr[0]) return false;

  //  insert
  int i = 1;
  while ((i < _size) && (value < _arr[i]))
  {
    _arr[i - 1] = _arr[i];
    _tag[i - 1] = _tag[i];
    i++;
  }
  _arr[i - 1] = value;
  _tag[i - 1] = tag;
  return true;
}


bool TOPMINext::fill(float value, uint32_t tag)
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


uint32_t TOPMINext::getTag(uint8_t index)
{
  if ((_tag == NULL) || (index >= _count)) return 0xFFFFFFFF;
  return _tag[_count - 1 - index];
}


//  -- END OF FILE --

