
[![Arduino CI](https://github.com/RobTillaart/NeumannCorrector/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/NeumannCorrector/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/NeumannCorrector/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/NeumannCorrector/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/NeumannCorrector/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/NeumannCorrector.svg)](https://github.com/RobTillaart/NeumannCorrector/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/NeumannCorrector/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/NeumannCorrector.svg?maxAge=3600)](https://github.com/RobTillaart/NeumannCorrector/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/NeumannCorrector.svg)](https://registry.platformio.org/libraries/robtillaart/NeumannCorrector)


# NeumannCorrector

NeumannCorrector is an Arduino library for a correcting a random streams of bits.


## Description

**Experimental**

NeumannCorrector is an experimental library.
The goal of a NeumannCorrector is to extract a random stream of bits from a stream
that is unbalanced in the number of ones and zeros.
The working is based upon the fact that in such a stream there will always be an
equal amount of 0->1 transitions as 1->0 transitions.
The algorithm compares pairs of bits, resulting in an often substantial lower
bitrate at the outside. At least a factor 2 and often more (= worse).
For large number of bits the unbalance(skew/bias) is removed.

The 0.1.0 version is more or less a reference implementation.
It can be used for experiments and for educational purposes. 

As always remarks are welcome.


### Related to 

- https://github.com/RobTillaart/NeumannCorrector
- https://github.com/RobTillaart/DEVRANDOM
- https://github.com/RobTillaart/randomHelpers
- https://github.com/RobTillaart/Prandom
- https://link.springer.com/referenceworkentry/10.1007/978-1-4419-5906-5_520


## Interface

```cpp
#include "NeumannCorrector.h"
```

### Constructor + meta

- **NeumannCorrector()** constructor, internal size == 32 bits hardcoded
and can be command-line overruled.
- **void clear()** sets the index of the internal buffer to 0.
- **uint8_t available()** returns bits available in internal buffer.
- **uint8_t size()** returns the size of the internal buffer. 
Size of 32 is hardcoded, and can be command-line overruled.

### Add

- **void add(uint8_t in)** adds zero or more bits of the parameter to the internal buffer.

### Get

- **uint8_t get()** returns 8 bits from the internal buffer,
even if these are not (all) available.
- **uint16_t get16()** returns 16 bits from the internal buffer,
even if these are not (all) available.
- **uint32_t get32()** returns 32 bits from the internal buffer,
even if these are not (all) available.


## Future

#### Must

- documentation

#### Should


#### Could

- add XOR mask in constructor, to XOR every incoming value
  - or a multiply add shift mask?
- extend unit tests.
- add16() + add32() ?


#### Wont

- add a non-zero starting value for internal buffer?


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

