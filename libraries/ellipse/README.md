
[![Arduino CI](https://github.com/RobTillaart/ellipse/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/ellipse/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/ellipse/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/ellipse/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/ellipse/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/ellipse.svg)](https://github.com/RobTillaart/ellipse/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/ellipse/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/ellipse.svg?maxAge=3600)](https://github.com/RobTillaart/ellipse/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/ellipse.svg)](https://registry.platformio.org/libraries/robtillaart/ellipse)


# ellipse

Arduino library with ellipse math.


## Description

This experimental library provides basic ellipse math. 
It was written to test different perimeter algorithms.

Trigger was a video of Dr. Matt Parker, with the title:
"Why is there no equation for the perimeter of an ellipse?"
 https://www.youtube.com/watch?v=5nW3nJhBHL0


## Interface

```cpp
#include "ellipse.h"
```

- **ellipse(float a, float b)** constructor, a >= b 
- **float area()** returns the area of the ellipse.
- **float circumference()** good algorithm (= Ramanujan 1).
- **float eccentricity()** return the eccentricity e. 
This is an indication of flatness of the ellipse. 0 is a circle 1 is flat line.
- **void  setA(float a)** change the long radius.
- **void  setB(float b)** change the short radius.
- **float getA()** return long radius of the ellipse.
- **float getB()** return short radius of the ellipse.
- **float getC()** distance to focus point form centre along the longer axis. 


#### Perimeter algorithms

Perimeter == circumference

- **float perimeter_ref()** slower but best known algorithm (Ramanujan 2)
- **float perimeter_Keppler()** good and fast algorithm for eccentricity between 1 and 2.
- **float perimeter_Ramanujan1()** good algorithm.
- **float perimeter_Parker()** Matt Parker's algorithm, better than Ramanujan, but not symmetric.
- **float perimeter_Ramanujan2()** slow but best known algorithm.

See performance example for differences in timing and accuracy.


#### Convenience functions

- **bool isCircle(float epsilon = 0.0)**  | a - b | < eps.
- **bool isFlat()** true if a > 4b, where a = longest radius.


#### Experimental

- **float angle()** returns the angle if the ellipse was the
shadow of a circle, Returns 0..90°, 0° == circle, 90° == line.


## Operation

See examples.


## Future

#### Must

- improve documentation
  - refer Wikipedia.
  
#### Should

- make constructor symmetric (a < b or a > b ==> all possible.
- make other code symmetric.

#### Could

- replace float by double?
- additional functions
  - Bresenham to draw ellipse?

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

