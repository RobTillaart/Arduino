
[![Arduino CI](https://github.com/RobTillaart/VolumeConverter/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/VolumeConverter/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/VolumeConverter/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/VolumeConverter/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/VolumeConverter/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/VolumeConverter.svg)](https://github.com/RobTillaart/VolumeConverter/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/VolumeConverter/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/VolumeConverter.svg?maxAge=3600)](https://github.com/RobTillaart/VolumeConverter/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/VolumeConverter.svg)](https://registry.platformio.org/libraries/robtillaart/VolumeConverter)


# VolumeConverter

Arduino library to convert volume units.


## Description

VolumeConverter is a library containing a VolumeConverter class.

It consists of setters to set a certain volume in one of the
many supported units. Internally it is converted to liters.
Then the user can use a getter to get the volume in one of the
supported units.

Besides conversion the class also allows one to add different
units and convert them.

The purpose of the library is conversion and can be used for
educational programs too.

The library is open for additions, including obscure volume metrics 
and volume related math functions and constants.
Also good examples (e.g. educational) are welcome.


#### Accuracy

As the library uses floats the accuracy is limited especially
if one tries to add or convert the extremes of the scales.
E.g. Long tons to teaspoons will loose significant digits.


## Interface

```cpp
#include "VolumeConverter.h"
```

Internal representation is the **liter** as it the ISO standard.

#### Constructor

- **VolumeConverter()** sets the internal value to 0.

#### Setters

- **void setLiters(float value = 0)**
- **void setMilliLiters(float value = 0)**
- **void setCubicMeters(float value = 0)**
- **void setLongTons(float value = 0)**
- **void setShortTons(float value = 0)**
- **void setBarrels(float value = 0)**
- **void setGallons(float value = 0)**
- **void setQuarts(float value = 0)**
- **void setPints(float value = 0)**
- **void setCups(float value = 0)**
- **void setFluidOunces(float value = 0)**
- **void setTableSpoons(float value = 0)**
- **void setTeaSpoons(float value = 0)**

#### Adders

- **void addLiters(float value = 0)**
- **void addMilliLiters(float value = 0)**
- **void addCubicMeters(float value = 0)**
- **void addLongTons(float value = 0)**
- **void addShortTons(float value = 0)**
- **void addBarrels(float value = 0)**
- **void addGallons(float value = 0)**
- **void addQuarts(float value = 0)**
- **void addPints(float value = 0)**
- **void addCups(float value = 0)**
- **void addFluidOunces(float value = 0)**
- **void addTableSpoons(float value = 0)**
- **void addTeaSpoons(float value = 0)**

#### getters

- **float getLiters()**
- **float getMilliLiters()**
- **float getCubicMeters()**
- **float getLongTons()**
- **float getShortTons()**
- **float getBarrels()**
- **float getGallons()**
- **float getQuarts()**
- **float getPints()**
- **float getCups()**
- **float getFluidOunces()**
- **float getTableSpoons()**
- **float getTeaSpoons()**


## Future

#### Must

- improve documentation

#### Should

- consider using double instead of float.

#### Could

- add more unit tests
- add more examples

#### won't (unless)


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


