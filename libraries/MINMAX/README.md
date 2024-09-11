

[![Arduino CI](https://github.com/RobTillaart/MINMAX/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MINMAX/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MINMAX/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MINMAX/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MINMAX/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MINMAX.svg)](https://github.com/RobTillaart/MINMAX/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MINMAX/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MINMAX.svg?maxAge=3600)](https://github.com/RobTillaart/MINMAX/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MINMAX.svg)](https://registry.platformio.org/libraries/robtillaart/MINMAX)


# MINMAX

Library for finding peaks (minimum and maximum) in a signal.


## Description

The MINMAX library is a simple peak finder in a stream of floats.

The **add()** function indicates after adding a number if the minimum and/or the
maximum value has been changed by means of a bit flag which is returned.
If a peak is found, it will be used as the new **minimum()** or **maximum()**
until a call to **reset()**.

The library can **reset()** the minimum and maximum to 0 to start again.
The first **add()** after the **reset()** will set the minimum and maximum
to the value added.

The library has the option to auto-reset after a predefined number of **add()** calls.

Finally the library keeps track when the last peaks occurred.


## Interface

```cpp
#include "MINMAX.h"
```
### Core

- **MINMAX()** Constructor,
- **uint8_t add(float value)** add next value. Returns status (bit flags), see table below.
- **void reset()** resets the minimum and maximum to 0.
- **void setResetDefaults(float minimum, float maximum)** sets the default values for minimum and maximum defining an initial range / window.
- **float minimum()** returns last minimum. Can be higher than previous call due to **reset()** or **autoReset()**.
If no call to **add()** is made yet it will return 0.
- **float maximum()** returns last maximum. Can be lower than previous call due to **reset()** or **autoReset()**.
If no call to **add()** is made yet it will return 0.
- **lastValue()** returns last value added.


### AutoReset

- **uint32_t count()** returns number of **add()** calls since last (auto)reset.
- **void setAutoResetCount(uint32_t count)** sets an auto-reset moment after count calls to **add()**.
There will be at least one value processed.
When count is set to 0, there will be no autoReset.
- **uint32_t getAutoResetCount()** returns set value.


### Timestamps

- **lastMin()** timestamp in millis() when minimum was last updated.
- **lastMax()** timestamp in millis() when maximum was last updated.


### Return flags add()

Return flags of **add()** - is a bit mask.

|  flag                |  value  |  description      |
|:---------------------|:-------:|:------------------|
|  MINMAX_NO_CHANGE    |  0x00   |  no change        |
|  MINMAX_MIN_CHANGED  |  0x01   |  minimum changed  |
|  MINMAX_MAX_CHANGED  |  0x02   |  maximum changed  |
|  MINMAX_RESET_DONE   |  0x80   |  reset done       |

NOTE: After a reset() the next add() will return both MINMAX_MIN_CHANGED and MINMAX_MAX_CHANGED (0x03)

NOTE: After an autoReset in add() it will return 0x83.

### CallBack

- **void addCallBack( void (\* func)(void) )** add a function to be called
when the minimum or the maximum has changed.
See examples.


### setResetDefaults()

- **void setResetDefaults(minimum, maximum)** sets the default values for minimum and maximum defining an initial range / window when **reset()** is called.
This will reduce an abundance of new min/max values in the first part of a stream, possibly causing unneeded call back calls.

The constructor sets both to zero (0) by default. The user can now override these values.
There are no default values for the parameters in the function.
The user is responsible and even allowed to set minimum to be larger than maximum.
The new values become active after the call to **reset()**.

The function does not change or reset the **lastMin()** and **lastMax()** timestamps. 
Only after **reset()** these are set to 0 again.

Note that with an initial range set, the **lastMin()** and **lastMax()** timestamps 
may be zero for quite a while.

Typical code snippet

```cpp
mm.setResetDefaults(-10, 20);  //  arbitrary values
mm.reset();                    //  activate them
```


### Dampening

Since 0.3.0 the MINMAX library has experimental support for a linear dampening 
of the minimum and maximum.

In every call to **add()** the values of MIN and MAX are brought closer together.
Therefore one does not need to reset them as these two are constantly adjusted
towards each other. 
The amount of dampening is a positive float and its value depends on the typical
values one adds with **mm.add(value)**. 
If the dampening value is too large, the min and max will follow the "signal"
quite fast.

Note: MIN is dampened first, and MAX is later. This might cause that MAX cannot
be dampened anymore for the full amount. This is an arbitrary choice.

- **void setDampening(const float value)** set dampening value. Default 0.
- **float getDampening()** get the current dampening value.

Note: The behavior might change a bit in the future e.g. both dampen for 50% of
the dampening value seems to be a valid behavior. Also make the dampening for MAX and MIN different could be an option.


## Obsolete

- **void autoReset(uint32_t count)** obsolete since 0.2.0
Replaced by **void setAutoResetCount(uint32_t count)**



## Future

#### Must

- documentation

#### Should

- consider an (featured) extended class and a (simple) base class.
- separate call back for **MINMAX_MIN_CHANGED** and **MINMAX_MAX_CHANGED**
- add **getLastEvent()**
- add AVG **average()** **sum()**
  - like a digital multimeter (DMM)
  - **sum()** would be sufficient as average can be derived.

#### Could

- Template class to allow other types
  - int32_t uint64_t double etc.
  - now you loose precision.
- a related class might be **WINDOW(min, max)** that counts and call backs if
a value is out of a predefined range.
- **void setResetDefaults(minimum, maximum, bool adjust = true)** add an adjust flag 
that allows / reject adaption of min / max. (extended class).
  - define MINMAX_MIN_CHANGED => MINMAX_MIN_EXCEEDED (new or reuse?)
- improve dampening strategy(?)

#### Wont (unless)

- thresholds, windowing + triggers  (separate class!)
- auto-reset after time? (would affect all functions  ?)
  - need a uint32_t start;
  - need a uint32_t threshold;
  - millis() - start > threshold) => action.
  - should be tested for in every function call.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

