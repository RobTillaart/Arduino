
[![Arduino CI](https://github.com/RobTillaart/TOPMAX/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/TOPMAX/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/TOPMAX/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/TOPMAX/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/TOPMAX/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/TOPMAX/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/TOPMAX.svg?maxAge=3600)](https://github.com/RobTillaart/TOPMAX/releases)


# TOPMAX

Arduino library to track the top N maxima.

## Description

This experimental library tracks the top N maxima of a series of values. 
It can be used e.g. to track the top 5 peak temperatures over a given 
period of time.


#### Links

- https://github.com/RobTillaart/TOPMAX
- https://github.com/RobTillaart/TOPMIN
- https://github.com/RobTillaart/runningAverage
- https://github.com/RobTillaart/MINMAX


## Interface

```cpp
#include "TOPMAX.h"
```

- **TOPMAX(uint8_t size = 5)** Constructor, defines the number of elements it can hold.
Default number of elements is 5. If size < 3 it becomes 3.
- **uint8_t count()** returns the number of elements in the internal array.
- **uint8_t size()** returns the maximum number of elements in the internal array. 
- **void reset()** reset the internal counter to 0, clearing the system.
- **bool add(float value)** add a value to the TOPMAX object to check it needs to be in the top N of maxima.
- **float get(uint8_t index)** get an element of the internal array.
index == count().
- **bool fill(float value)** convenience function to fill the internal array 
with a single value e.g. 0.


# Future

#### Must

- keep functional in sync with TOPMIN
- improve documentation.


#### Should

- add unit tests.
- add more examples.


#### Could

- create template class
- create derived class that holds an index or timestamp
  - uint32_t extra per element.


#### Wont

