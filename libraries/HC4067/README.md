
[![Arduino CI](https://github.com/RobTillaart/HC4067/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/HC4067/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/HC4067/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/HC4067/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/HC4067/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/HC4067/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/HC4067.svg?maxAge=3600)](https://github.com/RobTillaart/HC4067/releases)


# HC4067

HC4067 is an Arduino library for a HC4067 16 channel multiplexer.


## Description

HC4067 is a library to control the CD74HC4067 16 channel
multiplexer / demultiplexer and compatible devices.

The HC4067 allows e.g one analog port read up to 16 different analog channels,
or one digital port to read the state of 16 buttons.


The channel selection is done with four select lines **S0..S3**

The device can be enabled/disabled by the enable line **E**


#### Compatibles

Not tested, considered compatible.
- CD74HC4067, 74HC4067, 74HCT4067


## Hardware connection

Typical connection is to connect the four **select pins** to four IO Pins of your board.

The optional **enablePin E** must be connected to GND if not used.
This way the device is continuous enabled.

Example multiplexing analog in.

```
        processor                      HC4067
     +-------------+              +-------------+
     |             |              |             |
     |          S0 |------------->| S0       Y0 |
     |          S1 |------------->| S1       Y1 |
     |          S2 |------------->| S2       Y2 |
     |          S3 |------------->| S3       Y3 |
     |             |              |          Y4 |
     |          E  |------------->| Enable   Y5 |
     |             |              |          Y6 |
     |             |              |          Y7 |
     |         A0  |<-------------| Z        Y8 |
     |             |              |          Y9 |
     |             |              |         Y10 |
     |             |              |         Y11 |
     |             |              |         Y12 |
     |             |              |         Y13 |
     |        GND  |--------------| GND     Y14 |
     |             |              | VCC     Y15 |
     |             |              |             |
     +-------------+              +-------------+
```


## Interface

```cpp
#include "HC4067.h"
```

#### Core

- **HC4067(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t enablePin = 255)** constructor.
Set the 4 select pins and optional the enable pin.
If the enablePin == 255 it is considered not used.
- **void setChannel(uint8_t channel)** set the current channel.
Valid values 0..15, this value is not checked, only the lower 4 bits will be used.
- **uint8_t getChannel()** get current channel 0..15.


#### Enable

These functions work only if enablePin is set in the constructor.

- **void enable()** idem.
- **void disable()** idem.
- **bool isEnabled()** idem.
Also returns true if enablePin is not set.


## Future

#### Must

- elaborate documentation
  - links etc.


#### Should

- optimizations
  - performance setChannel
- investigate how to use with only 3 lines or 2 lines.
  - set s3 / s2 to LOW always or so


#### Could

- next() and prev() as channel selector.
  - internal channel variable needed.
- move code to .cpp file
- investigate
  - can it be used as 16 channel OUTPUT (yes but)
  - is it buffered?


#### Won't (unless requested)

- optimizations
  - only do digitalWrite when changed? gain is minimal.
  - now takes 24 micros on UNO if set.

