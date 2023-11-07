
[![Arduino CI](https://github.com/RobTillaart/integer24/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/integer24/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/integer24/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/integer24/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/integer24/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/integer24.svg)](https://github.com/RobTillaart/integer24/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/integer24/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/integer24.svg?maxAge=3600)](https://github.com/RobTillaart/integer24/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/integer24.svg)](https://registry.platformio.org/libraries/robtillaart/integer24)


# integer24

Arduino library for the integer24 data types uint24_t and int24_t.


## Description

The integer24 is an **experimental** library to implement support
for the following two 24 bit data types:
- **int24_t**
- **uint24_t**

Version 0.1.0 implements a **typedef** for both types.

Note: AVR does support __uint24 and __int24 which uses only 3 bytes.
This allows an UNO to have ~30% more elements (in theory) in an array
with the same memory usage as an uint32_t array.

This library is only (limited) tested with AVR - UNO.

So use with care.


#### Range

|  platform  |  type      |  minimum    |  maximum   |  notes     |
|:----------:|:----------:|:-----------:|:----------:|:-----------|
|  AVR       |  uint24_t  |  0          |   16777215 |  __uint24  |
|  AVR       |  int24_t   | -8388608    |    8388607 |  __int24   |
|  other     |  uint24_t  |  0          | 4294967296 | uint32_t for now |
|  other     |  int24_t   | -2147483648 | 2147483648 | int32_t for now  |

Note the range for other platforms may change in the future to
those matching AVR.

If other platforms are known to implement (3byte) int24 data types
please let me know so I can add these.


#### Known limitations

- The AVR uint24_t and int24_t cannot be printed without casting.
  - see integer24_explore_printing.ino
- Arduino-CI does not implement __int24 __uint24 so no tests can be done.


## Interface

```cpp
#include "integer24.h"
```


## Future

#### Must

- update documentation
- get hands on experience, especially AVR
- document what is learned.

#### Should

- implement **char \* convert24(int24_t)** and **char \* convert24(uint24_t)**
  - length = 8 + \0 = 9
  - fprintf(buf, "%d", (uint32_t)val); ?
  - char *  itoa ( int value, char * str, int base );
  - see integer24_explore_printing.ino

#### Could

- implement a class for both types
  - implement **printTo()**
  - basic math, comparison, negation, ...

#### Won't 


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

