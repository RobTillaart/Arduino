
[![Arduino CI](https://github.com/RobTillaart/Stopwatch_RT/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Stopwatch_RT/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Stopwatch_RT.svg?maxAge=3600)](https://github.com/RobTillaart/Stopwatch_RT/releases)


# Stopwatch_RT

Arduino Library implementing a stopwatch including seconds, milliseconds microseconds

## Description

The stopwatch class allows one to create a stopwatch with 4 levels of resolution
- MICROS - microseconds 
- MILLIS - milliseconds (default)
- SECONDS - seconds
- MINUTES - minutes (added 0.2.0)

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
restrictions and limitations as these functions with respect to overflow 
and precision.
This means minutes and seconds will overflow also after about 49 days.


## Interface

### Core

- **StopWatch(resolution = MILLIS)** constructor, with default resolution.
- **void start()** start counting
- **void stop()** stop counting
- **uint32_t elapsed()** returns the time in chosen units since last **start()**
- **void reset()** resets the counting to 0.

The use of value() is depreciated, use **elapsed()** instead.

### Status

- **bool isRunning()** returns true if clock is counting.
- **enum state()** returns RESET, RUNNING or STOPPED.
- **void setResolution(resolution)** - changes the resolution of the stopwatch and resets it. Even when called with the current resolution a reset will take place. 
- **enum resolution()** returns MICROS, MILLIS, SECONDS or MINUTES

### Printable

As the stopwatch implements the printable interface from 0.3.1 one can call
```cpp
Serial.println(stopwatch);
```

To get output like "115 ms" or "159753 us" including the units.


### Calibration

If processors internal clock are not accurately enough, one can adjust two constants in the StopWatch.h file. Use ar own risk..

- STOPWATCH_SECONDS_DIVIDER
- STOPWATCH_MINUTES_DIVIDER


## Future

- with rising of faster processors in Arduino eco system, 
NANOS might added. Be aware that these short timeframes are better measured e.g. by a hardware timer.
- create getters and setters for the calibration constants so they can 
changed under program control.

## Operation

See examples
