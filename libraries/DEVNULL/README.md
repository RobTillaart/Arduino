
[![Arduino CI](https://github.com/RobTillaart/DEVNULL/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DEVNULL/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DEVNULL/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DEVNULL/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DEVNULL/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DEVNULL/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DEVNULL.svg?maxAge=3600)](https://github.com/RobTillaart/DEVNULL/releases)


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


#### Version 0.1.2

- sets the timeout for reading to 0. No need to wait longer with DEVNULl.
  this improves the **find(...)** calls substantially.
- added **size_t write( const uint8_t \*buffer, size_t size)** for faster string processing.


## Interface

- **DEVNULL()** constructor, sets the timeout to zero.
- **int available()** always return zero.
- **int peek()** always returns EOF.
- **int read()** always return EOF.
- **void flush()** does nothing but keeps some compilers happy.
- **size_t write(const uint8_t data)** implements print interface. returns 1.

0.1.2 added to improve performance a few percent (UNO).

- **size_t write( const uint8_t \*buffer, size_t size)** implements print interface. returns size.


## Operation

Use with care.

See examples.


## Future

- add optional delay to mimic pause / tune behaviour for simulating other devices
  microseconds - milliseconds?
  delay per byte or per call to write? (esp long arrays might need other performance
  feels out of scope for /dev/null
- add byte counter (uint32_t)
- add lastWrittenByte() - look at the last byte written to the bottomless pit.


