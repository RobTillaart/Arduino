
[![Arduino CI](https://github.com/RobTillaart/HC4052/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/HC4052/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/HC4052/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/HC4052/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/HC4052/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/HC4052/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/HC4052.svg?maxAge=3600)](https://github.com/RobTillaart/HC4052/releases)


# HC4052

HC4052 is an Arduino library for a HC4052 2 x 4 channel multiplexer.


## Description

HC4052 is a library to control the CD74HC4052 8 channel
multiplexer / demultiplexer and compatible devices.

The HC4052 allows e.g one analog port read up to 8 different analog channels,
or one digital port to read the state of 8 buttons.


The channel selection is done with four select lines **A, B, C**

The device can be enabled/disabled by the enable line **INH**


#### Compatibles

to elaborate.


#### Related to 

- https://github.com/RobTillaart/HC4051  (1x8 mux)
- https://github.com/RobTillaart/HC4052  (2x8 mux)
- https://github.com/RobTillaart/HC4053  (3x2 mux)
- https://github.com/RobTillaart/HC4067  (1x16 mux)


## Hardware connection

Typical connection is to connect the four **select pins** to four IO Pins of your board.

The optional **enablePin (INH)** must be connected to GND if not used.
This way the device is continuous enabled.

Example multiplexing analog in.

```
        processor                      HC4052
     +-------------+              +-------------+
     |             |              |             |
     |           A |------------->| A        X0 |
     |           B |------------->| B        X1 |
     |      enable |------------->| INH      X2 |
     |             |              |          X3 |
     | analog in   |<-------------| X           |
     |             |              |             |
     | analog in   |<-------------| Y        Y0 |
     |             |              |          Y1 |
     |         GND |--------------| GND      Y2 |
     |             |              | VCC      Y3 |
     |             |              |             |
     +-------------+              +-------------+
```


## Interface

```cpp
#include "HC4052.h"
```

#### Core

- **HC4052(uint8_t A, uint8_t B, uint8_t enablePin = 255)** constructor.
Set the two select pins and optional the enable pin.
If the enablePin == 255 it is considered not used.
- **void setChannel(uint8_t channel)** set the current channel.
Valid values 0..3, this value is not checked, only the lower 2 bits will be used.
- **uint8_t getChannel()** get current channel 0..3.


#### Enable

These functions work only if enablePin is set in the constructor.

- **void enable()** idem.
- **void disable()** idem.
- **bool isEnabled()** idem.
Also returns true if enablePin is not set.


## Future

- keep in sync with HC4067 et.al.

