
[![Arduino CI](https://github.com/RobTillaart/HC4053/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/HC4053/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/HC4053/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/HC4053/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/HC4053/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/HC4053.svg)](https://github.com/RobTillaart/HC4053/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/HC4053/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/HC4053.svg?maxAge=3600)](https://github.com/RobTillaart/HC4053/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/HC4053.svg)](https://registry.platformio.org/libraries/robtillaart/HC4053)


# HC4053

HC4053 is an Arduino library for a HC4053 3x2 channel multiplexer.


## Description

HC4053 is a library to control the CD74HC4053 3x2 channel
multiplexer / demultiplexer and compatible devices.

The HC4053 is in fact three separate controllable switches in one,
and every switch can be set indepently in one of two positions.
This is functionaly different from both the 4051, 4052 and 4067
in which there is only one channel selection

The independent channel selection is done with three select lines **A, B, C**.

The device can be enabled/disabled by the enable line **INH**


#### Compatibles

to elaborate.


#### Related to 

- https://github.com/RobTillaart/HC4051  (1x8 mux)
- https://github.com/RobTillaart/HC4052  (2x4 mux)
- https://github.com/RobTillaart/HC4053  (3x2 mux)
- https://github.com/RobTillaart/HC4067  (1x16 mux)


## Hardware connection

Typical connection is to connect the three **select pins** to three IO Pins of your board.

The optional **enablePin (INH)** must be connected to GND if not used.
This way the device is continuous enabled.

Example multiplexing 3x analog in.

```
        processor                      HC4053
     +-------------+              +-------------+
     |             |              |             |
     |           E |------------->| INH         |
     |             |              |             |
     |           A |------------->| A        X0 |
     | analog    X |<-------------| X        X1 |
     |             |              |             |
     |           B |------------->| B        Y0 |
     | analog    Y |<-------------| Y        Y1 |
     |             |              |             |
     |           C |------------->| C        Z0 |
     | analog    Z |<-------------| Z        Z1 |
     |             |              |             |
     |             |              |             |
     |             |              |             |
     |         GND |--------------| GND         |
     |             |              | VCC         |
     |             |              |             |
     +-------------+              +-------------+
```


## Interface

```cpp
#include "HC4053.h"
```

#### Core

- **HC4053(uint8_t A, uint8_t B, uint8_t C, uint8_t enablePin = 255)** constructor.
Set the three select pins and optional the enable pin.
If the enablePin == 255 it is considered not used.
- **void setChannel(uint8_t channel)** sets A, B and C to channel in one call.
Think of it as a master switch.
Valid values 0, 1, this value is not checked, only last bit is used.
Note the channels will not change at the very same moment.
- **void setChannelA(uint8_t channel)** sets A to channel.
Valid values 0, 1, this value is not checked, only last bit is used.
- **void setChannelB(uint8_t channel)** sets B to channel.
Valid values 0, 1, this value is not checked, only last bit is used.
- **void setChannelC(uint8_t channel)** sets C to channel.
Valid values 0, 1, this value is not checked, only last bit is used.
- **uint8_t getChannelA()** get current A channel 0 or 1.
- **uint8_t getChannelB()** get current B channel 0 or 1.
- **uint8_t getChannelC()** get current C channel 0 or 1.


#### Enable

These functions work only if enablePin is set in the constructor.

- **void enable()** idem.
- **void disable()** idem.
- **bool isEnabled()** idem.
Also returns true if enablePin is not set.


## Future

- keep in sync with HC4067 et.al.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

