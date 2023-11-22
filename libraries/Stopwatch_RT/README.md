
[![Arduino CI](https://github.com/RobTillaart/Stopwatch_RT/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/Stopwatch_RT/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/Stopwatch_RT/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/Stopwatch_RT/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/Stopwatch_RT/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/Stopwatch_RT.svg)](https://github.com/RobTillaart/Stopwatch_RT/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Stopwatch_RT/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Stopwatch_RT.svg?maxAge=3600)](https://github.com/RobTillaart/Stopwatch_RT/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/Stopwatch.svg)](https://registry.platformio.org/libraries/robtillaart/Stopwatch)


# Stopwatch_RT

Arduino Library implementing a stopwatch including seconds, milliseconds microseconds.


## Description

The stopwatch class allows one to create a stopwatch with 4 levels of resolution:
- **MICROS** - microseconds 
- **MILLIS** - milliseconds (default)
- **SECONDS** - seconds
- **MINUTES** - minutes (added 0.2.0)

Note that the resolution chosen implies the finest granularity of units measured.
E.g. if chosen minutes then one cannot measure half (30 sec) or other part of a minute.

The resolution is typically set in the constructor, however since 0.2.0 one can call
**setResolution()** to change the 'tick unit' of the clock runtime. 
This way one can reuse the stopwatch object without creating a new one and thereby
save some memory.

**Warning:** Changing the resolution will reset the stopwatch 
as start time and stop time will become meaningless.
The stopwatch will reset even when the resolution is the current resolution.

This library is based upon millis() and micros() and therefore has the same 
restrictions and limitations as these functions with respect to overflow and precision.
This means minutes and seconds will overflow also after about 49 days.

#### Related

- https://github.com/RobTillaart/CountDown


## Interface

```cpp
#include "StopWatch.h"
```

### Core

- **StopWatch(Resolution resolution = MILLIS)** constructor, with default resolution.
- **void start()** start counting
- **void stop()** stop counting
- **uint32_t elapsed()** returns the time in chosen units since last **start()**
- **void reset()** resets the counting to 0.
- **char getUnits()** returns u, s, m , M. 


### Status

- **bool isRunning()** returns true if clock is counting.
- **bool isStopped()** returns true if clock is stopped.
- **bool isReset()** returns true if clock is reset.
- **enum state()** returns RESET, RUNNING or STOPPED.
- **void setResolution(Resolution resolution)** changes the resolution of the stopwatch and resets it. 
Even when called with the current resolution a reset will take place. 
- **enum resolution()** returns MICROS, MILLIS, SECONDS or MINUTES.


### Printable

As the stopwatch implements the printable interface since version 0.3.1 one can call
```cpp
Serial.println(stopwatch);
```

To get output like "115 ms" or "159753 us" including the units.


### Calibration

If processors internal clock are not accurately enough, one can adjust 
the two constants in the StopWatch.h file. Use at your own risk.

- **STOPWATCH_SECONDS_DIVIDER**  default 1000
- **STOPWATCH_MINUTES_DIVIDER**  default 60000


### Obsolete

The use of **value()** is obsolete, use **elapsed()** instead.


## Operation

See examples


## Future

#### Must

- improve documentation

#### Should

- create getters and setters for the calibration constants so they can 
changed runtime under program control. Must it be float + round() or uint32_t ?

#### Could

- with rising of faster processors in Arduino ecosystem, NANOS might added. 
Be aware that these short time frames are better measured e.g. by a hardware timer.
- **resolution()** ==> **getResolution()**

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

