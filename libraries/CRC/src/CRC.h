#pragma once
//
//    FILE: CRC.h
//  AUTHOR: Rob Tillaart
// VERSION: 1.0.2
// PURPOSE: Arduino library for CRC8, CRC12, CRC16, CRC32, CRC64
//     URL: https://github.com/RobTillaart/CRC


#include "CrcParameters.h"
#include "CRC8.h"
#include "CRC12.h"
#include "CRC16.h"
#include "CRC32.h"
#include "CRC64.h"

#define CRC_LIB_VERSION       (F("1.0.2"))


uint8_t calcCRC8(
    const uint8_t *array, crc_size_t length,
    uint8_t polynome   = CRC8_POLYNOME,
    uint8_t initial    = CRC8_INITIAL,
    uint8_t xorOut     = CRC8_XOR_OUT,
    bool reverseIn     = CRC8_REV_IN,
    bool reverseOut    = CRC8_REV_OUT,
    crc_size_t yieldPeriod = CRC_YIELD_DISABLED);

uint16_t calcCRC12(
    const uint8_t *array, crc_size_t length,
    uint16_t polynome  = CRC12_POLYNOME,
    uint16_t initial   = CRC12_INITIAL,
    uint16_t xorOut    = CRC12_XOR_OUT,
    bool reverseIn     = CRC12_REV_IN,
    bool reverseOut    = CRC12_REV_OUT,
    crc_size_t yieldPeriod = CRC_YIELD_DISABLED);

uint16_t calcCRC16(
    const uint8_t *array, crc_size_t length,
    uint16_t polynome  = CRC16_POLYNOME,
    uint16_t initial   = CRC16_INITIAL,
    uint16_t xorOut    = CRC16_XOR_OUT,
    bool reverseIn     = CRC16_REV_IN,
    bool reverseOut    = CRC16_REV_OUT,
    crc_size_t yieldPeriod = CRC_YIELD_DISABLED);

uint32_t calcCRC32(
    const uint8_t *array, crc_size_t length,
    uint32_t polynome  = CRC32_POLYNOME,
    uint32_t initial   = CRC32_INITIAL,
    uint32_t xorOut    = CRC32_XOR_OUT,
    bool reverseIn     = CRC32_REV_IN,
    bool reverseOut    = CRC32_REV_OUT,
    crc_size_t yieldPeriod = CRC_YIELD_DISABLED);

uint64_t calcCRC64(
    const uint8_t *array, crc_size_t length,
    uint64_t polynome  = CRC64_POLYNOME,
    uint64_t initial   = CRC64_INITIAL,
    uint64_t xorOut    = CRC64_XOR_OUT,
    bool reverseIn     = CRC64_REV_IN,
    bool reverseOut    = CRC64_REV_OUT,
    crc_size_t yieldPeriod = CRC_YIELD_DISABLED);


[[deprecated("Use calcCRC8() instead")]]
uint8_t crc8(
    const uint8_t *array, crc_size_t length,
    uint8_t polynome   = CRC8_POLYNOME,
    uint8_t initial    = CRC8_INITIAL,
    uint8_t xorOut     = CRC8_XOR_OUT,
    bool reverseIn     = CRC8_REV_IN,
    bool reverseOut    = CRC8_REV_OUT,
    crc_size_t yieldPeriod = CRC_YIELD_DISABLED);

[[deprecated("Use calcCRC12() instead")]]
uint16_t crc12(
    const uint8_t *array, crc_size_t length,
    uint16_t polynome  = CRC12_POLYNOME,
    uint16_t initial   = CRC12_INITIAL,
    uint16_t xorOut    = CRC12_XOR_OUT,
    bool reverseIn     = CRC12_REV_IN,
    bool reverseOut    = CRC12_REV_OUT,
    crc_size_t yieldPeriod = CRC_YIELD_DISABLED);

[[deprecated("Use calcCRC16() instead")]]
uint16_t crc16(
    const uint8_t *array, crc_size_t length,
    uint16_t polynome  = CRC16_POLYNOME,
    uint16_t initial   = CRC16_INITIAL,
    uint16_t xorOut    = CRC16_XOR_OUT,
    bool reverseIn     = CRC16_REV_IN,
    bool reverseOut    = CRC16_REV_OUT,
    crc_size_t yieldPeriod = CRC_YIELD_DISABLED);

[[deprecated("Use calcCRC16() with CRC16_CCITT_FALSE params instead")]]
uint16_t crc16_CCITT(
    const uint8_t *array, crc_size_t length,
    uint16_t polynome  = CRC16_CCITT_FALSE_POLYNOME,
    uint16_t initial   = CRC16_CCITT_FALSE_INITIAL,
    uint16_t xorOut    = CRC16_CCITT_FALSE_XOR_OUT,
    bool reverseIn     = CRC16_CCITT_FALSE_REV_IN,
    bool reverseOut    = CRC16_CCITT_FALSE_REV_OUT,
    crc_size_t yieldPeriod = CRC_YIELD_DISABLED);

[[deprecated("Use calcCRC32() instead")]]
uint32_t crc32(
    const uint8_t *array, crc_size_t length,
    uint32_t polynome  = CRC32_POLYNOME,
    uint32_t initial   = CRC32_INITIAL,
    uint32_t xorOut    = CRC32_XOR_OUT,
    bool reverseIn     = CRC32_REV_IN,
    bool reverseOut    = CRC32_REV_OUT,
    crc_size_t yieldPeriod = CRC_YIELD_DISABLED);

[[deprecated("Use calcCRC64() instead")]]
uint64_t crc64(
    const uint8_t *array, crc_size_t length,
    uint64_t polynome  = CRC64_POLYNOME,
    uint64_t initial   = CRC64_INITIAL,
    uint64_t xorOut    = CRC64_XOR_OUT,
    bool reverseIn     = CRC64_REV_IN,
    bool reverseOut    = CRC64_REV_OUT,
    crc_size_t yieldPeriod = CRC_YIELD_DISABLED);


//  -- END OF FILE --

