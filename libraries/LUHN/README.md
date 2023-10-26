
[![Arduino CI](https://github.com/RobTillaart/LUHN/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/LUHN/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/LUHN/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/LUHN/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/LUHN/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/LUHN.svg)](https://github.com/RobTillaart/LUHN/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/LUHN/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/LUHN.svg?maxAge=3600)](https://github.com/RobTillaart/LUHN/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/LUHN.svg)](https://registry.platformio.org/libraries/robtillaart/LUHN)


# LUHN

Arduino Library for calculating LUHN checksum.


## Description

The LUHN algorithm is a checksum (a.k.a. mod 10) invented by **Hans Peter Luhn** in 1960. 
It is used to validate a variety of product ID's to detect typing errors an/of digit swaps.
So it is not to secure a number but to prevent common mistakes when entering a code in a system.
The LUHN check uses very few resources and is pretty fast. 

Basic idea is to put all digits-1 through the formula and the output should equal the last digit.

This LUHN library also includes a "stream" based LUHN calculation, in which digits can be add 
one at a time (from a stream) and it will return the LUHN checksum so far.
This is a new application as LUHN depends on the length of the input being odd or even.
To handle this two values are maintained (for odd and even lengths) and the correct one is returned.

Maintaining two checksums makes the stream **add(c)** algorithm substantial slower (~4x) than 
the normally used **generateChecksum(buffer)** or the **isValid(buffer)**. 
However that is a small price for the new functionality.

The amount of data that can be added in stream mode is infinite in theory.
However that is not tested for obvious reasons, internally a 32 bit counter exists.


#### Notes

- some LUHN validations uses the reversed product string.
- 0.1.x versions are obsolete due to incorrect math.


#### Related

- https://en.wikipedia.org/wiki/Luhn_algorithm
- https://github.com/RobTillaart/Adler
- https://github.com/RobTillaart/CRC
- https://github.com/RobTillaart/Fletcher
- https://github.com/RobTillaart/LUHN


## Interface

```cpp
#include "LUHN.h"
```

- **LUHN()** constructor
- **bool isValid(char \* buffer )** validates the code in the parameter buffer. 
The parameter buffer is a '\0' terminated char array. Length should be less than 254.
- **bool isValid(const char \* buffer )** idem.
- **char generateChecksum(char \* buffer)**
Returns the char '0'..'9' which is the checksum of the code in the parameter buffer.
The parameter buffer is a '\0' terminated char array. Length should be less than 254.
- **char generateChecksum(const char \* buffer)** idem.
- **bool generate(char \* buffer, uint8_t length, char \* prefix)**
Generates a char array including LUHN number with a defined prefix of max length.
Returns false if the prefix exceeds length -1.


#### Stream

- **char add(char c)** add char, returns LUHN so far.
- **char reset()** return last LUHN.
- **uint32_t count()** return internal counter.
If this value is zero, a new LUHN can be calculated, otherwise call **reset()** first.

The internal counter for the stream interface is 32 bit.
This limits the number of add() calls to about 4 billion.
For current implementation the counter is used for even/odd detection,
and even when it overflows one gets the correct **LUHN**.


## Future

#### Must

#### Should

- look for optimizations
  - common code **isValid()** and **generateChecksum()**

#### Could

#### Won't (unless)

- create a HEX equivalent of LUHN
  - LUHN16 ?
  - easy to enter HEX code with verify / line.
  - mod N configurable so not only 10 but any N?
- uint64_t interface for up to 17 digits.
  - expensive on small processors.
- uint32_t interface for up to 8 digit ID's (99.999.999)
  - **isValid(uint32_t)**
  - **generateChecksum(uint32_t)**
  - how about leading zero's


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


