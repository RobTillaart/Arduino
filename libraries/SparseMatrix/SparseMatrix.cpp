//
//    FILE: SparseMatrix.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
//    DATE: 2022-07-12
// PURPOSE: Arduino library for sparse matrices
//     URL: https://github.com/RobTillaart/SparseMatrix
//
//  HISTORY:
//  0.1.0  2022-07-12  initial version
//  0.1.1  2022-07-13  add clear();
//                     add add(x, y, value);
//                     fix set(x, y, 0);
//  0.1.2  2022-07-14  increase size to uint16_t
//                     add SPARSEMATRIX_MAX_SIZE
//                     improve documentation


#include "SparseMatrix.h"


SparseMatrix::SparseMatrix(uint16_t sz)
{
  _count = 0;
  _size  = sz;
  if ( _size > SPARSEMATRIX_MAX_SIZE)
  {
    _size = SPARSEMATRIX_MAX_SIZE;
  }
  _x     = (uint8_t *) malloc(sz);
  _y     = (uint8_t *) malloc(sz);
  _value = (float *)   malloc(sz * sizeof(float));
  //  catch malloc error
  if (_x && _y && _value) return;
  //  if malloc error set size to zero.
  _size = 0;
}


SparseMatrix::~SparseMatrix()
{
  if (_x) free(_x);
  if (_y) free(_y);
  if (_value) free(_value);
}


uint16_t SparseMatrix::size()
{
  return _size;
}


uint16_t SparseMatrix::count()
{
  return _count;
}


void SparseMatrix::clear()
{
  _count = 0;
}


float SparseMatrix::sum()
{
  float _sum = 0;
  for (uint16_t i = 0; i < _count; i++)
  {
    _sum += _value[i];
  }
  return _sum;
}


bool SparseMatrix::set(uint8_t x, uint8_t y, float value)
{
  int32_t pos = findPos(x, y);
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
      if (_count > 0)
      {
        _x[pos]     = _x[_count];
        _y[pos]     = _y[_count];
        _value[pos] = _value[_count];
      }
    }
    return true;
  }

  //  does not exist => new element ?
  if (value == 0) return true;
  if (_count >= _size) return false;
  _x[_count]     = x;
  _y[_count]     = y;
  _value[_count] = value;
  _count++;
  return true;
}


bool SparseMatrix::add(uint8_t x, uint8_t y, float value)
{
  int32_t pos = findPos(x, y);
  //  existing element
  if (pos > -1)
  {
    _value[pos] += value;
    if (_value[pos] == 0.0)
    {
      _count--;
      //  move last element
      //  efficiency is not a requirement yet.
      if (_count > 0)
      {
        _x[pos]     = _x[_count];
        _y[pos]     = _y[_count];
        _value[pos] = _value[_count];
      }
    }
    return true;
  }

  //  does not exist => new element ?
  if (value == 0) return true;
  if (_count >= _size) return false;
  _x[_count]     = x;
  _y[_count]     = y;
  _value[_count] = value;
  _count++;
  return true;
}


float SparseMatrix::get(uint8_t x, uint8_t y)
{
  int32_t pos = findPos(x, y);
  if (pos > -1)
  {
    return _value[pos];
  }
  return 0;
}


//////////////////////////////////////////////////////
//
//  PRIVATE
//
int32_t SparseMatrix::findPos(uint8_t x, uint8_t y)
{
  //  linear search - not optimized.
  for (uint16_t i = 0; i < _count; i++)
  {
    if ((_x[i] == x) && (_y[i] == y))
    {
      return (int32_t)i;
    }
  }
  return -1;
}



// -- END OF FILE --

