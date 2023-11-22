
[![Arduino CI](https://github.com/RobTillaart/timing/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/timing/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/timing/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/timing/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/timing/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/timing.svg)](https://github.com/RobTillaart/timing/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/timing/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/timing.svg?maxAge=3600)](https://github.com/RobTillaart/timing/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/timing.svg)](https://registry.platformio.org/libraries/robtillaart/timing)


# Timing

Arduino library with wrappers for seconds, milliseconds, and microseconds.


## Description

A request often made on the Arduino forum and otherwise is an option to reset
the **millis()** function to 0 or to another value.

This library provide wrapper classes around **millis()** and **micros()**
with the extra function to do reset the count by means of an offset.
To implement this only a 4 byte offset is needed per "clock".

The classes are based upon **millis()** and **micros()**.
Therefore they have the same restrictions as these functions with respect to
overflow and accuracy. Depending on e.g. interrupts, millis() and micros() can drift.


|  class         |  overflow after            |  Notes                |
|:---------------|:---------------------------|:----------------------|
|  seconds       |  49 days, 17:02:47         |  based upon millis()  |
|  milliSeconds  |  49 days, 17:02:47.297     |  based upon millis()  |
|  microSeconds  |  00 days  01:11:34.967296  |  based upon micros()  |


#### Tests

Code is tested on UNO and ESP32, should work on all platforms.

No performance tests as code is 'basic'.


## Applications

These classes make it easy to make a simple stopwatch, clock or countdown timer.
It is also possible to sync the time (e.g. millis()) with an external source,
which could be another Arduino.


## Interface

```cpp
#include "timing.h"
```

The interface of all three are very similar:

- **microSeconds()** constructor, sets the offset so it starts at 0.
- **milliSeconds()** constructor, sets the offset so it starts at 0.
- **seconds()** constructor, sets the offset so it starts at 0.
- **uint32_t now()** returns the time elapsed since its 'zero moment'.
Ether set during construction or by a call to **set(0)**.
- **void set(uint32_t value = 0UL)** sets the offset of the object.
As it is possible to set it to a non zero value it is easy to adjust the time.
This allows one e.g. to compensate for overhead. Default = zero.
- **void add(uint32_t value)** allows one to increment or decrement the offset for calibration.
Allows one to sync time e.g. with an external reference in small incremental steps.
- **uint32_t getOffset()** returns current offset in base units.
So seconds for seconds, millis for millis and micros for micros.
- **double toSeconds()** returns a float representation of the current value in seconds.
e.g. 15678 milliseconds becomes 15.678 seconds (SI units).

#### Experimental

- ** char \* toClock()** converts current seconds to a clock like char array "HH:MM:SS".
Only for the seconds class for now.


## Future

#### Must

- update documentation
  - describe rounding effect (seconds)

#### Should

- implement toClock()
  - seconds.toClock() -> DD 12:34:56  (days ??)
  - milliSeconds.toClock(3) -> 12:23:45.123    (3) == 3 decimals..
  - milliSeconds.toClock(1) -> 12:23:45.1
  - microSeconds.toCLock()  -> 12:23:45.123456  ???
  - printHelpers class?


```cpp
  // something like this.
  char * toClock()
  {
    static char buf[12];
    uint32_t _now = now();
    int hh = _now / 3600;
    _now = _now - hh * 3600;
    int mm  = _now / 60;
    int ss = _now - mm * 60;
    sprintf(buf, "%02d:%02d:%02d", hh, mm, ss);
    return buf;
  }
```


#### Could

- nanos() on ESP32 ?
  - measureable?
- implement printable interface
  - add unit (s, ms, us)
  - what layout to use? (culture dependent)
- create a uint64_t seconds type?

#### Wont
- move code to .cpp file?


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

