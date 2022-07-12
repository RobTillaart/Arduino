//
//    FILE: SparseMatrix.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2022-07-12
// PURPOSE: Arduino library for sparse matrices
//
//  HISTORY:
//  0.1.0  2022-07-12  initial version


#include "SparseMatrix.h"


SparseMatrix::SparseMatrix(uint8_t sz)
{
  _count = 0;
  _size  = sz;
  _x     = (uint8_t *) malloc(sz);
  _y     = (uint8_t *) malloc(sz);
  _value = (float *)   malloc(sz * sizeof(float));
  //  catch malloc error
  if (_x && _y && _value) return;
  _size = 0;
}


SparseMatrix::~SparseMatrix()
{
  if (_x) free(_x);
  if (_y) free(_y);
  if (_value) free(_value);
}


uint8_t SparseMatrix::size()
{
  return _size;
}


uint8_t SparseMatrix::count()
{
  return _count;
}

float SparseMatrix::sum()
{
  float _sum = 0;
  for (int i = 0; i < _count; i++)
  {
    _sum += _value[i];
  }
  return _sum;
}


bool SparseMatrix::set(uint8_t x, uint8_t y, float value)
{
  int pos = findPos(x, y);
  //  existing element
  if (pos > -1)
  {
    if (value != 0.0)
    {
      _value[pos] = value;
    }
    else
    {
      _count--;
      //  move last element
      //  efficiency is not a requirement yet.
      _x[pos] = _x[_count];
      _y[pos] = _y[_count];
      _value[pos] = _value[_count];
    }
    return true;
  }

  //  new element
  if (_count >= _size) return false;
  _x[_count] = x;
  _y[_count] = y;
  _value[_count] = value;
  _count++;
  return true;
}


float SparseMatrix::get(uint8_t x, uint8_t y)
{
  int pos = findPos(x, y);
  if (pos > -1)
  {
    return _value[pos];
  }
  return 0;
}


int SparseMatrix::findPos(uint8_t x, uint8_t y)
{
  for (int i = 0; i < _count; i++)
  {
    if ((_x[i] == x) && (_y[i] == y))
    {
      return i;
    }
  }
  return -1;
}



// -- END OF FILE --
