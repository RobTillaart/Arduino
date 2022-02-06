
[![Arduino CI](https://github.com/RobTillaart/Soundex/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/Soundex/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/Soundex/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/Soundex/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/Soundex/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Soundex/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Soundex.svg?maxAge=3600)](https://github.com/RobTillaart/Soundex/releases)


# Soundex

Arduino Library for calculating Soundex hash.


## Description

This library generates a (string based) hash based upon how a word sounds. 
This algorithm is called Soundex. 
The original algorithm was developed by Robert C. Russell and Margaret King Odell over 100 years ago. 
There are several variations of Soundex and these might be supported in the future.

The algorithm roughly copies the uppercase first letter of the word, followed by 3 digits replacing the consonants.

The base Soundex has 26 x 7 x 7 x 7 = 8918 possible outcomes, this could be encoded in an uint16_t. 


#### Links

- https://en.wikipedia.org/wiki/Soundex
- https://en.wikipedia.org/wiki/Metaphone  (not implemented)


## Interface

Use **\#include "Soundex.h"**

- **Soundex()** Constructor.
- **void setLength(uint8_t length = 4)** Sets the length to include more digits. max length = 11
- **uint8_t getLength()** returns current length.
- **char \* soundex(const char \* str)** determines the (Russell & Odell) Soundex code of the string.



#### Performance

Not tested ESP32 (and many other platforms) yet.
First numbers of **.soundex(str)** measured with test sketch shows the following timing per word.

| Checksum    | digits |  UNO 16 MHz | ESP32 240 MHz |
|:------------|:------:|:-----------:|:-------------:|
| Soundex     |   3    |     32 us   |               |



## Operation

See examples.


## Future ideas

- more testing
  - other platforms
  - different key lengths
  - string lengths
  - performance
- numeric version of Soundex
  - store in an uint16_t (bit fields 5,3,4,4)
  - uint16_t soundexN(const char \* str).
- efficient storage of the Soundex array
  - encode in nibbles. (13 bytes instead of 26) => more code, performance?
    0x01, 0x23, 0x01 etc.
- Other algorithms might be added in the future.
  - Daitch–Mokotoff Soundex 
  - Beider-Morse Soundex
  - Metaphone


