#pragma once
/*
  Author: Daniel Mohr
  Date: 2022-09-13

  Here are basic implementations which should give reference values.
*/

uint16_t basic_fletcher16(uint8_t *data, const size_t length)
{
  uint8_t s1 = 0;
  uint8_t s2 = 0;
  for (size_t i = 0; i < length; i++)
  {
     // UINT8_MAX = 255 = ((((uint16_t) 1) << 8) - ((uint16_t) 1))
    s1 = (uint8_t) (((uint16_t) s1 + (uint16_t) data[i]) % UINT8_MAX);
    s2 = (uint8_t) (((uint16_t) s2 + (uint16_t) s1) % UINT8_MAX);
  }
  return (((uint16_t) s2) << 8) | ((uint16_t) s1);
}

uint32_t basic_fletcher32(uint16_t *data, const size_t length)
{
  uint16_t s1 = 0;
  uint16_t s2 = 0;
  for (size_t i = 0; i < length; i++)
  {
    // UINT16_MAX = 65535UL = ((((uint32_t) 1) << 16) - ((uint32_t) 1))
    s1 = (uint16_t) (((uint32_t) s1 + (uint32_t) data[i]) % UINT16_MAX);
    s2 = (uint16_t) (((uint32_t) s2 + (uint32_t) s1) % UINT16_MAX);
  }
  return (((uint32_t) s2) << 16) | ((uint32_t) s1);
}

uint64_t basic_fletcher64(uint32_t *data, const size_t length)
{
  uint32_t s1 = 0;
  uint32_t s2 = 0;
  for (size_t i = 0; i < length; i++)
  {
    // UINT32_MAX = 4294967295ULL = ((((uint64_t) 1) << 32) - ((uint64_t) 1))
    s1 = (uint32_t) (((uint64_t) s1 + (uint64_t) data[i]) % UINT32_MAX);
    s2 = (uint32_t) (((uint64_t) s2 + (uint64_t) s1) % UINT32_MAX);
  }
  return (((uint64_t) s2) << 32) | ((uint64_t) s1);
}
