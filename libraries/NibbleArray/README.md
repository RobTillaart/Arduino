
[![Arduino CI](https://github.com/RobTillaart/nibbleArray/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/nibbleArray/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/nibbleArray.svg?maxAge=3600)](https://github.com/RobTillaart/nibbleArray/releases)


# nibbleArray

Arduino library for a compact array of nibbles (4 bit units)


## Description

A nibble is a 4 bit element, which can hold a value 0..15 (0..F in HEX). It can be seen as an **uint4_t** type.

The nibbleArray is an array that stores 2 nibbles in a byte therefor it is 
twice as small as a normal array.

The current implementation can hold 510 elements. This is due a limitation of
the UNO which can alloc max 255 bytes in one **malloc()** call.

This **NIBBLEARRAY_MAXSIZE** can be defined compiletime "-D NIBBLEARRAY_MAXSIZE" 
or one can adjust it in the library if other platforms can allocate more memory.


## Interface

The interface of the nibbleArray is straightforward:

- **nibbleArray(uint16_t size)** constructor
- **set(index, value)** set a value in the nibbleArray, index must be in range
otherwise 0xFF will be returned.
- **get(index)** get value from index, index must be in range 
otherwise 0xFF will be returned
- **size()** returns the size of the array.
- **clear()** set all elements to 0;
- **SetAll(value)** set all elements to value (0..15)


## Operation

See examples


## Todo

- todo's to issues
- implement NIBBLEARRAY_ERROR_VALUE for set and setAll ??
- allow larger allocations for non AVR, how?
- setAll( f() ) - fill the array by calling a function n times?
- align interface with boolArray and bitArray.

