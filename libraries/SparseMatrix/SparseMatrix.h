#pragma once
//
//    FILE: SparseMatrix.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2022-07-12
// PURPOSE: Arduino library for sparse matrices
//     URL: https://github.com/RobTillaart/SparseMatrix
//


#include "Arduino.h"

#define SPARSEMATRIX_LIB_VERSION        (F("0.2.0"))

#ifndef SPARSEMATRIX_MAX_SIZE
#define SPARSEMATRIX_MAX_SIZE           1000
#endif


class SparseMatrix
{
public:
  SparseMatrix(uint16_t size);
  ~SparseMatrix();

  uint16_t size();
  uint16_t count();
  float    sum();
  void     clear();

  //  returns false if no slots free
  //  could return # free slots?
  bool     set(uint8_t x, uint8_t y, float value);
  //  adds a value to element x, y (e.g. for 2D histogram)
  bool     add(uint8_t x, uint8_t y, float value);
  float    get(uint8_t x, uint8_t y);

  //  BOUNDING BOX
  //  four sides between all values != 0 are located.
  //  returns false if zero elements, count == 0.
  bool     boundingBox(uint8_t &minX, uint8_t &maxX, uint8_t &minY, uint8_t &maxY);
  bool     boundingBoxX(uint8_t &minX, uint8_t &maxX);
  bool     boundingBoxY(uint8_t &minY, uint8_t &maxY);

  //  TRAVERSE
  bool     first(uint8_t &x, uint8_t &y, float &value);
  bool     next(uint8_t &x, uint8_t &y, float &value);
  bool     prev(uint8_t &x, uint8_t &y, float &value);
  bool     last(uint8_t &x, uint8_t &y, float &value);

  //  LOW LEVEL API
  //  returns index of x, y if in set
  //  otherwise -1
  int32_t  findPosition(uint8_t x, uint8_t y);
  float    getValue(uint16_t position);
  bool     setValue(uint16_t position, float value);
  uint16_t compact();


private:
  uint16_t _size   = 0;
  uint16_t _count  = 0;
  uint16_t _tindex = 0;  //  traverseIndex.

  uint8_t  *_x     = NULL;
  uint8_t  *_y     = NULL;
  float    *_value = NULL;

  //  removes element at position (from findPosition)
  //  pre: count > 0
  bool     removeElement(uint16_t position);
  //  creates a new element if value != 0 and if there is room
  bool     newElement(uint8_t x, uint8_t y, float value);
};


//  -- END OF FILE --

