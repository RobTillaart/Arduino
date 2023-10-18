#pragma once
//
//    FILE: BoolArray.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.8
//    DATE: 2015-12-06
// PURPOSE: BoolArray library for Arduino
//     URL: https://github.com/RobTillaart/BoolArray.git

//  BoolArray implement a compact array of booleans of max size 2000.
//  For larger arrays one need to modify the code, or use BitArray.
//  Tested on AVR only


#include "Arduino.h"


#define BOOLARRAY_LIB_VERSION     (F("0.2.8"))

#define BOOLARRAY_MAXSIZE         (250 * 8)       // 2000

#define BOOLARRAY_OK              0x00
#define BOOLARRAY_ERROR           0xFF
#define BOOLARRAY_SIZE_ERROR      0xFE
#define BOOLARRAY_INIT_ERROR      0xFD


class BoolArray
{
public:
  BoolArray();
  ~BoolArray();

  uint8_t  begin(const uint16_t size);

  uint16_t size();
  uint8_t  memory();

  uint8_t  setAll(const uint8_t value);
  uint8_t  clear();
  uint8_t  get(const uint16_t index);
  uint8_t  set(const uint16_t index, const uint8_t value);
  uint8_t  toggle(const uint16_t index);

private:
  uint8_t   _masks[8] = {1, 2, 4, 8, 16, 32, 64, 128};
  uint8_t * _array;
  uint16_t  _size  = 0;
  uint8_t   _bytes = 0;
};


//  -- END OF FILE --

