
[![Arduino CI](https://github.com/RobTillaart/Logistic/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/Logistic/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/Logistic/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/Logistic/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/Logistic/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/Logistic.svg)](https://github.com/RobTillaart/Logistic/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Logistic/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Logistic.svg?maxAge=3600)](https://github.com/RobTillaart/Logistic/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/Logistic.svg)](https://registry.platformio.org/libraries/robtillaart/Logistic)


# Logistic

Arduino library to explore the logistic formula. (chaos, bifurcation)


## Description

The logistic function is a function known from the chaos theories.
It represents a model of e.g. how fast a rabbits reproduce and other processes.

The basic function is pretty simple 
```cpp
//  reproductionRate R = 0.0 - 4.0
//  in == 0.0 - 1.0  (think percentage of some maximum population)
out = reproductionRate * in * (1 - in);
```

For values of reproductionRate R 
- below 1 the function stabilizes goes to 0
- between 1 and 3 the function stabilizes after a few dozen iterations.
- between 3 and ~3.57 the stabilization jumps between 2, 4, 8 values (called bifucation)
  - see around R == { 3, 3.45, 3.54, 3.56, 3.57}
- above 3.57 the function turns to chaos with some stability zones. At least visually.

There are a lot of (mathematical) interesting aspects to be found in the functions behaviour.

If you have ideas (or links) to that should be in this library, please open an issue.



#### Related

- https://en.wikipedia.org/wiki/Logistic_map
- https://en.wikipedia.org/wiki/Feigenbaum_constants
- https://www.vanderbilt.edu/AnS/psychology/cogsci/chaos/workshop/BD.html


## Interface

```cpp
#include "Logistic.h"
```

- **Logistic(float rate = 2.0, float in = 0.5)** Constructor  
  - rate = reproduction rate = 0.0 - 4.0
  - in   = input population = 0.0 - 1.0
- **void setRate(float rate)** set / change the reproduction rate.
- **float getRate()** get the current rate.
- **float iterate(float in)** make one iteration given a start value.
- **float iterate()** make an iteration with the last calculated value.

## Future

#### Must

- improve documentation.
  - related links (youtube?)
- add examples

#### Should

- Look for other "logistic functions"
- elaborate the library
  - **stable()** checks delta between previous and current value.
  - **period()** tries to find a repeating period in the values?
  - **count()** iteration counter.

#### Could

- add unit tests
- add graphics? => user task?

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,