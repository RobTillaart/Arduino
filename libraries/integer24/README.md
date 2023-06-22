
[![Arduino CI](https://github.com/RobTillaart/integer24/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/integer24/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/integer24/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/integer24/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/integer24/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/integer24/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/integer24.svg?maxAge=3600)](https://github.com/RobTillaart/integer24/releases)


# integer24

Arduino library for the integer24 data types uint24_t and int24_t.


## Description

The integer24 is an **experimental** library to implement support
for the following two 24 bit data types:
- **int24_t**
- **uint24_t**

Version 0.1.0 implements a **typedef** for both types.

Note: AVR does support __uint24 and __int24 which uses only 3 bytes.
This allows an UNO to have 30% more elements (in theory).


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
- Arduino-CI does not implement __int24 __uint24 so no tests can be done.


## Future

#### Must

- get hands on experience, especially AVR

#### Should

- improve documentation

#### Could

- implement a class for both types?
  - implement **printTo()**

#### Won't 

