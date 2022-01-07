//
//    FILE: DistanceTable.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
// PURPOSE: Arduino library to store a symmetrical distance table in less memory
//     URL: https://github.com/RobTillaart/DistanceTable

//  HISTORY
//  0.1.00  initial version
//  0.1.01  refactor
//  0.1.2   fix overflow;  add some error detection; revert float to float to memory
//  0.1.3   2017-07-27  Fix issue #33
//  0.1.4   2019-01-10  add size()
//  0.1.5   2020-06-07  fix library.json, minor edits
//  0.1.6   2020-12-20  Arduino-CI + unit test
//  0.2.0   2021-01-19  refactor
//                      properly named functions,
//                      add setAll(), minimum(), maximum() and count()
//  0.2.1   2021-10-26  update build-CI, update readme.md
//                      default value in constructor
//  0.2.2   2021-12-17  update license, readme, minor edits
//  0.3.0   2022-01-06  add invert flag, add unit tests
//                      add countAbove(), countBelow()
//                      fix allocation + # elements




#include "DistanceTable.h"


DistanceTable::DistanceTable(uint8_t dimension, float value)
{
  // ATMEL 328 has ~2000 bytes RAM,
  // so roughly 30X30 = 900 floats(4Bytes) => 1740 bytes is max feasible
  _invert = false;
  _distanceTable = NULL;
  _dimension = dimension;
  _elements  = 0;

  if (dimension < 2) return;
  _elements = (_dimension * (_dimension - 1)) / 2;
  _distanceTable = (float *) malloc(_elements * sizeof(float));
  if (_distanceTable == NULL)
  {
    _dimension = 0;
    _elements  = 0;
  }
  setAll(value);
}


DistanceTable::~DistanceTable()
{
  if (_distanceTable != NULL)
  {
    free(_distanceTable);
  }
}


void DistanceTable::setAll(float value)
{
  for (uint16_t index = 0; index < _elements; index++)
  {
    _distanceTable[index] = value;
  }
};


void DistanceTable::set(uint8_t x, uint8_t y, float value )
{
  if ( x == y ) return;
  // comment next line to skip range check (squeeze performance)
  if ( (x >= _dimension) || (y >= _dimension)) return;

  if ( x < y )
  {
    uint8_t t = x; x = y; y = t;  // swap
    if (_invert) value = -value;
  }
  // prevent overflow by moving to 16 bit
  uint16_t index = x;
  index = (index * (index - 1)) / 2 + y;
  _distanceTable[index] = value;
};


float DistanceTable::get (uint8_t x, uint8_t y)
{
  bool flag = false;
  if ( x == y ) return 0.0;  // TODO even true when x and y are out of range??
  // comment next line to skip range check (squeeze performance)
  if ( (x >= _dimension) || (y >= _dimension)) return -1;  // NAN ?

  if ( x < y )
  {
    uint8_t t = x; x = y; y = t;
    flag = true;
  }
  uint16_t index = x;
  index = (index * (index-1))/2 + y;
  float value = _distanceTable[index];
  if (_invert && flag) value = -value;
  return value;
};


// triangular dump
void DistanceTable::dump(Print * stream)
{
  stream->println();
  for (uint8_t i = 0; i < _dimension; i++)
  {
    for (uint8_t j = 0; j <_dimension; j++)
    {
      stream->print(get(i, j));
      stream->print("\t");
    }
    stream->println();
  }
  stream->println();
};


float DistanceTable::minimum(uint8_t &x, uint8_t &y)
{
  float mi = _distanceTable[0];
  x = 0;
  y = 0;
  for (uint8_t xx = 1; xx < _dimension; xx++)
  {
    uint16_t index = (xx * (xx - 1))/2;
    for (uint8_t yy = 0; yy < xx; yy++)
    {
      float value = _distanceTable[index + yy];
      if (value < mi)
      {
        mi = value;
        x = xx;
        y = yy;
      }
      else if (_invert)
      {
        value = -value;
        if (value < mi)
        {
          mi = value;
          x = yy;
          y = xx;
        }
      }
    }
  }
  return mi;
}


float DistanceTable::maximum(uint8_t &x, uint8_t &y)
{
  float ma = _distanceTable[0];
  x = 0;
  y = 0;
  for (uint8_t xx = 1; xx < _dimension; xx++)
  {
    uint16_t index = (xx * (xx - 1))/2;
    for (uint8_t yy = 0; yy < xx; yy++)
    {
      float value = _distanceTable[index + yy];
      if (value > ma)
      {
        ma = value;
        x = xx;
        y = yy;
      }
      else if (_invert)
      {
        value = -value;
        if (value > ma)
        {
          ma = value;
          x = yy;
          y = xx;
        }
      }
    }
  }
  return ma;
}


uint16_t DistanceTable::count(float value, float epsilon)
{
  uint16_t cnt = 0;
  for (uint16_t index = 0; index < _elements; index++)
  {
    float current = _distanceTable[index];
    if (abs (current - value) < epsilon) cnt++;
    else if (_invert)
    {
      if (abs (current + value) < epsilon) cnt++;
    }
  }
  if (_invert) return cnt;
  return cnt * 2;  // count the symmetrical elements too.
}


uint16_t DistanceTable::countAbove(float value)
{
  uint16_t cnt = 0;
  for (uint16_t index = 0; index < _elements; index++)
  {
    float current = _distanceTable[index];
    if (current > value) cnt++;
    else if (_invert)
    {
      if (-current > value) cnt++;
    }
  }
  if (_invert) return cnt;
  return cnt * 2;  // count the symmetrical elements too.
}


uint16_t DistanceTable::countBelow(float value)
{
  uint16_t cnt = 0;
  for (uint16_t index = 0; index < _elements; index++)
  {
    float current = _distanceTable[index];
    if (current < value) cnt++;
    else if (_invert)
    {
      if (-current < value) cnt++;
    }
  }
  if (_invert) return cnt;
  return cnt * 2;  // count the symmetrical elements too.
}


// --- END OF FILE ---

