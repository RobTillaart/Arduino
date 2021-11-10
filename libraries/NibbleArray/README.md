
[![Arduino CI](https://github.com/RobTillaart/nibbleArray/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/nibbleArray/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/nibbleArray/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/nibbleArray/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/nibbleArray/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/nibbleArray/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/nibbleArray.svg?maxAge=3600)](https://github.com/RobTillaart/nibbleArray/releases)


# nibbleArray

Arduino library for a compact array of nibbles (4 bit units).


## Description

A nibble is a 4 bit element, which can hold a value 0..15 (0..F in HEX). 
It can be seen as an **uint4_t** type.

The nibbleArray is an array that stores 2 nibbles in a byte therefore it is 
twice as small as a normal array.

The current implementation can hold 510 elements. This is due a limitation of
the UNO which can **alloc** max 255 bytes in one **malloc()** call.

This **NIBBLEARRAY_MAXSIZE** can be defined compile time "-D NIBBLEARRAY_MAXSIZE" 
or one can adjust it in the library if other platforms can allocate more memory.


## Interface

The interface of the nibbleArray is straightforward:

- **nibbleArray(uint16_t size)** constructor
- **uint8_t set(uint16_t index, uint8_t value)** set a value in the nibbleArray.
Index must be in range otherwise 0xFF = NIBBLEARRAY_ERROR_INDEX will be returned.
If value > 15 it will be truncated. 
- **uint8_t get(uint16_t index)** get value from the nibbleArray. 
Index must be in range otherwise 0xFF = NIBBLEARRAY_ERROR_INDEX will be returned.
- **uint16_t size()** returns the size of the array.
- **uint16_t memory()** returns the memory used in bytes.
- **void clear()** set all elements to 0.
- **void SetAll(uint8_t value)** set all elements to value (0..15). 
If value > 15 it will be truncated.


## Operation

See examples


## Future

#### must

- align interface with boolArray and bitArray.
  - is there some base class?
  - align error codes.
- add a begin() function that does the work now done in constructor
- allow larger allocations for non AVR, how?
  - don't test for size, user responsibility?


#### could

- implement NIBBLEARRAY_ERROR_VALUE for set and setAll ??
  - for now user responsibility.


#### won't

- setAll( f() ) - fill the array by calling a function n times?

