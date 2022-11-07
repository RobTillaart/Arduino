
[![Arduino CI](https://github.com/RobTillaart/Fraction/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/Fraction/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/Fraction/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/Fraction/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/Fraction/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Fraction/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Fraction.svg?maxAge=3600)](https://github.com/RobTillaart/Fraction/releases)


# Fraction

Arduino library to implement a Fraction data type (experimental).


## Description

The fraction library implements fractional numbers a.k.a. Q, 
(integers are Z and floats/doubles are R),
and the conversion to floats.

The code is working with a number of limitations among others:
- denominator is max 4 digits to keep code for multiply and divide simple
- Fractions are not exact (even floats are not exact)
- the range of numbers supported is limited.
- code is experimental still.

That said, the library is useful e.g. to display float numbers as a fraction.
From programming point of view the **fractionize()** function, converting a double
into a fraction is a nice programming problem, fast with a minimal error.

In short, use fractions with care otherwise your sketch might get broken ;)


## Operations

See examples


## Use with care

The library is reasonably tested, and if problems arise please let me know.


## Future

#### must
- improve documentation
- test test test ...

#### should
- investigate divide by zero errors
- investigate better fractionize() - depends on nom/denom size

#### could
- extend unit tests
- experiment with bigger nominator/denominator using all of 32767 possibilities ?
- add famous constants as Fraction e.g FRAC_PI = (355, 113) ??

