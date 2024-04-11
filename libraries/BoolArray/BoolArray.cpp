//
//  FILE: BoolArray.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
//    DATE: 2015-12-06
// PURPOSE: BoolArray library for Arduino
//     URL: https://github.com/RobTillaart/BoolArray
//          http://forum.arduino.cc/index.php?topic=361167


#include "BoolArray.h"


/////////////////////////////////////////////////////////
//
//  16 bit version
//
BoolArray::BoolArray()
{
  _array = NULL;
  _size = 0;
}


BoolArray::~BoolArray()
{
  if (_array) free(_array);
}


uint8_t BoolArray::begin(const uint16_t size)
{
  //  is this test needed....
  if (size > BOOLARRAY_MAXSIZE)
  {
    return BOOLARRAY_SIZE_ERROR;
  }
  // do we need to re-allocate?
  if (_size != size)
  {
    _size  = size;
    _bytes = (_size + 7) / 8;
    if (_array) 
    {
      free(_array);
    }
    _array = (uint8_t *) malloc(_bytes);
    if (_array == NULL)
    {
      _size = 0;
      _bytes = 0;
      return BOOLARRAY_INIT_ERROR;
    }
  }
  return BOOLARRAY_OK;
}


uint16_t BoolArray::size()
{
  return _size;
}


uint16_t BoolArray::memory()
{
  return _bytes;
}


uint8_t BoolArray::setAll(const uint8_t value)
{
  if (_array == NULL) return BOOLARRAY_INIT_ERROR;
  uint8_t *p = _array;
  uint8_t t = _bytes;
  if (value == 0) 
  {
    while(t--) *p++ = 0;
  }
  else
  {
    while(t--) *p++ = 0xFF;
  }
  return BOOLARRAY_OK;
}


uint8_t BoolArray::clear()
{
  return setAll(0);
}


uint8_t BoolArray::get(const uint16_t index)
{
  if (_array == NULL) return BOOLARRAY_INIT_ERROR;
  if (index >= _size) return BOOLARRAY_SIZE_ERROR;
  uint8_t by = index / 8;
  uint8_t bi = index & 7;
  return (_array[by] & _masks[bi]) > 0;
}


uint8_t BoolArray::set(const uint16_t index, const uint8_t value)
{
  if (_array == NULL) return BOOLARRAY_INIT_ERROR;
  if (index >= _size) return BOOLARRAY_SIZE_ERROR;
  uint8_t by = index / 8;
  uint8_t bi = index & 7;
  if (value == 0) _array[by] &= ~_masks[bi];
  else _array[by] |= _masks[bi];
  return BOOLARRAY_OK;
}


uint8_t BoolArray::toggle(const uint16_t index)
{
  if (_array == NULL) return BOOLARRAY_INIT_ERROR;
  if (index >= _size) return BOOLARRAY_SIZE_ERROR;
  uint8_t by = index / 8;
  uint8_t bi = index & 7;
  _array[by] ^= _masks[bi];
  return BOOLARRAY_OK;
}



/////////////////////////////////////////////////////////
//
//  32 bit version for large bool arrays
//
BoolArray32::BoolArray32()
{
  _array = NULL;
  _size = 0;
}


BoolArray32::~BoolArray32()
{
  if (_array) free(_array);
}


uint8_t BoolArray32::begin(const uint32_t size)
{
  if (size > BOOLARRAY_MAXSIZE)
  {
    return BOOLARRAY_SIZE_ERROR;
  }
  //  do we need to re-allocate?
  if (_size != size)
  {
    _size  = size;
    _bytes = (_size + 7) / 8;
    if (_array)
    {
      free(_array);
    }
    _array = (uint8_t *) malloc(_bytes);
    if (_array == NULL)
    {
      _size = 0;
      _bytes = 0;
      return BOOLARRAY_INIT_ERROR;
    }
  }
  return BOOLARRAY_OK;
}


uint32_t BoolArray32::size()
{
  return _size;
}


uint32_t BoolArray32::memory()
{
  return _bytes;
}


uint8_t BoolArray32::setAll(const uint8_t value)
{
  if (_array == NULL)
  {
    return BOOLARRAY_INIT_ERROR;
  }
  uint8_t *p = _array;
  uint32_t t = _bytes;
  if (value == 0)
  {
    while (t--) *p++ = 0;
  }
  else
  {
    while (t--) *p++ = 0xFF;
  }
  return BOOLARRAY_OK;
}


uint8_t BoolArray32::clear()
{
  return setAll(0);
}


uint8_t BoolArray32::get(const uint32_t index)
{
  if (_array == NULL)
  {
    return BOOLARRAY_INIT_ERROR;
  }
  if (index >= _size)
  {
    return BOOLARRAY_SIZE_ERROR;
  }
  uint32_t by = index / 8;
  uint8_t bi = index & 7;
  return (_array[by] & _masks[bi]) > 0;
}


uint8_t BoolArray32::set(const uint32_t index, const uint8_t value)
{
  if (_array == NULL)
  {
    return BOOLARRAY_INIT_ERROR;
  }
  if (index >= _size)
  {
    return BOOLARRAY_SIZE_ERROR;
  }
  uint32_t by = index / 8;
  uint8_t bi = index & 7;
  if (value == 0) _array[by] &= ~_masks[bi];
  else _array[by] |= _masks[bi];
  return BOOLARRAY_OK;
}


uint8_t BoolArray32::toggle(const uint32_t index)
{
  if (_array == NULL)
  {
    return BOOLARRAY_INIT_ERROR;
  }
  if (index >= _size)
  {
    return BOOLARRAY_SIZE_ERROR;
  }
  uint32_t by = index / 8;
  uint8_t bi = index & 7;
  _array[by] ^= _masks[bi];
  return BOOLARRAY_OK;
}



//  -- END OF FILE --

