//
//    FILE: CRC.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 1.0.2
// PURPOSE: Arduino library for CRC8, CRC12, CRC16, CRC32, CRC64
//     URL: https://github.com/RobTillaart/CRC


#include "CRC.h"

uint8_t calcCRC8(
  const uint8_t *array, crc_size_t length,
  uint8_t polynome, uint8_t initial, uint8_t xorOut,
  bool reverseIn, bool reverseOut, crc_size_t yieldPeriod)
{
  CRC8 crc(polynome, initial, xorOut, reverseIn, reverseOut);
  yieldPeriod == CRC_YIELD_DISABLED ?
    crc.add(array, length) :
    crc.add(array, length, yieldPeriod);
  return crc.calc();
}

uint16_t calcCRC12(
  const uint8_t *array, crc_size_t length,
  uint16_t polynome, uint16_t initial, uint16_t xorOut,
  bool reverseIn, bool reverseOut, crc_size_t yieldPeriod)
{
  CRC12 crc(polynome, initial, xorOut, reverseIn, reverseOut);
  yieldPeriod == CRC_YIELD_DISABLED ?
    crc.add(array, length) :
    crc.add(array, length, yieldPeriod);
  return crc.calc();
}

uint16_t calcCRC16(
  const uint8_t *array, crc_size_t length,
  uint16_t polynome, uint16_t initial, uint16_t xorOut,
  bool reverseIn, bool reverseOut, crc_size_t yieldPeriod)
{
  CRC16 crc(polynome, initial, xorOut, reverseIn, reverseOut);
  yieldPeriod == CRC_YIELD_DISABLED ?
    crc.add(array, length) :
    crc.add(array, length, yieldPeriod);
  return crc.calc();
}

uint32_t calcCRC32(
  const uint8_t *array, crc_size_t length,
  uint32_t polynome, uint32_t initial, uint32_t xorOut,
  bool reverseIn, bool reverseOut, crc_size_t yieldPeriod)
{
  CRC32 crc(polynome, initial, xorOut, reverseIn, reverseOut);
  yieldPeriod == CRC_YIELD_DISABLED ?
    crc.add(array, length) :
    crc.add(array, length, yieldPeriod);
  return crc.calc();
}

uint64_t calcCRC64(
  const uint8_t *array, crc_size_t length,
  uint64_t polynome, uint64_t initial, uint64_t xorOut,
  bool reverseIn, bool reverseOut, crc_size_t yieldPeriod)
{
  CRC64 crc(polynome, initial, xorOut, reverseIn, reverseOut);
  yieldPeriod == CRC_YIELD_DISABLED ?
    crc.add(array, length) :
    crc.add(array, length, yieldPeriod);
  return crc.calc();
}

uint8_t crc8(
  const uint8_t *array, crc_size_t length,
  uint8_t polynome, uint8_t initial, uint8_t xorOut,
  bool reverseIn, bool reverseOut, crc_size_t yieldPeriod)
{
  return calcCRC8(array, length, polynome, initial, xorOut, reverseIn, reverseOut, yieldPeriod);
}

uint16_t crc12(
  const uint8_t *array, crc_size_t length,
  uint16_t polynome, uint16_t initial, uint16_t xorOut,
  bool reverseIn, bool reverseOut, crc_size_t yieldPeriod)
{
  return calcCRC12(array, length, polynome, initial, xorOut, reverseIn, reverseOut, yieldPeriod);
}

uint16_t crc16(
  const uint8_t *array, crc_size_t length,
  uint16_t polynome, uint16_t initial, uint16_t xorOut,
  bool reverseIn, bool reverseOut, crc_size_t yieldPeriod)
{
  return calcCRC16(array, length, polynome, initial, xorOut, reverseIn, reverseOut, yieldPeriod);
}

uint16_t crc16_CCITT(
  const uint8_t *array, crc_size_t length,
  uint16_t polynome, uint16_t initial, uint16_t xorOut,
  bool reverseIn, bool reverseOut, crc_size_t yieldPeriod)
{
  return calcCRC16(array, length, polynome, initial, xorOut, reverseIn, reverseOut, yieldPeriod);
}

uint32_t crc32(
  const uint8_t *array, crc_size_t length,
  uint32_t polynome, uint32_t initial, uint32_t xorOut,
  bool reverseIn, bool reverseOut, crc_size_t yieldPeriod)
{
  return calcCRC32(array, length, polynome, initial, xorOut, reverseIn, reverseOut, yieldPeriod);
}

uint64_t crc64(
  const uint8_t *array, crc_size_t length,
  uint64_t polynome, uint64_t initial, uint64_t xorOut,
  bool reverseIn, bool reverseOut, crc_size_t yieldPeriod)
{
  return calcCRC64(array, length, polynome, initial, xorOut, reverseIn, reverseOut, yieldPeriod);
}


//  -- END OF FILE

