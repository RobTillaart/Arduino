
[![Arduino CI](https://github.com/RobTillaart/relativity/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/relativity/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/relativity/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/relativity/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/relativity/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/relativity.svg)](https://github.com/RobTillaart/relativity/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/relativity/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/relativity.svg?maxAge=3600)](https://github.com/RobTillaart/relativity/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/relativity.svg)](https://registry.platformio.org/libraries/robtillaart/relativity)


# relativity

Arduino library with relativity functions.


## Description

This experimental library implements a number of functions that give an
indication of the time dilation etcetera due to relativistic speed.

Goal: Educational purposes or when one puts a cube-sat into space :)


## Interface

```cpp
#include "relativity.h"
```

- **relativity()** constructor.
- **double getC()** returns speed of light.
- **double getG()** returns gravitational constant.
- **double factor(double speed)** returns sqrt(1-v2/c2).
- **double gamma(double speed)** returns 1/sqrt(1-v2/c2).
- **double relativeTime(double time, double speed)** returns the relative time for given time and speed.
- **double relativeLength(double length, double speed)** returns the relative length for given length and speed.
- **double relativeMass(double mass, double speed)** returns the relative mass for given mass and speed.
- **double EnergyMass(double mass, double speed)** returns the energyMass for given mass and speed. Think E = mc^2.


### Caching variants

These functions are the same however the math to calculate a given factor and gamma is done only once and cached. 
So these functions will perform a bit better, especially if floating point is slow.

- **void setSpeed(double speed = 0)** set the speed and calculate the factor and gamma to minimize math for next functions.
- **double getSpeed()** returns speed set.
- **double getFactor()** returns factor for speed set.
- **double getGamma()** returns gamma for speed set.
- **double relativeTime(double time)** returns the relative time for speed set with **setSpeed()**.
- **double relativeLength(double length)** returns the relative length for speed set.
- **double relativeMass(double mass)** returns the relative mass for speed set.
- **double EnergyMass(double mass)** returns the energy mass for for speed set.


### Gravity effects

- **double gravitationalTime(double time, double speed)** returns time dilation due to gravitational effects.
- **double diameterEarth(double longitude = 45)** calculates the diameter of the Earth given it is not a nice 
circle but more an ellipse, flatter on the poles and thicker on the equator.
Longitude is in degrees -90 .. 90.
- **double getPlanetMass(uint8_t n)** returns planet mass in **kg** 
where parameter n: 0 = Sun, 1 = Mercury etc.
- **double getPlanetRadius(uint8_t n)** returns planet radius in **km** 
where parameter n: 0 = Sun, 1 = Mercury etc.


## Operations

See examples for typical usage.


## Future

#### Must

- documentation

#### Should

- test test test test

#### Could

- Split .h into .h and .cpp
- add more functions
  - Schwarzschild horizon etc
- fix some overflow conditions.
- add moons?
  - need a database :)
- add caching version of mass / radius;
- move code to .cpp

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

