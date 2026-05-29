//
//    FILE: BitArray.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.9
// PURPOSE: BitArray library for Arduino
//     URL: https://github.com/RobTillaart/BitArray
//          http://forum.arduino.cc/index.php?topic=361167


#include "BitArray.h"


/////////////////////////////////////////////////////////
//
//  16 bit version
//  max memory that can be allocated is 64 KB.
//
BitArray::BitArray()
{
  _array = nullptr;
  _size  = 0;
  _bytes = 0;
  _bits  = 0;
}


BitArray::~BitArray()
{
  if (_array)
  {
    free(_array);
  }
}


int BitArray::begin(const uint8_t elementSize, const uint16_t elementCount)
{
  if ((elementSize == 0) || (elementSize > 32))
  {
    _error = BA_ELEMENT_SIZE_ERR;
    return _error;
  }
  if (((1UL * elementSize * elementCount + 7) / 8) > BITARRAY_MAXSIZE)
  {
    _error = BA_SIZE_ERR;
    return _error;
  }

  _bits = elementSize;
  _size = elementCount;
  _bytes = (1UL * _bits * _size + 7) / 8;
  if (_array != nullptr)
  {
    free(_array);
  }
  _array = (uint8_t *) malloc(_bytes);
  if (_array == nullptr)
  {
    _bits = 0;
    _size = 0;
    _bytes = 0;
    _error = BA_NO_MEMORY_ERR;
    return _error;
  }

  _error = BA_OK;
  return _error;
}


uint16_t BitArray::get(const uint16_t index)
{
  uint16_t v = 0;
  uint32_t pos = index * _bits;

  for (uint8_t i = _bits; i-- > 0;)
  {
    v <<= 1;
    v += _bitget(pos + i);
  }
  return v;
}


uint16_t BitArray::set(const uint16_t index, uint16_t value)
{
  uint32_t pos = index * _bits;
  uint16_t mask = 1UL;
  for (uint8_t i = 0; i < _bits; i++)
  {
    uint8_t v = (value & mask) > 0 ? 1 : 0;
    _bitset(pos + i, v);
    mask <<= 1;
  }
  return value;
}


uint16_t BitArray::toggle(const uint16_t index)
{
  uint16_t v = 0;
  uint32_t pos = index * _bits;
  for (uint8_t i = _bits; i-- > 0;)
  {
    v <<= 1;
    v += _bittoggle(pos + i);
  }
  return v;
}


int BitArray::clear()
{
  if (_array == NULL)
  {
    _error = BA_NO_MEMORY_ERR;
    return _error;
  }
  uint8_t *p = _array;
  uint16_t t = _bytes;
  while (t--)
  {
    *p++ = 0;
  }
  _error = BA_OK;
  return _error;
}


int BitArray::setAll(uint16_t value)
{
  if (_array == NULL)
  {
    _error = BA_NO_MEMORY_ERR;
    return _error;
  }
  for (uint16_t i = 0; i < capacity(); i++)
  {
    set(i, value);
  }
  _error = BA_OK;
  return _error;
}


/////////////////////////////////////////////////
//
//  PRIVATE
//
inline uint8_t BitArray::_bitget(uint32_t pos)
{
  uint16_t by = pos / 8;
  uint8_t  bi = pos & 7;
  return (_array[by] >> bi) & 0x01;
}


inline void BitArray::_bitset(uint32_t pos, uint8_t value)
{
  uint16_t by = pos / 8;
  uint8_t  bi = pos & 7;
  if (value == 0) _array[by] &= ~(1 << bi);
  else _array[by] |= (1 << bi);
}


inline uint8_t BitArray::_bittoggle(const uint32_t pos)
{
  uint16_t by = pos / 8;
  uint8_t  bi = pos & 7;
  uint8_t mask = 1 << bi;
  _array[by] ^= mask;
  return ((_array[by] & mask) > 0);
}


/////////////////////////////////////////////////////////
//
//  32 bit version
//
BitArray32::BitArray32()
{
  _array = nullptr;
  _size  = 0;
  _bytes = 0;
  _bits  = 0;
}


BitArray32::~BitArray32()
{
  if (_array)
  {
    free(_array);
  }
}


int BitArray32::begin(const uint8_t elementSize, const uint32_t elementCount)
{
  if ((elementSize == 0) || (elementSize > 32))
  {
    _error = BA_ELEMENT_SIZE_ERR;
    return _error;
  }
  if (((1UL * elementSize * elementCount + 7) / 8) > BITARRAY_MAXSIZE)
  {
    _error = BA_SIZE_ERR;
    return _error;
  }

  _bits = elementSize;
  _size = elementCount;
  _bytes = (1UL * _bits * _size + 7) / 8;
  if (_array != nullptr)
  {
    free(_array);
  }
  _array = (uint8_t *) malloc(_bytes);
  if (_array == nullptr)
  {
    _bits = 0;
    _size = 0;
    _bytes = 0;
    _error = BA_NO_MEMORY_ERR;
    return _error;
  }

  _error = BA_OK;
  return _error;
}


uint32_t BitArray32::get(const uint32_t index)
{
  uint32_t v = 0;
  uint32_t pos = index * _bits;

  for (uint8_t i = _bits; i-- > 0;)
  {
    v <<= 1;
    v += _bitget(pos + i);
  }
  return v;
}


uint32_t BitArray32::set(const uint32_t index, uint32_t value)
{
  uint32_t pos = index * _bits;
  uint32_t mask = 1UL;
  for (uint8_t i = 0; i < _bits; i++)
  {
    uint8_t v = (value & mask) > 0 ? 1 : 0;
    _bitset(pos + i, v);
    mask <<= 1;
  }
  return value;
}


uint32_t BitArray32::toggle(const uint32_t index)
{
  uint32_t v = 0;
  uint16_t pos = index * _bits;
  for (uint8_t i = _bits; i-- > 0;)
  {
    v <<= 1;
    v += _bittoggle(pos + i);
  }
  return v;
}


int BitArray32::clear()
{
  if (_array == NULL)
  {
    _error = BA_NO_MEMORY_ERR;
    return _error;
  }
  uint8_t *p = _array;
  uint32_t t = _bytes;
  while (t--)
  {
    *p++ = 0;
  }
  _error = BA_OK;
  return _error;
}


int BitArray32::setAll(uint32_t value)
{
  if (_array == NULL)
  {
    _error = BA_NO_MEMORY_ERR;
    return _error;
  }
  for (uint32_t i = 0; i < capacity(); i++)
  {
    set(i, value);
  }
  _error = BA_OK;
  return _error;
}


/////////////////////////////////////////////////
//
//  PRIVATE
//
inline uint8_t BitArray32::_bitget(uint32_t pos)
{
  uint32_t by = pos / 8;
  uint8_t  bi = pos & 7;
  return (_array[by] >> bi) & 0x01;
}


inline void BitArray32::_bitset(uint32_t pos, uint8_t value)
{
  uint32_t by = pos / 8;
  uint8_t  bi = pos & 7;
  if (value == 0) _array[by] &= ~(1 << bi);
  else _array[by] |= (1 << bi);
}


inline uint8_t BitArray32::_bittoggle(const uint32_t pos)
{
  uint32_t by = pos / 8;
  uint8_t  bi = pos & 7;
  uint8_t mask = 1 << bi;
  _array[by] ^= mask;
  return ((_array[by] & mask) > 0);
}


//  -- END OF FILE --

