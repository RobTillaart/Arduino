#pragma once
//
//    FILE: SparseMatrix.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2022-07-12
// PURPOSE: Arduino library for sparse matrices
//


#include "Arduino.h"

#define SPARSEMATRIX_LIB_VERSION        (F("0.1.0"))


class SparseMatrix
{
public:
  SparseMatrix(uint8_t sz);
  ~SparseMatrix();

  uint8_t  size();
  uint8_t  count();
  float    sum();

  //  returns false if no slots free
  //  could return # free slots?
  bool     set(uint8_t x, uint8_t y, float value);
  float    get(uint8_t x, uint8_t y);


private:
  int       _size   = 0;
  int       _count  = 0;

  uint8_t   *_x     = NULL;
  uint8_t   *_y     = NULL;
  float     *_value = NULL;

  //  returns index of x,y if in set
  //  otherwise -1
  int findPos(uint8_t x, uint8_t y);
};


// -- END OF FILE --

