#pragma once
//
//    FILE: nibbleArray.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.6
// PURPOSE: Arduino library for a compact array of nibbles (4 bits)
//     URL: https://github.com/RobTillaart/nibbleArray


#include "Arduino.h"


#define NIBBLEARRAY_LIB_VERSION         (F("0.2.6"))


#ifndef NIBBLEARRAY_MAXSIZE
// UNO BASED MAXSIZE?
#define NIBBLEARRAY_MAXSIZE             510
#endif

#define NIBBLEARRAY_OK                  0x00
#define NIBBLEARRAY_ERROR_INDEX         0xFF


class nibbleArray
{
public:
  nibbleArray(const uint16_t size);
  ~nibbleArray();

  //  return 0..F if ok
  //  returns 0xFF for index error.
  uint8_t   get(const uint16_t index);
  //  returns 0xFF for index error.
  uint8_t   set(const uint16_t index, uint8_t value);

  uint16_t  size();
  uint16_t  memory();

  void      clear();
  void      setAll(uint8_t value);

private:
  uint8_t  * _arr;
  uint16_t _size;
  uint8_t  _bytes = 0;
};


//  -- END OF FILE --

