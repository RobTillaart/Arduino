
[![Arduino CI](https://github.com/RobTillaart/FLE/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/FLE/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/FLE/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/FLE/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/FLE/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/FLE.svg)](https://github.com/RobTillaart/FLE/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/FLE/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/FLE.svg?maxAge=3600)](https://github.com/RobTillaart/FLE/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/FLE.svg)](https://registry.platformio.org/libraries/robtillaart/FLE)


# FLE

Arduino library for Arduino library for float with error data type


## Description

This **experimental** library provides basic math when have a quantity with a certain 
error margin. E.g. when you approximate PI as 22/7 it is not exact. By doing the 
math with FLE's one can see how much error adds up in an calculation.

Note: This library is experimental and only usable for educational purposes.
There is no active development.


## Interface

```cpp
#include "FLE.h"
```


### Printable

The FLE class implements the public interface of Printable.
This allows you to print an FLE in human readable form.

```cpp
    FLE x(3.14, 0.002);
    x.setDecimals(4);
    Serial.println(x);                 // will print 3.1400 ± 0.0020
    Serial.println(x.setDecimals(2));  // will print 3.14 ± 0.00
    Serial.println(x.value());         // will print 3.14
```

When the ± char does not print correctly, one could change the font.


### Functions

- **FLE(val = 0, err = 0)** constructor, with default value and error set to 0.
- **PrintTo(Print& p)** printable interface, define a stream to print to.  
Format is "value ± error" see above (plus-minus ± = char(0177))
- **setDecimals(n)** will print the FLE both value and error with n decimals.
- **setSeparator(char c)** overrules the standard ± char. (0177)
- **value()** returns value part.
- **error()** return error part.
- **relError()** returns relative error, except when value == 0. 
Then the function returns 0. Q: should this be "NaN" ?
- **high()** returns value + error margin (= max real value).
- **low()** returns value - error margin (= min real value).

Furthermore the basic math is implemented, "+, -, \*, /, +=, -=, \*=, /="


#### Set like functions

- **bool in(FLE y)** x.in(y) returns true if x lies completely in y  (range is a subset)
- **FLE shared(FLE y)** returns the overlapping range. 


#### Weak propositions

Experimental.

- **bool peq(FLE &y)** possible equal.
- **bool pne(FLE &y)** possible not equal.
- **bool plt(FLE &y)** possible less than.
- **bool ple(FLE &y)** possible less equal.
- **bool pgt(FLE &y)** possible greater than.
- **bool pge(FLE &y)** possible greater equal.


## Operation

- negative numbers not tested yet

See example


## Future

#### Must

- update documentation

#### Should

#### Could

- comparison (investigate, what means equal or less than ..)
- functions log, exp,
- functions sqr, sqrt, pow
- functions sin, cos, tan (+ inverse + hyp)
- test ad infinitum 
- option to set the ± char for platforms that cannot print it.
- test negative numbers
- test large / small numbers.
- test other separator
- more demo sketches...

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

