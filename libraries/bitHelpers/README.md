
[![Arduino CI](https://github.com/RobTillaart/bitHelpers/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/bitHelpers/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/bitHelpers.svg?maxAge=3600)](https://github.com/RobTillaart/bitHelpers/releases)


# bitHelpers

Arduino library with functions on bit level

## Description

This library contains functions to manipulate bits and bitpatterns in an 
efficient way. 
For most functions a 8 - 64 bit optimized version exist. 

The library is tested on ESP32 and Arduino UNO but not for all possible values. 
other platforms are expected to work without modification. 
If they don't please let me know.

New bit functions can be added or investigated, please post an issue.


## Interface

### 0.1.0
BitCount, several implementations to compare performance.
- **bitCountReference(uint32_t val)** returns nr of bits set in a value.
- **bitCountKR(uint32_t val)** Kerningham bitCount
- **bitCountArray(uint32_t val)** count per nybble with lookup table
- **bitCountF1(uint32_t val)** SWAG algorithm variant
- **bitCountF2(uint32_t val)** SWAG algorithm variant

BitCount - fastest version: uint8_t .. uint64_t
- **bitCount(val)**  

Reverse: uint8_t .. uint64_t
- **bitReverse()**    reverses bits in a uint8_t .. uint64_t
- **nybbleReverse()** reverses nybbles (4 bit) in a uint8_t .. uint64_t
- **byteReverse()**   reverses bytes (8 bit) in a uint16_t .. uint64_t
- **wordReverse()**   reverses words (16 bit) in uint32_t and uint64_t

Swap upper and lower half: uint8_t .. uint64_t
- **swap()** 0x12345678 ==> 0x56781234

Rotate Left / Right: uint8_t .. uint64_t
- **bitRotateLeft(value, pos)**
- **bitRotateRight(value, pos)** 

BitFlip: uint8_t .. uint64_t  a.k.a toggle
- **bitFlip(value, pos)** flips a single bit at pos

BitRot: uint8_t .. uint64_t
- **bitRot(value, chance)** random damage to a single bit of a value, chance = float 0.0 .. 1.0 
that one random bit is toggled. 
**bitRot()** is a function that can be used to mimic single bit errors in communication protocols.  
*Note: a chance of 50% for 2 uint8_t is not equal to 50% chance for 1 uint16_t.*

### 0.1.1 added

How many bits are needed to store / transmit a number?
- **bitsNeededReference(n)** reference implementation for uit to uint64_t.
- **bitsNeeded(n)** A 'recursive strategy' for uint8_t .. uint64_t provides a fast answer. 

The following functions are made as the normal **bitset()** etc do not work for 64 bit.
These functions are optimized for speed for **AVR**, **ESP32** and **ESP8266**. 
- **bitSet64(x, bit)** set bit of uint64_t
- **bitClear64(x, bit)** clear bit of uint64_t
- **bitToggle64(x, bit)** toggle bit of uint64_t
- **bitWrite64(x, bit, value)** set bit of uint64_t to 0 or 1
- **bitRead64(x, bit)** reads bit from uint64_t 

Also added are macro versions of these five functions.
- **mbitSet64(x, bit)** set bit of uint64_t
- **mbitClear64(x, bit)** clear bit of uint64_t
- **mbitToggle64(x, bit)** toggle bit of uint64_t
- **mbitWrite64(x, bit, value)** set bit of uint64_t to 0 or 1
- **mbitRead64(x, bit)** reads bit from uint64_t 

### 0.1.2 added

Added arduino-ci and unit tests


## Future

- besides **bitRot()** one can also have timing issues when clocking in bits. 
A function could be created to mimic such timing error, by shifting bits from a 
specific position. e.g. 
- parShiftLeft(00001010, 4) ==> 00011010
- bitBurst(00000000, 3) ==>  00111000 any group of 3 bits will toggle.
- bitRot(value, chance = 50%, times = 1) extention...
- bitNoggle(value, bit) - toggle all but one bit. (why?)
- bitSort(value) ==> 00101001 ==> 00000111
- many more :)

## Operations

See examples.
