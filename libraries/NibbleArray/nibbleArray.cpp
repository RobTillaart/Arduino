//
//    FILE: nibbleArray.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: compact storage for array of nibbles
//     URL:
//
// HISTORY:
// 0.1.00 by Rob Tillaart (12/APR/2015)
//
// Released to the public domain
//

#include "nibbleArray.h"

/////////////////////////////////////////////////////
//
// PUBLIC
//
nibbleArray::nibbleArray(uint16_t size)
{
    arr = (uint16_t *) malloc((size+1)/2);
}

nibbleArray::~nibbleArray()
{
    if (arr != NULL) free(arr);
}

uint8_t nibbleArray::get(const uint16_t idx)
{
    if (idx > _size) return 255; // magic error nr
    if (idx & 1) return arr[idx/2] & 0x0F;
    return arr[idx/2] >> 4;
}

uint8_t nibbleArray::set(const uint16_t idx, uint8_t value)
{
    if (idx > _size) return 255; // magic error nr.
    uint8_t v = value & 0x0F;
    if (idx & 1) arr[idx/2] = (arr[idx/2] & 0xF0) | v;
    else arr[idx/2] = (arr[idx/2] & 0x0F) | (v << 4);
}

//
// END OF FILE
//