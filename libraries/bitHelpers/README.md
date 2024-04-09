
[![Arduino CI](https://github.com/RobTillaart/BitHelpers/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/BitHelpers/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/BitHelpers/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/BitHelpers/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/BitHelpers/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/BitHelpers.svg)](https://github.com/RobTillaart/BitHelpers/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/BitHelpers/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/BitHelpers.svg?maxAge=3600)](https://github.com/RobTillaart/BitHelpers/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/BitHelpers.svg)](https://registry.platformio.org/libraries/robtillaart/BitHelpers)


# bitHelpers

Arduino library with functions on bit level.


## Description

This library contains functions to manipulate bits and bit patterns in an 
efficient way. 
For most functions a 8 - 64 bit optimized version exist. 

The library is tested on ESP32 and Arduino UNO but not for all possible values. 
other platforms are expected to work without modification. 
If they don't please file an issue on GitHub.

New bit functions can be added or investigated, please file an issue on GitHub.


#### Related

- https://github.com/RobTillaart/BitArray


## Interface

```cpp
#include "bitHelpers.h"
```

#### BitCount

several implementations to compare performance.

- **uint8_t bitCountReference(uint32_t value)** returns number of bits set in a value.
- **uint8_t bitCountKR(uint32_t value)** Kerningham Ritchie bitCount.
- **uint8_t bitCountArray(uint32_t value)** count per nibble with lookup table.
- **uint8_t bitCountF1(uint32_t value)** SWAG algorithm variant.
- **uint8_t bitCountF2(uint32_t value)** SWAG algorithm variant.

BitCount - fastest version, SWAG algorithm

- **uint8_t  bitCount(uint8_t value)**
- **uint8_t  bitCount(uint16_t value)**
- **uint8_t  bitCount(uint32_t value)**
- **uint8_t  bitCount(uint64_t value)**


#### Reverse

T = uint8_t .. uint64_t

- **T bitReverse(T value)** reverses bits.
- **T nybbleReverse(T value)** reverses nibbles (4 bit) in a uint8_t .. uint64_t.
- **T byteReverse(T value)** reverses bytes (8 bit) in a uint16_t .. uint64_t.
- **T wordReverse(T value)** reverses words (16 bit) in uint32_t and uint64_t.

#### Swap 

swap upper and lower half: uint8_t .. uint64_t. Is like rotate 50%

- **T swap(T value)** 0x12345678 ==> 0x56781234.


#### BitRotate

Rotate Left / Right: uint8_t .. uint64_t
if position larger than # bits original value is returned.

- **T bitRotateLeft(T value, uint8_t position)**
- **T bitRotateRight(T value, uint8_t position)** 


#### BitFlip

BitFlip: uint8_t .. uint64_t  a.k.a toggle
if position larger than # bits original value is returned.

- **T bitFlip(T value, uint8_t position)** flips a single bit at position


#### BitRot

BitRot: uint8_t .. uint64_t

- **T bitRotRef(T value, float chance = 0.5, uint8_t times = 1)** reference implementation.
- **T bitRot(T value, float chance = 0.5, uint8_t times = 1)** random damage to a single bit of a value,
chance = float 0.0 .. 1.0 that one random bit is toggled. 
The times parameter allows to apply this n times.
**bitRot()** is a function that can be used to mimic (single) bit errors in communication protocols.  
*Note: a chance of 50% for 2 uint8_t is not equal to 50% chance for 1 uint16_t.*


#### BitsNeeded

How many bits are needed to store / transmit a number?

- **bitsNeededReference(n)** reference implementation for uint8_t to uint64_t.
- **bitsNeeded(n)** A 'recursive strategy' for uint8_t .. uint64_t provides a fast answer. 


#### BitSet64 et al.

The following functions are made as the normal **bitset()** etcetera do not work for 64 bit.
These functions are optimized for speed for **AVR**, **ESP32** and **ESP8266**. 

- **void bitSet64(uint64_t & x, uint8_t bit)** set bit of uint64_t
- **void bitClear64(uint64_t & x, uint8_t bit)** clear bit of uint64_t
- **void bitToggle64(uint64_t & x, uint8_t bit)** toggle bit of uint64_t
- **void bitWrite64(uint64_t & x, uint8_t bit, uint8_t value)** set bit of uint64_t to 0 or 1
- **void bitRead64(uint64_t & x, uint8_t bit)** reads bit from uint64_t 

Also added are macro versions of these five functions.

- **mbitSet64(x, bit)** set bit of uint64_t
- **mbitClear64(x, bit)** clear bit of uint64_t
- **mbitToggle64(x, bit)** toggle bit of uint64_t
- **mbitWrite64(x, bit, value)** set bit of uint64_t to 0 or 1
- **mbitRead64(x, bit)** reads bit from uint64_t 


## Future

#### Must

- improve documentation
- improve readability of code

#### Should

- add performance tests
- **bitRotateLeftRight()** should it do modulo position?
- **bitsNeededRef()** correct for value 0?
- **nybbleReverse()** => **nibbleReverse()**


#### Could

- besides **bitRot()** one can also have timing issues when clocking in bits. 
A function could be created to mimic such timing error, by shifting bits from a 
specific position. e.g. 
- **parShiftLeft(00001010, 3)** ==> 00011010
- **bitBurst(00000000, 3)** ==>  00111000 any group of 3 bits will toggle. edges?
- **bitRot(value, chance = 50%, times = 1)** extension...
- **bitNoggle(value, bit)** - toggle all but one bit. (why?)
- **bitSort(value)** 00101001 ==> 00000111
or with minimal # toggles?
- **bitReverse(uint32_t x, uint8_t n)** see below.
- **byteReverse24(uint32_t x)** dedicated 24 bit = 3 bytes e.g RGB ==> BGR
- **byteRotate24(uint32_t x)** dedicated 24 bit = 3 bytes e.g RGB
- **byteInverse(uint32_t x)** (a,b,c,d) => (255-a, 255-b, 255-c, 255-d) = rather simple ~?
- **isBitPalindrome()** byte, word ...
- **bitSwap(value, p, q)** 
- many more :)


#### Wont


## ideas

#### BitReverse n bit number

Trick to reverse a number of n bits  ( 0 < n < 32 ).
Could also be done similar with 64 bit and or byte / nibble reverse.

not as fast as a dedicated version.
```cpp
uint32_t bitReverse(uint32_t x, uint8_t n)
{
  uint32_t r = bitReverse(x);
  return r >> (32 - n);       // reverse only top n bits.
}
```
Could be added in next release...

Q: what to do with the first (32-n) bits?
Just reverse the last 24 bits and clear bit 24-31 is different than
reversing the last 24 bits and keep bit 24-31 as is.
```cpp
uint32_t bitReverse(uint32_t x, uint8_t n)
{
  uint32_t y = (x >> n) << n;
  uint32_t r = bitReverse(x);
  r >>= (32 - n);
  return y | r;
}
```


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

