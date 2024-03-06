
[![Arduino CI](https://github.com/RobTillaart/float16/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/float16/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/float16/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/float16/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/float16/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/float16.svg)](https://github.com/RobTillaart/float16/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/float16/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/float16.svg?maxAge=3600)](https://github.com/RobTillaart/float16/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/float16.svg)](https://registry.platformio.org/libraries/robtillaart/float16)

# float16

Arduino library to implement float16 data type.


## Description

This **experimental** library defines the float16 (2 byte) data type, including conversion
function to and from float32 type. It is definitely **work in progress**.

The library implements the **Printable** interface so one can directly print the
float16 values in any stream e.g. Serial.

The primary usage of the float16 data type is to efficiently store and transport
a floating point number. As it uses only 2 bytes where float and double have typical
4 and 8 bytes, gains can be made at the price of range and precision.


#### Breaking change 0.2.0

Version 0.2.0 has a breaking change as a conversion bug has been found.
See for details in issue #10.
For some specific values the mantissa overflowed when the float 16 was 
assigned a value to. This overflow was not detected / corrected.

During the analysis of this bug it became clear that the sub-normal numbers 
were also implemented correctly. This is fixed too in 0.2.0.

There is still an issue 0 versus -0

**This makes all pre-0.2.0 version obsolete.** 


## Specifications


| attribute | value        |  notes  |
|:----------|:-------------|:--------|
| size      | 2 bytes      | layout s  eeeee  mmmmmmmmmm  (1,5,10)
| sign      | 1 bit        |
| exponent  | 5 bit        |
| mantissa  | 10 bit       | ~ 3 digits
| minimum   | 5.96046 E−8  |  smallest positive number.
|           | 1.0009765625 |  1 + 2^−10 = smallest number larger than 1.
| maximum   | 65504        |
|           |              |


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

    0    11111    0000000000 = infinity
    1    11111    0000000000 = −infinity

    0    01101    0101010101 = 0.333251953125 ≈ 1/3
*/
```


#### Related

- https://wokwi.com/projects/376313228108456961  (demo of its usage)


## Interface

```cpp
#include "float16.h"
```

#### Constructors

- **float16(void)** defaults to zero.
- **float16(double f)** constructor.
- **float16(const float16 &f)** copy constructor.


#### Conversion

- **double toDouble(void)** convert to double (or float).
- **uint16_t getBinary()** get the 2 byte binary representation.
- **void setBinary(uint16_t u)** set the 2 bytes binary representation.
- **size_t printTo(Print& p) const** Printable interface.
- **void setDecimals(uint8_t d)** idem, used for printTo.
- **uint8_t getDecimals()** idem.

Note the setDecimals takes one byte per object which is not efficient for arrays of float16.
See array example for efficient storage using set/getBinary() functions.


#### Compare

Standard compare functions. Since 0.1.5 these are quite optimized,
so it is fast to compare e.g. 2 measurements.

- **bool operator == (const float16& f)**
- **bool operator != (const float16& f)**
- **bool operator >  (const float16& f)**
- **bool operator >= (const float16& f)**
- **bool operator <  (const float16& f)**
- **bool operator <= (const float16& f)**


#### Math (basic)

Math is done by converting to double, do the math and convert back.
These operators are added for convenience only.
Not planned to optimize these.

- **float16 operator + (const float16& f)**
- **float16 operator - (const float16& f)**
- **float16 operator \* (const float16& f)**
- **float16 operator / (const float16& f)**
- **float16& operator += (const float16& f)**
- **float16& operator -= (const float16& f)**
- **float16& operator \*= (const float16& f)**
- **float16& operator /= (const float16& f)**

negation operator.
- **float16 operator - ()** fast negation.

- **int sign()** returns 1 == positive, 0 == zero,  -1 == negative.
- **bool isZero()** returns true if zero. slightly faster than **sign()**.
- **bool isInf()** returns true if value is (-)infinite.


#### Experimental 0.1.8

- **bool isNaN()** returns true if value is not a number.


## Notes


## Future

#### Must

- update documentation.

#### Should

- unit tests of the above.
- how to handle 0 == -0  (0x0000 == 0x8000)
- investigate ARM alternative half-precision
_ARM processors support (via a floating point control register bit) 
an "alternative half-precision" format, which does away with the 
special case for an exponent value of 31 (111112).[10] It is almost 
identical to the IEEE format, but there is no encoding for infinity or NaNs; 
instead, an exponent of 31 encodes normalized numbers in the range 65536 to 131008._


#### Could

- copy constructor?
- update documentation.
- error handling.
  - divide by zero errors.
- look for optimizations.
- rewrite **f16tof32()** with bit magic.
- add storage example - with SD card, FRAM or EEPROM
- add communication example - serial or Ethernet?

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

