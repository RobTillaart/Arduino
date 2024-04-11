//
//    FILE: FastCRC32.cpp
//  AUTHOR: vovagorodok
// PURPOSE: Arduino class for CRC
//     URL: https://github.com/RobTillaart/CRC


#include "FastCRC32.h"


namespace
{
// Conditionally use pgm memory if it is available.
#if defined(PROGMEM)
    #define FLASH_PROGMEM PROGMEM
    #define FLASH_READ_DWORD(x) (pgm_read_dword_near(x))
#else
    #define FLASH_PROGMEM
    #define FLASH_READ_DWORD(x) (*(uint32_t*)(x))
#endif

static const uint32_t crc32LookupTable[] FLASH_PROGMEM = {
    0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac,
    0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
    0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
    0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c
};
}

FastCRC32::FastCRC32() :
  _crc(CRC32_INITIAL),
  _count(0u)
{}

void FastCRC32::restart()
{
  _crc = CRC32_INITIAL;
  _count = 0u;
}

uint32_t FastCRC32::calc() const
{
  return _crc ^ CRC32_XOR_OUT;
}

crc_size_t FastCRC32::count() const
{
  return _count;
}

void FastCRC32::add(uint8_t value)
{
  _count++;
  _add(value);
}

void FastCRC32::add(const uint8_t *array, crc_size_t length)
{
  _count += length;
  while (length--)
  {
    _add(*array++);
  }
}

void FastCRC32::add(const uint8_t *array, crc_size_t length, crc_size_t yieldPeriod)
{
  _count += length;
  crc_size_t period = yieldPeriod;
  while (length--)
  {
    _add(*array++);
    if (--period == 0)
    {
      yield();
      period = yieldPeriod;
    }
  }
}

void FastCRC32::_add(uint8_t value)
{
  //  via http://forum.arduino.cc/index.php?topic=91179.0
  uint8_t index = 0u;

  index = _crc ^ (value >> (0 * 4));
  _crc = FLASH_READ_DWORD(crc32LookupTable + (index & 0x0f)) ^ (_crc >> 4);
  index = _crc ^ (value >> (1 * 4));
  _crc = FLASH_READ_DWORD(crc32LookupTable + (index & 0x0f)) ^ (_crc >> 4);
}
