
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

The primary usage of the float16ext data type is to efficiently store and transport
a floating point number. As it uses only 2 bytes where float and double have typical
4 and 8 bytes, gains can be made at the price of range and precision.

Note that float16ext only has ~3 significant digits.

To print a float16, one need to convert it with toFloat(), toDouble() or toString(decimals). 
The latter allows concatenation and further conversion to an char array.

In pre 0.3.0 version the Printable interface was implemented, but it has been removed
as it caused excessive memory usage when declaring arrays of float16.


#### ARM alternative half-precision

-https://en.wikipedia.org/wiki/Half-precision_floating-point_format#ARM_alternative_half-precision

_ARM processors support (via a floating point control register bit) 
an "alternative half-precision" format, which does away with the 
special case for an exponent value of 31 (111112).[10] It is almost 
identical to the IEEE format, but there is no encoding for infinity or NaNs; 
instead, an exponent of 31 encodes normalized numbers in the range 65536 to 131008._

Implemented in https://github.com/RobTillaart/float16ext class.


#### Difference with float16 and float16ext

The float16ext library has an extended range as it supports values from +- 65504 
to +- 131008.

The float16ext does not support INF, -INF and NAN. These values are mapped upon
the largest positive, the largest negative and the largest positive number.

The -0 and 0 values will both exist.


Although they share a lot of code float16 and float16ext should not be mixed.
In the future these libraries might merge / derive one from the other.


#### Breaking change 0.2.0

Version 0.3.0 has a breaking change. The **Printable** interface is removed as 
it causes larger than expected arrays of float 16 (See #16). On ESP8266 every
float16 object was 8 bytes and on AVR it was 5 bytes instead of the expected 2 bytes.

To support printing the class added two new conversion functions:
```cpp
f16.toFloat();
f16.toString(decimals);

Serial.println(f16.toFloat(), 4);
Serial.println(f16.toString(4));
```
This keeps printing relative easy.

The footprint of the library is now smaller and one can now create compact array's
of float16 elements using only 2 bytes per element.

## Specifications

layout is same as float16, however the range is different.

|  Attribute  |  Value          |  Notes  |
|:------------|:----------------|:--------|
|  size       |  2 bytes        |  layout s  eeeee  mmmmmmmmmm  (1, 5, 10)
|  sign       |  1 bit          |
|  exponent   |  5 bit          |
|  mantissa   |  10 bit         |  3 - 4 digits
|  minimum    |  ±5.96046 E−8   |  smallest number.
|             |  ±1.0009765625  |  1 + 2^−10 = smallest number larger than 1.
|  maximum    |  ±131008        |
|             |                 |

± = ALT 0177


#### Example values

Source: https://en.wikipedia.org/wiki/Half-precision_floating-point_format

```cpp
/*
   SIGN  EXP     MANTISSA
    0    01111    0000000000 = 1
    0    01111    0000000001 = 1 + 2−10 = 1.0009765625 (next smallest float after 1)
    1    10000    0000000000 = −2

    0    11110    1111111111 = 65504  (max half precision)

    0    00001    0000000000 = 2−14 ≈ 6.10352 × 10−5 (minimum positive normal)
    0    00000    1111111111 = 2−14 - 2−24 ≈ 6.09756 × 10−5 (maximum subnormal)
    0    00000    0000000001 = 2−24 ≈ 5.96046 × 10−8 (minimum positive subnormal)

    0    00000    0000000000 = 0
    1    00000    0000000000 = −0

    0    01101    0101010101 = 0.333251953125 ≈ 1/3
*/
```


#### Related

- https://github.com/RobTillaart/float16
- https://github.com/RobTillaart/float16ext
- https://github.com/RobTillaart/fraction
- https://en.wikipedia.org/wiki/Half-precision_floating-point_format


## Interface

```cpp
#include "float16ext.h"
```

#### Constructors

- **float16ext(void)** defaults value to zero.
- **float16ext(double f)** constructor.
- **float16ext(const float16ext &f)** copy constructor.


#### Conversion

- **double toDouble(void)** convert value to double or float (if the same e.g. UNO).
- **float toFloat(void)** convert value to float.
- **String toString(unsigned int decimals = 2)** convert value to a String with decimals.
Please note that the accuracy is only 3-4 digits for the whole number so use decimals
with care.


#### Export and store

To serialize the internal format e.g. to disk, two helper functions are available.

- **uint16_t getBinary()** get the 2 byte binary representation.
- **void setBinary(uint16_t u)** set the 2 bytes binary representation.


#### Compare

The library implement the standard compare functions. 
These are optimized, so it is fast to compare 2 float16ext values.

Note: comparison with a float or double always include a conversion.
You can improve performance by converting e.g. a threshold only once before comparison.

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

Negation operator.
- **float16ext operator - ()** fast negation.

Math helpers.
- **int sign()** returns 1 == positive, 0 == zero,  -1 == negative.
- **bool isZero()** returns true if zero. slightly faster than **sign()**.

The float16ext does not support INF or NAN.


## Future

#### Must

- update documentation.
- keep in sync with float16 lib where possible.

#### Should


#### Could


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

