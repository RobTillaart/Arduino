#ifndef BoolArray_H
#define BoolArray_H
//
//    FILE: BoolArray.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
// VERSION: 0.1.3
// PURPOSE: BoolArray library for Arduino
// HISTORY: See BoolArray.cpp
//
// Released to the public domain
//
// BoolArray implement a compact array of booleans of max size 2000.
// For larger arrays one need to modify the code, or use BitArray.
//

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define BOOLARRAY_LIB_VERSION   "0.1.3"
#define BOOLARRAY_MAXSIZE       (250*8)
#define BOOLARRAY_OK            0x00
#define BOOLARRAY_ERROR         0xFF
#define BOOLARRAY_SIZE_ERROR    0xFE
#define BOOLARRAY_INIT_ERROR    0xFD

class BoolArray
{
public:
    BoolArray();
    ~BoolArray();

    uint8_t begin(const uint16_t size);
    uint8_t clear();
    uint8_t setAll(const uint8_t value);
    uint8_t get(const uint16_t idx);
    uint8_t set(const uint16_t idx, const uint8_t value);
    uint8_t toggle(const uint16_t idx);

private:
    uint8_t * _ar;
    uint16_t _size;
};

#endif
