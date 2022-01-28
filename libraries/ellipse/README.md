
[![Arduino CI](https://github.com/RobTillaart/ellipse/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/ellipse/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/ellipse/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/ellipse/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/ellipse/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/ellipse/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/ellipse.svg?maxAge=3600)](https://github.com/RobTillaart/ellipse/releases)


# ellipse

Arduino library with ellipse math


## Description

This experimental library provides basic ellipse math. 
It was written to test different perimeter algorithms.

Trigger was a video of Dr. Matt Parker.
 https://www.youtube.com/watch?v=5nW3nJhBHL0


## Interface

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

- **float perimeter_ref()** slower but best known algorithm (Ramanujan 2)
- **float perimeter_Keppler()** good and fast algorithm for eccentricity between 1 and 2.
- **float perimeter_Ramanujan1()** good algorithm.
- **float perimeter_Ramanujan2()** slow but best known algorithm.

See performance example for differences in timing.


## Operation

See examples.


## Future

- make constructor symmetric (a < b or a > b ==> all possible.
- make other code symmetric.
- additional functions
  - **bool isCircle()**  a == b
  - **bool isFlat()**  a > 4 \* b ?
  - bresenham to draw ellipse?
- documentation
  - refer wikipedia.


