#pragma once
//
//    FILE: DistanceTable.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.4
// PURPOSE: Arduino library to store a symmetrical distance table in less memory
//     URL: https://github.com/RobTillaart/DistanceTable
//


#include "Arduino.h"


#define DISTANCETABLE_LIB_VERSION     (F("0.3.4"))


class DistanceTable
{
public:
  explicit DistanceTable(uint8_t dimension, float value = 0);
  ~DistanceTable();

  void     clear() { setAll(0); };
  void     setAll(float value);
  bool     set(uint8_t x, uint8_t y, float value );
  float    get(uint8_t x, uint8_t y);


  //  the invert flag tells that get(x, y) == -get(y, x);
  void     setInvert(bool invert = false) { _invert = invert; };
  bool     getInvert() { return _invert; };


  //  minimum and maximum skip x == y  pairs as these are 0.
  float    minimum(uint8_t &x, uint8_t &y);
  float    maximum(uint8_t &x, uint8_t &y);
  float    sum();
  float    average();


  //  column functions
  float   sumOfColumn(uint8_t x);
  float   averageOfColumn(uint8_t x, bool skipSelf = false);
  float   minimumOfColumn(uint8_t x, bool skipSelf = false);
  float   maximumOfColumn(uint8_t x, bool skipSelf = false);


  //  GeoMetric Median - EXPERIMENTAL
  //  see Wikipedia.
  //  this is a sort of GM search, there can be more than one
  //      returns the first occurrence of the minimum column.
  //      this is a point "closest" to all other points.
  //  these three functions sweep over the whole table.
  float   geometricMedian(uint8_t &x);
  float   minColumn(uint8_t &x);  //  is same as geometricMedian()
  float   maxColumn(uint8_t &x);  //  furthest away on average.


  //  epsilon allows 'almost equal' searches
  //  if (invert == false) count counts both (x,y) and (y,x)  => always even nr.
  //  if (invert == true)  count counts (x,y) and (y,x) separately.
  //  count skips x == y  pairs so counting zero's is missing the diagonal.
  uint16_t count(float value, float epsilon = 0.0);
  uint16_t countAbove(float value);
  uint16_t countBelow(float value);


  //  debug
  //  default dumps to Serial but other stream are possible
  void     dump(Print * stream = &Serial);
  uint8_t  dimension()  { return _dimension; };
  uint16_t elements()   { return _elements; };
  uint16_t memoryUsed() { return _elements * sizeof(float); };


  //  Obsolete in future 0.4.0
  uint16_t size() { return memoryUsed(); };

protected:
  uint8_t  _dimension;
  uint16_t _elements;
  float *  _distanceTable;
  bool     _invert;
};


//  --- END OF FILE ---

