
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
Furthermore to improve precision the class uses doubles, so platforms that support 
the double data type can gain extra precision (might be slower).

If there are formats missing please open an issue, with a link to its description.

### Example

To convert from one less known format to another just takes two calls, example:

```cpp
  AngleConvertor AC;

  AC.setPechus(24.2);
  float x = AC.getAngularMil();
```

If you need to convert a lot of data between two formats, it is also possible to 
pre-calculate a factor so the conversion is faster.
On an UNO R3 the gain goes up almost 20%, see example below.


```cpp
  AngleConvertor AC;

  AC.setDegrees(1);  //  any non zero value will work.
  //  factor to convert Pechus to AngularMil
  float factor = AC.getAngularMil() / AC.getPechus();
  //  use the factor
  sum = 0;
  for (int i = 0; i < 1000; i++)
  {
    sum += i * factor;
  }

```

### 0.3.0

Add ADDERS, see below.
These functions are meant especially to add different units more efficiently.
Adding many times the same unit gives a lot of conversions which is far less 
efficient than adding them first and convert only once.


### Formats

|  name           |  full circle  |  notes  |
|:----------------|--------------:|:--------|
|  Degrees        |          360  |
|  Radians        |         2 PI  |  2 PI is aka MU = 6.283...
|  Gradians       |          400  |
|  AngularMil     |         6400  |
|  BinaryRadians  |          256  |
|  CentiTurn      |          100  |  equals percent
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

If units are missing, please open an issue.


### Related

- https://github.com/RobTillaart/AngleConvertor
- https://github.com/RobTillaart/AverageAngle
- https://github.com/RobTillaart/Angle
- https://github.com/RobTillaart/runningAngle
- https://github.com/RobTillaart/AS5600 - magnetic angle measurements

For printing floats in scientific or engineering format

https://github.com/RobTillaart/printHelpers


## Interface

```cpp
#include "AngleConvertor.h"
```

### Constructor

- **AngleConvertor()** create an AngleConvertor, default value is zero.


### Setters

Default value = 0 for all formats.

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

### Adders

No default to add, functions do not return a value. 
This could have been degrees, but why not radians or other.

The adders allow to add/subtract different formats easily, as shown 
in the extreme example below.

```cpp
  AngleConvertor AC;

  AC.setDegrees();  //  start value
  AC.addGRadians(125);
  AC.addAngularMil(-34.56);
  AC.addHexacontade(2.76);

  result = AC.getPercent();
```

Please not that adding one type - e.g. only radians can 

- **void addDegrees(double value)**
- **void addRadians(double value)**
- **void addGradians(double value)**
- **void addAngularMil(double value)**
- **void addBinaryRadians(double value)**
- **void addCentiTurn(double value)**
- **void addDiameterPart(double value)**
- **void addHexacontade(double value)**
- **void addHourAngle(double value)**
- **void addMilliRadians(double value)**
- **void addMilliTurn(double value)**
- **void addMinuteTime(double value)**
- **void addOctant(double value)**
- **void addPechus(double value)**
- **void addPercent(double value)**
- **void addPoints(double value)**
- **void addQuadrant(double value)**
- **void addQuarterPoint(double value)**
- **void addSecondsTime(double value)**
- **void addSextant(double value)**
- **void addSign(double value)**
- **void addTurn(double value)**

### Getters

The getters do not return a value "modulo full turns" so values
can be e.g. above 2 PI or below 0 radians.

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


### WindRose

From: https://forum.arduino.cc/t/function-optimization-wind-direction-open-for-ideas/92493/10

Converts an angle in degrees to a char array like "WSW".
0 and 360 degrees is considered North. 

- **char \* windrose()** converter version.
- **char \* windrose(double degrees)** stand alone version.
degrees should be between 0 and 360, as function does no normalization.


## Future

#### Must

- improve documentation

#### Should

- investigate constexpr double constants?

#### Could

- add more conversions
- integrate with **Angle class** ?
  - printing can be a lot of work
- windrose array in PROGMEM
- add add_SOME_UNIT(float), like in volumeConvertor class.
- extend unit tests.

#### Wont

- investigate fmod full turns? (getters flag?)


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

