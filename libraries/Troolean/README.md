
[![Arduino CI](https://github.com/RobTillaart/Troolean/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/Troolean/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/Troolean/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/Troolean/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/Troolean/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/Troolean.svg)](https://github.com/RobTillaart/Troolean/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Troolean/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Troolean.svg?maxAge=3600)](https://github.com/RobTillaart/Troolean/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/Troolean.svg)](https://registry.platformio.org/libraries/robtillaart/Troolean)


# Troolean

Arduino Library for a three state logic data type supporting {True False Unknown}.


## Description

Troolean is a data type that implements three state logic with the values 
{True False Unknown }

Logic operators are similar to boolean and behave the same for the familiar boolean values.

Trooleans can be used e.g. to indicate a value is valid, invalid or unknown to be valid or not.
Imagine a monitoring application which has different sensors e.g. temperature. 
If the sensor is sampled less than 1 minute ago one could say the value is valid.
If the last sample is taken more than an hour ago it could have changed (a lot) or not. 
So one does not know if the temperature has become invalid or not. 
Boolean logic would make it invalid, but troolean allows to state we just don't know. 
As long as there is no urgency (need a valid value) one does not need to resample yet.

See also https://en.wikipedia.org/wiki/Three-valued_logic


## Interface

```cpp
#include "Troolean.h"
```

#### Constructor
- **Troolean()** value is unknown.
- **Troolean(const int8_t)** 0 = false, -1 = unknown anything else = true
- **Troolean(const Troolean&)** copy constructor.

#### Equality operators
- **bool operator ==** equals
- **bool operator !=** not equal
- **operator bool()** convert to boolean.

#### Logical operators
- **Troolean operator !  ** negation, not UNKNOWN == UNKNOWN.
- **Troolean operator && ** AND
- **Troolean operator || ** OR

#### Value operators
- **bool isTrue()** if not false and if not unknown.
- **bool isFalse()** idem.
- **bool isUnknown()** idem.


## Operation

See examples


## Future

#### Must

- fix **isTrue()** to allow internal values to be anything except 0 and -1  (0.2.0)
- check logical operators.
- update documentation

#### Should

- add unit tests  (derive from test troolean.ino?)
- add examples

#### Could

- Troolean operator &&=
- Troolean operator ||=
- bool toBool(); // returns random true/false if unknown....

#### Wont

- extend with don't care ?  ==> four state logic ?  Foolean?
  - => new class.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


