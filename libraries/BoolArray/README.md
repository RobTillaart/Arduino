
[![Arduino CI](https://github.com/RobTillaart/BoolArray/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/BoolArray/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/BoolArray/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/BoolArray/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/BoolArray/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/BoolArray.svg)](https://github.com/RobTillaart/BoolArray/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/BoolArray/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/BoolArray.svg?maxAge=3600)](https://github.com/RobTillaart/BoolArray/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/BoolArray.svg)](https://registry.platformio.org/libraries/robtillaart/BoolArray)


# BoolArray

Arduino library for compact array of booleans of max size 2000 (UNO).


## Description

The BoolArray class allows the user to instantiate an array of booleans, allocating only one bit per element. 
For example one could create an array of 1000 throws with a coin. Normally this would take 1000 bytes,
but BoolArray can store one throw in 1 bit, so 1000 throws in approx 125 bytes.

The class is optimized for storage by packing 8 elements of the array in one byte.
You need to check if your application needs more performance than this library can deliver. 

#### Notes

The BoolArray class allocates dynamic memory.
The **BOOLARRAY_MAXSIZE** is set to 10000 (booleans). 
This number is chosen as it is about the maximum one can allocate in one call on an UNO. 

If one want to allocate more booleans, adjust the **BOOLARRAY_MAXSIZE**. 
This can be done as a command line option.

The library is tested on AVR architecture only.


#### BoolArray32

Since 0.3.0 a **BoolArray32** class is added - **experimental** for now.

Where the **BoolArray** class can have max 65535 booleans, the **BoolArray32** class
has a 32 bit interface allowing up to 4 billion++ booleans in theory. 
Although most IOT devices would not have enough memory, it allows one to have more than
65535 booleans. 

Also it might be that the **BoolArray32** class is faster on some platforms
that are native 32 bit (not verified yet). 
On an Arduino UNO the **BoolArray32** class is slower.(verified).


#### Related

The BitArray library is one from a set of three:

- https://github.com/RobTillaart/BitArray for elements of user defined size in bits (values 0 .. 2^n-1).
- https://github.com/RobTillaart/BoolArray for elements of 1 bit (values 0 .. 1).
- https://github.com/RobTillaart/nibbleArray for elements of 4 bits or smaller (values 0 .. 15).


BoolArray is faster than BitArray as it only supports single bits and does not need to merge parts
of different bytes to read/write a value. However BoolArray currently only supports 2000 bits while
BitArray can support more.

## Performance

See **boolArrayDemo0.ino**

Indicative performance figures.

|  class        |  function   |  UNO    |  ESP32   |  Notes   |
|:--------------|:-----------:|:-------:|:--------:|:--------:|
|  BoolArray    |  set(0)     |  10.37  |          |  
|  BoolArray    |  set(1)     |  10.25  |          |
|  BoolArray    |  get(i)     |  16.03  |          |
|  BoolArray    |  setAll(0)  |    96   |          |  per 2000
|  BoolArray    |  setAll(1)  |   100   |          |  per 2000
|               |             |         |          |
|  BoolArray32  |  set(0)     |  15.97  |          |
|  BoolArray32  |  set(1)     |  15.84  |          |
|  BoolArray32  |  get(i)     |  24.20  |          |
|  BoolArray32  |  setAll(0)  |   148   |          |  per 2000
|  BoolArray32  |  setAll(1)  |   144   |          |  per 2000

- UNO 16 MHz, ESP32 240 MHz.
- toggle() is expected to be similar to set()
- clear() is a wrapper around setAll(0) so similar.


## Interface

```cpp
#include "BoolArray.h"
```

#### Constructor

- **BoolArray()** Constructor
- **~BoolArray()** Destructor
- **uint8_t begin(uint32_t size)** dynamically allocates size elements (8 booleans in one byte). 
Returns **BOOLARRAY_OK** on success.

#### Meta

- **uint16_t size()** returns number of boolean elements.
- **uint16_t memory()** returns number of bytes used.

#### Base

The following functions return **BOOLARRAY_OK** on success.

- **uint8_t setAll(uint8_t value)** Sets all elements to false (0) or true (all other values).
- **uint8_t clear()** Sets all elements to false.
- **uint8_t get(uint16_t index)** Return 0 or 1 OR an error value which can be interpreted as true. 
So one need to check these carefully.
- **uint8_t set(uint16_t index, uint8_t value)** Set the element to false (0) or true (all other values).
- **uint8_t toggle(uint16_t index)** Toggles element at index. 


## Future

#### Must

- improve documentation
  - add performance figures (UNO + ESP32)

#### Should

- performance test on ESP32
- performance for **clear()** dedicated loop vs **setAll(0)** call
- investigate template class 
  - improve allocation (see PrintCharArray)

#### Could

- update examples.
- investigate **uint32_t array[N]** for BoolArray32 (ESP32?)
  - adjust math 

#### Wont

- performance intern 16 bit instead of 8 bit is NOT faster on UNO


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

