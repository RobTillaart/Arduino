
[![Arduino CI](https://github.com/RobTillaart/GAMMA/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/GAMMA/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/GAMMA/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/GAMMA/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/GAMMA/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/GAMMA.svg)](https://github.com/RobTillaart/GAMMA/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/GAMMA/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/GAMMA.svg?maxAge=3600)](https://github.com/RobTillaart/GAMMA/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/GAMMA.svg)](https://registry.platformio.org/libraries/robtillaart/GAMMA)


# GAMMA

Arduino Library for the GAMMA function to adjust brightness of LED's etc.


## Description

This library provides a GAMMA lookup class. It is typical used to
change the intensity / brightness of a LED to match the human eye.
When a LED is given 50% PWM it looks far brighter for the eye.

This lib provides a balance between an expensive math function and the speed
of a lookup table.

The accuracy of the library depends on the size of the internal array.
A size of 256 is the reference. Smaller arrays use interpolation and
these interpolated values are good (< 1%) down to internal array size 16.
The size can be as small as 2 which is pretty inaccurate.
In this latter case the curve is approximated by only two linear interpolations.
In short, choose the size that fits your application.

The library has a **setGamma(float gamma)** function that allows an application
to change the gamma value runtime.
This allows adjustments that are not possible with a fixed table.

The class provides **dump()** to create a table e.g. to place in PROGMEM.
Since 0.2.2 the library also has **dumpArray()** to generate a C-style array.

Note: tested on UNO and ESP32 only.


#### Related

- https://en.wikipedia.org/wiki/Gamma_correction
- https://github.com/RobTillaart/map2colour


## Interface

```cpp
#include "gamma.h"
```

### Core functions

- **GAMMA(uint16_t size = 32)** constructor, gets the size of the internal
array as parameter. The default for size = 32 as this is a good balance between performance
and size of the internal array.
The size parameter must be in {2, 4, 8, 16, 32, 64, 128, 256 }.
- **~GAMMA()** destructor.
- **bool begin()** The internal array is allocated and initialized with a gamma == 2.8.
This is an often used value to adjust light to human eye responses.
Note that **begin()** must be called before any other function.
Returns false if allocation fails.
- **void setGamma(float gamma)** calculates and fills the array with new values.
This can be done runtime so runtime adjustment of gamma mapping is possible.
This calculation are relative expensive and takes quite some time (depending on size).
If the array already is calculated for gamma, the calculation will be skipped.
The parameter **gamma** must be > 0. The value 1 gives an 1:1 mapping.
Returns false if gamma <= 0 or if no array is allocated.
- **float getGamma()** returns the set gamma value.
- **uint8_t operator \[uint8_t index\]** allows the GAMMA object to be accessed as an array.
like ```x = G[40];``` Makes it easy to switch with a real array.
The value returned is in the range 0 .. 255, so the user may need to scale it e.g. to 0.0 - 1.0.
Note: if internal array not allocated the function returns 0.
As this is a legitimate value the user should take care.


### Development functions

- **uint16_t size()** returns the size of the internal array.
This is always a power of 2.
- **uint16_t distinct()** returns the number of distinct values in the internal array.
Especially with larger internal arrays there will be more duplicate numbers.
- **bool dump(Stream \*str = &Serial)** dumps the internal array to a stream, default Serial.
Useful to create an array in RAM, PROGMEM, EEPROM, in a file or wherever.
Returns false if no array is allocated.
- **void dumpArray(Stream \*str = &Serial)** dumps the internal array to a stream, default Serial, as a C-style array. See example.
Returns false if no array is allocated.


## Operation

See example.


## Future ideas

#### Must

- improve documentation

#### Should

- test other platforms

#### Could

- uint16 version?
  - GAMMA16,
  - GAMMA32,
  - GAMMA_RGB ?

#### Wont

- look for optimizations (done in 0.4.0)
  - getter \[\]
  - setGamma -> pow() is expensive
  - setGamma(gamma)  gamma = 1.0 is linear, less math (too specific?)


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

