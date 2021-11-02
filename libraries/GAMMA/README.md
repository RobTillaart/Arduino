
[![Arduino CI](https://github.com/RobTillaart/GAMMA/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/GAMMA/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/GAMMA/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/GAMMA/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/GAMMA/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/GAMMA/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/GAMMA.svg?maxAge=3600)](https://github.com/RobTillaart/GAMMA/releases)


# GAMMA

Arduino Library for the GAMMA function to adjust brightness of LED's etc.


## Description

This library is provides a gamma lookup class. It is typical used to 
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
This allows adjustments that a fixed table does not have.

The class can be used to dump the internal table e.g. to place in PROGMEM.

Note: tested on UNO and ESP32 only.


## Interface

### Core functions

- **GAMMA(uint16_t size = 32)** constructor, gets the size of the internal
array as parameter. The default for size = 32 as this is a good balance between performance
and size of the internal array. The size parameter must be in {2, 4, 8, 16, 32, 64, 128, 256 }.
- **begin()** The array is initialized with a gamma == 2.8 which is an often used value.  
**begin()** must be called before any other function.
- **setGamma(float gamma)** calculates and fills the array with new values.
This can be done runtime so runtime adjustment of gamma mapping.  
This function takes relative quite some time.
The parameter **gamma** must be > 0. The value 1 gives an 1:1 mapping.
- **getGamma()** returns the set gamma value.
- **operator \[\]** allows the GAMMA object to be accessed as an array.
like ```x = G[40];``` Makes it easy to switch with a real array.


### Development functions

- **size()** returns size of the internal array.
- **distinct()** returns the number of distinct values in the table. Especially with larger internal tables this will happen.
- **dump()** dumps the internal table to Serial. Can be useful to create
an array in RAM, PROGMEM or wherever.


## Operation

See example


## Future ideas

- test other platforms
- improve documentation
- look for optimizations 
- uint16 version?
-
