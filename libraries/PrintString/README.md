
[![Arduino CI](https://github.com/RobTillaart/PrintString/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PrintString/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PrintString.svg?maxAge=3600)](https://github.com/RobTillaart/PrintString/releases)


# PrintString

Arduino library to print to a String


## Description

PrintString is a class that buffers a number of print statements in a String.
This String can be requested to process later.

- buffer slowly generated data, and send it with minimum time between bytes
  e.g. to maximize packets for ethernet
- print to buffer to see how many chars the output is;
  use to prevent "display line overflow"
  (e.g. floats)


## Interface

- **PrintString()** constructor
- **size_t write(uint8_t c)** workhorse of Print interface.
- **void clear()** wipes the internal String buffer
- **int size()** current usage of the buffer
- **String getString()** to access the buffer.


## Operational

See examples
