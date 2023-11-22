
[![Arduino CI](https://github.com/RobTillaart/tinySHT2x/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/tinySHT2x/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/tinySHT2x/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/tinySHT2x/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/tinySHT2x/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/tinySHT2x.svg)](https://github.com/RobTillaart/tinySHT2x/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/tinySHT2x/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/tinySHT2x.svg?maxAge=3600)](https://github.com/RobTillaart/tinySHT2x/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/tinySHT2x.svg)](https://registry.platformio.org/libraries/robtillaart/tinySHT2x)


# tinySHT2x

Arduino library specific for AVR tiny processors. 


## Description

**Experimental**

Not portable, AVR only

#### Related

Based upon https://github.com/RobTillaart/SHT2x


## Interface

```cpp
#include "tinySHT2x.h"
```

- see https://github.com/RobTillaart/SHT2x


## Future

#### Must

- test test test test (Viktor)
- improve documentation

#### Should

#### Could

- Can a tiny have another Wire than Wire?
- Check the status bit (temperature / humidity flag) 
  - datasheet page 8, LSB bit 1 - bit 0 not used)
  - needed?
- Move Wire parameter to constructor?


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,
