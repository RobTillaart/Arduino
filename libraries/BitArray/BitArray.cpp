//
//    FILE: BitArray.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.07
// PURPOSE: BitArray library for Arduino
//     URL: http://forum.arduino.cc/index.php?topic=361167

//
// Released to the public domain
//
// 0.1.07 - private calls inline -> performance & footprint
// 0.1.06 - refactored
// 0.1.05 - added upper limits
// 0.1.04 - improve performance
// 0.1.03 - refactoring
// 0.1.02 - first stabile version (at last)
// 0.1.01 - added clear() + fixed set bug
// 0.1.00 - initial version
//

#include "BitArray.h"

BitArray::~BitArray()
{
    for (uint8_t i = 0; i < BA_MAX_SEGMENTS; i++)
    {
        if (_ar[i]) free(_ar[i]);
    }
}

uint8_t BitArray::begin(const uint8_t bits, const uint16_t size)
{
    if (bits == 0 || bits > 32)
    {
        _error = BA_ELEMENT_SIZE_ERR;
        return _error;
    }
    if ((1UL * bits * size)/8 > (1UL * BA_MAX_SEGMENTS * BA_SEGMENT_SIZE))
    {
        _error = BA_SIZE_ERR;
        return _error;
    }

    for (uint8_t i = 0; i < BA_MAX_SEGMENTS; i++)
    {
        if (_ar[i]) free(_ar[i]);
    }

    _segments = 0;
    _bits = bits;
    _bytes = (_bits * size + 7) / 8;
    uint16_t b = _bytes;
    while (b > 0)
    {
        _ar[_segments] = (uint8_t*) malloc(min(b, BA_SEGMENT_SIZE));
        if (_ar[_segments] == NULL)
        {
            _error = BA_NO_MEMORY_ERR;
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
    for (uint8_t i = _bits; i-- > 0;)
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
    for (uint8_t i = 0; i < _bits; i++)
    {
        uint8_t v = (value & mask) > 0 ? 1 : 0;
        _bitset(pos + i, v);
        mask <<= 1;
    }
    return value;
}

void BitArray::clear()
{
    uint16_t b = _bytes;
    for (uint8_t s = 0; s < _segments; s++)
    {
        uint8_t *p = _ar[s];
        if (p)
        {
            uint8_t t = min(b, BA_SEGMENT_SIZE);
            b -= t;
            while(t--)
            {
                *p++ = 0;
            }
        }
        if (b == 0) break;
    }
}

// PRIVATE
inline uint8_t BitArray::_bitget(uint16_t pos)
{
    uint8_t se = 0;
    uint16_t re = pos;
    while (re >= (BA_SEGMENT_SIZE * 8))  // 8 == #bits in uint8_t
    {
        se++;
        re -= (BA_SEGMENT_SIZE * 8);
    }
    uint8_t by = re / 8;
    uint8_t bi = re & 7;
    uint8_t * p = _ar[se];
    return (p[by] >> bi) & 0x01; // bitRead(p[by], bi);
}

inline void BitArray::_bitset(uint16_t pos, uint8_t value)
{
    uint8_t se = 0;
    uint16_t re = pos;
    while (re >= (BA_SEGMENT_SIZE * 8))
    {
        se++;
        re -= (BA_SEGMENT_SIZE * 8);
    }
    uint8_t by = re / 8;
    uint8_t bi = re & 7;
    uint8_t * p = _ar[se];
    if (value == 0) p[by] &= ~(1 << bi); // bitClear(p[by], bi);
    else p[by] |= (1 << bi);             // bitSet(p[by], bi);
}

// END OF FILE
