
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


#### Formats


|  name           |  full circle  |
|:----------------|--------------:|
|  Degrees        |          360  |
|  Radians        |         2 PI  |
|  Gradians       |          400  |
|  AngularMil     |         6400  |
|  BinaryRadians  |          256  |
|  CentiTurn      |          100  |
|  DiameterPart   |          120  |
|  Hexacontade    |           60  |
|  HourAngle      |           24  |
|  MilliTurn      |         1000  |
|  MinuteTime     |         1440  |
|  Octant         |            8  |
|  Pechus         |          180  |
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

- **void setDegrees(float value = 0)**
- **void setRadians(float value = 0)**
- **void setGradians(float value = 0)**
- **void setAngularMil(float value = 0)**
- **void setBinaryRadians(float value = 0)**
- **void setCentiTurn(float value = 0)**
- **void setDiameterPart(float value = 0)**
- **void setHexacontade(float value = 0)**
- **void setHourAngle(float value = 0)**
- **void setMilliTurn(float value = 0)**
- **void setMinuteTime(float value = 0)**
- **void setOctant(float value = 0)**
- **void setPechus(float value = 0)**
- **void setPoints(float value = 0)**
- **void setQuadrant(float value = 0)**
- **void setQuarterPoint(float value = 0)**
- **void setSecondsTime(float value = 0)**
- **void setSextant(float value = 0)**
- **void setSign(float value = 0)**
- **void setTurn(float value = 0)**


#### Getters

- **float getDegrees()**
- **float getRadians()**
- **float getGradians()**
- **float getAngularMil()**
- **float getBinaryRadians()**
- **float getCentiTurn()**
- **float getDiameterPart()**
- **float getHexacontade()**
- **float getHourAngle()**
- **float getMilliTurn()**
- **float getMinuteTime()**
- **float getOctant()**
- **float getPechus()**
- **float getPoints()**
- **float getQuadrant()**
- **float getQuarterPoint()**
- **float getSecondsTime()**
- **float getSextant()**
- **float getSign()**
- **float getTurn()**

#### WindRose


From: https://forum.arduino.cc/t/function-optimization-wind-direction-open-for-ideas/92493/10

Converts an angle in degrees to a char array like "WSW".
0 and 360 degrees is considered North. 

- **char \* windrose()** converter version.
- **char \* windrose(float degrees)** stand alone version.
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

