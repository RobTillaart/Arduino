
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
but BitArray can store one throw in 3 bits, so 100 throws in approx 40 bytes (some overhead)
Another example is to store multiple 10 bit analogRead() values efficiently.
Normally one need 2 bytes per sample so 20 samples would need 40 bytes, where BitArray would 
only need 25 bytes.

Typical element size is 1..10, the maximum size supported is 32 bits.
For larger objects one has to make an array of those objects (or patch the library).

The BitArray class is optimized for storage and takes care of efficiently packing the elements 
into multiple bytes, and byte borders. Depending where an element is located writing and reading
will take more time. You need to check if your application needs more performance than
this library can deliver.


### Breaking Change 0.3.0

The internal storage structure has been changed (simplified).
The BitArray class is limited to 16 bit math. 
- can allocate a theoretical maximum of 64 KB (elementSize x Count).
- can have a theoretical maximum of 65535 elements

Other changes
- function **bits()** is replaced by **elementSize()**.
- function **segments()** is removed.


**Experimental**

A new BitArray32 class is created if one needs to go beyond the 16 bit math
/ 64 K limits. This is minimal tested yet.


### Related

The BitArray library is one from a set of three:

- https://github.com/RobTillaart/BitArray for elements of user defined size in bits (values 0 .. 2^n-1).
- https://github.com/RobTillaart/BoolArray for elements of 1 bit (values 0 .. 1).
- https://github.com/RobTillaart/nibbleArray for elements of 4 bits or smaller (values 0 .. 15).


### Notes

The BitArray class allocates dynamic memory in a byte array when calling **begin()**. 
When calling **begin()** again, it will free the allocated memory and allocate new.

Note that this can lead to fragmented memory or allocation failures. So one should
check the return value of **begin()** if allocation succeeded.


## Interface

```cpp
#include "BitArray.h"
```

The **BitArray32()** has a similar interface, although parameter and return types are 32 bit
where **BitArray()** uses 16 bit types.

### Constructor

- **BitArray()** Constructor.
- **~BitArray()** Destructor, frees dynamic memory.
- **uint8_t begin(const uint8_t elementSize, const uint16_t elementCount)**
Frees memory used and allocates the memory requested. 
The maximum number of elements is 65535 if memory allows, 
the maximum element size is 32.
Returns an error-code or **BA_OK**.


### Administrative

- **uint16_t capacity()** idem.
- **uint16_t memory()** idem.
- **uint16_t elementSize()** idem. (replaces bits())


### Error

- **int getError()** idem.

|  Error                |  value  |  Notes  |
|:----------------------|:-------:|:--------|
|  BA_ERR               |    -1   |
|  BA_OK                |    0    |
|  BA_NO_MEMORY_ERR     |    1    |
|  BA_IDX_RANGE_ERR     |    2    |
|  BA_ELEMENT_SIZE_ERR  |    3    |
|  BA_SIZE_ERR          |    4    |


### base functions

- **int clear()** sets all elements to 0.
- **uint16_t get(const uint16_t index)** gets the value of the element at index.
- **uint16_t set(const uint16_t index, uint32_t value)** sets index to value.
Overwrites existing value.
Returns value.
- **int setAll(uint32_t value)** sets whole array to value.
- **uint16_t toggle(const uint16_t index)** toggles value at index.
Return value is maxValue (debug info).


## Future

#### Must

- improve documentation.

#### Should

- test BitArray()
- test BitArray32().

#### Could

- add more functional examples.
- rename internal variables to match API
- investigate element size of 64 (for doubles) and beyond.


#### Wont

- move code to .cpp


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


