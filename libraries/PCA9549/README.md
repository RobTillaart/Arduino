
[![Arduino CI](https://github.com/RobTillaart/PCA9549/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PCA9549/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PCA9549/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PCA9549/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PCA9549/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/PCA9549.svg)](https://github.com/RobTillaart/PCA9549/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PCA9549/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PCA9549.svg?maxAge=3600)](https://github.com/RobTillaart/PCA9549/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/PCA9549.svg)](https://registry.platformio.org/libraries/robtillaart/PCA9549)


# PCA9549

Arduino Library for PCA9549 I2C octal bus switch.


## Description

Library for the PCA9549 and compatibles.

The library allows you to switch on/off 8 channels uniquely or simultaneously.

**Warning**
The library is not tested yet.

The library caches the channels enabled, and if a channel is enabled,
it will not be enabled again (low level) to optimize performance.


#### I2C 

I2C address of the device itself is 0x70 .. 0x77.


#### Related

- https://github.com/RobTillaart/TCA9549 - strong interface and code similarity


## Interface

```cpp
#include "PCA9549.h"
```

#### Constructor

- **PCA9549(const uint8_t deviceAddress, TwoWire \*wire = &Wire)** Constructor.
deviceAddress = 0x70 .. 0x77, wire = Wire or WireN.
- **bool begin(uint8_t mask = 0x00)**  set mask of channels to be enabled, default all disabled.
- **bool isConnected()** returns true if address of the multiplexer is found on I2C bus.


#### Channel functions

All "channel functions" return true on success.

- **bool enableChannel(uint8_t channel)** enables channel 0 .. 7 non-exclusive.
Multiple channels can be enabled in parallel.
- **bool disableChannel(uint8_t channel)** disables channel 0 .. 7.
Will not disable other channels.
- **bool selectChannel(uint8_t channel)** enables a single channel 0 .. 7 exclusive.
All other channels will be disabled in the same call, so not before or after.
- **bool isEnabled(uint8_t channel)** returns true if the channel is enabled.
- **bool disableAllChannels()** fast way to disable all.
- **bool setChannelMask(uint8_t mask)** enables 0 or more channels simultaneously with a bit mask.
- **uint8_t getChannelMask()** reads back the bit mask of the channels enabled.


#### Reset

- **void setResetPin(uint8_t resetPin)** sets the pin to reset the chip. (Not tested)
- **void reset()** trigger the reset pin.
- **int getError()** returns the last I2C error.


#### Forced IO

When forced IO is set all writes and read - **getChannelMask()** - will go to the device.
If the flag is set to false it will cache the value of the channels enabled.
This will result in more responsive / faster calls.
Note that writes are only optimized if the channels are already set.

- **void setForced(bool forced = false)** set forced write, slower but more robust.
  - forced == false == fast mode (default).
  - forced == true == slower, robust mode.
- **bool getForced()** returns set flag.


## Error Codes

Not implemented yet, preparation for future.

|  name                   |  value  |  description            |
|:------------------------|:-------:|:------------------------|
|  PCA9549_OK             |   00    |  no error               |


## Future


#### Must

- improve documentation.

#### Should

- keep aligned with TCA9548 / PCA9548 library where meaningful.
- add examples e.g. real life scenarios.
- test with hardware

#### Could

- improve error handling.

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,



