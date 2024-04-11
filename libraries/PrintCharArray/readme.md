
[![Arduino CI](https://github.com/RobTillaart/PrintCharArray/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PrintCharArray/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PrintCharArray/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PrintCharArray/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PrintCharArray/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/PrintCharArray.svg)](https://github.com/RobTillaart/PrintCharArray/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PrintCharArray/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PrintCharArray.svg?maxAge=3600)](https://github.com/RobTillaart/PrintCharArray/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/PrintCharArray.svg)](https://registry.platformio.org/libraries/robtillaart/PrintCharArray)


# PrintCharArray

Arduino library to print to a char array. 


## Description

PrintCharArray is a class that implements the Print interface and an internal char array. 
It will effectively buffer a number of print statements and allows it to be printed or 
processed (for real) later. 
The internal buffer can be set in the constructor and has a minimum of 20 bytes and
a maximum of 250 bytes. Default size is 100 bytes.

Applications
- Buffer slowly generated data, and send it with minimum time between bytes.
  Use it e.g. for faster printing to SD card or Ethernet which can handle larger buffers.
- print to buffer to see how many chars the output will be.
  - use to prevent "display line overflow" (e.g. floats).
  - use to right align output (see examples).

#### Template class 

Since 0.4.0 the library has a template class too - Thanks to me21.
See also issue #7.

This template class is called PrintCharArrayT for now.

The interface and functionality is similar (except constructor).
Performance is similar, footprint is smaller on AVR (no malloc lib).
The space needed will not be dynamically allocated (stack iso heap).

```
printCharArray4.ino = 3532 bytes. global var use 422 bytes.
printCharArray4_template.ino = 2840 bytes. global var use 627 bytes.
```

This template version needs more testing, so labelled **experimental** for now.


#### Related

- https://github.com/RobTillaart/PrintCharArray captures data in a char array buffer.
- https://github.com/RobTillaart/PrintSize counts length of a number of print commands.
- https://github.com/RobTillaart/PrintString captures data in a String.


## Interface

```cpp
#include "PrintCharArray.h"
```

- **PrintCharArray(uint8_t size = 100)** constructor, default size of 100 bytes. 
- **size_t write(uint8_t c)** workhorse I of Print interface.
- **size_t write(uint8_t \* str, uint8_t length)** workhorse II of Print interface.
- **void clear()** wipes the internal buffer.
- **int available()** shows how much space is left in the internal buffer.
Replaces free().
- **int size()** current usage of the buffer.
- **int bufSize()** size of the whole buffer. 
Recall that a char array must have a '\0' delimiter.
- **char \* getBuffer()** to access the buffer.


## Interface template version

- **PrintCharArrayT<int BUFSIZE>** constructor, no default size.

Remaining interface is identical.


## Operation

See examples.


## Future

#### Must

- documentation

#### Should

- testing
  - platforms
  - template version

#### Could

- examples
  - inject spaces in "middle align" example? possible?
  - rename size() => length()
  - rename bufSize() => size() ? ambiguous renaming.
  - add real live examples.
- **size_t repeat(uint8_t length, uint8_t c)** convenience function for alignment.
- add error flag


#### Wont

- move code to .cpp file


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


