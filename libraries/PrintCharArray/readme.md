
[![Arduino CI](https://github.com/RobTillaart/PrintCharArray/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PrintCharArray/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PrintCharArray.svg?maxAge=3600)](https://github.com/RobTillaart/PrintCharArray/releases)


# PrintCharArray

Arduino library to print to a char array


## Description

PrintCharArray is a class implements the Print interface and an internal char array. 
It will buffer a number of print statements and allows it to be printed or processed 
(for real) later. 
The internal buffer can be set in the constructor and has a minimum of 20 bytes and
a maximum of 250 bytes.

Applications
- buffer slowly generated data, and send it with minimum time between bytes
  use it e.g. for faster printing to SD card or Ethernet.
- print to buffer to see how many chars the output is;
  use to prevent "display line overflow" (e.g. floats)


## Interface

- **PrintCharArray(uint8_t size = 100)** constructor
- **size_t write(uint8_t c)** workhorse of Print interface.
- **void clear()** wipes the internal buffer
- **int available()** shows how much space is left in the internal buffer.
Replaces free().
- **int size()** current usage of the buffer
- **int bufSize()** size of the whole buffer. recall that a char array must have a '\0' delimiter.
- **char \* getBuffer()** to access the buffer.


## Operation

See examples
