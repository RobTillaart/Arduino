
[![Arduino CI](https://github.com/RobTillaart/ADG729/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/ADG729/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/ADG729/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/ADG729/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/ADG729/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/ADG729.svg)](https://github.com/RobTillaart/ADG729/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/ADG729/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/ADG729.svg?maxAge=3600)](https://github.com/RobTillaart/ADG729/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/ADG729.svg)](https://registry.platformio.org/libraries/robtillaart/ADG729)


# ADG729

Arduino Library for I2C ADG729 matrix switch. 2x4 Multiplexer.


## Description

**Experimental**

Library for the ADG729 dual 2x4 channel multiplexer.

The library allows you to select 0 to 8 switches uniquely or simultaneously.
These 8 switches are arranged in 2x4 switches to multiplex 2 lines A and B.
Both the A and B switches can be in 16 states, from 0000 - 1111.

The library caches the channels enabled, and if a channel is enabled,
it will not be enabled again (low level) to optimize performance.
This can however be overruled.

The device works with 2.3 V to 5.5 V so it should work with most MCU's.

Note: By connecting line A and B the ADG729 can act like an ADG728.

**Warning**

The library is not tested with hardware yet.


#### I2C 

I2C address of the device itself is 0x4C .. 0x4F.


#### I2C performance

The ADG729 can work up to 400 KHz according to the datasheet.


#### Related

Other multiplexers

- https://github.com/RobTillaart/HC4051  (1x8 mux)
- https://github.com/RobTillaart/HC4052  (2x4 mux)
- https://github.com/RobTillaart/HC4053  (3x2 mux)
- https://github.com/RobTillaart/HC4067  (1x16 mux)
- https://github.com/RobTillaart/ADG725  (2x16 mux)
- https://github.com/RobTillaart/ADG726  (2x16 mux)
- https://github.com/RobTillaart/ADG729  (1x8 mux)
- https://github.com/RobTillaart/ADG729  (2x4 mux)
- https://github.com/RobTillaart/ADG731  (1x32 mux)
- https://github.com/RobTillaart/ADG732  (1x32 mux)
- https://github.com/RobTillaart/TCA9548  I2C multiplexer


## Interface

```cpp
#include "ADG729.h"
```

#### Interaction models

**Warning**

There are two interaction models with the ADG729. 
These exist of single-channel and dual-channel functions. 
Note that mixing these two interaction models might complicate the logic of your code. 
However it is allowed.


#### Constructor

- **ADG729(const uint8_t deviceAddress, TwoWire \*wire = &Wire)** Constructor.
deviceAddress = 0x4C .. 0x4F, wire = Wire or WireN.
- **bool begin(uint8_t mask = 0x00)**  set mask of channels to be enabled, default all disabled.
- **bool isConnected()** returns true if address of the multiplexer is found on I2C bus.


#### Single channel functions

All channel functions return true on success.

- **bool enableChannel(uint8_t channel)** enables channel 0 .. 7 **non-exclusive**.  
Multiple channels can be enabled in parallel.
- **bool disableChannel(uint8_t channel)** disables channel 0 .. 7.
Will not disable other channels.
- **bool selectChannel(uint8_t channel)** enables a single channel 0 .. 7 **exclusive**.  
All other channels will be disabled in the same call, so not before or after.
- **bool isEnabled(uint8_t channel)** returns true if the channel is enabled.
- **bool disableAllChannels()** fast way to disable all channels.


#### Dual Channel functions

All channel functions return true on success.

These functions set channels in pairs, the same channel for both A and B.
The advantage of the dual channel functions is that the switches are set simultaneously.
These functions are ideal e.g. to multiplex I2C or RS232 as these are buses
use two wires.

- **bool enableAB(uint8_t channel)** enables channel 0 .. 3 for both A and B **non-exclusive**.
- **bool disableAB(uint8_t channel)** disables channel 0 .. 3 for both A and B .
Will not disable other channels.
- **bool selectAB(uint8_t channel)** enables a single channel 0 .. 3 **exclusive**.  
All other channels will be disabled in the same call, so not before or after.
- **bool isEnabledAB(uint8_t channel)** returns true if the channel is enabled for both A and B.

The **select()** function sets the A and B switch uniquely and independently at the same time.
It allows e.g. to make a routing matrix, if one connects A and B together.
Now one can select which A connects to which B, in total 4 x 4 possibilities.

- **bool select(uint8_t A, uint8_t B)** A, B = 0..3


#### Mask functions

Multiple channels can also be enabled in one call with a mask.
These functions do the hard work for the single and dual channel functions.

- **bool setChannelMask(uint8_t mask)** enables 0 or more channels simultaneously with a bit mask.
- **uint8_t getChannelMask()** reads back the bit mask of the channels enabled.


#### Debug

- **int getError()** returns the last (I2C) status / error.


#### Forced IO

When forced IO is set, all writes and read, e.g. **uint8_t getChannelMask()**, 
will go to the device.
If the **forced-IO** flag is set to false, it will cache the value of the channels enabled.
This will result in far more responsive and faster calls.
Note that writes are only optimized if the channels are already set.  
Forced IO is also used to speed up **getChannelMask()**.

- **void setForced(bool forced = false)** set forced write, slower but more robust.
  - forced == false == fast mode (default).
  - forced == true == slower, robust mode.
- **bool getForced()** returns set flag.


## Error Codes

Not implemented yet, preparation for future.

|  name                  |  value  |  description            |
|:-----------------------|:-------:|:------------------------|
|  ADG729_OK             |   00    |  no error               |
|  ADG729_ERROR_I2C      |  -10    |  detected an I2C error  |
|  ADG729_ERROR_CHANNEL  |  -20    |  channel out of range   |


## Future


#### Must

- improve documentation.
- test with hardware.

#### Should

- add examples.
- improve error handling.

#### Could

- extend the unit tests.

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,



