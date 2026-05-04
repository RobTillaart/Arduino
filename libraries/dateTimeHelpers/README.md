
[![Arduino CI](https://github.com/RobTillaart/dateTimeHelpers/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/dateTimeHelpers/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/dateTimeHelpers/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/dateTimeHelpers/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/dateTimeHelpers/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/dateTimeHelpers.svg)](https://github.com/RobTillaart/dateTimeHelpers/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/dateTimeHelpers/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/dateTimeHelpers.svg?maxAge=3600)](https://github.com/RobTillaart/dateTimeHelpers/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/dateTimeHelpers.svg)](https://registry.platformio.org/libraries/robtillaart/dateTimeHelpers)


# dateTimeHelpers

Arduino library with date and time helper functions.

## Description

This library contains functions that have the goal to help with date and time processing.
It is primary a placeholder for date and time related functions.

Please report missing functions, open an issue or preferably a PR.

Feedback as always is welcome.

### Related libraries

- https://github.com/RobTillaart/printHelpers
- https://github.com/RobTillaart/stopWatch_RT
- https://github.com/RobTillaart/CountDown
- https://github.com/RobTillaart/timing


### Implementation notes

- the functions share an output buffer.
This can give problems when prints are made fast after each other as the buffer
 is not printed completely before it is filled again. (think also RTOS).
Possible solution is to copy the buffer before printing.
- math is straightforward, may be optimized? sprintf()?
- code has repeating parts, may be optimized?


## Interface

```cpp
#include "dateTimeHelpers.h"
```

### Constants

```cpp
constexpr uint32_t SECONDS_MINUTE = 60;
constexpr uint32_t SECONDS_HOUR   = 3600;
constexpr uint32_t SECONDS_DAY    = 86400;
constexpr uint32_t SECONDS_WEEK   = 604800;
```

### Display functions, seconds

- **void secondsSplit(uint32_t seconds, uint16_t \* days, uint8_t \* hours, uint8_t \* minutes, uint8_t \* sec)** Splits the seconds into days, hours, minutes and seconds. 
This is the worker for the next three. 
Note: days is max 65535 == 179 years.
- **char \* seconds2duration(uint32_t seconds, bool displaySeconds = false, bool displayDay = true)** returns "days 00:00:00 .. 23:59:59" or "days 00:00 .. 23:59"
- **char \* seconds2clock24(uint32_t seconds, bool displaySeconds = false)** returns "00:00:00 .. 23:59:59" or "00:00 .. 23:59"
- **char \* seconds2clock12(uint32_t seconds, bool displaySeconds = false)** returns "00:00:00 .. 12:59:59" or "00:00 .. 12:59". 
Note this function has no morning or afternoon indication.
- **char \* seconds2clockAMPM(uint32_t seconds, bool displaySeconds = false)** returns "00:00:00 AM .. 12:59:59 PM" or "00:00 AM .. 12:59 PM". 


### Display functions, millis and micros

- **char \* micros2duration(uint32_t micros)** returns "0 00:00.000.000 .. 0 01:11:34.967.295" 
(experimental)
- **char \* millis2duration(uint32_t millis)** returns "days 00:00:00.000 .. 23:59:59.999"
- **char \* millis2clock(uint32_t millis)** returns "00:00:00.000 .. 23:59:59.999"

Note: call print(micros2duration(v) + 2) to remove days field which is always zero.
Adding an offset works also strips from start with other functions.


### AM PM 

**seconds2clockAMPM** has two more or less undefined moments: midnight (00:00 AM 12:00 PM) and noon (12:00 AM 12:00 PM).
See https://www.npl.co.uk/resources/q-a/is-midnight-12am-or-12pm)

At night one uses 00:15 AM and after noon one uses 12:15 PM.
Therefore I use in this implementation:
- midnight == 00:00 AM 
- noon == 12:00 PM


## Convertors

Note: the following functions use float math so there might occur rounding.

- **float seconds2weeks(uint32_t seconds)** idem.
- **float seconds2days(uint32_t seconds)** idem.
- **float seconds2hours(uint32_t seconds)** idem.
- **float seconds2quarters(uint32_t seconds)** idem.
- **float seconds2minutes(uint32_t seconds)** idem.


## Angle for clock hands

The angle of the hour hand (et al) of an analog clock changes every second.
If you want it to behave as a digital clock only fill in the hours
and the minutes and leave the seconds zero (0).

The functions return the angle in degrees, with zero degrees at the
top of the clock (at 12).

The functions assume that minutes and seconds are normalized (0..59).
Tenths of a second is not supported.

- **float hourAngle(uint8_t hh, uint8_t mm, uint8_t ss)** 
- **float minuteAngle(uint8_t mm, uint8_t ss)**
- **float secondAngle(uint8_t ss)**


## Future

#### Must

- improve documentation
- test a lot

#### Should 

- redo by reference functions?
- optimize for performance
  - secondsSplit() (see fast math lib)
  - seconds2clock24 => divmod10
- merge code where possible
- extend examples
- add unit tests
- create .cpp file, + move code
- fix micros2duration() => remove days?

#### Could

- date math functions 
  - days=date-date or date = date + days
  - day of week
- time math functions (which?)
- 64 bit versions of convertors?
- unusual time units for converters?
  - atomic time
- "classify" ?
  - extern "C" ?


#### Won't


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


