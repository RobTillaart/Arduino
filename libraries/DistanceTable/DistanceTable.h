#pragma once
//
//    FILE: DistanceTable.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: Arduino library to store a symmetrical distance table in less memory
//     URL: https://github.com/RobTillaart/DistanceTable
//


#include "Arduino.h"


#define DISTANCETABLE_LIB_VERSION     (F("0.2.0"))


class DistanceTable
{
public:
  explicit DistanceTable(uint8_t dimension);
  ~DistanceTable();

  void     clear() { setAll(0); };
  void     setAll(float value);
  void     set(uint8_t x, uint8_t y, float value );
  float    get(uint8_t x, uint8_t y);


  // minimum and maximum skip x == y  pairs as these are 0.
  float    minimum(uint8_t &x, uint8_t &y);
  float    maximum(uint8_t &x, uint8_t &y);


  // epsilon allows 'almost equal' searches
  // count counts (x,y) but not (y,x) again.
  // count skips x == y  pairs...
  uint16_t count(float value, float epsilon = 0.0);


  // debug
  // default dumps to Serial but other stream are possible
  void     dump(Print * stream = &Serial);
  uint8_t  dimension()  { return _dimension; };
  uint16_t elements()   { return _elements; };
  uint16_t memoryUsed() { return _elements * sizeof(float); };


// Obsolete in future
  uint16_t size() { return memoryUsed(); };

protected:
  uint8_t  _dimension;
  uint16_t _elements;
  float *  _distanceTable;

};

// --- END OF FILE ---
