
[![Arduino CI](https://github.com/RobTillaart/MINMAX/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MINMAX/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MINMAX/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MINMAX/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MINMAX/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MINMAX/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MINMAX.svg?maxAge=3600)](https://github.com/RobTillaart/MINMAX/releases)


# MINMAX

Library for finding peaks (minimum and maximum) in signal.


## Description

The MINMAX library is a simple peak finder in a stream of floats. 

It indicates if after adding a number the minimum and/or the maximum value has been changed by means of a bit flag that is returned. If a peak is found, it will be used as the new reference until a reset.


The library can reset the minimum and maximum to 0 to start again. 

The library has also the option to auto-reset after a predefined number of **add()** calls.


## Interface

- **MINMAX** Constructor
- **uint8_t add(float value)** add next value. Returns status (bit flags), see table below.
- **void reset()** resets the minimum and maximum to 0.
- **void setAutoResetCount(uint32_t count)** sets an auto-reset moment after count calls to **add()**.  
There will be at least one value processed.
- **uint32_t getAutoResetCount()** returns set value.
- **float minimum()** returns last minimum. Can be higher than previous call due to **reset()** or **autoReset()**.  
If no call to **add()** is made it will return 0.
- **float maximum()** returns last maximum. Can be lower than previous call due to **reset()** or **autoReset()**.   
If no call to **add()** is made it will return 0.
- **uint32_t count()** returns number of **add()** calls since last (auto)reset.


Return values of **add()**

| flag | description     |
|:----:|:----------------|
| 0x00 | no change       |
| 0x01 | minimum changed |
| 0x02 | maximum changed |
| 0x80 | reset done      |


## Obsolete

- **void autoReset(uint32_t count)** obsolete, replaced by **void setAutoResetCount()**


## Operation

The examples show the basic working of the functions.


## Future

- update documentation.
- define FLAGS
- add call back functions?
- thresholds, windowing + triggers  (separate class?)
- auto-reset after time? (would affect all functions  ?)
  - need a uint32_t start;
  - need a uint32_t threshold;
  - millis() - start > threshold) => action.
-

