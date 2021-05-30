
[![Arduino CI](https://github.com/RobTillaart/ShiftOutSlow/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/ShiftOutSlow/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/ShiftOutSlow.svg?maxAge=3600)](https://github.com/RobTillaart/ShiftOutSlow/releases)

# ShiftOutSlow

Arduino library for shiftOut with build-in delay - e.g. for 74HC595

A library for shiftInSlow also exist.

## Description


ShiftOutSlow is an experimental library that has a build in delay (in microseconds) that allows tuning the time per bit. 
This allows one to improve reliability e.g. when using longer lines.

The datapin and clockpin are set in the constructor, the delay is settable per byte send to be able to optimize runtime.

ShiftOutSlow implements the print interface.


## Performance

The performance of **write()** with a delay of 0 microseconds is slower than the default Arduino 
**shiftOut()** due to some overhead. 

The delay requested is split in two (expect rounding errors) to have "nice" looking pulses.


## Interface

The interface exists of the following functions:
- **ShiftOutSlow(datapin, clockpin, bitorder = LSBFIRST)** constructor.
- **size_t write(uint8_t data)** writes a new value
- **uint8_t lastWritten()** returns last value written
- **void setDelay(uint16_t microseconds)** set delay per bit from 0 .. 65535 microseconds.
- **uint16_t getDelay()** returns the set delay in microseconds.
- **bool setBitOrder(bitOrder)** set LSBFIRST or MSBFIRST. Returns false for other values.
- **uint8_t getBitOrder(void)** returns LSBFIRST or MSBFIRST


## Notes

- to be tested


## Operation

See examples

