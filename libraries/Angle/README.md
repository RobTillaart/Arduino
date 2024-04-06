
[![Arduino CI](https://github.com/RobTillaart/Angle/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/Angle/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/Angle/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/Angle/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/Angle/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/Angle.svg)](https://github.com/RobTillaart/Angle/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Angle/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Angle.svg?maxAge=3600)](https://github.com/RobTillaart/Angle/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/Angle.svg)](https://registry.platformio.org/libraries/robtillaart/Angle)


# Angle

Arduino library for basic math for Angles in degrees, minute, seconds and ten-thousands.


## Description

Angle is an Arduino class to print, compare and do basic maths with angles
in degrees, minutes seconds and ten-thousands. The class was created to be
able to print an angle with minutes and seconds instead of as a floating point
or radians.

To make the library more useful basic maths ( + - \* / ) 
and comparisons ( == != < <= > >= ) are added to the class.

The library implements the Printable interface, allowing one to call

**Serial.println(angle)** or **SD.print(angle)**.

Degree sign ° = ALT-0176 (Windows)


#### Related

- https://github.com/RobTillaart/AngleConvertor
- https://github.com/RobTillaart/AverageAngle
- https://github.com/RobTillaart/Angle
- https://github.com/RobTillaart/runningAngle


## Interface

```cpp
#include "Angle.h"
```

#### Constructors

- **Angle(int dd = 0, int mm = 0, int ss = 0, int tt = 0)** create an Angle, default is zero.
- **Angle(double alpha)** create an Angle from a double.
- **Angle(char \* str)** create an Angle from a string e.g. "45.31234".


#### Base

- **int sign()** returns -1 or 1.
- **int degree()** returns # degrees.
- **int minute()** returns # minutes.
- **int second()** returns # seconds.
- **int tenthousand()** returns # ten-thousands of a second.


#### Conversions

- **double toDouble()** returns the angle as a double (0..360.0, float on UNO).
- **double toRadians()** returns the angle in radians (0..TWO_PI).
- **void fromRadian(double rad)** create an angle from radians.

More conversions - https://github.com/RobTillaart/AngleConvertor


#### Equality operators

The library supports equality operator "==", "!=", "<" "<=" ">" and ">=" .


#### Math operators

- **negate** returns -angle.
- **addition** and **subtract** add angles to angles.
- **multiplication** and **division** multiply an angle with a double.
- **ratio**  ratio = Angle/Angle.


## Operation

See examples.


## Note

The library has not been tested extensively and it could still contain bugs. 
Especially the constructor does not check input so use it carefully.


## Future

#### Must

- improve documentation

#### Should

- Test normalize code
  - unit tests, sketch?
- test more 
  - TOCHECK in code
- improve code quality


#### Could

- optimize code where possible
  - low priority
- move all code to .cpp
- change output format to confirm standard 4°12'14.1234"

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


