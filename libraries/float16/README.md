

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
a floating point number. As it uses only 2 bytes where float and double have typical 
4 and 8 bytes, gains can be made at the price of range and precision.


## Specifications


| attribute | value        |  notes  |
|:----------|:-------------|:--------|
| size      | 2 bytes      | layout s  eeeee  mmmmmmmmmm
| sign      | 1 bit        |            
| exponent  | 5 bit        |            
| mantissa  | 11 bit       | ~ 3 digits 
| minimum   | 5.96046 E−8  |  smallest positive number. 
|           | 1.0009765625 |  1 + 2^−10 = smallest nr larger than 1. 
| maximum   | 65504        |            
|           |              |            


## Interface

to elaborate

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


## Notes


## Future


#### 0.1.6

- update documentation.
- unit tests of the above.
- isNan().


#### later

- update documentation.
- error handling.
  - divide by zero errors.
- look for optimizations.
- rewrite **f16tof32()** with bit magic.
- add storage example - with SD card, FRAM or EEPROM
- add communication example - serial or Ethernet?

