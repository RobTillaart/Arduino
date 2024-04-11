#pragma once
//
//    FILE: FastCRC32.h
//  AUTHOR: vovagorodok
// PURPOSE: Arduino class for CRC
//     URL: https://github.com/RobTillaart/CRC


#include "CrcParameters.h"
#include "CrcDefines.h"


class FastCRC32
{
public:
  FastCRC32();

  void restart();
  uint32_t calc() const;
  crc_size_t count() const;
  void add(uint8_t value);
  void add(const uint8_t *array, crc_size_t length);
  void add(const uint8_t *array, crc_size_t length, crc_size_t yieldPeriod);

private:
  void _add(uint8_t value);

  uint32_t _crc;
  crc_size_t _count;
};

