
[![Arduino CI](https://github.com/RobTillaart/Complex/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/Complex/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/Complex/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/Complex/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/Complex/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/Complex.svg)](https://github.com/RobTillaart/Complex/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Complex/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Complex.svg?maxAge=3600)](https://github.com/RobTillaart/Complex/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/Complex.svg)](https://registry.platformio.org/libraries/robtillaart/Complex)


# Complex

Arduino library for Complex mathematical operations.


## Description

This library defines the complex data type and all the common mathematical functions for it.

These functions include basic = "+ - \* /" and also power and goniometric functions.

The library implements the **Printable** interface so one can directly print the complex values
in any stream e.g. Serial.


## Interface

```cpp
#include "Complex.h"
```

See Complex.h for a full list of functions implemented.

The library uses **float** for the real and imaginary part so precision is limited.
Reasons are memory and performance, see also Future section below.

The library implements the constant **one** as this value is often used in the code.


## Note

The library has a big footprint so it fills up the memory of an UNO quite fast,
especially if all functionality is used.


#### Known problem

Issue found in version 0.1.9 - https://github.com/RobTillaart/Arduino/issues/90
Class does not compile for DUE and TEENSY
Also Raspberry Pico - https://github.com/RobTillaart/Complex/issues/6

Apparently the name "Complex" is already in use (reserved) by some non-AVR compilers 
so it won't include the Complex.h file. Problem seen on Due and Teensy3.5


#### Solution

- Make a copy of the Complex Library and rename the folder to CComplex
- Rename Complex.h to CComplex.h
- Rename Complex.cpp to CComplex.cpp
- change one line in CComplex.cpp to include CComplex.h
- note your sketches need to include CComplex.h too.


## Future

#### Must

- improve documentation

#### Should

#### Could

- create a (8 byte) double based variant for high precision e.g. Complex8()  
  - Note that some platforms map double to float
  - others support float in hardware etc.  
  - so expect a big difference in both memory and performance.

#### Wont

- create the constant **i** ??
  - => expect conflicts with int i...


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


