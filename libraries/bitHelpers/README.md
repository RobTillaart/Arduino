
[![Arduino CI](https://github.com/RobTillaart/bitHelpers/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/bitHelpers/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/bitHelpers/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/bitHelpers/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/bitHelpers/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/bitHelpers/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/bitHelpers.svg?maxAge=3600)](https://github.com/RobTillaart/bitHelpers/releases)


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


## Interface


### 0.1.0

BitCount, several implementations to compare performance.

- **uint8_t bitCountReference(uint32_t value)** returns number of bits set in a value.
- **uint8_t bitCountKR(uint32_t value)** Kerningham Ritchie bitCount.
- **uint8_t bitCountArray(uint32_t value)** count per nybble with lookup table.
- **uint8_t bitCountF1(uint32_t value)** SWAG algorithm variant.
- **uint8_t bitCountF2(uint32_t value)** SWAG algorithm variant.

BitCount - fastest version, SWAG algorithm

- **uint8_t  bitCount(uint8_t value)** available for 16, 32 and 64 bit.

Reverse: uint8_t .. uint64_t

- **T bitReverse(T value)** reverses bits in a uint8_t .. uint64_t.
- **T nybbleReverse(T value)** reverses nibbles (4 bit) in a uint8_t .. uint64_t.
- **T byteReverse(T value)** reverses bytes (8 bit) in a uint16_t .. uint64_t.
- **T wordReverse(T value)** reverses words (16 bit) in uint32_t and uint64_t.

Swap upper and lower half: uint8_t .. uint64_t.

- **T swap(T value)** 0x12345678 ==> 0x56781234.

Rotate Left / Right: uint8_t .. uint64_t
if pos larger than # bits original value is returned.

- **T bitRotateLeft(T value, uint8_t pos)**
- **T bitRotateRight(T value, uint8_t pos)** 

BitFlip: uint8_t .. uint64_t  a.k.a toggle
if pos larger than # bits original value is returned.

- **T bitFlip(T value, uint8_t pos)** flips a single bit at pos

BitRot: uint8_t .. uint64_t

- **T bitRot(T value, float chance = 0.5, uint8_t times = 1)** random damage to a single bit of a value,
chance = float 0.0 .. 1.0 that one random bit is toggled. 
The times parameter allows to apply this n times.
**bitRot()** is a function that can be used to mimic single bit errors in communication protocols.  
*Note: a chance of 50% for 2 uint8_t is not equal to 50% chance for 1 uint16_t.*


### 0.1.1 added

How many bits are needed to store / transmit a number?

- **bitsNeededReference(n)** reference implementation for uint8_t to uint64_t.
- **bitsNeeded(n)** A 'recursive strategy' for uint8_t .. uint64_t provides a fast answer. 

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


### 0.1.2 and beyond

See CHANGELOG.md


## Operations

See examples.


## Future

- improve documentation
- improve readability of code
- add performance tests


#### Functions add

- besides **bitRot()** one can also have timing issues when clocking in bits. 
A function could be created to mimic such timing error, by shifting bits from a 
specific position. e.g. 
- **parShiftLeft(00001010, 3)** ==> 00011010
- **bitBurst(00000000, 3)** ==>  00111000 any group of 3 bits will toggle. edges?
- **bitNoggle(value, bit)** - toggle all but one bit. (why?)
- **bitSort(value)** 00101001 ==> 00000111
or with minimal # toggles?
- **bitReverse(uint32_t x, uint8_t n)**
- **byteReverse24(uint32_t x)** dedicated 24 bit = 3 bytes e.g RGB
- **byteInverse(uint32_t x)** (a,b,c,d) => (255-a, 255-b, 255-c, 255-d) = rather simple ~?
- **isBitPalindrome()** byte, word ...
- **bitSwap(value, p, q)** 


#### Functions fix

- **bitRotateLeftRight()** should it do modulo pos?
- **bitsNeededRef()** correct for value 0?


#### BitReverse n bit number

Trick to reverse a number of n bits  ( 0 < n < 32 ).
Could also be done similar with 64 bit and or byte / nibble reverse.

not as fast as a dedicated version.
```cpp
uint32_t bitReverse(uint32_t x, uint8_t n)
{
  uint32_t r = bitReverse(x);
  return r >> (32 - n);
}
```
Could be added in next release...

Q: what to do with the first (32-n) bits?
Just reverse the last 24 bits and clear bit 24-31 is different than
reversing the last 24 bits and keel bit 24-31 as is.
```cpp
uint32_t bitReverse(uint32_t x, uint8_t n)
{
  uint32_t y = (x >> n) << n;
  uint32_t r = bitReverse(x);
  r >>= (32 - n);
  return y | r;
}
```

