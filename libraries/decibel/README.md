
[![Arduino CI](https://github.com/RobTillaart/decibel/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/decibel/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/decibel/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/decibel/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/decibel/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/decibel.svg)](https://github.com/RobTillaart/decibel/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/decibel/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/decibel.svg?maxAge=3600)](https://github.com/RobTillaart/decibel/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/decibel.svg)](https://registry.platformio.org/libraries/robtillaart/decibel)


# decibel

Arduino library for fast decibel calculation.


## Description

**Experimental**

This library is used to calculate decibel, or **dB** of a value.

Decibel is in fact a logarithmic scaling and calculating dB is straightforward, 
often from a single value or from a ratio e.g. gain in dB uses output / input.

```cpp
dB = 10 x log10(value);
dB = 10 x log10(value1 / value2);
```

Decibel is often used in audio as our hearing is sort of logarithmic.
When the maximum output is defined as 1, so the amplification range is from 0..1
the dB scale goes from -infinity to 0, in practice the lower value
is not infinity but e.g. goes from -63 to 0.

The goal of the library is to provide a function to calculate
the dB value faster with less accuracy.
For many applications e.g. display the value this is good enough.

The library also provides an **inverseDecibel()** function to reverse the math. 
This can be used e.g. to calculate the output / input values from the gain.

Feedback, as always is welcome.


### Related

- https://github.com/RobTillaart/fast_math
- https://github.com/RobTillaart?tab=repositories&q=math


### Performance

INdicative times in microseconds per call.

|  Function          |  UNO  |  ESP32  |  Notes  |
|:-------------------|:-----:|:-------:|:--------|
|  decibel()         |  176  |   13.4  |
|  inverseDecibel()  |  204  |   11.8  |
|  decibelFast()     |   80  |   0.46  |
|                    |       |         |

On AVR the decibelFast() is more than 2x as fast.

There is no inverseDBFast() function (yet).


### Accuracy decibelFast

The sketch **decibel_compare.ino** compares the output of the
**decibel()** and the **decibelFast()**

In this sketch the largest absolute error = 0.003993 if steps are 0.001.
So the error seems to be smaller than 0.4%.

The average absolute error = 0.000984 if steps are 0.001, which
is roughly 0.1%.

From the above indications one can conclude that the **decibelFast()** 
will always give 2 or more correct decimals.

If these errors are acceptable differs per application and depends 
on your requirements.


### Accuracy inverseDecibel

The sketch **decibel_inverse.ino** compares the input of the
**decibel()** and the output of **inverseDecibel()**

The accuracy in the test is 6 decimals, which is acceptable when 
using (4 byte) float.


## Interface

```cpp
#include "decibel.h"
```

- **float decibel(float alpha)** calculate the decibel value.
This implementation takes the absolute value of alpha so negative values
will not return NAN.
If alpha == 0 the return value is "inf" == infinity.
- **float inverseDecibel(float alpha)** reverse math.
Will always return a positive value.
- **float decibelFast(float alpha)** calculates the decibel value,
less accurate but faster.


## Future

#### Must

- improve documentation
- test on more hardware

#### Should


#### Could

- use of double for the accurate functions?
- find related functions to include?

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


