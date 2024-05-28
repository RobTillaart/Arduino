
[![Arduino CI](https://github.com/RobTillaart/HC4052/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/HC4052/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/HC4052/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/HC4052/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/HC4052/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/HC4052.svg)](https://github.com/RobTillaart/HC4052/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/HC4052/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/HC4052.svg?maxAge=3600)](https://github.com/RobTillaart/HC4052/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/HC4052.svg)](https://registry.platformio.org/libraries/robtillaart/HC4052)


# HC4052

HC4052 is an Arduino library for a HC4052 2 x 4 channel multiplexer.


## Description

HC4052 is a library to control the CD74HC4052 2 x 4 channels
multiplexer / demultiplexer and compatible devices.

The HC4052 allows e.g to multiplex an I2C bus (SDA + SCL) simultaneous to read multiple
sensors that have a fixed address. 
Another application is to switch Serial (UNO has only one HW Serial) between different
devices.
Or to switch audio channels (not tested) etc.

It is also possible to use the HC4067 to select an OUTPUT channel.
The signal pin can be connected to VCC (5V) or an IO pin set to OUTPUT.
Only the selected channel can show the HIGH level of the IO pin if set to HIGH.
Not selected pins will all be set to LOW.

The channel selection is done with two select lines **A, B** or **S0, S1**.

The device can be enabled/disabled by the enable line **INH** or **E**.


#### Compatibles

- https://assets.nexperia.com/documents/data-sheet/74HC_HCT4052.pdf
  - 74HC4052 (CMOS level)
  - 74HCT4052 (TTL level)


#### Related

- https://github.com/RobTillaart/HC4051  (1x8 mux)
- https://github.com/RobTillaart/HC4052  (2x4 mux)
- https://github.com/RobTillaart/HC4053  (3x2 mux)
- https://github.com/RobTillaart/HC4067  (1x16 mux)
- https://github.com/RobTillaart/MAX14661 (2x16 mux, I2C)
- https://tronixstuff.com/2013/08/05/part-review-74hc4067-16-channel-analog-multiplexerdemultiplexer/


## Hardware connection

Typical connection is to connect the two **select pins** to two IO pins of your board.

The optional **enablePin(INH)** must be connected to GND if not used.
This way the device will be continuous enabled.

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
- **bool setChannel(uint8_t channel)** set the current channel.
Valid values 0..3, this value is checked (since 0.2.1).
Returns false if channel out of range.
If the channel is already selected it does not change it.
Note the three channels will not change at the very same moment, 
possibly resulting in an invalid selection for a (very short) time.  
The disable flag can be set to false so the device is not disabled during channel switching.
Default the device is disabled during channel switching to prevent (very short) ghost channels.
Note that a call to **setChannel()** will always enable the device again.
Note the device cannot be disabled if there is no enable pin configured.
- **uint8_t getChannel()** returns the current channel 0..3.
The selected channel is also returned when the multiplexer is disabled.


#### Enable

These functions work only if enablePin is set in the constructor.

- **void enable()** enables the device to multiplex.
- **void disable()** disables the device, no channel is selected.
- **bool isEnabled()** returns the current status of the device.
Also returns true if the enablePin is not set in the constructor.


## Future

#### Must

- keep in sync with HC4067 et.al.

#### Should

#### Could

- add examples
  - i2c scan

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

