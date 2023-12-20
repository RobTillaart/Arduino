
[![Arduino CI](https://github.com/RobTillaart/geomath/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/geomath/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/geomath/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/geomath/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/geomath/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/geomath.svg)](https://github.com/RobTillaart/geomath/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/geomath/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/geomath.svg?maxAge=3600)](https://github.com/RobTillaart/geomath/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/geomath.svg)](https://registry.platformio.org/libraries/robtillaart/geomath)


# Geomath

Library for geographical math functions.


## Description

Experimental library, use with care.

The geomath library is a collection of functions for doing math in a geographical context.
The library act primary as a placeholder for these related functions.

Wrote them long ago and share them because they might be useful e.g.
for educational purposes.


#### related

- https://github.com/RobTillaart/AtomicWeight
- https://github.com/RobTillaart/printHelpers (to print scientific notation)


## Interface

```cpp
#include geomath.h
```

#### Sphere class

Placeholder for some math

- **sphere(float radius)** constructor,
constructs a sphere (planet) with a certain radius.
- **float circumference(float latitude) returns the length in same units as used in constructor.
- **float angle(float distance)** returns the angle between two points,
given the distance. (E.g. Tokio Buenos Aires)


#### Haversine 

To calculate the distance between two points with longitude and lattitude.

- **double haverSine((double lat1, double lon1, double lat2, double lon2)**
- **double fastHaverSine(double lat1, double lon1, double lat2, double lon2)**


## Future

#### Must

- update documentation
- need more math


#### Should

- add more functions
- add unit tests
- escape velocity math
- heat inside earth ?
- find my sunset/sunrise formulas.


#### Could


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

