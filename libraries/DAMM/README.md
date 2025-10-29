
[![Arduino CI](https://github.com/RobTillaart/DAMM/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DAMM/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DAMM/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DAMM/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DAMM/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DAMM.svg)](https://github.com/RobTillaart/DAMM/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DAMM/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DAMM.svg?maxAge=3600)](https://github.com/RobTillaart/DAMM/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DAMM.svg)](https://registry.platformio.org/libraries/robtillaart/DAMM)


# DAMM

Arduino library for calculating DAMM checksum.


## Description

**Experimental**

The DAMM algorithm is a checksum (a.k.a. mod 10) invented by **H. Michael Damm** in 2004. 
It is used to validate a variety of product ID's to detect typing errors and/or digit swaps.
So it is not to secure a number but to prevent common mistakes when entering a code in a system.
A DAMM test is typically done before the characters are converted to digits.

The DAMM check uses a lookup per character in a 10x10 matrix of integers and is overall pretty fast.
This library has a DAMM_small class which uses a 10x5 matrix to save RAM and is slightly slower.

Basic idea of the DAMM test is to put all digits (minus last one) through the 'formula' 
and the output should equal the last digit. 

This DAMM library also includes a "stream" based DAMM calculation, in which digits or
characters can be add one at a time (from a stream) and it will return the DAMM checksum 
so far. This allows a stream to have a DAMM checksum e.g. after every 10 digits.

The amount of data that can be added in stream mode is infinite in theory.
However that is not tested for obvious reasons, internally a 32 bit counter exists.

Feedback as always is welcome.


### Related

- https://github.com/RobTillaart/Adler
- https://github.com/RobTillaart/CRC
- https://github.com/RobTillaart/DAMM
- https://github.com/RobTillaart/Fletcher
- https://github.com/RobTillaart/LUHN

Backgrounders

- https://en.wikipedia.org/wiki/Damm_algorithm
- https://en.wikipedia.org/wiki/Luhn_algorithm
- https://en.wikipedia.org/wiki/Verhoeff_algorithm (no Arduino code known)


## Performance

See damm_performance.ino.

The DAMM_small is about 50% slower than DAMM for generateChecksum().
In stream mode the difference is ~6% (AVR UNO R3).
Do your own test to see which class meets your need.


## Interface

```cpp
#include "DAMM.h"
```

The interface is kept similar to the LUHN library as it is related.

### Constructor

- **DAMM()** Constructor, faster version, uses 100 bytes matrix.
- **DAMM_small()** Constructor, slower version, uses 50 byte matrix.

### Normal mode

- **bool isValid(char \* buffer)** validates the code in the parameter buffer. 
The parameter buffer is a '\0' terminated char array. Length should be less than 254.
- **bool isValid(const char \* buffer )** idem.
- **char generateChecksum(char \* buffer)**
Returns the char '0'..'9' which is the checksum of the code in the parameter buffer.
The parameter buffer is a '\0' terminated char array. Length should be less than 254.
- **char generateChecksum(const char \* buffer)** idem.

### Stream mode

Note there is no parameter check in the code.

- **char add(int x)** add int type (0..9), returns DAMM so far. (actual workhorse).
- **char add(char c)** add char ('0'..'9'), returns DAMM so far.
- **char reset()** returns last DAMM, and resets the internals.
- **uint32_t count()** return internal counter.
If this value is zero, a new DAMM can be calculated, otherwise call **reset()** first.

The internal counter for the stream interface is 32 bit.
This limits the number of add() calls to about 4 billion.
Even when it overflows one gets the correct **DAMM** checksum.


## Future

#### Must

- improve documentation
- test
- keep in sync with LUHN if possible

#### Should

- can we make the faster version faster?
  - local lookup per function to squeeze
- add parameter check in the slower version (as it is already slower).
  - or interpret any char "mod 10" e.g. A = 0x61 ==> 0x01
  - new options / scope for DAMM check  (LUHN too?)

#### Could

- add generate() function (see LUHN library).
- investigate reset(start value) - might be useful to restart in a stream.
- investigate small / slow version as derived class

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


