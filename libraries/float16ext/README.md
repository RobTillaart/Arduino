
[![Arduino CI](https://github.com/RobTillaart/float16ext/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/float16ext/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/float16ext/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/float16ext/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/float16ext/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/float16ext.svg)](https://github.com/RobTillaart/float16ext/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/float16ext/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/float16ext.svg?maxAge=3600)](https://github.com/RobTillaart/float16ext/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/float16ext.svg)](https://registry.platformio.org/libraries/robtillaart/float16ext)

# float16ext

Arduino library to implement float16ext data type.


## Description

This **experimental** library defines the float16ext (2 byte) data type, including conversion
function to and from float32 type. It is an extension to the float16 library.
Reference -https://en.wikipedia.org/wiki/Half-precision_floating-point_format#ARM_alternative_half-precision

The library implements the **Printable** interface so one can directly print the
float16ext values in any stream e.g. Serial.

The primary usage of the float16ext data type is to efficiently store and transport
a floating point number. As it uses only 2 bytes where float and double have typical
4 and 8 bytes, gains can be made at the price of range and precision.

Note that float16ext only has ~3 significant digits.


#### Difference with float16

The float16ext library has an extended range as it supports values from +- 65504 
to +- 131008.

The float16ext does not support INF, -INF and NAN. These values are mapped upon
the largest positive, the largest negative and the largest positive number.

The -0 and 0 values will both exist.


Although they share a lot of code float16 and float16ext should not be mixed.
In the future these libraries might merge / derive one from the other.


## Specifications

layout is same as float16.

| attribute | value        |  notes  |
|:----------|:-------------|:--------|
| size      | 2 bytes      | layout s  eeeee  mmmmmmmmmm  (1, 5, 10)
| sign      | 1 bit        |
| exponent  | 5 bit        |
| mantissa  | 10 bit       | ~ 3 digits
| minimum   | 5.96046 E−8  |  smallest positive number.
|           | 1.0009765625 |  1 + 2^−10 = smallest number larger than 1.
| maximum   | 131008       |
|           |              |


#### Related

- https://github.com/RobTillaart/float16
- https://en.wikipedia.org/wiki/Half-precision_floating-point_format


## Interface

```cpp
#include "float16ext.h"
```

#### Constructors

- **float16ext(void)** defaults to zero.
- **float16ext(double f)** constructor.
- **float16ext(const float16ext &f)** copy constructor.


#### Conversion

- **double toDouble(void)** convert to double (or float).
- **uint16_t getBinary()** get the 2 byte binary representation.
- **void setBinary(uint16_t u)** set the 2 bytes binary representation.
- **size_t printTo(Print& p) const** Printable interface.
- **void setDecimals(uint8_t d)** idem, used for printTo.
- **uint8_t getDecimals()** idem.

Note the setDecimals takes one byte per object which is not efficient for arrays of float16ext.
See array example for efficient storage using set/getBinary() functions.


#### Compare

Standard compare functions. Since 0.1.5 these are quite optimized,
so it is fast to compare e.g. 2 measurements.

- **bool operator == (const float16ext& f)**
- **bool operator != (const float16ext& f)**
- **bool operator >  (const float16ext& f)**
- **bool operator >= (const float16ext& f)**
- **bool operator <  (const float16ext& f)**
- **bool operator <= (const float16ext& f)**


#### Math (basic)

Math is done by converting to double, do the math and convert back.
These operators are added for convenience only.
Not planned to optimize these.

- **float16ext operator + (const float16ext& f)**
- **float16ext operator - (const float16ext& f)**
- **float16ext operator \* (const float16ext& f)**
- **float16ext operator / (const float16ext& f)**
- **float16ext& operator += (const float16ext& f)**
- **float16ext& operator -= (const float16ext& f)**
- **float16ext& operator \*= (const float16ext& f)**
- **float16ext& operator /= (const float16ext& f)**

negation operator.
- **float16ext operator - ()** fast negation.

- **int sign()** returns 1 == positive, 0 == zero,  -1 == negative.
- **bool isZero()** returns true if zero. slightly faster than **sign()**.


## Notes


## Future

#### Must

- update documentation.
- keep in sync with float16 lib

#### Should


#### Could


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

