#pragma once
//
//    FILE: randomHelpers.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.7
// PURPOSE: Arduino library with helper function for faster random bits
//     URL: https://github.com/RobTillaart/randomHelpers


#include "Arduino.h"

#define RANDOM_HELPERS_VERSION                (F("0.2.7"))


//  the idea is to have one buffer ( __randomBuffer) which holds 32 random bits.
//  Every call fetches bits from that buffer and if it does not hold enough
//  bits any more it fills the buffer first. This way the relative expensive
//  calls to random() which produces a 32 bit number are minimized in an
//  efficient way.
//
//  TBD: put it in a class ?


///////////////////////////////////////////////////////////////////////////
//
//  An example of a simple pseudo-random number generator is the
//  Multiply-with-carry method invented by George Marsaglia.
//  it has two initializers (not zero) which can be changed
//  to seed the generator.
//

uint32_t Marsaglia();

bool seedMarsaglia(uint32_t a, uint32_t b);

bool getRandom1();

uint8_t getRandom2();

uint8_t getRandom3();

uint8_t getRandom4();

uint8_t getRandom5();

uint8_t getRandom6();

uint8_t getRandom7();

uint8_t getRandom8();

uint16_t getRandom16();

uint32_t getRandom24();

uint32_t getRandom32();

uint64_t getRandom64();


/////////////////////////////////////////////////
//
//  TYPICAL USES
//
bool inline flipCoin();  //  0..1

uint8_t throwDice();     //  1..6



/*
//  works well for 1..16; but above it is worse
uint32_t getRandomBits(uint8_t n)
{
  if (__randomIdx < n)
  {
    __randomBuffer = getRandom32();
    __randomIdx = 32;
  }
  uint32_t rv = __randomBuffer & ((1UL << n) - 1);
  __randomBuffer >>= n;
  __randomIdx -= n;
  return rv;
}
*/


//  n = 1..31
//  TODO: performance gain too low for n > 16
uint32_t getRandomBits(uint8_t n);


//  -- END OF FILE --

