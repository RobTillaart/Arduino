
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

#### 0.1.2

The library has 2 new experimental functions, **soundex16()** and **soundex32()**. 
These functions pack a Soundex length 5 hash in a uint16_t and a length 10 in a uint32_t.

Advantages: 
- better hash
- saves 60% of RAM, 
- allows faster comparisons.
- printable as HEX

Disadvantage:
- unknown / new.


The hash codes of these new SoundexNN() are a continuous numeric range.

| Checksum  | bytes | chars | range/values  | used  |  notes      |
|:----------|:-----:|:-----:|--------------:|:-----:|:------------|
| soundex   |   5   |  4    |         8.917 | 1e-6% | default     |
| soundex16 |   2   |  5    |        62.425 | 95.3% | 0xF3D9      |
| soundex32 |   4   |  10   | 1.049.193.781 | 24.4% | 0x3E89 6D35 |

Note that soundex16 and soundex32 compresses info much better than
the standard soundex.



#### Links

- https://en.wikipedia.org/wiki/Soundex
- https://en.wikipedia.org/wiki/Metaphone  (not implemented)


## Interface

Use **\#include "Soundex.h"**

- **Soundex()** Constructor.
- **void setLength(uint8_t length = 4)** Sets the length to include more digits. max length = 11
- **uint8_t getLength()** returns current length.
- **char \* soundex(const char \* str)** determines the (Russell & Odell) Soundex code of the string.
- **uint16_t soundex16(const char \* str)** determines the (Russell & Odell) Soundex code with length 5
of the string and packs it in an uint16_t.
Note: preferably printed in HEX.
- **uint32_t soundex32(const char \* str)** determines the (Russell & Odell) Soundex code with length 10
of the string and packs it in an uint16_t.
Note: preferably printed in HEX.


#### Performance

Not tested ESP32 (and many other platforms) yet.
First numbers of **.soundex("Trichloroethylene")** measured with a test sketch shows the following timing per word.

| Checksum  | digits | UNO 16 MHz | ESP32 240 MHz | notes |
|:----------|:------:|:----------:|:-------------:|:------|
| soundex   |   4    |    28 us   |     4 us      |
| soundex16 |   5    |    48 us   |     6 us      | not optimized
| soundex32 |   10   |   120 us   |    10 us      | not optimized


## Operation

See examples.


## Future ideas

- more testing
  - other platforms
  - different key lengths
  - string lengths
  - performance
- efficient storage of the Soundex array
  - encode in nibbles. (13 bytes instead of 26) => more code, performance?
    0x01, 0x23, 0x01 etc.
- Other algorithms might be added in the future.
  - reverse_soundex()
  - Daitch–Mokotoff Soundex 
  - Beider-Morse Soundex
  - Metaphone


