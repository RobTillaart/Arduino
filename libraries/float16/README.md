

[![Arduino CI](https://github.com/RobTillaart/float16/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/float16/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/float16/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/float16/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/float16/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/float16/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/float16.svg?maxAge=3600)](https://github.com/RobTillaart/Complex/releases)


# float16

Arduino library to implement float16 data type.


## Description

This **experimental** library defines the float16 (2 byte) data type, including conversion 
function to and from float32 type. It is definitely **work in progress**.

The library implements the **Printable** interface so one can directly print the 
float16 values in any stream e.g. Serial.

The primary usage of the float16 data type is to efficiently store and transport 
a floating point number. As it is only 2 bytes where float and double have typical 
4 and 8, gains can be made at the price of range and precision.


## Specifications


| attribute | value        |  notes       |
|:----------|:-------------|:-------------|
| Size      | 2 bytes      |              |
| sign      | 1 bit        |              |
| mantissa  | 11 bit       | ~ 3 digits   |
| exponent  | 4 bit        |              |
| minimum   | 1.0009765625 |  1 + 2^−10   |
| maximum   | 65504        |              |
|           |              |              |


## Interface

to elaborate

#### Constructors

- **float16(void)** defaults to zero.
- **float16(double f)** constructor.
- **float16(const float16 &f)** copy constructor.


#### Conversion

- **double toDouble(void)** convert to double (or float)
- **size_t printTo(Print& p) const** Printable interface.
- **void setDecimals(uint8_t d)** idem, used for printTo.
- **uint8_t getDecimals()** idem.

Note the setDecimals takes one byte per object which is not efficient for arrays.
See array example for efficient storage using set/getBinary() functions.


#### Compare

to elaborate


## Notes


#### comparison functions

First version of inequality operations are implemented by converting data to double and compare those. 
The strategy is to get these working first and optionally optimize them later.


## TODO (future)

to get focus on getting things done...


#### 0.1.4

the following should work:

- update documentation
- positive numbers
- negative numbers
- infinity
- rounding to zero (e.g. 1e-30)
- array of numbers.
- unit tests of the above..


#### 0.1.5

- update documentation
- comparison operators
- unit tests of the above..


#### 0.1.6

- update documentation
- get basic math working (+-*/)
- isNan()
- isINF()
- abs()
- sgn()
- unit tests of the above..


#### later

- update documentation
- get basic math II working += -= *= /=
- divide by zero errors.
- f16tof32() + f32tof16()
- rewrite toDouble with bit magic
- ...


