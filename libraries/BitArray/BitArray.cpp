//
//    FILE: BitArray.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.8
// PURPOSE: BitArray library for Arduino
//     URL: https://github.com/RobTillaart/BitArray
//          http://forum.arduino.cc/index.php?topic=361167


#include "BitArray.h"


BitArray::BitArray()
{
  for (uint8_t i = 0; i < BA_MAX_SEGMENTS; i++)
  {
    _ar[i] = NULL;
  }
}


BitArray::~BitArray()
{
  for (uint8_t i = 0; i < BA_MAX_SEGMENTS; i++)
  {
    if (_ar[i]) free(_ar[i]);
  }
}


uint8_t BitArray::begin(const uint8_t bits, const uint16_t size)
{
  if ((bits == 0) || (bits > 32))
  {
    _error = BA_ELEMENT_SIZE_ERR;
    return _error;
  }
  if (((1UL * bits * size)/8) > (1UL * BA_MAX_SEGMENTS * BA_SEGMENT_SIZE))
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
    _ar[_segments] = (uint8_t*) malloc(min(b, (uint16_t) BA_SEGMENT_SIZE));
    if (_ar[_segments] == NULL)
    {
      _error = BA_NO_MEMORY_ERR;
      return _error;
    }
    b = b - min(b, (uint16_t) BA_SEGMENT_SIZE);
    _segments++;
  }
  _error = BA_OK;
  return _error;
}


uint32_t BitArray::get(const uint16_t index)
{
  //  if (_error != BA_OK) return BA_ERR;
  //  if (index >= _size) return BA_IDX_RANGE;
  uint32_t v = 0;
  uint16_t pos = index * _bits;

  for (uint8_t i = _bits; i-- > 0;)
  {
    v <<= 1;
    v += _bitget(pos + i);
  }
  return v;
}


uint32_t BitArray::set(const uint16_t index, uint32_t value)
{
  //  if (_error != BA_OK) return BA_ERR;
  //  if (index >= _size) return BA_IDX_RANGE;
  uint16_t pos = index * _bits;
  uint32_t mask = 1UL;
  for (uint8_t i = 0; i < _bits; i++)
  {
    uint8_t v = (value & mask) > 0 ? 1 : 0;
    _bitset(pos + i, v);
    mask <<= 1;
  }
  return value;
}


uint32_t BitArray::toggle(const uint16_t index)
{
  //  if (_error != BA_OK) return BA_ERR;
  //  if (index >= _size) return BA_IDX_RANGE;
  uint32_t v = 0;
  uint16_t pos = index * _bits;
  for (uint8_t i = _bits; i-- > 0;)
  {
    v <<= 1;
    v += _bittoggle(pos + i);
  }
  return v;
}


void BitArray::clear()
{
  uint16_t b = _bytes;
  for (uint8_t s = 0; s < _segments; s++)
  {
    uint8_t *p = _ar[s];
    if (p)
    {
      uint8_t t = min(b, (uint16_t) BA_SEGMENT_SIZE);
      b -= t;
      while(t--)
      {
        *p++ = 0;
      }
    }
    if (b == 0) break;
  }
}



void BitArray::setAll(uint32_t value)
{
  for (uint16_t i = 0; i < capacity(); i++)
  {
    set(i, value);
  }
}


//      16 bit address usage is faster
//  TODO verify correctness
//
// void BitArray::clear()
// {
    // uint16_t b = _bytes;
    // for (uint8_t s = 0; s < _segments; s++)
    // {
        // uint8_t *q = _ar[s];
        // uint16_t *p = (uint16_t*)q;
        // if (p)
        // {
            // for (uint8_t t = 0; t < BA_SEGMENT_SIZE/2; t++)
            // {
              // *p++ = 0;    // might be bug @ edge..
            // }
        // }
        // if (b == 0) break;
    // }
// }


/////////////////////////////////////////////////
//
//  PRIVATE
//
inline uint8_t BitArray::_bitget(uint16_t pos)
{
  uint8_t se = 0;
  uint16_t re = pos;
  while (re >= (BA_SEGMENT_SIZE * 8))  //  8 == #bits in uint8_t
  {
    se++;
    re -= (BA_SEGMENT_SIZE * 8);
  }
  uint8_t by = re / 8;
  uint8_t bi = re & 7;
  uint8_t * p = _ar[se];

  return (p[by] >> bi) & 0x01;          //  bitRead(p[by], bi);
}


inline void BitArray::_bitset(uint16_t pos, uint8_t value)
{
  uint8_t se = 0;
  uint16_t re = pos;
  while (re >= (BA_SEGMENT_SIZE * 8))   //  8 == #bits in uint8_t
  {
    se++;
    re -= (BA_SEGMENT_SIZE * 8);
  }
  uint8_t by = re / 8;
  uint8_t bi = re & 7;
  uint8_t * p = _ar[se];

  if (value == 0) p[by] &= ~(1 << bi);  //  bitClear(p[by], bi);
  else p[by] |= (1 << bi);              //  bitSet(p[by], bi);
}


inline uint8_t BitArray::_bittoggle(const uint16_t pos)
{
  uint8_t se = 0;
  uint16_t re = pos;
  while (re >= (BA_SEGMENT_SIZE * 8))   //  8 == #bits in uint8_t
  {
    se++;
    re -= (BA_SEGMENT_SIZE * 8);
  }
  uint8_t by = re / 8;
  uint8_t bi = re & 7;
  uint8_t * p = _ar[se];

  uint8_t mask = 1 << bi;
  p[by] ^= mask;
  return (mask > 0);
  //  return ((p[by] & mask) > 0);  0.3.0
}


//  -- END OF FILE --

