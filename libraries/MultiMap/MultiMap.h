#pragma once
//
//    FILE: MultiMap.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2011-01-26
// PURPOSE: Arduino library for fast non-linear mapping or interpolation of values
//     URL: https://github.com/RobTillaart/MultiMap
//     URL: http://playground.arduino.cc/Main/MultiMap



#define MULTIMAP_LIB_VERSION                (F("0.2.0"))


#include "Arduino.h"


////////////////////////////////////////////////////////////////////////
//
//  SINGLE TYPE MULTIMAP - LINEAR SEARCH - the reference
//
//  note: the in array must have increasing values
template<typename T>
T multiMap(T value, T* _in, T* _out, uint8_t size)
{
  //  output is constrained to out array
  if (value <= _in[0]) return _out[0];
  if (value >= _in[size-1]) return _out[size-1];

  //  search right interval
  uint8_t pos = 1;  // _in[0] already tested
  while(value > _in[pos]) pos++;

  //  this will handle all exact "points" in the _in array
  if (value == _in[pos]) return _out[pos];

  //  interpolate in the right segment for the rest
  return (value - _in[pos-1]) * (_out[pos] - _out[pos-1]) / (_in[pos] - _in[pos-1]) + _out[pos-1];
}


////////////////////////////////////////////////////////////////////////
//
//  SINGLE TYPE MULTIMAP CACHE - LINEAR SEARCH
//
//  note: the in array must have increasing values
//  performance optimized version if inputs do not change often
//     e.g.  2 2 2 2 2 3 3 3 3 5 5 5 5 5 5 8 8 8 8 5 5 5 5 5
//  implements a minimal cache of the lastValue.
template<typename T>
T multiMapCache(T value, T* _in, T* _out, uint8_t size)
{
  static T lastValue = -1;
  static T cache = -1;

  if (value == lastValue)
  {
    return cache;
  }
  lastValue = value;

  //  output is constrained to out array
  if (value <= _in[0])
  {
    cache = _out[0];
  }
  else if (value >= _in[size-1])
  {
    cache = _out[size-1];
  }
  else
  {
    //  search right interval; index 0 _in[0] already tested
    uint8_t pos = 1;
    while(value > _in[pos]) pos++;

    //  this will handle all exact "points" in the _in array
    if (value == _in[pos])
    {
      cache = _out[pos];
    }
    else
    {
      //  interpolate in the right segment for the rest
      cache = (value - _in[pos-1]) * (_out[pos] - _out[pos-1]) / (_in[pos] - _in[pos-1]) + _out[pos-1];
    }
  }
  return cache;
}


////////////////////////////////////////////////////////////////////////
//
//  SINGLE TYPE MULTIMAP - BINARY SEARCH
//
//  should be faster for size >= 10
//  (rule of thumb)
//
//  note: the in array must have increasing values
template<typename T>
T multiMapBS(T value, T* _in, T* _out, uint8_t size)
{
  //  output is constrained to out array
  if (value <= _in[0]) return _out[0];
  if (value >= _in[size-1]) return _out[size-1];

  //  Binary Search, uint16_t needed to prevent overflow.
  uint16_t lower = 0;
  uint16_t upper = size - 1;
  while (lower < upper - 1)
  {
    uint8_t mid = (lower + upper) / 2;
    if (value >= _in[mid]) lower = mid;
    else upper = mid;
  }

  return (value - _in[lower]) * (_out[upper] - _out[lower]) / (_in[upper] - _in[lower]) + _out[lower];
}


////////////////////////////////////////////////////////////////////////
//
//  MULTITYPE MULTIMAP - LINEAR SEARCH
//
//  note: the in array must have increasing values
template<typename T1, typename T2>
T2 multiMap(T1 value, T1* _in, T2* _out, uint8_t size)
{
  //  output is constrained to out array
  if (value <= _in[0]) return _out[0];
  if (value >= _in[size-1]) return _out[size-1];

  //  search right interval
  uint16_t pos = 1;  // _in[0] already tested
  while(value > _in[pos]) pos++;

  //  this will handle all exact "points" in the _in array
  if (value == _in[pos]) return _out[pos];

  //  interpolate in the right segment for the rest
  return (value - _in[pos-1]) * (_out[pos] - _out[pos-1]) / (_in[pos] - _in[pos-1]) + _out[pos-1];
}


////////////////////////////////////////////////////////////////////////
//
//  MULTITYPE MULTIMAP - BINARY SEARCH
//  should be faster for size >= 10
//  (rule of thumb)
//
//  note: the in array must have increasing values
template<typename T1, typename T2>
T2 multiMapBS(T1 value, T1* _in, T2* _out, uint8_t size)
{
  //  output is constrained to out array
  if (value <= _in[0]) return _out[0];
  if (value >= _in[size-1]) return _out[size-1];

  //  Binary Search, uint16_t needed to prevent overflow.
  uint16_t lower = 0;
  uint16_t upper = size - 1;
  while (lower < upper - 1)
  {
    uint16_t mid = (lower + upper) / 2;
    if (value >= _in[mid]) lower = mid;
    else upper = mid;
  }

  return (value - _in[lower]) * (_out[upper] - _out[lower]) / (_in[upper] - _in[lower]) + _out[lower];
}


//  -- END OF FILE --

