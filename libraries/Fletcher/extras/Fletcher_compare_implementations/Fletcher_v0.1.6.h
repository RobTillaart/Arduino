#pragma once
/*
  Author: Daniel Mohr
  Date: 2022-09-12

  Here are implementations, which were used in release '0.1.6'.

  Fletcher16.cpp
  Fletcher16.h
  Fletcher32.cpp
  Fletcher32.h
  Fletcher64.cpp
  Fletcher64.h
*/

#define FLETCHER_16_v0_1_6 255
#define FLETCHER_32_v0_1_6 65535UL
#define FLETCHER_64_v0_1_6 4294967295ULL

uint16_t fletcher16_v0_1_6(uint8_t *data, const uint16_t length)
{
#ifdef ARDUINO_ARCH_AVR
  uint8_t _s1 = 0;
  uint8_t _s2 = 0;
#else
  uint16_t _s1 = 0;
  uint16_t _s2 = 0;
#endif
  for (uint16_t i = 0; i < length; i++)
    {
#if defined(ARDUINO_ARCH_AVR)
      uint8_t t = 0xFF - data[i];
      if (t >= _s1) _s1 += data[i];
      else _s1 = _s1 + data[i] + 1;

      t = 0xFF - _s1;
      if (t >= _s2) _s2 += _s1;
      else _s2 = _s2 + _s1 + 1;

#elif defined(ARDUINO_ARCH_SAMD) || defined(ESP32) || defined(ESP8266)
      _s1 += data[i];
      _s1 = (_s1 & 255) + (_s1 >> 8);
      _s2 += _s1;
      _s2 = (_s2 & 255) + (_s2 >> 8);

#else
      //  REFERENCE
      _s1 += data[i];
      if (_s1 >= FLETCHER_16_v0_1_6) _s1 -= FLETCHER_16_v0_1_6;
      _s2 += _s1;
      if (_s2 >= FLETCHER_16_v0_1_6) _s2 -= FLETCHER_16_v0_1_6;
#endif
    }
  if (_s1 >= FLETCHER_16_v0_1_6) _s1 -= FLETCHER_16_v0_1_6;
  if (_s2 >= FLETCHER_16_v0_1_6) _s2 -= FLETCHER_16_v0_1_6;
  return (((uint16_t)_s2) << 8) | _s1;
}

uint32_t fletcher32_v0_1_6(uint16_t *data, const uint16_t length)
{
#ifdef ARDUINO_ARCH_AVR
  uint16_t _s1 = 0;
  uint16_t _s2 = 0;
#else
  uint32_t _s1 = 0;
  uint32_t _s2 = 0;
#endif
  for (uint16_t i = 0; i < length; i++)
    {
#ifdef ARDUINO_ARCH_AVR 
      unsigned int t = _s1;
      //  Serial.println("__builtin_uadd_overflow");
      if (__builtin_uadd_overflow(t, data[i], &t)) {
	t++;
      }
      _s1 = t;
      t = _s2;
      if (__builtin_uadd_overflow(t, _s1, &t)) {
	t++;
      } 
      _s2 = t;
#elif defined(ARDUINO_ARCH_SAMD) || defined(ESP32) || defined(ESP8266)
      _s1 += data[i];
      _s1 = (_s1 & 65535UL) + (_s1 >> 16);
      _s2 += _s1;
      _s2 = (_s2 & 65535UL) + (_s2 >> 16);
#else
      _s1 += data[i];
      if (_s1 >= FLETCHER_32_v0_1_6) _s1 -= FLETCHER_32_v0_1_6;
      _s2 += _s1;
      if (_s2 >= FLETCHER_32_v0_1_6) _s2 -= FLETCHER_32_v0_1_6;
#endif
    }
  if (_s1 >= FLETCHER_32_v0_1_6) _s1 -= FLETCHER_32_v0_1_6;
  if (_s2 >= FLETCHER_32_v0_1_6) _s2 -= FLETCHER_32_v0_1_6;
  return (((uint32_t)_s2) << 16) | _s1;
}

uint64_t fletcher64_v0_1_6(uint32_t *data, const uint16_t length)
{
#if defined(ARDUINO_ARCH_AVR) || defined(ESP32) || defined(ESP8266)
  uint32_t _s1 = 0;
  uint32_t _s2 = 0;
#else
  uint64_t _s1 = 0;
  uint64_t _s2 = 0;
#endif
  for (uint16_t i = 0; i < length; i++)
    {
#if defined(ARDUINO_ARCH_AVR)  || defined(ESP32) || defined(ESP8266)
      uint32_t t = 0xFFFFFFFF - data[i];
      if (t >= _s1) _s1 += data[i];
      else _s1 = _s1 + data[i] + 1;
  
      t = 0xFFFFFFFF - _s1;
      if (t >= _s2) _s2 += _s1;
      else _s2 = _s2 + _s1 + 1;
#elif defined(ARDUINO_ARCH_SAMD)
      _s1 += data[i];
      _s1 = (_s1 & ((((uint64_t) 1) << 32) - 1)) + (_s1 >> 32);
      _s2 += _s1;
      _s2 = (_s2 & ((((uint64_t) 1) << 32) - 1)) + (_s2 >> 32);
#else
      _s1 += data[i];
      if (_s1 >= FLETCHER_64_v0_1_6) _s1 -= FLETCHER_64_v0_1_6;
      _s2 += _s1;
      if (_s2 >= FLETCHER_64_v0_1_6) _s2 -= FLETCHER_64_v0_1_6;
#endif
    }
  if (_s1 >= FLETCHER_64_v0_1_6) _s1 -= FLETCHER_64_v0_1_6;
  if (_s2 >= FLETCHER_64_v0_1_6) _s2 -= FLETCHER_64_v0_1_6;
  return (((uint64_t)_s2) << 32) | _s1;
}
