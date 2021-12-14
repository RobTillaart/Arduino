
[![Arduino CI](https://github.com/RobTillaart/BoolArray/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/BoolArray/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/BoolArray/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/BoolArray/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/BoolArray/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/BoolArray/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/BoolArray.svg?maxAge=3600)](https://github.com/RobTillaart/BoolArray/releases)


# BoolArray

Arduino library for compact array of booleans of max size 2000 (UNO).


## Description

The BoolArray class allows the user to instantiate an array of booleans, allocating only one bit per element. 
For example one could create an array of 1000 throws with a coin. Normally this would take 1000 bytes,
but BoolArray can store one throw in 1 bit, so 1000 throws in approx 125 bytes.

The class is optimized for storage by packing 8 elements of the array in one byte.
You need to check if your application needs more performance than this library can deliver. 

The BoolArray library is one from a set of three:

- **BitArray**  for elements of user defined size in bits (values 0 .. 2^n-1)
- **BoolArray** for elements of 1 bit (values 0 .. 1)
- **nybbleArray** for elements of 4 bits (values 0 .. 15)

BoolArray is faster than BitArray as it only supports single bits and does not need to merge parts
of different bytes to read/write a value. However BoolArray currently only supports 2000 bits while
BitArray can support more.


## Interface

- **BoolArray()** Constructor
- **~BoolArray()** Destructor
- **uint8_t begin(uint16_t size)** dynamically allocates size elements (8 bools in one byte). Returns **BOOLARRAY_OK** on success.
- **uint16_t size()** returns number of bool elements.
- **uint16_t memory()** returns number of bytes used.
- **uint8_t setAll(uint8_t value)** Sets all elements to false (0) or true (all other values).
- **uint8_t set(uint16_t index, uint8_t value)** Set the element to false (0) or true (all other values).
- **uint8_t get(uint16_t index)** Return 0 or 1 OR an error value which can be interpreted as true. 
So one need to check these carefully.
- **uint8_t toggle(uint16_t index)** Toggles element at index. Returns **BOOLARRAY_OK** on success.
- **uint8_t clear()** Sets all elements to false.


## Operation

Check out the examples.


## Notes

The BoolArray class allocates dynamic memory.
The **BOOLARRAY_MAXSIZE** is set to 2000, this was chosen as **malloc()** can only allocate 255 bytes 
in one call on an UNO. This is not checked with the recent versions of the IDE any more.

The library is tested on AVR architecture only.


## Future

- performance test on ESP32
- performance for **clear()** dedicated loop vs **setAll(0)** call
- update examples.

