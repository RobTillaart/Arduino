
[![Arduino CI](https://github.com/RobTillaart/FLE/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/FLE/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/FLE.svg?maxAge=3600)](https://github.com/RobTillaart/FLE/releases)

# FLE

Arduino library for Arduino library for float with error datatype

## Description

This experimental library provides basic math when have a quantity with a certain 
error margin. E.g. when you approximate PI as 22/7 it is not exact. By doing the 
math with FLE's one can see how much error adds up in an calculation.


## Interface

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
- **PrintTo(Print& p)** printable interface, define a stream to pritn to.  
Format is "val ± err" see above (plusminus = char(0177))
- **setDecimals(n)** will print the FLE bot val and err with n decimals.
- **setSeparator(char c)** overrules the standard ± char. (0177)
- **value()** returns val part
- **error()** return err part
- **relError()** returns relative error, except when val == 0. 
Then it return 0. Q: should this be "NaN
- **high()** returns val + error margin (= max real value)
- **low()** returns val - error margin (= min real value)

furthermore the basic math is implemented, "+, -, *, /, +=, -=, *=, /="

## Todo

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

## Operation

- negative numbers not tested yet

See example
