
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

**Experimental**

This library provides some basic ellipse math.
It was written to test different perimeter algorithms.

Trigger was a video of Dr. Matt Parker, with the title:
"Why is there no equation for the perimeter of an ellipse?"
 https://www.youtube.com/watch?v=5nW3nJhBHL0

If anyone has a better perimeter algorithm, either faster or more accurate,
or a relevant link to add, let me know.

As always feedback is welcome.

###  Formula

Typical an ellipse is defined as the set of points for which 

```
  (x*x)/(a*a) + (y*y)/(b*b) == 1
```

Another definition states that the sum of the distances from every point 
of the ellipse to the focal points is constant (2x longest axis).


### Related

- https://en.wikipedia.org/wiki/Ellipse
- https://www.youtube.com/watch?v=5nW3nJhBHL0
- https://www.mathsisfun.com/geometry/ellipse-perimeter.html
- https://web.tecnico.ulisboa.pt/~mcasquilho/compute/com/,ellips/PerimeterOfEllipse.pdf (serious math)


## Interface

```cpp
#include "ellipse.h"
```

### Constructor

- **ellipse(float a, float b)** constructor.
The user is responsible that A >= B.

### Area Circumference

- **float area()** returns the area of the ellipse.
- **float circumference()** good algorithm (= Ramanujan 1).

### Attributes

The user is responsible that A >= B.

- **float eccentricity()** return the eccentricity e.
This is an indication of flatness of the ellipse. 
0 is a circle and 1 is flat line.
- **float ratio()** returns B / A.
- **void  setA(float a)** change the long radius.
- **void  setB(float b)** change the short radius.
- **float getA()** returns value set in constructor or setA().
- **float getB()** returns value set in constructor or setB().
- **float getC()** distance to focus point form centre along the longer axis.
Compares A and B to find longest radius. 
A.k.a. linear eccentricity.
- **float getH()** often used parameter in ellipses math, no physical meaning known.
- **float getLongRadius()** get longest radius of the ellipse.
Compares A and B to find longest.
- **float getShortRadius()** get shortest radius of the ellipse.
Compares A and B to find shortest.

### Perimeter algorithms

Perimeter == circumference

- **float perimeter_reference()** slower, best known algorithm (Ramanujan2)
- **float perimeter_Kepler()** good and fast algorithm for A/B between 1 and 2.
- **float perimeter_Ramanujan1()** good algorithm.
- **float perimeter_Parker()** Matt Parker's algorithm, not symmetric.
- **float perimeter_Ramanujan2()** slower, best known algorithm.
- **float perimeter_binomial()** very slow, as accurate as Ramanujan2.
Higher accuracy possible by adding more terms.
- **float perimeter_Parker_fast()** very fast, approximation only.
- **float perimeter_polynome()** fast, approximation only (better than Parker_fast, 2x slower). 
Formula is a quadratic approximation of Ramanujan2.



Numbers from version 0.1.4

|   A  |   B  |   ecc.     |  algorithm   |  time  |  circumference  |
|:----:|:----:|:----------:|:-------------|:------:|:---------------:|
|  10  |  10  |  0.000000  |  Ramanujan1  |   104  |  62.8319        |
|  10  |  10  |  0.000000  |  Ramanujan2  |   120  |  62.8319        |
|  10  |  10  |  0.000000  |  Kepler      |    36  |  62.8319        |
|  10  |  10  |  0.000000  |  Parker      |   160  |  62.8296        |
|      |      |            |              |        |                 |
|  10  |   5  |  0.866025  |  Ramanujan1  |   104  |  48.4421        |
|  10  |   5  |  0.866025  |  Ramanujan2  |   188  |  48.4422        |
|  10  |   5  |  0.866025  |  Kepler      |    32  |  48.4422        |
|  10  |   5  |  0.866025  |  Parker      |   160  |  48.4411        |
|      |      |            |              |        |                 |
|  10  |   1  |  0.994987  |  Ramanujan1  |   108  |  40.6055        |
|  10  |   1  |  0.994987  |  Ramanujan2  |   188  |  40.6393        |
|  10  |   1  |  0.994987  |  Kepler      |    36  |  34.5575        |
|  10  |   1  |  0.994987  |  Parker      |   164  |  40.5942        |

Note the failing Kepler function for high eccentricity.

Run ellipse_performance.ino example for latest version.


### Convenience functions

- **bool isCircle(float epsilon = 0.0)**  | a - b | < eps.
- **bool isFlat()** true if a > 4b, where a = longest radius.


### Experimental

- **float angle()** returns the angle in degrees if the ellipse was the
shadow of a circle. Returns 0..90°, 0° == circle, 90° == line.


## Operation

See examples.


## Future

#### Must

- improve documentation
  - refer Wikipedia.

#### Should

- make constructor symmetric (a < b or a > b ==> all possible.
- make other code symmetric.
- force A is long radius, so it is clear.
- implement unit tests

#### Could

- add math checks like DIV_ZERO
- replace float by double? (performance penalty!).
- additional functions (See wikipedia)
  - e.g. float latusRectum() = (bxb)/a
  

#### Wont
- Bresenham to draw ellipse? (not a drawing lib)


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

