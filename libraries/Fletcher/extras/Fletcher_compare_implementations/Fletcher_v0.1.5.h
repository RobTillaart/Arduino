#pragma once
/*
  Author: Daniel Mohr
  Date: 2022-09-09

  Here are implementations, which were used in release '0.1.5'.

  Fletcher16.cpp
  Fletcher16.h
  Fletcher32.cpp
  Fletcher32.h
  Fletcher64.cpp
  Fletcher64.h
*/

#define FLETCHER_16_v0_1_5 255
#define FLETCHER_32_v0_1_5 65535UL
#define FLETCHER_64_v0_1_5 4294967295ULL

uint16_t fletcher16_v0_1_5(uint8_t *data, const uint16_t length)
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
  return (_s2 << 8) | _s1;
}

uint32_t fletcher32_v0_1_5(uint16_t *data, const uint16_t length)
{
  uint32_t _s1 = 0;
  uint32_t _s2 = 0;
  for (uint16_t i = 0; i < length; i++)
    {
      _s1 += data[i];
#if defined(ARDUINO_ARCH_SAMD) || defined(ESP32) || defined(ESP8266)
      _s1 = (_s1 & 65535UL) + (_s1 >> 16);
#else
      if (_s1 >= FLETCHER_32_v0_1_5) _s1 -= FLETCHER_32_v0_1_5;
#endif
      _s2 += _s1;
#if defined(ARDUINO_ARCH_SAMD) || defined(ESP32) || defined(ESP8266)
      _s2 = (_s2 & 65535UL) + (_s2 >> 16);
#else
      if (_s2 >= FLETCHER_32_v0_1_5) _s2 -= FLETCHER_32_v0_1_5;
#endif
    }
  return (_s2 << 16) | _s1;
}

uint64_t fletcher64_v0_1_5(uint32_t *data, const uint16_t length)
{
  uint64_t _s1 = 0;
  uint64_t _s2 = 0;
  for (uint16_t i = 0; i < length; i++)
    {
      _s1 += data[i];
#if defined(ARDUINO_ARCH_SAMD) || defined(ESP32) || defined(ESP8266)
      _s1 = (_s1 & ((((uint64_t) 1) << 32) - 1)) + (_s1 >> 32);
#else
      if (_s1 >= FLETCHER_64_v0_1_5) _s1 -= FLETCHER_64_v0_1_5;
#endif
      _s2 += _s1;
#if defined(ARDUINO_ARCH_SAMD) || defined(ESP32) || defined(ESP8266)
      _s2 = (_s2 & ((((uint64_t) 1) << 32) - 1)) + (_s2 >> 32);
#else
      if (_s2 >= FLETCHER_64_v0_1_5) _s2 -= FLETCHER_64_v0_1_5;
#endif
    }
  return (_s2 << 32) | _s1;
}
