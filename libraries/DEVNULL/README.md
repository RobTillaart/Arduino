
[![Arduino CI](https://github.com/RobTillaart/DEVNULL/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DEVNULL/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DEVNULL/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DEVNULL/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DEVNULL/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DEVNULL.svg)](https://github.com/RobTillaart/DEVNULL/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DEVNULL/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DEVNULL.svg?maxAge=3600)](https://github.com/RobTillaart/DEVNULL/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DEVNULL.svg)](https://registry.platformio.org/libraries/robtillaart/DEVNULL)


# DEVNULL

Arduino library for a /dev/null stream.


## Description

The library implements a stream class that mimics the **/dev/null**
device of a Linux system. You can write everything to it.
You can never read data from it as it always returns EOF (end of file);

The 0.1.0 version is a minimal implementation that can be optimized.
it implements the **write(const uint8_t data)** call and e.g. a float is still
converted to individual characters that are send one after another.
Strings and text send every byte.

The advantage is that printing takes time and e.g. one can use it to measure
the **print** class performance.

Performance can be increased by implementing all methods of the print interface
with only a return 0; (or at least **print(Type)** as the **println(T)** would only
call once extra for the "\n".

Feedback as always is welcome.


### DEVNULL_ENABLE_DEBUG

Since version 0.1.9 (see issue #11) the library has a define

```cpp
//  allows command line overrule
#ifndef DEVNULL_ENABLE_DEBUG
#define DEVNULL_ENABLE_DEBUG    1
#endif
```

This allows to set the **DEVNULL_ENABLE_DEBUG** to zero on the command line or in code.
This will reduce the footprint of the library to a bare minimum.
On AVR (UNO R3, IDE 1.8.19) it saved 1 byte memory and 28 bytes PROGMEM.

Please note that setting **DEVNULL_ENABLE_DEBUG 0** will result in two warnings as the
parameters of the **write()** calls are not used any more.


### Related

- https://github.com/RobTillaart/DEVFULL
- https://github.com/RobTillaart/DEVNULL
- https://github.com/RobTillaart/DEVRANDOM


## Interface

```cpp
#include "DEVNULL.h"
```

### Constructor

- **DEVNULL()** constructor, sets the timeout to zero.

### Stream interface

- **int available()** always return zero.
- **int peek()** always returns EOF.
- **int read()** always return EOF.
- **void flush()** does nothing but keeps some compilers happy.
- **size_t write(const uint8_t data)** implements print interface. returns 1.
- **size_t write( const uint8_t \*buffer, size_t size)** implements print interface.
Returns size.
- **int lastByte()** returns last byte written (debug and test purpose).
Returns -1 if no byte has been written yet.
This function is not available when **DEVNULL_ENABLE_DEBUG 0**
is defined, see above.


## Future

#### Must

#### Should

#### Could

- **flush()** could reset bottomLessPit to -1?

#### Wont

- add byte counter (uint32_t)
  - extended derived class DEVNULL_EXT ?
- investigate if DEVNULL can be used to harvest entropy?
  - to seed random generator.
  - sum xor of all data + timestamp?
  - enable / disable flag (complex)
  - => /dev/entropy class
- add delay to mimic pause / tune behaviour for simulating devices
  - microseconds
  - delay per byte, esp long arrays might need other performance
  - out of scope for /dev/null => separate class?
- implement Print class to increase performance?
  - derived class?


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

