
[![Arduino CI](https://github.com/RobTillaart/moduloMap/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/moduloMap/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/moduloMap/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/moduloMap/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/moduloMap/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/moduloMap.svg)](https://github.com/RobTillaart/moduloMap/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/moduloMap/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/moduloMap.svg?maxAge=3600)](https://github.com/RobTillaart/moduloMap/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/moduloMap.svg)](https://registry.platformio.org/libraries/robtillaart/moduloMap)


# moduloMap

Arduino library for the moduloMap class.


## Description

The moduloMap is an experimental library that optimizes modular mapping.

How do I define modular mapping?

Imagine the mapping of all real numbers on a subset in a modular way.
Imagine the real number line rolled around a defined circle with a minimum and maximum value.
After one rotation the numbers mapped to start over again.

E.g. moduloMap(7, 13) maps all the real numbers to the interval \[7; 13> modulo 6.

So the numbers 7..13 do not change as they are already within the range 7-13.
The number 6 is mapped on 12, 5 on 11, 4 on 10, .. 1 on 7, 0 on 12 -1 on 11 etc.
Similar the numbers in between e.g 5.5 is mapped on 11.5 

Note: there is no scaling.

Other name might be circular mapping, although it might be any shape.
(for now circles is complex enough)


### Applications 

- modular mapping of rotations to angles.  
This can be on 0-360 degrees or 0-2PI radians or -180-180 degrees
or even -90..270 degrees.
- hoist math  
Imagine a hoist, that needs to roll up / roll off a long rope around a cylinder.
- wire cutter  
Determine the length of a wire for a wire cutter by moving it between two
wheels with known circumference.
- math fun  


#### Related

Other mapping libraries

- https://github.com/RobTillaart/FastMap
- https://github.com/RobTillaart/Gamma
- https://github.com/RobTillaart/map2colour
- https://github.com/RobTillaart/moduloMap
- https://github.com/RobTillaart/MultiMap


## Interface

```cpp
#include "moduloMap.h"
```

- **moduloMap()** constructor.
- **bool begin(float minimum, float maximum)** define the range the numbers should be mapped to.
Returns true if minimum < maximum, false otherwise.
- **float map(float value)** actual mapping of a value to a number within the range.
- **float rotations(float value)** how many ranges (maximum - minimum) fit in a given length.  
Think of it as how many rotations must a hoist must make to "free" a rope of given length.
Or how many rotations a hoist has to make to roll up a rope of given length.
This includes the minimum that already has rolled off / should stay rolled off.

Get internal parameters (for debug)
- **float getMinimum()** idem.
- **float getMaximum()** idem.
- **float getRange()** idem.


## Performance

Tested with moduloMap_performance.ino on AVR.

|  version  |  1000 x map  |
|:---------:|:------------:|
|  0.1.0    |  44120 us    |
|  0.1.1    |  36340 us    |


## Operation

The examples show the basic working of the functions.


## Future

#### Must

- elaborate documentation
- add examples

#### Should

- move code to .cpp file

#### Could

- are there other than circular modulo?
  - triangular, square, pentagram, fractal?
  - increasing length per rotation (complex)
- add **begin(float radius)**
  - assumes circle from 0..max

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

