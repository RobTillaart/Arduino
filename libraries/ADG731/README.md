
[![Arduino CI](https://github.com/RobTillaart/ADG731/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/ADG731/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/ADG731/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/ADG731/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/ADG731/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/ADG731/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/ADG731.svg?maxAge=3600)](https://github.com/RobTillaart/ADG731/releases)


# ADG731

Arduino library for ADG731 - 32 to 1 channel multiplexer.


## Description

**Experimental**

ADG731 is an Arduino class that controls a 1 x 32 multiplexer over a SPI
like interface.
Only one of the 32 channels can be connected at the same time.
The library also support to set them all off (17th state).

This library can be used to connect 32 analog devices to one analog port.

On power-up, all switches are in the OFF state.

This library can be used e.g. to connect 32 analog devices to 
one analog port, or to select between 32 DHT22 sensors.

Not tests with hardware have been done yet, so use with care.
Feedback welcome!


TODO insert picture.


#### Related

- https://github.com/RobTillaart/HC4051 (1x8 mux)
- https://github.com/RobTillaart/HC4052 (2x8 mux)
- https://github.com/RobTillaart/HC4053 (3x2 mux)
- https://github.com/RobTillaart/HC4067 (1x16 mux)
- https://github.com/RobTillaart/ADG725 (2x16 mux)
- https://github.com/RobTillaart/ADG731 (1x32 mux)


## Interface

```cpp
#include "ADG731.h"
```

- **ADG731(uint8_t clockPin, uint8_t dataPin, uint8_t syncPin)** constructor.
- **void setChannel(uint8_t channel)** set the current channel.
Valid values for channel are 0..31.
- **uint8_t getChannel()** get last set channel == 0..31 or ADG731_ALLOFF.
- **uint8_t channelCount()** returns 32 for ADG731.


## Future

#### Must

- improve documentation
- test with hardware

#### Should

- add examples
- check performance

#### Could


#### Wont


