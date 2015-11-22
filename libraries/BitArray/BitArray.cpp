//
//    FILE: BitArray.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.03
// PURPOSE: BitArray library for Arduino
//     URL: 

//
// Released to the public domain
//
// 0.1.03 - refactoring
// 0.1.02 - first stabile version (at last)
// 0.1.01 - added clear() + fixed set bug
// 0.1.00 - initial version
//
// todo
// - performance optimizations.
// - max value (#bits != maxValue) ??

#include "BitArray.h"

BitArray::~BitArray()
{
    for (byte i = 0; i < 8; i++)
    {
        if (_ar[i]) free(_ar[i]);
    }
}

byte BitArray::begin(const byte bits, const uint16_t size)
{
    for (byte i = 0; i < 8; i++)
    {
        if (_ar[i]) free(_ar[i]);
    }
    _bits = bits;
    _size = size;
    _bytes = (_bits * _size + 7) / 8;
    if (_bytes > 1600)
    {
        _error = BA_NO_MEMORY;
        return _error;
    }
    uint16_t b = _bytes;
    _segments = 0;
    while (b > 0)
    {
        _ar[_segments] = (byte*) malloc(min(b, BA_SEGMENT_SIZE));
        if (_ar[_segments] == NULL) 
        {
            _error = BA_NO_MEMORY;
            return _error;
        }
        b = b - min(b, BA_SEGMENT_SIZE);
        _segments++;
    }
    _error = BA_OK;
    return _error;
}

uint32_t BitArray::get(const uint16_t idx)
{
    // if (_error != BA_OK) return BA_ERR;
    // if (idx >= _size) return BA_IDX_RANGE;
    uint32_t v = 0;
    uint16_t pos = idx * _bits;
    for (byte i = _bits; i-- > 0;)
    {
        v <<= 1;
        v += _bitget(pos + i);
    }
    return v;
}

uint32_t BitArray::set(const uint16_t idx, uint32_t value)
{
    // if (_error != BA_OK) return BA_ERR;
    // if (idx >= _size) return BA_IDX_RANGE;
    uint16_t pos = idx * _bits;
    uint32_t mask = 1UL;
    for (byte i = 0; i < _bits; i++)
    {
        byte v = (value & mask) > 0 ? 1 : 0;
        _bitset(pos + i, v);
        mask <<= 1;
    }
    return value;
}

void BitArray::clear()
{
    uint16_t b = _bytes;

    for (byte s = 0; s < _segments; s++)
    {
        byte *p = _ar[s];
        if (p)
        {
            for (int i = 0; i < min(b, BA_SEGMENT_SIZE); i++) 
            { 
                p[i] = 0;
            }
            b -= min(b, BA_SEGMENT_SIZE);
        }
        if (b == 0) break; 
    }
}  

// PRIVATE
byte BitArray::_bitget(uint16_t pos)
{
    uint16_t se = pos / (BA_SEGMENT_SIZE * 8);
    uint16_t re = pos - se * (BA_SEGMENT_SIZE * 8);
    uint16_t by = re / 8;
    uint16_t bi = re & 7;
    byte * p = _ar[se];
    return bitRead(p[by], bi);
}

void BitArray::_bitset(uint16_t pos, byte value)
{
    uint16_t se = pos / (BA_SEGMENT_SIZE * 8);
    uint16_t re = pos - se * (BA_SEGMENT_SIZE * 8);
    uint16_t by = re / 8;
    uint16_t bi = re & 7;
    byte * p = _ar[se];
    if (value == 0) bitClear(p[by], bi);
    else bitSet(p[by], bi);
}
