#pragma once
//
//    FILE: bitHelpers.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.12
//    DATE: 2015-11-07
// PURPOSE: Arduino library with functions on bit level
//     URL: https://github.com/RobTillaart/bitHelpers


#include "Arduino.h"


#define BITHELPER_LIB_VERSION         (F("0.1.12"))


//  used by bitRot()
//  power of 2 gives better uniform distribution in the last bits
#define BH_BIG_NR                     (1073741824)


////////////////////////////////////////////////
//
//  BIT COUNT TEST
//
uint8_t bitCountReference(uint32_t value);

uint8_t bitCountKR(uint32_t value);

uint8_t bitCountArray(uint32_t value);

uint8_t bitCountF1(uint32_t value);

uint8_t bitCountF2(uint32_t value);


////////////////////////////////////////////////
//
//  BIT COUNT
//
uint8_t bitCount(uint8_t value);

uint8_t bitCount(uint16_t value);

uint8_t bitCount(uint32_t value);

uint8_t bitCount(uint64_t value);


////////////////////////////////////////////////
//
//  BIT REVERSE
//
uint8_t bitReverse(uint8_t value);

uint16_t bitReverse(uint16_t value);

uint32_t bitReverse(uint32_t value);

uint64_t bitReverse(uint64_t value);


////////////////////////////////////////////////
//
//  NYBBLE REVERSE
//
uint8_t nybbleReverse(uint8_t value);

uint16_t nybbleReverse(uint16_t value);

uint32_t nybbleReverse(uint32_t value);

uint64_t nybbleReverse(uint64_t value);


////////////////////////////////////////////////
//
//  BYTE REVERSE
//
uint16_t byteReverse(uint16_t value);

uint32_t byteReverse(uint32_t value);

uint64_t byteReverse(uint64_t value);


////////////////////////////////////////////////
//
//  WORD REVERSE
//
uint32_t wordReverse(uint32_t value);

uint64_t wordReverse(uint64_t value);


////////////////////////////////////////////////
//
//  SWAP HI LO
//
uint8_t swap(uint8_t value);

uint16_t swap(uint16_t value);

uint32_t swap(uint32_t value);

uint64_t swap(uint64_t value);


////////////////////////////////////////////////
//
//  BIT ROTATE LEFT
//
uint8_t bitRotateLeft(uint8_t value, uint8_t position);

uint16_t bitRotateLeft(uint16_t value, uint8_t position);

uint32_t bitRotateLeft(uint32_t value, uint8_t position);

uint64_t bitRotateLeft(uint64_t value, uint8_t position);


////////////////////////////////////////////////
//
//  BIT ROTATE RIGHT
//
uint8_t  bitRotateRight(uint8_t value, uint8_t position);

uint16_t bitRotateRight(uint16_t value, uint8_t position);

uint32_t bitRotateRight(uint32_t value, uint8_t position);

uint64_t bitRotateRight(uint64_t value, uint8_t position);


////////////////////////////////////////////////////
//
//  BIT FLIP
//
uint8_t bitFlip(uint8_t value, uint8_t position);

uint16_t bitFlip(uint16_t value, uint8_t position);

uint32_t bitFlip(uint32_t value, uint8_t position);

uint64_t bitFlip(uint64_t value, uint8_t position);


////////////////////////////////////////////////////
//
//  BIT ROT
//
uint8_t bitRotRef(uint8_t value, float chance = 0.5);

uint16_t bitRotRef(uint16_t value, float chance = 0.5);

uint32_t bitRotRef(uint32_t value, float chance = 0.5);

uint64_t bitRotRef(uint64_t value, float chance = 0.5);


uint8_t bitRot(uint8_t value, float chance = 0.5, uint16_t times = 1);

uint16_t bitRot(uint16_t value, float chance = 0.5, uint16_t times = 1);

uint32_t bitRot(uint32_t value, float chance = 0.5, uint16_t times = 1);

uint64_t bitRot(uint64_t value, float chance = 0.5, uint16_t times = 1);


////////////////////////////////////////////////////
//
//  BIT-SET64 -CLEAR64 -TOGGLE64 -READ64 -WRITE64
//
//  MACROS
//  only 64 bit data types are handled 64 bit.
#define mbitSet64(value, bit)    ((value) |=  (sizeof(value)<5?1UL:1ULL) <<(bit))
#define mbitClear64(value, bit)  ((value) &= ~(sizeof(value)<5?1UL:1ULL) <<(bit))
#define mbitToggle64(value, bit) ((value) ^=  (sizeof(value)<5?1UL:1ULL) <<(bit))

#define mbitRead64(value, bit) ( ((value) &  ((sizeof(value)<5?1UL:1ULL) <<(bit))) ? 1 : 0)
#define mbitWrite64(value, bit, bitvalue) (bitvalue ? mbitSet64(value, bit) : mbitClear64(value, bit))


//  FUNCTIONS

void bitSet64(uint64_t & x, uint8_t n);

void bitClear64(uint64_t & x, uint8_t n);

void bitToggle64(uint64_t & x, uint8_t n);

uint8_t bitRead64(uint64_t & x, uint8_t bit);

void bitWrite64(uint64_t & x, uint8_t bit, uint8_t value);


////////////////////////////////////////////////////
//
//  BITS NEEDED
//

//  reference
uint8_t bitsNeededRef(uint64_t x);

//  workers
uint8_t bitsNeeded(uint8_t x);

uint8_t bitsNeeded(uint16_t x);

uint8_t bitsNeeded(uint32_t x);

uint8_t bitsNeeded(uint64_t x);


//  -- END OF FILE --

