//
//    FILE: nibbleArray.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.6
// PURPOSE: Arduino library for a compact array of nibbles (4 bits)
//     URL: https://github.com/RobTillaart/nibbleArray


#include "nibbleArray.h"


nibbleArray::nibbleArray(const uint16_t size)
{
  _size = size;
  if (_size > (uint16_t) NIBBLEARRAY_MAXSIZE)
  {
    _size = (uint16_t) NIBBLEARRAY_MAXSIZE;
  }
  _bytes = (_size + 1)/2;
  _arr = (uint8_t *) malloc(_bytes);
}


nibbleArray::~nibbleArray()
{
  if (_arr != NULL)
  {
    free(_arr);
  }
}


uint8_t nibbleArray::get(const uint16_t index)
{
  //  disable this check for more speed
  if (index > _size)
  {
    return NIBBLEARRAY_ERROR_INDEX;
  }
  if (index & 1) return _arr[index/2] & 0x0F;
  return _arr[index/2] >> 4;
}


uint8_t nibbleArray::set(const uint16_t index, uint8_t value)
{
  //  disable this check for more speed
  if (index > _size)
  {
    return NIBBLEARRAY_ERROR_INDEX;
  }
  uint8_t v = value & 0x0F;
  if (index & 1) _arr[index/2] = (_arr[index/2] & 0xF0) | v;
  else _arr[index/2] = (_arr[index/2] & 0x0F) | (v << 4);
  return NIBBLEARRAY_OK;
}


uint16_t nibbleArray::size()
{
  return _size;
};


uint16_t nibbleArray::memory()
{
  return _bytes;
};


void nibbleArray::clear()
{
  memset(_arr, 0, (_size + 1)/2);
}


void nibbleArray::setAll(uint8_t value)
{
  uint8_t v = value & 0x0F;
  v |= (v << 4);
  memset(_arr, v, (_size + 1)/2);
}


//  -- END OF FILE --

