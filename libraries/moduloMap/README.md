
[![Arduino CI](https://github.com/RobTillaart/moduloMap/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/moduloMap/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/moduloMap/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/moduloMap/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/moduloMap/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/moduloMap/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/moduloMap.svg?maxAge=3600)](https://github.com/RobTillaart/moduloMap/releases)


# moduloMap

Arduino library for the moduloMap class.


## Description

The moduloMap is an experimental library that optimizes modular mapping.

What is modular mapping?

Imagine the mapping of all real numbers on a subset in a modular way.
E.g. map all the real numbers to  \[7; 13>  that is module 6, with numbers 7..13 do not change as they are already in the range.
6 is mapped on 12, 5 on 11, 4 on 10, .. 1 on 7, 0 on 12 -1 on 11 etc.

Imagine a line rolled around a circle.

Better known example is the modular mapping of angles.
This can be on 0-360 degrees or 0-2PI radians or -180-180 degrees
or even -90..270 degrees.

Other name might be circular mapping.


## Version

0.1.0 is initial version, the reference implementation.


## Interface

- **moduloMap()** constructor.
- **void begin(float minimum, float maximum)**
- **float map(float value)**


## Operation

The examples show the basic working of the functions.


## Future
- elaborate documentation
- optimize performance
- add examples
- move code to .cpp file
- add changelog.md
- add performance test
- are there other than circular modulos
  - triangular, fractal?
- add link to related libraries
  - angles + fastmap?
- elaborate API.

