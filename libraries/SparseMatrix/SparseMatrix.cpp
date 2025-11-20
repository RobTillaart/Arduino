//
//    FILE: SparseMatrix.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2022-07-12
// PURPOSE: Arduino library for sparse matrices
//     URL: https://github.com/RobTillaart/SparseMatrix


#include "SparseMatrix.h"


SparseMatrix::SparseMatrix(uint16_t size)
{
  _count = 0;
  _size  = size;
  if ( _size > SPARSEMATRIX_MAX_SIZE)
  {
    _size = SPARSEMATRIX_MAX_SIZE;
  }
  _x     = (uint8_t *) malloc(size);
  _y     = (uint8_t *) malloc(size);
  _value = (float *)   malloc(size * sizeof(float));
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
  int32_t position = findPosition(x, y);
  //  existing element
  if (position > -1)
  {
    _value[position] = value;
    if (_value[position] == 0.0) removeElement(position);
    return true;
  }

  //  does not exist => new element ?
  return newElement(x, y, value);
}


bool SparseMatrix::add(uint8_t x, uint8_t y, float value)
{
  int32_t position = findPosition(x, y);
  //  existing element
  if (position > -1)
  {
    _value[position] += value;
    if (_value[position] == 0.0) removeElement(position);
    return true;
  }

  //  does not exist => new element ?
  return newElement(x, y, value);
}


float SparseMatrix::get(uint8_t x, uint8_t y)
{
  int32_t position = findPosition(x, y);
  if (position > -1)
  {
    return _value[position];
  }
  return 0;
}


bool SparseMatrix::boundingBox(uint8_t &minX, uint8_t &maxX, uint8_t &minY, uint8_t &maxY)
{
  if (_count == 0) return false;
  uint8_t _minx = 255, _maxx = 0,
          _miny = 255, _maxy = 0;
  for (uint16_t i = 0; i < _count; i++)
  {
    if (_x[i] < _minx) _minx = _x[i];
    if (_x[i] > _maxx) _maxx = _x[i];
    if (_y[i] < _miny) _miny = _y[i];
    if (_y[i] > _maxy) _maxy = _y[i];
  }
  minX = _minx;
  maxX = _maxx;
  minY = _miny;
  maxY = _maxy;
  return true;
}


bool SparseMatrix::boundingBoxX(uint8_t &minX, uint8_t &maxX)
{
  if (_count == 0) return false;
  uint8_t _minx = 255, _maxx = 0;
  for (uint16_t i = 0; i < _count; i++)
  {
    if (_x[i] < _minx) _minx = _x[i];
    if (_x[i] > _maxx) _maxx = _x[i];
  }
  minX = _minx;
  maxX = _maxx;
  return true;
}


bool SparseMatrix::boundingBoxY(uint8_t &minY, uint8_t &maxY)
{
  if (_count == 0) return false;
  uint8_t _miny = 255, _maxy = 0;
  for (uint16_t i = 0; i < _count; i++)
  {
    if (_y[i] < _miny) _miny = _y[i];
    if (_y[i] > _maxy) _maxy = _y[i];
  }
  minY = _miny;
  maxY = _maxy;
  return true;
}


bool SparseMatrix::first(uint8_t &x, uint8_t &y, float &value)
{
  if (_count == 0) return false;
  _tindex = 0;
  x = _x[_tindex];
  y = _y[_tindex];
  value = _value[_tindex];
  return true;
}

bool SparseMatrix::next(uint8_t &x, uint8_t &y, float &value)
{
  if (_count == 0) return false;
  if (_tindex >= _count - 1) return false;
  _tindex++;
  x = _x[_tindex];
  y = _y[_tindex];
  value = _value[_tindex];
  return true;
}

bool SparseMatrix::prev(uint8_t &x, uint8_t &y, float &value)
{
  if (_count == 0)  return false;
  if (_tindex == 0) return false;
  _tindex--;
  x = _x[_tindex];
  y = _y[_tindex];
  value = _value[_tindex];
  return true;
}

bool SparseMatrix::last(uint8_t &x, uint8_t &y, float &value)
{
  if (_count == 0) return false;
  _tindex = _count - 1;
  x = _x[_tindex];
  y = _y[_tindex];
  value = _value[_tindex];
  return true;
}


//////////////////////////////////////////////////////
//
//  LOW LEVEL API
//
int32_t SparseMatrix::findPosition(uint8_t x, uint8_t y)
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


float SparseMatrix::getValue(uint16_t position)
{
  if (position >= _count) return NAN;
  return _value[position];
}


bool SparseMatrix::setValue(uint16_t position, float value)
{
  if (position >= _count) return false;
  _value[position] = value;
  return true;
}


uint16_t SparseMatrix::compact()
{
  for (int position = _count - 1; position >= 0; position--)
  {
    if (_value[position] == 0.0) removeElement(position);
  }
  return _count;
}


//////////////////////////////////////////////////////
//
//  PRIVATE
//

bool SparseMatrix::removeElement(uint16_t position)
{
  if (position >= _count) return false;

  _count--;
  //  move last element
  //  efficiency (keep sorted) is no requirement.
  if (position == _count) return true;
  _x[position]     = _x[_count];
  _y[position]     = _y[_count];
  _value[position] = _value[_count];
  return true;
}


bool SparseMatrix::newElement(uint8_t x, uint8_t y, float value)
{
  if (value == 0.0) return true;
  if (_count >= _size) return false;
  _x[_count]     = x;
  _y[_count]     = y;
  _value[_count] = value;
  _count++;
  return true;
}


//  -- END OF FILE --

