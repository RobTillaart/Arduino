#pragma once
//
//    FILE: SparseArray.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
//    DATE: 2022-07-17
// PURPOSE: Arduino library for sparse arrays of floats
//     URL: https://github.com/RobTillaart/SparseArray
//


#include "Arduino.h"

#define SPARSEARRAY_LIB_VERSION        (F("0.1.2"))

#ifndef SPARSEARRAY_MAX_SIZE
#define SPARSEARRAY_MAX_SIZE           1000
#endif


class SparseArray
{
public:
  SparseArray(uint16_t sz);
  ~SparseArray();

  uint16_t size();
  uint16_t count();
  float    sum();
  void     clear();


  //  returns false if no slots free
  bool     set(uint16_t x, float value);
  //  adds value to element x
  bool     add(uint16_t x, float value);
  float    get(uint16_t x);


  //  returns two values between all values != 0 are located.
  void     boundingSegment(uint16_t &minX, uint16_t &maxX);


protected:
  uint16_t  _size   = 0;
  uint16_t  _count  = 0;

  uint16_t  *_x     = NULL;  //  support array's [0..65535]
  float     *_value = NULL;

  //  returns index of x if in set
  //  otherwise -1
  int32_t findPos(uint16_t x);

  //  removes element at position (from findPos)
  //  pre: count > 0
  void    removeElement(uint16_t pos);
  //  creates a new element if value != 0 and if there is room
  bool    newElement(uint16_t x, float value);
};


//  -- END OF FILE --

