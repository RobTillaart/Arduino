//
//  FILE: BoolArray.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.3
// PURPOSE: BoolArray library for Arduino
//   URL: https://github.com/RobTillaart/BoolArray.git
//      http://forum.arduino.cc/index.php?topic=361167


//  0.2.3  2021-01-19  update readme
//  0.2.2  2020-12-15  add arduino-CI + unit tests
//  0.2.1  2020-06-05  Fix library.json
//  0.2.0  2020-03-29  #pragma, readme.md,

//  0.1.4  2017-07-16  added masks for performance
//  0.1.3              added toggle
//  0.1.02             added errorhandling
//  0.1.01             fixed constructor - Thanks WPD64 + error handling
//  0.1.00             initial version
//


#include "BoolArray.h"


BoolArray::BoolArray()
{
  _ar = NULL;
  _size = 0;
}


BoolArray::~BoolArray()
{
  if (_ar) free(_ar);
}


uint8_t BoolArray::begin(const uint16_t size)
{
  if (size > BOOLARRAY_MAXSIZE) return BOOLARRAY_SIZE_ERROR;
  _size = size;
  if (_ar) free(_ar);
  _ar = (byte*) malloc((_size + 7) / 8);
  return BOOLARRAY_OK;
}


uint8_t BoolArray::get(const uint16_t index)
{
  if (_ar == NULL) return BOOLARRAY_INIT_ERROR;
  if (index >= _size) return BOOLARRAY_SIZE_ERROR;
  uint8_t by = index / 8;
  uint8_t bi = index & 7;
  return (_ar[by] & masks[bi]) > 0;
}


uint8_t BoolArray::set(const uint16_t index, const uint8_t value)
{
  if (_ar == NULL) return BOOLARRAY_INIT_ERROR;
  if (index >= _size) return BOOLARRAY_SIZE_ERROR;
  uint8_t by = index / 8;
  uint8_t bi = index & 7;
  if (value == 0) _ar[by] &= ~masks[bi];
  else _ar[by] |= masks[bi];
  return BOOLARRAY_OK;
}


uint8_t BoolArray::toggle(const uint16_t index)
{
  if (_ar == NULL) return BOOLARRAY_INIT_ERROR;
  if (index >= _size) return BOOLARRAY_SIZE_ERROR;
  uint8_t by = index / 8;
  uint8_t bi = index & 7;
  _ar[by] ^= masks[bi];
  return BOOLARRAY_OK;
}


// 32 bit is even faster, 
uint8_t BoolArray::setAll(const uint8_t value)
{
  if (_ar == NULL) return BOOLARRAY_INIT_ERROR;
  uint8_t *p = _ar;
  uint8_t t = (_size + 7) / 8;
  if (value == 0) 
  {
    while(t--) *p++ = 0;
  }
  else
  {
    while(t--) *p++ = 0xFF;  // set 16 bits at once  
  }  
  return BOOLARRAY_OK;
}


// -- END OF FILE --
