
[![Arduino CI](https://github.com/RobTillaart/AngleConvertor/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AngleConvertor/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AngleConvertor/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AngleConvertor/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AngleConvertor/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AngleConvertor/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AngleConvertor.svg?maxAge=3600)](https://github.com/RobTillaart/AngleConvertor/releases)


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


#### Related to
- https://github.com/RobTillaart/AverageAngle
- https://github.com/RobTillaart/Angle
- https://github.com/RobTillaart/runningAngle


## Interface

#### Constructor

- **AngleConvertor()** create an AngleConvertor, default value is zero.


#### setters

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


#### getters

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


## Operation

See examples.


## Future

#### must
- improve documentation

#### should


#### could
- add dedicated functions == faster (on request only).
- add more conversions
- integrate with **Angle class** ?
  - printing can be a lot of work


