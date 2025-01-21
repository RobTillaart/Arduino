
[![Arduino CI](https://github.com/RobTillaart/millis64/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/millis64/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/millis64/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/millis64/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/millis64/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/millis64.svg)](https://github.com/RobTillaart/millis64/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/millis64/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/millis64.svg?maxAge=3600)](https://github.com/RobTillaart/millis64/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/millis64.svg)](https://registry.platformio.org/libraries/robtillaart/millis64)


# millis64

Arduino library for millis64 micros64 millis32 micros32, time counters with optional offset.


## Description

**Experimental**

This library implements 64 bit time counters optional with offset.
It also provides 32 bit versions with optional offset.
These functions were inspired by code from docdoc to count ```millis()``` rollOvers.

- https://forum.arduino.cc/t/arduino-millis-looping-after-45-5104-days/1343661

When using an offset, one typically has to use the same offset throughout your whole
program or only slightly adjust if needed, e.g. after an external reference pulse
of an RTC or from data from an NTP packet.


The **millis64()** and **micros64()** are build upon the existing **millis()** 
and **micros()** functions and therefore slower of course.

As always, constructive feedback is welcome.

### Boards

Some boards already implement millis64 and/or micros64. 
If so one could not use this library as is (but it is fairly easy to adapt)

|  board    |  millis64  |  micros64  |
|:----------|:----------:|:----------:|
|  UNO      |     N      |     N      |
|  ESP32    |     N      |     N      |
|  ESP8266  |     N      |    YYY     |
|  M4       |     N      |     N      |
|  RPIpico  |     N      |     N      |



### Print

To print the 64 bit timestamp one can use
- https://github.com/RobTillaart/printHelpers  (includes HEX printing too)


### Performance

The **millis64()** and **micros64()** functions are slower than **micros()** 
and **millis()** so not always optimal for all projects.

Run the **millis64_performance.ino** to get an indication of the performance
on your platform of choice to see if it meets your needs.


Indicative times in micros for Arduino UNO.

|  function          |  UNO   |
|:-------------------|:------:|
|  millis()          |  1452  |
|  millis32()        |  1444  |
|  millis32(offset)  |  1696  |
|  millis64()        |  3900  |
|  millis64(offset)  |  5096  |
|                    |        |
|  micros()          |  3716  |
|  micros32()        |  3716  |
|  micros32(offset)  |  3964  |
|  micros64()        |  6288  |
|  micros64(offset)  |  7488  |


### Drift, accuracy and precision

Be aware that the functions in this library will drift in time due to interrupts, 
deviations in frequency of crystals, resonators, and more. 
Also the values of the millis64 and micros64() is not persistent.
So do not use them to replace a professional (atomic) clock.


## Interface

```cpp
#include "millis64.h"
```

### 64 bit

- **millis64(uint32_t offset = 0)** offset is optional.
Returns an unsigned 64 bit integer, milliseconds since start of sketch.
This function rolls over (offset === 0) after approx. 213 billion days > 500 million years.
  - note: function must be called at least once every 24 days to not miss a rollover.
- **micros64(uint32_t offset = 0)** offset is optional.
Returns an unsigned 64 bit integer, microseconds since start of sketch.
This function rolls over (offset === 0)  after approx. 213 million days > 500.000 years.
  - note: function must be called at least once every 30 minutes to not miss a rollover.

The library has commented versions of the (offset) functions that only need to be called 
once in 49 days / 70 minutes. However these are slower so not preferred. 
And it should not be too much trouble to call them twice or?


### 32 bit

These functions add an optional offset to the millis() and micros().
This allows e.g. to do roll over testing or align the millis32() with an external clock.
The latter could be based upon an RTC or NTP.

- **millis32(uint32_t offset = 0)** idem.
- **micros32(uint32_t offset = 0)** idem.


## Future

#### Must

- improve documentation

#### Should

- **uint32_t nano()** would be great to have (some protocols might like them)
- **void delayNano()** would be great to have (some protocols might like them)
- investigate 64 bit offsets.
- investigate a millis64 class, esp. performance.

#### Could

- example to sync offset with an NTP packet. (needs 64 bit offset?)

#### Wont

- delay64() no blocking for so long...
- delayMicros64() no blocking for so long...


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


