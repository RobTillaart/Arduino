
[![Arduino CI](https://github.com/RobTillaart/LengthConverter/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/LengthConverter/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/LengthConverter/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/LengthConverter/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/LengthConverter/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/LengthConverter.svg)](https://github.com/RobTillaart/LengthConverter/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/LengthConverter/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/LengthConverter.svg?maxAge=3600)](https://github.com/RobTillaart/LengthConverter/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/LengthConverter.svg)](https://registry.platformio.org/libraries/robtillaart/LengthConverter)


# LengthConverter

Arduino library for to convert units of length.


## Description

**Experimental**

This library is a simple class to convert units of length from one
unit to another. This is done by converting to and from meters (SI unit).
Furthermore the library allows to add (subtract) other units of length.

Example.
```cpp
LC.setYard(3);
LC.addFoot(2.5);
LC.addMeter(1.5);
len = LC.getInch();
```

The conversion factors used might differ with your expectation, however 
there are different "standards" in different countries.
Tried to follow the international standards as much as possible.

There are several different categories, ranging in size, e.g. the
atomic units and the astronomical units. Mixing different units may
result in loss of precision.

Note that the internal representation is a double and this is on
several boards implemented as a 4 byte float with only 6-7 significant digits.

For the best results of mixing units, one should sort the values on size and
add them from small to large if possible. 
This approach gives the smallest error.

Although the library is written mainly to be used for educational purpose,
it can be used in other applications too. 

For the units supported see **LengthConverter.h**.
If units are missing, please let me know.

Feedback as always is welcome.



### Related

- https://github.com/RobTillaart/pressure - pressure conversions
- https://github.com/RobTillaart/Temperature - temperature conversions
- https://github.com/RobTillaart/VolumeConverter - volume conversions
- https://github.com/RobTillaart/printHelpers - print in scientific and engineering format


### Tested

Tested on Arduino UNO R3. Should work on all.


## Interface

```cpp
#include "LengthConverter.h"
```

Look into the .h for supported formats. 
In essence for every supported unit there are

- **void setUNIT(double value)** set the internal value from UNIT.
- **void addUNIT(double value)** add a value in UNIT to internal value.
- **double getUNIT()** return the value in UNIT.

Notes:
- To subtract a length use ```LC.addUNIT(-value)```.
- To add multiple same lengths use ```LC.addUNIT(value * N)```.


### Math

- **void multiply(double factor)** to multiply the internal value.
- **void divide(double factor)** to divide the internal value.


## Future

#### Must

- improve documentation

#### Should

- add more (obscure) units
- add examples
  - convert, add, multiply, divide

#### Could

- redo magic numbers? (too much?).
- create unit tests
- update keywords.txt

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


