
[![Arduino CI](https://github.com/RobTillaart/AngleConvertor/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AngleConvertor/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AngleConvertor/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AngleConvertor/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AngleConvertor/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AngleConvertor.svg)](https://github.com/RobTillaart/AngleConvertor/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AngleConvertor/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AngleConvertor.svg?maxAge=3600)](https://github.com/RobTillaart/AngleConvertor/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AngleConvertor.svg)](https://registry.platformio.org/libraries/robtillaart/AngleConvertor)


# AngleConvertor

Arduino library for converting angles (degrees/radians) to less known formats.


## Description

AngleConvertor is an Arduino class to convert an angle from and to less known formats.

Since 0.2.0 the class uses degrees as internal format as that improved precision a bit
compared to the pre-0.2.0 version that used radians.
Furthermore to improve precision the class uses doubles, so platforms that support these
can gain extra precision.


#### Formats


|  name           |  full circle  |  notes  |
|:----------------|--------------:|:--------|
|  Degrees        |          360  |
|  Radians        |         2 PI  |  2PI is aka MU
|  Gradians       |          400  |
|  AngularMil     |         6400  |
|  BinaryRadians  |          256  |
|  CentiTurn      |          100  |
|  DiameterPart   |          120  |
|  Hexacontade    |           60  |
|  HourAngle      |           24  |
|  MilliRadians   |      2000 PI  |
|  MilliTurn      |         1000  |
|  MinuteTime     |         1440  |
|  Octant         |            8  |
|  Pechus         |          180  |
|  Percent        |          100  |  equals CentiTurn.
|  Points         |           32  |
|  Quadrant       |            4  |
|  QuarterPoint   |          128  |
|  SecondsTime    |        86400  |
|  Sextant        |            6  |
|  Sign           |           12  |
|  Turn           |            1  |


#### Related

- https://github.com/RobTillaart/AngleConvertor
- https://github.com/RobTillaart/AverageAngle
- https://github.com/RobTillaart/Angle
- https://github.com/RobTillaart/runningAngle


## Interface

```cpp
#include "AngleConvertor.h"
```


#### Constructor

- **AngleConvertor()** create an AngleConvertor, default value is zero.


#### Setters

- **void setDegrees(double value = 0)**
- **void setRadians(double value = 0)**
- **void setGradians(double value = 0)**
- **void setAngularMil(double value = 0)**
- **void setBinaryRadians(double value = 0)**
- **void setCentiTurn(double value = 0)**
- **void setDiameterPart(double value = 0)**
- **void setHexacontade(double value = 0)**
- **void setHourAngle(double value = 0)**
- **void setMilliRadians(double value = 0)**
- **void setMilliTurn(double value = 0)**
- **void setMinuteTime(double value = 0)**
- **void setOctant(double value = 0)**
- **void setPechus(double value = 0)**
- **void setPercent(double value = 0)**
- **void setPoints(double value = 0)**
- **void setQuadrant(double value = 0)**
- **void setQuarterPoint(double value = 0)**
- **void setSecondsTime(double value = 0)**
- **void setSextant(double value = 0)**
- **void setSign(double value = 0)**
- **void setTurn(double value = 0)**


#### Getters

- **double getDegrees()**
- **double getRadians()**
- **double getGradians()**
- **double getAngularMil()**
- **double getBinaryRadians()**
- **double getCentiTurn()**
- **double getDiameterPart()**
- **double getHexacontade()**
- **double getHourAngle()**
- **double getMilliRadians()**
- **double getMilliTurn()**
- **double getMinuteTime()**
- **double getOctant()**
- **double getPechus()**
- **double getPercent()**
- **double getPoints()**
- **double getQuadrant()**
- **double getQuarterPoint()**
- **double getSecondsTime()**
- **double getSextant()**
- **double getSign()**
- **double getTurn()**


#### WindRose

From: https://forum.arduino.cc/t/function-optimization-wind-direction-open-for-ideas/92493/10

Converts an angle in degrees to a char array like "WSW".
0 and 360 degrees is considered North. 

- **char \* windrose()** converter version.
- **char \* windrose(double degrees)** stand alone version.
degrees should be between 0 and 360, as function does no normalization.


## Operation

See examples.


## Future

#### Must

- improve documentation

#### Should


#### Could

- add dedicated functions == faster (on request only).
- add more conversions
- integrate with **Angle class** ?
  - printing can be a lot of work
- windrose array in PROGMEM


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

