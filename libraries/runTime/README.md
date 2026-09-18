
[![Arduino CI](https://github.com/RobTillaart/runTime/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/runTime/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/runTime/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/runTime/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/runTime/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/runTime.svg)](https://github.com/RobTillaart/runTime/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/runTime/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/runTime.svg?maxAge=3600)](https://github.com/RobTillaart/runTime/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/runTime.svg)](https://registry.platformio.org/libraries/robtillaart/runTime)


# runTime

Arduino library to measure cumulative series of run times.


## Description

**Experimental**

This library is used to add up one or more runs of "on" time.
This sum is counted in seconds.
The goal of the library is e.g. to track the runtime (uptime or elapsed time)
of a device or a process over a long time.
In this period the device can be switched on and off multiple times. 
This runtime can be requested in seconds, minutes, hours or days.
Besides the runtime the library also counts how often 
the counter (== device) has started.
Finally the library can report the average runtime in seconds, 
minutes, hours or days.

The maximum duration is 49.710 days or about 136 years.

The library uses **millis()** so the internal values need to be 
updated at least once per 49 days when running continuously.
This must be done by calling **update()**.
When the clock is stopped one does not need to update every 49 days.

Feedback as always is welcome.


### Operational time

The library does not track the "operational time" or total time. 
Therefore it is not possible to calculate the runtime as a percentage
of the total time. This would allow to make statements like 
"Device has run 1459 hours in the last 100 days = 60.79%".

There are ideas to add this in the future. 


### Picture

To visualize the concept, a minimalistic picture

```
   0      10               30        40        50          70
---|------|................|---------|.........|-----------|------
   T0     START            STOP      START     STOP       T1

runtime = sum(stop - start) = 30
runCount = 2

//  not supported (yet)
total time = T1 - T0  = 70
percentage = 30/70*100% = 42.86%
```


### Accuracy

The library does truncate the **millis()** internally when converting 
to seconds, however it tracks the milliseconds remaining to add later.
This improves the accuracy, especially when the individual runs are 
relative short.

Note this library is only as accurate as the underlying millis() is.
The library does not support compensation for this drift.
As the drift may vary over time this is not a trivial problem.

A first order compensation may be a **drift factor** which compensates 
for the average deviation over time. This can be multiplying the numbers 
with a configurable float e.g. 1.015 or 0.99973.

Support for the drift factor in the library might be added in the future.

With the use of NTP or an RTC there are more options to tackle this.
For now these are out of the scope of the library.


### Persistence

The library does not store its data in an NVRAM so it does not keep 
the counting persistent over reboots.
For now the user is responsible to "backup" the counter.


### Related

- https://github.com/RobTillaart/DS1682 - hardware runtime counter
- https://github.com/RobTillaart/DS1683 - hardware runtime counter
- https://github.com/RobTillaart/millis64
- https://github.com/RobTillaart/stopWatch_RT

Other
- https://github.com/RobTillaart/dateTimeHelpers - formatting
- https://github.com/RobTillaart/printHelpers


### Tested

On Arduino UNO R3.


## Interface

```cpp
#include "runTime.h"
```

### Constructor

- **runTime()** creates the time counter and resets internals.

### Control

- **void start()** starts the internal counting. If the counting is running
it is not started again. One must use reset() or stop() first.
- **void stop()** stops the internal counting and adds the last run to the
internal runtime counter. 
- **void update()** updates the internal counting. Must be called at least
once per 49 days, typically once per day.
- **void reset(uint32_t startValue = 0)** resets the internal counters to zero.
Optional one can set a number of start seconds.
- **bool isRunning()** returns true is the counting is running.

### Measurement

- **uint32_t seconds()** returns the seconds runtime, includes the active run.
- **float minutes()** wrapper around seconds, partial minutes is in decimal format.
E.g. 15 minutes 25 seconds ==> 15.42 (rounded).
- **float hours()** wrapper around seconds, partial hours is in decimal format.
- **float days()** wrapper around seconds, partial days is in decimal format.
- **uint32_t runCount()** returns the number of runs (== starts).
Returns zero after reset() and no run started yet.

### Statistics

- **float averageSeconds()** returns seconds / runCount.
When runCount == 0, it returns 0.
- **float averageMinutes()** returns minutes / runCount.
When runCount == 0, it returns 0.
- **float averageHours()** returns hours / runCount.
When runCount == 0, it returns 0.
- **float averageDays()** returns days / runCount.
When runCount == 0, it returns 0.


### PrintTo

The class implements the **Printable** interface, allowing to
print the object directly.
Currently it returns seconds, might change in the future.

```cpp
runTime rt;
...
Serial.println(rt);
```

## Future

#### Must

- improve documentation

#### Should

- investigate operational time.
  - extended class as more data needs tracking?
  - tracking "not running" time would be sufficient.
  - add runtime as percentage of total time
- investigate drift support
  - drift depends on runtime, interrupts and more?
  - driftCorrect(ms) - call daily / hourly?
  - setDriftFactor(float) - first order compensation
  - API?

#### Could

- investigate persistence over reboot support.
  - external storage?
  - watchdog persistence?
  - FRAM snapshots? user responsibility?
- add examples
- extend unit tests (if possible)
- redefine printTo() layout?
- access to remainder?
- track the largest run, the shortest? to get a range?

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


