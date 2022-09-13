#pragma once
/*
  Author: Daniel Mohr
  Date: 2022-09-09

  Here are implementations with bit shifts instead of modulo.
*/

uint16_t fletcher16_bit_shift(uint8_t *data, const uint16_t length)
{
  uint16_t _s1 = 0;
  uint16_t _s2 = 0;
  for (uint16_t i = 0; i < length; i++)
  {
    _s1 += data[i];
    _s1 = (_s1 & 255) + (_s1 >> 8);
    _s2 += _s1;
    _s2 = (_s2 & 255) + (_s2 >> 8);
  }
  if (_s1 >= 255) _s1 -= 255;
  if (_s2 >= 255) _s2 -= 255;
  return (_s2 << 8) | _s1;
}

uint32_t fletcher32_bit_shift(uint16_t *data, const uint16_t length)
{
  uint32_t _s1 = 0;
  uint32_t _s2 = 0;
  for (uint16_t i = 0; i < length; i++)
  {
    _s1 += data[i];
    _s1 = (_s1 & 65535UL) + (_s1 >> 16);
    _s2 += _s1;
    _s2 = (_s2 & 65535UL) + (_s2 >> 16);
  }
  if (_s1 >= 65535UL) _s1 -= 65535UL;
  if (_s2 >= 65535UL) _s2 -= 65535UL;
  return (_s2 << 16) | _s1;
}

uint64_t fletcher64_bit_shift(uint32_t *data, const uint16_t length)
{
  uint64_t _s1 = 0;
  uint64_t _s2 = 0;
  for (uint16_t i = 0; i < length; i++)
  {
    _s1 += data[i];
    _s1 = (_s1 & ((((uint64_t) 1) << 32) - 1)) + (_s1 >> 32);
    _s2 += _s1;
    _s2 = (_s2 & ((((uint64_t) 1) << 32) - 1)) + (_s2 >> 32);
  }
  if (_s1 >= 4294967295ULL) _s1 -= 4294967295ULL;
  if (_s2 >= 4294967295ULL) _s2 -= 4294967295ULL;
  return (_s2 << 32) | _s1;
}
