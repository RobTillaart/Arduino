#pragma once
/*
  Author: Daniel Mohr
  Date: 2022-09-10

  Here are implementations, which could be used in the next release.

  Fletcher16.cpp
  Fletcher16.h
  Fletcher32.cpp
  Fletcher32.h
  Fletcher64.cpp
  Fletcher64.h
*/

#include <Fletcher16.h>
#include <Fletcher32.h>
#include <Fletcher64.h>

uint16_t fletcher16_next(uint8_t *data, const size_t length)
{
  Fletcher16 checksum_instance;
  for (size_t i = 0; i < length; i++)
    {
      checksum_instance.add(data[i]);
    }
  return checksum_instance.getFletcher();
}

uint32_t fletcher32_next(uint16_t *data, const size_t length)
{
  Fletcher32 checksum_instance;
  for (size_t i = 0; i < length; i++)
    {
      checksum_instance.add(data[i]);
    }
  return checksum_instance.getFletcher();
}

uint64_t fletcher64_next(uint32_t *data, const size_t length)
{
  Fletcher64 checksum_instance;
  for (size_t i = 0; i < length; i++)
    {
      checksum_instance.add(data[i]);
    }
  return checksum_instance.getFletcher();
}
