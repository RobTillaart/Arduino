
[![Arduino CI](https://github.com/RobTillaart/BitArray/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/BitArray/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/BitArray/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/BitArray/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/BitArray/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/BitArray.svg)](https://github.com/RobTillaart/BitArray/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/BitArray/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/BitArray.svg?maxAge=3600)](https://github.com/RobTillaart/BitArray/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/BitArray.svg)](https://registry.platformio.org/libraries/robtillaart/BitArray)


# BitArray

Arduino library for compact array of objects with a size expressed in bits, typically 1..10.


## Description

The BitArray class allows the user to instantiate an array of elements, each of the same size in bits.
For example one could create an array of 100 throws with a dice. Normally this would take 100 bytes,
but BitArray can store one throw in 3 bits, so 100 throws in approx 40 bytes.
Another example is to store multiple 10 bit analogRead() values efficiently.

The class is optimized for storage and takes care of efficiently packing the elements 
into multiple bytes, and byte borders. Depending where an element is located writing and reading
can take more time. You need to check if your application needs more performance than
this library can deliver. 

#### Related

The BitArray library is one from a set of three:

- https://github.com/RobTillaart/BitArray for elements of user defined size in bits (values 0 .. 2^n-1).
- https://github.com/RobTillaart/BoolArray for elements of 1 bit (values 0 .. 1).
- https://github.com/RobTillaart/nibbleArray for elements of 4 bits or smaller (values 0 .. 15).


#### Notes

The BitArray class allocates dynamic memory, so called BA_SEGMENTS, 
each of 200 bytes.
As the memory size of different processors differ the maximum amount of SEGMENTS 
depends on architecture.

The library is tested on AVR architecture only.


## Interface

```cpp
#include "BitArray.h"

```

#### Constructor

- **BitArray()** Constructor
- **~BitArray()** Destructor, frees dynamic memory
- **uint8_t begin(const uint8_t bits, const uint16_t size)** Frees memory used and allocates the memory requested. 
The maximum number of elements is 65535 if memory allows, 
the maximum element size is 32.

Better names could be **bits == elementSize** and **size == elementCount**.


#### Admin

- **uint16_t capacity()** idem.
- **uint16_t memory()** idem.
- **uint16_t bits()** idem.
- **uint16_t segments()** idem.
- **uint8_t  getError()** idem.


#### base functions

- **void clear()** sets all elements to 0.
- **uint32_t get(const uint16_t index)** gets the value of the element at index.
- **uint32_t set(const uint16_t index, uint32_t value)** sets index to value.
Overwrites existing value.
Returns value.
- **void setAll(uint32_t value)** sets whole array to value.
- **uint32_t toggle(const uint16_t index)** toggles value at index.
Return value is maxValue (debug info).


## Future

#### Must


#### Should

- testing.
- is returning value in **set()** needed? (0.3.0)
  - as value is a parameter **void** seems good enough.
- return value **toggle()** could be new value? (0.3.0)
  - code prep is working (commented for now)
- naming parameters ** begin()** (0.3.0)


#### Could

- functional examples.
- investigate element size of 64 (for doubles) and beyond.
- move code to .cpp (0.3.0)


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


