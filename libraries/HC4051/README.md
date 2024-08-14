
[![Arduino CI](https://github.com/RobTillaart/HC4051/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/HC4051/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/HC4051/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/HC4051/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/HC4051/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/HC4051.svg)](https://github.com/RobTillaart/HC4051/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/HC4051/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/HC4051.svg?maxAge=3600)](https://github.com/RobTillaart/HC4051/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/HC4051.svg)](https://registry.platformio.org/libraries/robtillaart/HC4051)


# HC4051

HC4051 is an Arduino library for a HC4051 1x8 channel multiplexer.


## Description

HC4051 is a library to control the CD74HC4051 8 channel
multiplexer / demultiplexer and compatible devices.

The HC4051 allows e.g one analog port read up to 8 different analog channels,
or one digital port to read the state of 8 buttons.

It is also possible to use the HC4051 to select an OUTPUT channel.
The signal pin can be connected to VCC (5V) or an IO pin set to OUTPUT.
Only the selected channel can show the HIGH level of the IO pin if set to HIGH.
Not selected pins will all be set to LOW.

The channel selection is done with four select lines **A, B, C**

The device can be enabled/disabled by the enable line **INH**

### 0.3.0 breaking change

Version 0.3.0 has a bugfix for **setChannel()** which obsolete all previous versions.


#### Compatibles

To elaborate.


#### Related

- https://github.com/RobTillaart/HC4051  (1x8 mux)
- https://github.com/RobTillaart/HC4052  (2x4 mux)
- https://github.com/RobTillaart/HC4053  (3x2 mux)
- https://github.com/RobTillaart/HC4067  (1x16 mux)
- https://github.com/RobTillaart/MAX14661 (2x16 mux, I2C)
- https://tronixstuff.com/2013/08/05/part-review-74hc4067-16-channel-analog-multiplexerdemultiplexer/


## Hardware connection

Typical connection is to connect the three **select pins** to four IO pins of your board.

The optional **enablePin(INH)** must be connected to GND if not used.
This way the device will be continuous enabled.

Example multiplexing analog in.

```
        processor                      HC4051
     +-------------+              +-------------+
     |             |              |             |
     |           A |------------->| S0       Y0 |
     |           B |------------->| S1       Y1 |
     |           C |------------->| S2       Y2 |
     |             |              |          Y3 |
     |          E  |------------->| INH      Y4 |
     |             |              |          Y5 |
     |         A0  |<-------------| Y        Y6 |
     |             |              |          Y7 |
     |         GND |--------------| GND      Y8 |
     |             |              | VCC         |
     |             |              |             |
     +-------------+              +-------------+
```


#### Less Select lines

Note: the library does not meant for this mode, although it should work.
The GND-ed pins should be set to 255 (not tested).

It is possible to use less IO pins to connect to the S0..S3.
The ones not connected to an IO pin must be connected to GND (preferred).

|  S0   |  S1   |  S2   |  pins  |  notes  |
|:-----:|:-----:|:-----:|:------:|:-------:|
|  IO   |  IO   |  IO   |   0-7  |  default usage
|  IO   |  IO   |  GND  |   0-3  |
|  IO   |  GND  |  GND  |   0-1  |

Of course it is possible to set a Select pin to VCC instead of GND.
This will result in another subset of the Y pins to select from.


## Interface

```cpp
#include "HC4051.h"
```

### Core

- **HC4051(uint8_t A, uint8_t B, uint8_t C, uint8_t enablePin = 255)** constructor.
Set the three select pins and optional the enable pin.
If the enablePin == 255 it is considered not used.
- **bool setChannel(uint8_t channel, bool disable = true)** set the current channel.
Valid values 0..7, this value is checked (since 0.2.1).
Returns false if channel out of range.  
If the channel is already selected it does not change it.
Note the three channels will not change at the very same moment, 
possibly resulting in an invalid selection for a (very short) time.  
The disable flag can be set to false so the device is not disabled during channel switching.
Default the device is disabled during channel switching to prevent (very short) ghost channels.
Note that a call to **setChannel()** will always enable the device again.
Note the device cannot be disabled if there is no enable pin configured.
- **uint8_t getChannel()** returns the current channel 0..7.
The selected channel is also returned when the multiplexer is disabled.


### Enable

These functions work only if a valid **enablePin** is set in the constructor.

- **void enable()** enables the device to multiplex.
- **void disable()** disables the device, no channel is selected.
- **bool isEnabled()** returns the current status of the device.
Also returns true if the enablePin is not set in the constructor.


## Future

- keep in sync with HC4067 et.al.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

