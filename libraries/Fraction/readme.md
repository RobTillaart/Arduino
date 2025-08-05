
[![Arduino CI](https://github.com/RobTillaart/Fraction/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/Fraction/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/Fraction/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/Fraction/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/Fraction/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/Fraction.svg)](https://github.com/RobTillaart/Fraction/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Fraction/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Fraction.svg?maxAge=3600)](https://github.com/RobTillaart/Fraction/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/Fraction.svg)](https://registry.platformio.org/libraries/robtillaart/Fraction)


# Fraction

Arduino library to implement a Fraction data type.


## Description

**Experimental**

The fraction library implements fractional numbers (a / b) a.k.a. Q
(integers are Z and floats/doubles are R). 
It supports conversion from and to floats (doubles), the basic math
and equality operators, a **toString()** for printing in fraction format,
and some fraction specific functions.

The code is working with a number of limitations a.o.:
- the nominator is an int32_t, so relative large values with a decimal part can be expressed.
- Denominator is max 4 digits (1..9999) to keep code for multiply and divide simple
- Fractions are not always an exact representation of floats, even floats are not exact.
- The range of numbers supported is limited.
- The code is experimental.

That said, the library is useful e.g. to display float numbers as a fraction,
or only to display the numerator.
From programming point of view the **fractionize(float)** function, for 
converting a double or float into a fraction is a nice programming problem.
How to do it, how to do it fast, how to minimize the absolute error.

In short, use fractions with care otherwise your sketch might get broken ;)


### Notes on natural order

Depending on **fractionize(float)** algorithm used the natural order of numbers
might be broken. 
This means that if two floats are very close:
```
float f  <  float g  does not imply  Fraction(f)  <  Fraction(g)
float f  >  float g  does not imply  Fraction(f)  >  Fraction(g)
```

The minimalistic **fractionize** (see examples) keeps the natural order due its simplicity.
It does have a lower accuracy as only limited number of denominators are used.
This means that if two floats are very close:
```
float f  <  float g  implies  Fraction(f)  <=  Fraction(g)
float f  >  float g  implies  Fraction(g)  >=  Fraction(f)
```


### 0.3.0 new fractionize() algorithm

Thanks to Edgar Bonet for a new, faster and more precise **fractionize()** algorithm
based upon **Simple continued fractions**.

The new algorithm can / will change previous expected outputs.


### 0.2.0 Breaking change 1

When testing with the array implementation it became evident that some
Fractions were incorrect (not just inaccurate). 

An analysis lead to using reciproke values for fractions larger than 1.
By excluding the integerPart the problem looks solved in most cases. 
For very small values there are still problems as the fraction cannot be determined. 

A test sketch **fraction_extensive.ino** has been added to test all floats 
with up to five decimals 0.00000 .. 0.99999.
Results looking good but it is no proof of correctness or guarantee there 
are no issues left. In fact the well known fraction for PI = 355/113 is not 
found in 0.2.0 any more. This will be investigated in the future.


### 0.2.0 Breaking change 2

The 0.1.x version implemented the **Printable** interface to allow direct 
printing of a Fraction object.
However it became clear that this costs 2 extra bytes per element, which adds up
when creating arrays of fractions.

So the **Printable** interface is removed and replaced by a **toString()** function.

```cpp
Fraction fr(PI);
Serial.print(fr.toString());
```

Fractions can also be printed by using **toFloat()** or **toDouble()**


### Related

- https://en.wikipedia.org/wiki/Simple_continued_fraction

For printing floats in scientific or engineering format

- https://github.com/RobTillaart/printHelpers


## Interface

```cpp
#include "fraction.h"
```

### Constructors

- **Fraction(int32_t nominator = 0, int32_t denominator = 1)** Default constructor, default value = zero.
- **explicit Fraction(double)** construct a fraction from a double.
- **explicit Fraction(float)** idem.
- **explicit Fraction(int32_t p)** idem.
- **explicit Fraction(int16_t p)** idem.
- **explicit Fraction(int8_t p)** idem.
- **explicit Fraction(uint32_t p)** idem.
- **explicit Fraction(uint16_t p)** idem.
- **explicit Fraction(uint8_t p)** idem.
- **Fraction(const Fraction &f)** copy constructor.

### Equalities

The Fraction library implements ==, !=, >=, >, <, <=

 - **bool operator == (const Fraction&)** idem.
 - **bool operator != (const Fraction&)** idem.
 - **bool operator >  (const Fraction&)** idem.
 - **bool operator >= (const Fraction&)** idem.
 - **bool operator <  (const Fraction&)** idem.
 - **bool operator <= (const Fraction&)** idem.

### Basic Math

The Fraction library implements the following basic math:
- addition: + and += 
- subtraction: - and -+
- multiplication: \* and \*=
- division: / and /=
- negation: -

### Conversion

- **int32_t toInt32()** returns int(n/d), e.g. 17/4 => 4.
Truncates, no rounding, for rounding use ```round(F.toFloat());```
- **double toDouble()** converts the fraction to a double.
- **float toFloat()** converts the fraction to a float.
- **String toString()** converts the fraction to a String.
The format is "(n/d)", where n has optionally the sign.
- **bool isProper()** returns true if -1 < fraction < 1. Or the abs(fraction) < 1
- **float toAngle()** returns -180..180 degrees - uses atan2()
- **int32_t nominator()** returns the nominator.
- **int32_t denominator()** returns the denominator.

### Miscellaneous

Both mediant() and middle() can be used for e.g. a binary search.
Mediant() is slightly faster.

- **Fraction mediant(const Fraction& a, const Fraction& b)** mediant returns a fraction
that will always lie between fraction a and fraction b.
- **Fraction middle(const Fraction& a, const Fraction& d)** middle returns a fraction 
that lies in the mathematical middle of fraction a and fraction b.
- **Fraction setDenominator(const Fraction&, uint16_t)** returns a fraction with a 
defined denominator, (might be simplified still), e.g. power of 2.
- **Fraction reciprocal()** F = 1.0 / F, effectively swap nominator and denominator. 

## Use with care

The library is reasonably tested. If problems arise please open an issue.


## Future

#### Must

- improve documentation
- test test test ...

#### Should

- **float fractionize()** returns the error.
- investigate divide by zero errors
  - NAN in fraction?  =>  0/0 ?
  - INF in fraction?  =>  1/0 and -1/0?

#### Could

- extend unit tests
- experiment with bigger nominator/denominator using all of 32767 possibilities ?
- add famous constants as Fraction e.g 
  - FRAC_NULL = 0/1
  - FRAC_ONE  = 1/1
  - FRAC_PI   = 355/113
  - FRAC_E    = 3985/1466
  - FRAC_GOLDEN_RATIO = (2584/1597)
- **double stepsize()** ==> 1/abs(d)

#### Wont

- add parameters to **toString()** to set () and separator?
  e.g. **toString(char separator = '/', char open = '(', char close = ')')** 


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

