
[![Arduino CI](https://github.com/RobTillaart/PrintString/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PrintString/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PrintString/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PrintString/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PrintString/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PrintString/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PrintString.svg?maxAge=3600)](https://github.com/RobTillaart/PrintString/releases)


# PrintString

Arduino library to print to a String.


## Description

PrintString is a class that buffers a number of print statements in a String.
This String can be requested to process later.

- buffer slowly generated data, and send it with minimum time between bytes
  e.g. to maximize packets for Ethernet.
- print to buffer to see how many chars the output is;
  use to prevent "display line overflow"
  (e.g. floats)

There is a relation to https://github.com/RobTillaart/PrintCharArray


## Interface

- **PrintString()** constructor.
- **size_t write(uint8_t c)** workhorse I of Print interface.
- **size_t write(uint8_t \* str, uint8_t length)** workhorse II of Print interface.
- **void clear()** wipes the internal String buffer
- **int size()** current usage of the buffer.
- **String getString()** to access the buffer.


## Operational

See examples


## Future

- testing
- add examples
- rename examples
- add functions like **repeat(char c)** to inject e.g. 7 spaces etc.
- add error flag
- 
