
[![Arduino CI](https://github.com/RobTillaart/Soundex/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/Soundex/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/Soundex/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/Soundex/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/Soundex/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/Soundex.svg)](https://github.com/RobTillaart/Soundex/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Soundex/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Soundex.svg?maxAge=3600)](https://github.com/RobTillaart/Soundex/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/Soundex.svg)](https://registry.platformio.org/libraries/robtillaart/Soundex)


# Soundex

Arduino Library for calculating Soundex hash.


## Description

This library generates a (string based) hash based upon how a word sounds.
This algorithm is called Soundex.
The original algorithm was developed by Robert C. Russell and
Margaret King Odell over 100 years ago.
There are several variations of Soundex and these might be supported in the future.

The algorithm roughly copies the uppercase first letter of the word,
followed by 3 digits replacing the consonants.

The base Soundex has 26 x 7 x 7 x 7 = 8918 possible outcomes,
this could be easily encoded in an uint16_t.
This insight triggered the experimental functions **soundex16()** and **soundex32()**.
These experimental functions can be used e.g. to optimize word-searching 
as less bytes need to be compared / stored.


#### 0.1.2 Experimental

The library has two experimental functions, **soundex16()** and **soundex32()**.
These functions pack a Soundex length 5 hash in a uint16_t and a length 10 in a uint32_t.
They effectively compress the **soundex()** results.

Advantages (16 bit version):
- better hash as it adds 1 extra character
- saves 60% of RAM, (5 bytes vs 2 bytes).
- allows faster comparisons, (compare 2 bytes is faster than 5 )
- less storage/communication needed
- printable as HEX

Disadvantage:
- unknown / new.
- need extra processing.


The hash codes of these new SoundexNN() are a continuous numeric range.

|  Checksum   |  bytes  |  chars  |  range/values   |  used   |  notes       |
|:------------|:-------:|:-------:|----------------:|:-------:|:-------------|
|  soundex    |   5     |  4      |          8.917  |  1e-6%  |  default     |
|  soundex16  |   2     |  5      |         62.425  |  95.3%  |  0xF3D9      |
|  soundex32  |   4     |  10     |  1.049.193.781  |  24.4%  |  0x3E89 6D35 |

Note that soundex16() and soundex32() compresses info much better than
the standard soundex().


A **soundex64()** is technically possible and would use 8 bytes (not implemented).
It would allow to compress very long **soundex()** results (up to 22 chars) in 8 bytes.
Application might be chemical formulas.
It could use the **printHelper** library to print the uint64_t as HEX.


#### Related

- https://en.wikipedia.org/wiki/Soundex
- https://en.wikipedia.org/wiki/Metaphone  (not implemented)


## Interface

```cpp
#include "Soundex.h"
```

#### Core

- **Soundex()** Constructor.
- **void setLength(uint8_t length = 4)** Sets the length to include more digits.
Maximum length = SOUNDEX_MAX_LENGTH - 1 == 11 (default).
- **uint8_t getLength()** returns current length.
- **char \* soundex(const char \* str)** determines the (Russell & Odell) Soundex code of the string.

#### Experimental

- **uint16_t soundex16(const char \* str)** determines the (Russell & Odell) Soundex code with
length = 5 of the string and packs the result in an uint16_t.
Note: preferably printed in HEX.
- **uint32_t soundex32(const char \* str)** determines the (Russell & Odell) Soundex code with
length == 10 of the string and packs it in an uint32_t.
Note: preferably printed in HEX.


#### Performance

Not tested on other platforms.

First numbers of **soundex("Trichloroethylene")** measured with
a test sketch shows the following timing per word.

|  Checksum   |  digits  |  UNO 16 MHz  |  ESP32 240 MHz  |  notes  |
|:------------|:--------:|:------------:|:---------------:|:--------|
|  soundex    |    4     |     28 us    |      4 us       |
|  soundex16  |    5     |     48 us    |      6 us       | not optimized
|  soundex32  |    10    |    120 us    |     10 us       | not optimized


## Operation

See examples.


## Future

#### Must

- improve documentation
- add examples

#### Should

- more testing
  - other platforms
  - different key lengths
  - string lengths
  - performance

#### Could

- use spare bits of soundex16/32 as parity / checksum.
- add String interface e.g.
  - **String soundex(String str)**

#### Wont

- efficient storage of the Soundex array
  - encode in nibbles. (13 bytes instead of 26) => more code, performance?
    0x01, 0x23, 0x01 etc.
    (performance test was slower, gain in RAM == PROGMEM loss.
- Other algorithms might be added in the future.
  - reverse_soundex()
  - Daitch–Mokotoff Soundex
  - Beider-Morse Soundex
  - Metaphone


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

