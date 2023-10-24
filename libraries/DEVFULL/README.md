
[![Arduino CI](https://github.com/RobTillaart/DEVFULL/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DEVFULL/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DEVFULL/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DEVFULL/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DEVFULL/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DEVFULL.svg)](https://github.com/RobTillaart/DEVFULL/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DEVFULL/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DEVFULL.svg?maxAge=3600)](https://github.com/RobTillaart/DEVFULL/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DEVFULL.svg)](https://registry.platformio.org/libraries/robtillaart/DEVFULL)


# DEVFULL

Arduino library for a /dev/full stream.


## Description

The experimental library implements a stream class that mimics the **/dev/full**
device of a Linux system. You can write nothing to it as it is always full.
Every read data will return the value zero, just like **/dev/zero**.

Calls to **print()** and **println()** will be split up in multiple calls to **write()**.
This causes a return value of n x -28 ==> mostly a number in the 65xxx range

See - https://en.wikipedia.org/wiki//dev/full


#### Related

- https://github.com/RobTillaart/DEVFULL
- https://github.com/RobTillaart/DEVNULL
- https://github.com/RobTillaart/DEVRANDOM


## Interface

```cpp
#include "DEVFULL.h"
```

- **DEVFULL()** constructor, sets the timeout to zero.
- **int available()** always return INT_MAX = platform dependant.
- **int peek()** always returns 0.
- **int read()** always returns 0.
- **void flush()** does nothing but keeps some compilers happy.
- **size_t write(const uint8_t data)** always returns -28 (ENOSPC).
- **size_t write(const uint8_t \*buffer, size_t size)** implements print interface. 
Always returns -28 (ENOSPC).


## Error code

| value | name    | description |
|:------|:--------|:------------|
| -28   | ENOSPC  | No space available for writing onto the "storage device". |



## Operation

Use with care.

See examples.


## Future

#### Must

- improve documentation

#### Should

- improve code
- test different platforms.

#### Could

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

