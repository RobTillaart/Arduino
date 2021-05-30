
[![Arduino CI](https://github.com/RobTillaart/ShiftInSlow/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/ShiftInSlow/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/ShiftInSlow.svg?maxAge=3600)](https://github.com/RobTillaart/ShiftInSlow/releases)

# ShiftInSlow

Arduino library for shiftIn with build-in delay - e.g. for 74HC165

A library for shiftOutSlow also exist.

## Description

shiftInSlow is an experimental library that has a build in delay (in microseconds) that allows tuning the time per bit. 
This allows one to improve reliability e.g. when using longer lines.

The datapin and clockpin are set in the constructor, the delay is settable per byte send to be able to optimize runtime.


## Performance

The performance of **read()** with a delay of 0 microseconds is slower than the default Arduino 
**shiftIn()** due to some overhead. 

The delay requested is split in two (expect rounding errors) to have "nice" looking pulses.


## Interface

The interface exists of the following functions:
- **ShiftInSlow(datapin, clockpin, bitorder = LSBFIRST)** constructor.
- **int read(void)** reads a new value
- **int lastRead()** returns last value read
- **void setDelay(uint16_t microseconds)** set delay per bit from 0 .. 65535 microseconds.
- **uint16_t getDelay()** returns the set delay in microseconds.
- **bool setBitOrder(bitOrder)** set LSBFIRST or MSBFIRST. Returns false for other values.
- **uint8_t getBitOrder(void)** returns LSBFIRST or MSBFIRST


## Notes

- to be tested


## Operation

See examples

