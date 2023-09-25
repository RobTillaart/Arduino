//
//    FILE: DistanceTable.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.3
// PURPOSE: Arduino library to store a symmetrical distance table in less memory
//     URL: https://github.com/RobTillaart/DistanceTable


#include "DistanceTable.h"


DistanceTable::DistanceTable(uint8_t dimension, float value)
{
  //  ATMEL 328 has ~2000 bytes RAM,
  //  so roughly 30 x 30 = 900 floats (4 bytes) => 1740 bytes is max feasible
  //  no check as other platforms allow larger tables
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


bool DistanceTable::set(uint8_t x, uint8_t y, float value )
{
  //  comment next line to skip range check (squeeze performance)
  if ( (x >= _dimension) || (y >= _dimension)) return false;
  if (x == y) return (value == 0.0);

  if ( x < y )
  {
    uint8_t t = x; x = y; y = t;  // swap
    if (_invert) value = -value;
  }
  //  prevent overflow by moving to 16 bit
  uint16_t index = x;
  index = (index * (index - 1)) / 2 + y;
  _distanceTable[index] = value;
  return true;
};


float DistanceTable::get (uint8_t x, uint8_t y)
{
  //  comment next line to skip range check (squeeze performance)
  if ( (x >= _dimension) || (y >= _dimension)) return -1;  // NAN ?
  if ( x == y ) return 0.0;

  bool flag = false;
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


//  triangular dump
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


float DistanceTable::sum()
{
  float sum = 0;
  for (uint16_t index = 0; index < _elements; index++)
  {
    sum += _distanceTable[index];
  }
  return sum * 2;  //  double it as it is symmetrical
}


float DistanceTable::average()
{
  return sum() / _elements;
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
  return cnt * 2;  //  count the symmetrical elements too.
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
  return cnt * 2;  //  count the symmetrical elements too.
}


//  --- END OF FILE ---

