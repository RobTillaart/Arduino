//
//    FILE: DistanceTable.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: Arduino library to store a symmetrical distance table in less memory
//     URL: https://github.com/RobTillaart/DistanceTable


//  0.2.0   2021-01-19  refactor
//                      properly named functions, 
//                      add setAll(), minimum(), maximum() and count()
//  0.1.6   2020-12-20  arduino-ci + unit test
//  0.1.5   2020-06-07  fix library.json, minor edits
//  0.1.4   2019-01-10  add size()
//  0.1.3   2017-07-27  Fix issue #33
//  0.1.2   fix overflow;  add some error detection;  revert float to float to memory
//  0.1.01  refactor
//  0.1.00  initial version


#include "DistanceTable.h"


DistanceTable::DistanceTable(uint8_t dimension)
{
  // ATMEL 328 has 2000 bytes mem,
  // so roughly 30X30 = 900 floats(4Bytes) => 1740 bytes is max feasible
  _dimension = 0;
  _elements  = 0;
  if (dimension < 2) return;

  _dimension = dimension;
  _elements = _dimension;
  _elements *= ((_dimension - 1) / 2);
  _distanceTable = (float *) malloc(_elements * sizeof(float));
  if (_distanceTable == NULL)
  {
    _dimension = 0;
    _elements  = 0;
  }
  setAll(0);
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
  // comment next line to skip rangecheck (squeeze performance)
  if ( (x >= _dimension) || (y >= _dimension)) return;

  if ( x < y )
  {
    uint8_t t = x; x = y; y = t;  // swap
  }
  // prevent overflow by moving to 16 bit
  uint16_t index = x;
  index = (index * (index - 1)) / 2 + y;
  _distanceTable[index] = value;
};


float DistanceTable::get (uint8_t x, uint8_t y)
{
  if ( x == y ) return 0.0;  // TODO even true when x and y are out of range??
  // comment next line to skip rangecheck (squeeze performance)
  if ( (x >= _dimension) || (y >= _dimension)) return -1;  // NAN ?

  if ( x < y )
  {
    uint8_t t = x; x = y; y = t;
  }
  uint16_t index = x;
  index = (index * (index-1))/2 + y;
  return _distanceTable[index];
};


// triangular dump
void DistanceTable::dump(Print * stream)
{
  stream->println();
  uint16_t index = 0;
  for (uint8_t i = 0; i < _dimension - 1; i++)
  {
    for (uint8_t j = 0; j <= i; j++)
    {
      stream->print(_distanceTable[index++]);
      stream->print("\t");
    }
    stream->println();
  }
  stream->println();
};


float DistanceTable::minimum(uint8_t &x, uint8_t &y)
{
  float mi = _distanceTable[0];
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
    }
  }
  return mi;
}


float DistanceTable::maximum(uint8_t &x, uint8_t &y)
{
  float ma = _distanceTable[0];
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
    }
  }
  return ma;
}


uint16_t DistanceTable::count(float value, float epsilon)
{
  uint16_t cnt = 0;
  for (uint16_t index = 0; index < _elements; index++)
  {
    if (abs (_distanceTable[index] - value) < epsilon) cnt++;
  }
  return cnt;
}


// --- END OF FILE ---
