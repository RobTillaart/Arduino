
[![Arduino CI](https://github.com/RobTillaart/LUHN/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/LUHN/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/LUHN/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/LUHN/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/LUHN/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/LUHN/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/LUHN.svg?maxAge=3600)](https://github.com/RobTillaart/LUHN/releases)


# LUHN

Arduino Library for calculating LUHN checksum.


## Description

The LUHN algorithm is a checksum (a.k.a. mod 10) invented by **Hans Peter Luhn** in 1960. 
It is used to validate a variety of product ID's to detect typing errors an/of digit swaps.
So it is not to secure a number but to prevent common mistakes when entering a code in a system.
The LUHN check uses very few resources and is pretty fast. 

Basic idea is to put all digits-1 through the formula and the output should equal the last digit.

Note: some LUHN validations uses the reversed product string.


#### related

- https://en.wikipedia.org/wiki/Luhn_algorithm
- https://github.com/RobTillaart/Adler
- https://github.com/RobTillaart/CRC


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
- **bool generate(char \* buffer, uint8_t length, char \* prefix)**
Generates a char array including LUHN number with a defined prefix of max length.
Returns false if the prefix exceeds length -1.


## Future

#### must

- update documentation

#### should

- unit tests
- look for optimization
- stream interface
  - **uint8_t add(char c)** add char, return luhn sofar
  - **uint8_t reset()** reset luhn, return last luhn or void?

#### could

- uint32_t interface for up to 8 digit ID's (99.999.999)
  - **isValid(uint32_t)**
  - **generateChecksum(uint32_t)**
  - how about leading zero's

