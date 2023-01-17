#pragma once
//
//    FILE: CRC.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.3
// PURPOSE: Arduino library for CRC8, CRC12, CRC16, CRC16-CCITT, CRC32, CRC64
//     URL: https://github.com/RobTillaart/CRC
//


#include "Arduino.h"

#include "CRC_polynomes.h"

#define CRC_LIB_VERSION       (F("0.3.3"))


////////////////////////////////////////////////////////////////
//
//  fast reverse from bitHelper library
//
uint8_t reverse8(uint8_t in);

uint16_t reverse16(uint16_t in);

uint16_t reverse12(uint16_t in);

uint32_t reverse32(uint32_t in);

uint64_t reverse64(uint64_t in);



///////////////////////////////////////////////////////////////////////////////////
//
//  static functions for CRC
//

//  CRC POLYNOME = x8 + x5 + x4 + 1 = 1001 1000 = 0x8C
uint8_t crc8(const uint8_t *array, uint16_t length, const uint8_t polynome = 0xD5, const uint8_t startmask = 0x00, const uint8_t endmask = 0x00, const bool reverseIn = false, const bool reverseOut = false);

//  CRC POLYNOME = x12 + x3 + x2 + 1 =  0000 1000 0000 1101 = 0x80D
uint16_t crc12(const uint8_t *array, uint16_t length, const uint16_t polynome = 0x80D, const uint16_t startmask = 0x0000, const uint16_t endmask = 0x0000, const bool reverseIn = false, const bool reverseOut = false);

//  CRC POLYNOME = x15 + 1 =  1000 0000 0000 0001 = 0x8001
uint16_t crc16(const uint8_t *array, uint16_t length, const uint16_t polynome = 0x8001, const uint16_t startmask = 0x0000, const uint16_t endmask = 0x0000, const bool reverseIn = false, const bool reverseOut = false);

//  CRC-CCITT POLYNOME = x13 + X5 + 1 =  0001 0000 0010 0001 = 0x1021
uint16_t crc16_CCITT(uint8_t *array, uint16_t length);

//  CRC-32 POLYNOME =  x32 + ..... + 1
uint32_t crc32(const uint8_t *array, uint16_t length, const uint32_t polynome = 0x04C11DB7, const uint32_t startmask = 0, const uint32_t endmask = 0, const bool reverseIn = false, const bool reverseOut = false);

//  CRC-CCITT POLYNOME =  x64 + ..... + 1
//  CRC_ECMA64 = 0x42F0E1EBA9EA3693
uint64_t crc64(const uint8_t *array, uint16_t length, const uint64_t polynome = 0x42F0E1EBA9EA3693, const uint64_t startmask = 0, const uint64_t endmask = 0, const bool reverseIn = false, const bool reverseOut = false);


//  -- END OF FILE --

