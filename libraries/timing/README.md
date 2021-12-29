
[![Arduino CI](https://github.com/RobTillaart/timing/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/timing/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/timing/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/timing/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/timing/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/timing/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/timing.svg?maxAge=3600)](https://github.com/RobTillaart/timing/releases)


# Timing

Arduino library with wrappers for seconds millis micros.


## Description

A request often made on the Arduino forum and otherwise is an option to reset
the **millis()** function to 0 or another value. 
This library provide wrapper classes around **millis()** and **micros()** 
with the extra function to do this. 
To implement this only a 4 byte offset is needed.

The classes are based upon **millis()** and **micros()**.
Therefore they have the same restrictions as these functions with respect to 
overflow and accuracy. Depending on e.g. interrupts millis and micros can drift.


| class        | overflow after           | Notes               |
|:-------------|:-------------------------|:--------------------|
| seconds      | 49 days, 17:02:47        | based upon millis() |
| milliSeconds | 49 days, 17:02:47.297    |
| microSeconds | 00 days  01:11:34.967296 |


## Applications

These classes make it easy to make a simple stopwatch.
Or sync the time with an external source. 


## Interface 

The interface of all three are very similar:

- **microSeconds()** constructor, sets the offset so it starts at 0.
- **milliSeconds()** constructor, sets the offset so it starts at 0.
- **seconds()** constructor, sets the offset so it starts at 0.
- **uint32_t now()** returns the time elapsed since its 'zero moment'.
Ether set during construction or by a call to **set(0)**. 
- **void set(uint32_t value = 0UL)** sets the offset of the object. 
As it is possible to set it to a non zero value it is easy to adjust the time.
This allows one e.g. to compensate for overhead. Default = zero.
- **uint32_t getOffset()** returns current offset.


## Operation

See examples.


## Future

- test on ESP32
- nanos() on ESP32 ?
- implement printable interface (add unit)
  - ?
- implement toClock()
  - idea to give it a clock print layout
  - seconds.toClock() -> DD 12:34:56
  - milliSeconds.toClock(3) -> 12:23:45.123    (3) == 3 decimals..
  - milliSeconds.toClock(1) -> 12:23:45.1
  - microSeconds.toCLock()  -> 12:23:45.123456  ???
- implement toSeconds()
  - double milliSeconds.toSeconds() -> 45.123
  - double microSeconds.toSeconds() -> 45.123456
- update documentation
- rounding effect, describe

