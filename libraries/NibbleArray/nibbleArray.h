#pragma once
//
//    FILE: nibbleArray.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: Arduino library for a compact array of nibbles (4 bits)
//     URL: https://github.com/RobTillaart/nibbleArray
//
// HISTORY:
// see nibbleArray.cpp
//

#include <Arduino.h>

#define NIBBLEARRAY_LIB_VERSION "0.2.0"

#ifndef NIBBLEARRAY_MAXSIZE
#define NIBBLEARRAY_MAXSIZE       510
#endif

#define NIBBLEARRAY_OK            0x00
#define NIBBLEARRAY_ERROR_INDEX   0xFF

class nibbleArray
{
public:
  nibbleArray(uint16_t size);
  ~nibbleArray();

  // return 0..F if ok
  // retuns 0xFF for index error.
  uint8_t   get(const uint16_t idx);
  // retuns 0xFF for index error.
  uint8_t   set(const uint16_t idx, uint8_t value);

  uint16_t  size() { return _size; };
  void      clear();
  void      setAll(uint8_t val);

private:
  uint8_t  *arr;
  uint16_t _size;
};

// -- END OF FILE --
