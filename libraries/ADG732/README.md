
[![Arduino CI](https://github.com/RobTillaart/ADG732/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/ADG732/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/ADG732/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/ADG732/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/ADG732/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/ADG732.svg)](https://github.com/RobTillaart/ADG732/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/ADG732/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/ADG732.svg?maxAge=3600)](https://github.com/RobTillaart/ADG732/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/ADG732.svg)](https://registry.platformio.org/libraries/robtillaart/ADG732)


# ADG732

Arduino library for ADG732 - 32 to 1 channel multiplexer.


## Description

**Experimental**

ADG732 is an Arduino class that controls a 1 x 32 multiplexer over a
**parallel** interface.
Only one of the 32 channels can be connected at the same time.
The library also support to select none (== 33th state).

On power-up, all switches are in the OFF state == none connected.

This library can be used e.g. to connect 32 analog devices to
one analog port, or to select between 32 DHT22 sensors.

No tests with hardware have been done yet, so use with care.
Feedback welcome!


#### Related

- https://github.com/RobTillaart/HC4051 (1x8 mux)
- https://github.com/RobTillaart/HC4052 (2x8 mux)
- https://github.com/RobTillaart/HC4053 (3x2 mux)
- https://github.com/RobTillaart/HC4067 (1x16 mux)
- https://github.com/RobTillaart/ADG725 (2x16 mux)
- https://github.com/RobTillaart/ADG726 (2x16 mux)
- https://github.com/RobTillaart/ADG731 (1x32 mux)
- https://github.com/RobTillaart/ADG732 (1x32 mux)


## Interface

```cpp
#include "ADG732.h"
```

- **ADG732(uint8_t A, uint8_t B, uint8_t C, uint8_t D, uint8_t E, uint8_t CS, uint8_t EN, uint8_t WR)** constructor.
- **ADG732(uint8_t address[5], uint8_t CS, uint8_t EN, uint8_t WR)** constructor.
- **void setChannel(uint8_t channel)** set the current channel for both A and B.
Valid values for channel are 0..31.
Numbers larger than 31 will be "wrapped" modulo 32.
- **uint8_t getChannel()** get last set channel A == 0..31 or ADG732_ALLOFF.
- **uint8_t channelCount()** returns 32 for ADG732.
- **void allOff()** sets all channels to OFF, none selected.


## Future

#### Must

- improve documentation
- test with hardware
- keep in sync with ADG731 (interface)

#### Should

- add examples

#### Could

- **bool setChannel(uint8_t channel)** return false if out of range?

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


