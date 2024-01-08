
[![Arduino CI](https://github.com/RobTillaart/IEEE754tools/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/IEEE754tools/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/IEEE754tools/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/IEEE754tools/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/IEEE754tools/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/IEEE754tools.svg)](https://github.com/RobTillaart/IEEE754tools/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/IEEE754tools/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/IEEE754tools.svg?maxAge=3600)](https://github.com/RobTillaart/IEEE754tools/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/IEEE754tools.svg)](https://registry.platformio.org/libraries/robtillaart/IEEE754tools)


# IEEE754tools

Arduino library to manipulate IEEE754 float numbers fast.


## Description

IEEE754tools.h contains a collection of experimental bit-hacks to speed up 
a number of operations on floating point numbers on the **Arduino UNO**.
These bit-hacks started in 2010 (oldest code found), maybe even earlier.


#### Related 

- http://en.wikipedia.org/wiki/Double_precision
- http://en.wikipedia.org/wiki/Single-precision_floating-point_format
- https://github.com/RobTillaart/float16
- https://github.com/RobTillaart/printHelpers (to print scientific format float).


## WARNING

- **do not use** this lib for production code unless you verified the correctness.
Code is experimental, so use with care at your own risk.
- If you don't need micro-second speed ups **do not use** these code snippets.
- **do not use for ESP32** ESP32 does things differently ==> not all code works.


## Test results examples 

updated for 0.2.2

| example       |  UNO   |  ESP32  |
|:--------------|:------:|:-------:|
| fastNegate    |   Y    |    Y    |
| float2Double  |   Y    |    N    |
| IEEE754_equal |   Y    |    N    |


ESP32 - needs investigation as UNO verified code fails.
(something for a long winter)


## Interface

```cpp
#include "IEEE754tools.h"
```

See .h file for details.


## Operations

See examples


## Future

#### Must

- improve documentation
- test with double
- test on ESP23

#### Should

- investigate other speed ups
- bring more structure in this library

#### Could

- write more examples
  - example binary transfer over Serial
  - example binary transfer over Ethernet

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

