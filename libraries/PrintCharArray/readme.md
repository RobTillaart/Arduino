
[![Arduino CI](https://github.com/RobTillaart/PrintCharArray/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PrintCharArray/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PrintCharArray/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PrintCharArray/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PrintCharArray/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PrintCharArray/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PrintCharArray.svg?maxAge=3600)](https://github.com/RobTillaart/PrintCharArray/releases)


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
  - 

Related to https://github.com/RobTillaart/PrintSize and https://github.com/RobTillaart/PrintString.


## Interface

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


## Operation

See examples.


## Future

- testing
- examples
  - inject spaces in "middle align" example? possible?
  - rename some
  - add real live examples.
- add functions like **repeat(char c)** to inject e.g. 7 spaces etc.
- add error flag
- 

