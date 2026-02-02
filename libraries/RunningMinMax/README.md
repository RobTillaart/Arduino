
[![Arduino CI](https://github.com/RobTillaart/RunningMinMax/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/RunningMinMax/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/RunningMinMax/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/RunningMinMax/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/RunningMinMax/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/RunningMinMax.svg)](https://github.com/RobTillaart/RunningMinMax/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/RunningMinMax/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/RunningMinMax.svg?maxAge=3600)](https://github.com/RobTillaart/RunningMinMax/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/RunningMinMax.svg)](https://registry.platformio.org/libraries/robtillaart/RunningMinMax)


# RunningMinMax

Arduino library for a running Minimum and Maximum.


## Description

**Experimental**

RunningMinMax stores values in a ring buffer and can return the minimum,
maximum and the average of the buffer.
The first implementation is not optimized.

The library can be used e.g. to have an indication for the maximum
volume for a VU meter.

The library does not store timestamps of the samples (yet), that might
be a function in the future.

Feedback as always welcome.


### Related

- https://github.com/RobTillaart/Correlation
- https://github.com/RobTillaart/GST - Golden standard test metrics
- https://github.com/RobTillaart/Histogram
- https://github.com/RobTillaart/infiniteAverage
- https://github.com/RobTillaart/RunningAngle
- https://github.com/RobTillaart/RunningAverage
- https://github.com/RobTillaart/RunningMedian
- https://github.com/RobTillaart/RunningMinMax
- https://github.com/RobTillaart/statHelpers - combinations & permutations
- https://github.com/RobTillaart/Statistic
- https://github.com/RobTillaart/Student

For printing floats in scientific or engineering format

https://github.com/RobTillaart/printHelpers


## Interface

```cpp
#include "RunningMinMax.h"
```

### Constructor

- **RunningMinMax <T>(const uint8_t size)** Constructor, dynamically allocates memory.
- **~RunningMinMax()** Destructor.
- **uint8_t getSize()** returns size of internal array.
- **uint8_t getCount()** returns current used elements, getCount() <= getSize().
- **bool isFull()** returns true if the internal buffer is 100% filled.


### Base functions

- **clear()** resets internal buffer and variables, effectively empty the buffer.
- **add(const T value)** adds a new value to internal buffer, 
optionally replacing the oldest element if the buffer is full.
- **float getAverage()** returns average of the values in the internal buffer.
- **T getMaximum()** get the largest values in the buffer.
- **T getMinimum()** get the smallest value in the buffer.


## Performance

See performance example (version 0.2.0, UNO R3)

|  Type     |   add   |  min  |  max  |  avg  |
|:---------:|:-------:|:-----:|:-----:|:-----:|
|  float    |  10.88  |  108  |  108  |  256  |
|  int32_t  |   6.64  |   40  |   36  |  392  |
|  int16_t  |   5.76  |   28  |   32  |  384  |
|  int8_t   |   5.52  |   24  |   20  |  340  |
|           |         |       |       |       |

Average is expensive due to conversion to float,
except for float data type.
Removing (not using) the average function could
reduce footprint as no float math is used elsewhere.


## Future

#### Must

- improve documentation.
- test
- template class
  - user defines type

#### Should

- Stereo example
- Array example  
  - multichannel. (8 bit class needed)  
  - equalizer  (better example)


#### Could

- investigate for optimizations.
  - cache values + dirty flag(bitmask) when add.
  - only works when reading more often than writing.
- check for optimizations.
- IsEmpty(), noData()?
- extend unit tests

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


