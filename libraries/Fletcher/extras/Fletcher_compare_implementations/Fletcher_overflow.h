#pragma once
/*
  Author: Daniel Mohr
  Date: 2022-09-09

  Here are implementations with testing for overflow instead of modulo.
*/

#define FLETCHER_64_overflow 4294967295ULL

#ifdef ARDUINO_ARCH_AVR
uint32_t fletcher32_overflow(uint16_t *data, const uint16_t length)
{
  uint16_t _s1 = 0;
  uint16_t _s2 = 0;
  for (uint16_t i = 0; i < length; i++)
    {
      if (__builtin_uadd_overflow(_s1, data[i], &_s1)) {
	_s1++;
      }
      if (__builtin_uadd_overflow(_s2, _s1, &_s2)) {
	_s2++;
      }
    }
  return (((uint32_t) _s2) << 16) | ((uint32_t) _s1);
}
#endif

uint64_t fletcher64_overflow(uint32_t *data, const uint16_t length)
{
  uint32_t _s1 = 0;
  uint32_t _s2 = 0;
  for (uint16_t i = 0; i < length; i++)
    {
      if (__builtin_uaddl_overflow(_s1, data[i], &_s1)) {
	_s1++;
      }
      if (__builtin_uaddl_overflow(_s2, _s1, &_s2)) {
	_s2++;
      }

    }
  return (((uint64_t) _s2) << 32) | ((uint64_t) _s1);
}
