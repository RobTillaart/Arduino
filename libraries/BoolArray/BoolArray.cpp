//
//    FILE: BoolArray.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
// PURPOSE: BoolArray library for Arduino
//     URL: http://forum.arduino.cc/index.php?topic=361167

//
// Released to the public domain
//
// 0.1.3  - added toggle
// 0.1.02 - added errorhandling
// 0.1.01 - fixed constructor - Thanks WPD64 + error handling
// 0.1.00 - initial version
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

uint8_t BoolArray::get(const uint16_t idx)
{
    if (_ar == NULL) return BOOLARRAY_INIT_ERROR;
    if (idx >= _size) return BOOLARRAY_SIZE_ERROR;
    uint8_t by = idx / 8;
    uint8_t bi = idx & 7;
    uint8_t mask = 1 << bi;
    return (_ar[by] & mask) > 0;
}

uint8_t BoolArray::set(const uint16_t idx, const uint8_t value)
{
    if (_ar == NULL) return BOOLARRAY_INIT_ERROR;
    if (idx >= _size) return BOOLARRAY_SIZE_ERROR;
    uint8_t by = idx / 8;
    uint8_t bi = idx & 7;
    uint8_t mask = 1 << bi;
    if (value == 0) _ar[by] &= ~mask;
    else _ar[by] |= mask;
    return BOOLARRAY_OK;
}

uint8_t BoolArray::toggle(const uint16_t idx)
{
    if (_ar == NULL) return BOOLARRAY_INIT_ERROR;
    if (idx >= _size) return BOOLARRAY_SIZE_ERROR;
    uint8_t by = idx / 8;
    uint8_t bi = idx & 7;
    uint8_t mask = 1 << bi;
    _ar[by] ^= mask;
    return BOOLARRAY_OK;
}

uint8_t BoolArray::clear()
{
    return setAll(0);
}

uint8_t BoolArray::setAll(const uint8_t value)
{
    if (_ar == NULL) return BOOLARRAY_INIT_ERROR;
    uint8_t *p = _ar;
    uint8_t t = (_size + 7) / 8;
    uint8_t v = value?255:0;
    while(t--)
    {
        *p++ = v;
    }
    return BOOLARRAY_OK;
}

// END OF FILE
