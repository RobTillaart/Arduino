#pragma once
//
//    FILE: CrcFastReverse.h
//  AUTHOR: vovagorodok
// PURPOSE: Arduino class for CRC
//     URL: https://github.com/RobTillaart/CRC


#include "Arduino.h"

uint8_t reverse8bits(uint8_t in);
uint16_t reverse16bits(uint16_t in);
uint16_t reverse12bits(uint16_t in);
uint32_t reverse32bits(uint32_t in);
uint64_t reverse64bits(uint64_t in);

[[deprecated("Use reverse8bits() instead")]] uint8_t reverse8(uint8_t in);
[[deprecated("Use reverse12bits() instead")]] uint16_t reverse16(uint16_t in);
[[deprecated("Use reverse16bits() instead")]] uint16_t reverse12(uint16_t in);
[[deprecated("Use reverse32bits() instead")]] uint32_t reverse32(uint32_t in);
[[deprecated("Use reverse64bits() instead")]] uint64_t reverse64(uint64_t in);
