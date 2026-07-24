
[![Arduino CI](https://github.com/RobTillaart/PT2323/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PT2323/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PT2323/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PT2323/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PT2323/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/PT2323.svg)](https://github.com/RobTillaart/PT2323/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PT2323/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PT2323.svg?maxAge=3600)](https://github.com/RobTillaart/PT2323/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/PT2323.svg)](https://registry.platformio.org/libraries/robtillaart/PT2323)


# PT2323

Arduino library for PT2323 I2C 6 channel audio processor / selector.


## Description

**Experimental**

This library is to use the PT2323 I2C audio processor / selector from an Arduino.

The PT2323 is a 6-Channel Audio Selector specially designed for Home Theater Systems.
It provides a built-in 2-Channel to 6-Channel Translator, which can directly mix
traditional stereo channel to simulate a 6-Channel audio output.

6 channel = front left and right, centre, subwoofer and rear left and right.

Instead of rear the term surround is used too.

Some data, check datasheet for remarks.

|  feature                    |  value  |
|:----------------------------|:--------|
|  Total Harmonic Distortion  |  < 0.005% (1 KHz, 0.2 Vrms)
|  Supply Voltage             |  9V
|  Stereo Input               |  4
|  6-Channel Input            |  1
|  Maximum Input Voltage      |  3.75 Vrms (1 KHz, THD < 1%)
|  Low Noise                  |  No < 4 μVrms
|  Interface                  |  I2C, address 0x94
|  max I2C                    |  100 KHz
|  Power on time              |  300 ms (see datasheet)

The library is not tested with hardware yet.

Feedback as always is welcome.


### Related

Datasheet
- Datasheet V1.3, October 2005.

Audio
- https://github.com/RobTillaart/PT2257 I2C 2 channel volume controller
- https://github.com/RobTillaart/PT2314 I2C 4 channel audio processor
- https://github.com/RobTillaart/PT2323 I2C audio processor / selector
- https://github.com/RobTillaart/M61538FP 6 channel volume processor

Other
- https://github.com/RobTillaart/TCA9548 I2C multiplexer


## I2C

### I2C Address

The device has a fixed I2C address of 0x94 (148) so only one sensor
per I2C bus can be used.

### I2C multiplexing

Sometimes you need to control more devices than possible with the default
address range the device provides.
This is possible with an I2C multiplexer e.g. TCA9548 which creates up
to eight channels (think of it as I2C subnets) which can use the complete
address range of the device.

Drawback of using a multiplexer is that it takes more administration in
your code e.g. which device is on which channel.
This will slow down the access, which must be taken into account when
deciding which devices are on which channel.
Also note that switching between channels will slow down other devices
too if they are behind the multiplexer.

- https://github.com/RobTillaart/TCA9548


### I2C Performance

Maximum I2C clock = 100 KHz (page 6 datasheet).


## Interface

```cpp
#include "PT2323.h"
```

### Constructor

- **PT2323(TwoWire \*wire = &Wire)** optional select I2C bus.
- **bool begin()** checks if device is visible on the I2C bus.
- **bool isConnected()** Checks if device address can be found on I2C bus.
- **uint8_t getAddress()** Returns the fixed address 0x94 (148).


### Channel

Page 8 datasheet.

- **bool setChannel(uint8_t channel = 0)** channel = 0..3 or 6.
returns false if write to device fails.
- **uint8_t getChannel()** returns last set channel or 0 (default).


### Mute

Page 8 datasheet.

Functions return false if write to device fails.

- **bool muteFrontLeft(bool mute)** idem.
- **bool muteFrontRight(bool mute)** idem.
- **bool muteCenter(bool mute)** idem.
- **bool muteSubWoofer(bool mute)** idem.
- **bool muteRearLeft(bool mute)** idem.
- **bool muteRearRight(bool mute)** idem.
- **bool muteAll(bool mute)** (un)mute all channels.

Note RearLeft is SL in datasheet, RearRight is SR in datasheet.


### Surround

Page 8 datasheet.

- **bool setSurround(bool enable)** returns false if write to device fails.
- **bool getSurround()** returns cached status.


### Mixed Channel

Page 8 datasheet.

- **bool setMixedChannel(bool six_db)**
- **bool getMixedChannel()** returns cached status.


### Error / debug

- **int getLastError()** returns last low level I2C error.


## Future

#### Must

- improve documentation
- get hardware to test

#### Should

- improve error handling

#### Could

- add examples
- add unit tests (if possible)

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


