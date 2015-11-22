#ifndef BitArray_H
#define BitArray_H
//
//    FILE: BitArray.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
// VERSION: 0.1.03
// PURPOSE: BitArray library for Arduino
// HISTORY: See BitArray.cpp
//
// Released to the public domain
//
// BitArray allows you to make a compact array of objects with a size
// expressed in bits. typically 1..10.
// The interface uses uint32_t as that will be enough for most purposes.
// The main requirement is to optimize storage space 
// the total space may not exceed 256 bytes.
//
// Originally created to store lot of numbers between 1..6 dice rolls
// the storage is also usable to store e.g. raw 10 bit analogReads
// see demo sketches.
//

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define BITARRAY_LIB_VERSION "0.1.03"

#define BA_SEGMENT_SIZE 200

#define BA_ERR          0xFFFFFFFF
#define BA_OK           0x00
#define BA_NO_MEMORY    0x01
#define BA_IDX_RANGE    0x02

class BitArray
{
public:
    BitArray() {};
    ~BitArray();

    byte begin(const byte bits, const uint16_t size);

    uint16_t capacity() { return _bytes * 8 / _bits; };
    uint16_t memory()   { return _bytes; };
    uint16_t bits()     { return _bits; };
    uint16_t segments() { return _segments; };
    byte getError()     { return _error; };
    void clear();

    uint32_t get(const uint16_t idx);
    uint32_t set(const uint16_t idx, uint32_t value);

private:
    byte _bitget(const uint16_t idx);
    void _bitset(const uint16_t idx, const byte value);

    uint16_t _size = 0;
    uint16_t _bytes = 0;
    uint16_t _bits = 0;
    uint16_t _segments = 0;
    byte * _ar[8];
    byte _error = BA_NO_MEMORY;
};

#endif
