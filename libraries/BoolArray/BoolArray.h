#ifndef BoolArray_H
#define BoolArray_H
//
//    FILE: BoolArray.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
// VERSION: 0.1.00
// PURPOSE: BoolArray library for Arduino
// HISTORY: See BoolArray.cpp
//
// Released to the public domain
//
// BoolArray implement a comapct array of booleans of max size 2000
//

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define BOOLARRAY_LIB_VERSION   "0.1.01"
#define BOOLARRAY_MAXSIZE       (250*8)

class BoolArray
{
public:
    BoolArray();
    ~BoolArray();

    uint8_t begin(const uint16_t size);
    void clear();
    uint8_t get(const uint16_t idx);
    void set(const uint16_t idx, uint8_t value);

private:
    byte * _ar;
    uint16_t _size;
};

#endif
