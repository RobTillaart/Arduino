//
//    FILE: BoolArray.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.01
// PURPOSE: BoolArray library for Arduino
//     URL: http://forum.arduino.cc/index.php?topic=361167

//
// Released to the public domain
//
// 0.1.01 - fixed constructor - Thanks WPD64 + error handling
// 0.1.00 - initial version
//

#include "BoolArray.h"

BoolArray::BoolArray()
{
    _ar = null;
    _size = 0;
}

BoolArray::~BoolArray()
{
    if (_ar) free(_ar);
}

uint8_t BoolArray::begin(const uint16_t size)
{
    if (size > BOOLARRAY_MAXSIZE) return 255;
    _size = size;
    if (_ar) free(_ar);
    _ar = (byte*) malloc((_size+7)/8);
    return 0;
}

uint8_t BoolArray::get(const uint16_t idx)
{
    if (_ar == null) return 255;
    uint8_t by = idx / 8;
    uint8_t bi = idx & 7;
    return (_ar[by] >> bi) & 0x01;
}

void BoolArray::set(const uint16_t idx, uint8_t value)
{
    if (_ar == null) return;
    uint8_t by = idx / 8;
    uint8_t bi = idx & 7;
    if (value == 0) _ar[by] &= ~(1 << bi);
    else _ar[by] |= (1 << bi);
}

void BoolArray::clear()
{
    if (_ar == null) return;
    for (int i = 0; i < (_size+7)/8; i++)
    {
        _ar[i] = 0;
    }
}

// END OF FILE
