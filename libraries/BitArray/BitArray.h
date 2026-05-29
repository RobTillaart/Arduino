#pragma once
//
//    FILE: bitArray.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
// PURPOSE: BitArray library for Arduino
//     URL: https://github.com/RobTillaart/BitArray

//  BitArray allows you to make a compact array of objects with a size
//  expressed in bits. typically 1..10.
//  The interface uses uint32_t as that will be enough for most purposes.
//  The main requirement is to optimize storage space.
//
//  The BitArray uses an array of segments and the space per segment
//  may not exceed 256 bytes as this is a limit on some processors.
//
//  Originally created to store lot of numbers between 1..6 dice rolls
//  the storage is also usable to store e.g. raw 10 bit analogRead()'s.


#include "Arduino.h"

#define BITARRAY_LIB_VERSION              (F("0.3.0"))

//  adjust BITARRAY_MAXSIZE to your needs and board used.
//  BITARRAY_MAXSIZE is in bytes...
#ifndef BITARRAY_MAXSIZE
#define BITARRAY_MAXSIZE         1250
#endif


//  ERROR CODES
constexpr int BA_ERR              = -1;
constexpr int BA_OK               = 0;
constexpr int BA_NO_MEMORY_ERR    = 1;
constexpr int BA_IDX_RANGE_ERR    = 2;
constexpr int BA_ELEMENT_SIZE_ERR = 3;
constexpr int BA_SIZE_ERR         = 4;


/////////////////////////////////////////////////////////
//
//  16 bit version
//  max memory that can be allocated is 64 KB.
//
class BitArray
{
public:
  BitArray();
  ~BitArray();

  int      begin(const uint8_t elementSize, const uint16_t elementCount);

  uint16_t capacity()    { return _bytes * 8 / _bits; };
  uint16_t memory()      { return _bytes; };
  uint8_t  elementSize() { return _bits; };
  int      getError()    { return _error; };

  int      clear();
  uint16_t get(const uint16_t index);
  uint16_t set(const uint16_t index, uint16_t value);
  int      setAll(uint16_t value);
  uint16_t toggle(const uint16_t index);

private:
  uint8_t   _bitget(const uint32_t pos);
  void      _bitset(const uint32_t pos, const uint8_t value);
  uint8_t   _bittoggle(const uint32_t pos);

  uint8_t * _array;
  uint16_t  _size = 0;
  uint16_t  _bytes = 0;
  uint8_t   _bits = 0;
  uint8_t   _error = BA_OK;
};


/////////////////////////////////////////////////////////
//
//  32 bit version
//
class BitArray32
{
public:
  BitArray32();
  ~BitArray32();

  int      begin(const uint8_t elementSize, const uint32_t elementCount);

  uint32_t capacity()    { return _bytes * 8 / _bits; };
  uint32_t memory()      { return _bytes; };
  uint8_t  elementSize() { return _bits; };
  int      getError()    { return _error; };

  int      clear();
  uint32_t get(const uint32_t index);
  uint32_t set(const uint32_t index, uint32_t value);
  int      setAll(uint32_t value);
  uint32_t toggle(const uint32_t index);

private:
  uint8_t   _bitget(const uint32_t pos);
  void      _bitset(const uint32_t pos, const uint8_t value);
  uint8_t   _bittoggle(const uint32_t pos);

  uint8_t * _array;
  uint32_t  _size = 0;
  uint32_t  _bytes = 0;
  uint8_t   _bits = 0;
  uint8_t   _error = BA_OK;
};


//  -- END OF FILE --

