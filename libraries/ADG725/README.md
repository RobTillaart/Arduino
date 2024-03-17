
[![Arduino CI](https://github.com/RobTillaart/ADG725/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/ADG725/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/ADG725/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/ADG725/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/ADG725/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/ADG725.svg)](https://github.com/RobTillaart/ADG725/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/ADG725/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/ADG725.svg?maxAge=3600)](https://github.com/RobTillaart/ADG725/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/ADG725.svg)](https://registry.platformio.org/libraries/robtillaart/ADG725)


# ADG725

Arduino library for ADG725 - 16 to 1 channel (2x) multiplexer.


## Description

**Experimental**

ADG725 is an Arduino class that controls two 16 to 1 multiplexers
(or 1 to 16 multiplexer) over a SPI like interface.

The channel selection is disjunct which means that only  
one of the 16 channels can be connected (selected) at the same time.
The channels can be set per multiplexer or together (same channel) in one call.
The library also support to set them all off (17th state).

On power-up, all switches are in the OFF state, so no channel is selected.

This library can be used e.g. to connect 16 analog devices (potmeters) to
one analog port, or to select between 16 DHT22 sensors.

No tests with hardware have been done yet, so use with care.
Feedback welcome!


#### Multiple ADG725 in parallel

**To be tested**

It seems possible to connect multiple ADG725 devices side by side and control 
them as one. This would allow to create e.g a fast 8x16 multiplexer.

If you want to control them separately, every device need its own **syncPin**
a.k.a. Chip Select Pin. The data- and clockPin can be shared.
If you want to control them as one, all three lines should be shared.


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
#include "ADG725.h"
```

- **ADG725(uint8_t clockPin, uint8_t dataPin, uint8_t syncPin)** constructor.
- **void setChannel(uint8_t channel)** set the current channel for both A and B.
Valid values for channel are 0..15.
- **void setChannelA(uint8_t channel)** set the current channel for A only.
Valid values for channel are 0..15.
- **void setChannelB(uint8_t channel)** set the current channel for B only.
Valid values for channel are 0..15.
- **uint8_t getChannelA()** get last set channel A == 0..15 or ADG725_ALLOFF (128).
- **uint8_t getChannelB()** get last set channel B == 0..15 or ADG725_ALLOFF (128).
- **uint8_t channelCount()** returns 16 for ADG725, convenience for loops.
- **void allOff()** sets all channels to OFF, no channel selected.

## Future

#### Must

- improve documentation
- test with hardware
- keep in sync with ADG726 (interface)

#### Should

- add examples
- test multiple ADG725 in parallel

#### Could


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

