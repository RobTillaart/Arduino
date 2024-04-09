#pragma once
//
//    FILE: bitArray.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.8
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

#define BITARRAY_LIB_VERSION              (F("0.2.8"))


#define BA_SEGMENT_SIZE                   200


//  max memory is board type dependent
//  note the bitArray does not use all of the RAM
//  1K - max 600
#if defined(__AVR_ATmega168__)
#define BA_MAX_SEGMENTS 3
//  2K - max 1600
#elif defined(__AVR_ATmega328P__)
#define BA_MAX_SEGMENTS 8
//  8K - max 7000
#elif defined(__AVR_ATmega1280__)
#define BA_MAX_SEGMENTS 35
//  8K - max 7000
#elif defined(__AVR_ATmega2560__)
#define BA_MAX_SEGMENTS 35
//  1.25K - max 800
#elif defined(__AVR_ATmega16U4__)
#define BA_MAX_SEGMENTS 4
//  2.5K - max 2000
#elif defined(__AVR_ATmega32U4__)
#define BA_MAX_SEGMENTS 10
//  96K (64 + 32) DUE...
#elif defined(__SAM3X8E__)
#define BA_MAX_SEGMENTS 100
//  default max 1000
#else
#define BA_MAX_SEGMENTS 5
#endif


#define BA_ERR                            0xFFFFFFFF
#define BA_OK                             0x00
#define BA_NO_MEMORY_ERR                  0x01
#define BA_IDX_RANGE_ERR                  0x02
#define BA_ELEMENT_SIZE_ERR               0x03
#define BA_SIZE_ERR                       0x04


class BitArray
{
public:
  BitArray();
  ~BitArray();

  uint8_t  begin(const uint8_t bits, const uint16_t size);

  uint16_t capacity() { return _bytes * 8 / _bits; };
  uint16_t memory()   { return _bytes; };
  uint16_t bits()     { return _bits; };
  uint16_t segments() { return _segments; };
  uint8_t  getError() { return _error; };

  void     clear();
  uint32_t get(const uint16_t index);
  uint32_t set(const uint16_t index, uint32_t value);
  void     setAll(uint32_t value);
  uint32_t toggle(const uint16_t index);

private:
  uint8_t   _bitget(const uint16_t index);
  void      _bitset(const uint16_t index, const uint8_t value);
  uint8_t   _bittoggle(const uint16_t index);

  uint16_t  _bytes = 0;
  uint8_t   _bits = 0;
  uint8_t   _segments = 0;
  uint8_t * _ar[BA_MAX_SEGMENTS];
  uint8_t   _error = BA_NO_MEMORY_ERR;
};


//  -- END OF FILE --

