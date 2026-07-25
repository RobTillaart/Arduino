
[![Arduino CI](https://github.com/RobTillaart/PT2258/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PT2258/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PT2258/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PT2258/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PT2258/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/PT2258.svg)](https://github.com/RobTillaart/PT2258/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PT2258/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PT2258.svg?maxAge=3600)](https://github.com/RobTillaart/PT2258/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/PT2258.svg)](https://registry.platformio.org/libraries/robtillaart/PT2258)


# PT2258

Arduino library for PT2258 I2C 6 channel audio volume processor.


## Description

**Experimental**

This library is to use the PT2258 I2C 6 channel audio volume 
processor from an Arduino.

The PT2258 is a 6-Channel volume IC to be used e.g. for Home 
Theater Systems, car audio, computer multimedia sound, etc.

The library is rather simplistic, it provides setting volume 
or Attenuation per channel. Volume = 
The library caches the values so these can be retrieved later. 
Furthermore the library supports (un)muting all channels at once.

Some data, check datasheet for remarks.

|  feature                    |  value  |
|:----------------------------|:--------|
|  Supply Voltage             |  5-9V
|  Channels                   |  6
|  Attenuation                |  0 (full) to -79dB at 1dB/step
|  Volume                     |  0 (silent) to 79 (full) 
|  Low Noise                  |  S/N Ratio > 100 dBA
|  Interface                  |  I2C
|  max I2C clock              |  100 KHz
|  I2C addresses              |  4
|  Power on time              |  200 ms (see datasheet)

The library is not tested with hardware yet.

Feedback as always is welcome.


### Related

Datasheet
- Datasheet V1.3, October 2005.

Audio
- https://github.com/RobTillaart/PT2257 I2C 2 channel volume controller
- https://github.com/RobTillaart/PT2258 I2C 6 channel volume controller
- https://github.com/RobTillaart/PT2314 I2C 4 channel audio processor
- https://github.com/RobTillaart/PT2323 I2C audio processor / selector
- https://github.com/RobTillaart/M61538FP 6 channel volume processor

Other
- https://github.com/RobTillaart/TCA9548 I2C multiplexer
- https://github.com/RobTillaart/HC4052 (multiplexer for more inputs)


## I2C

### I2C Address

The device can have one of 4 different I2C addresses, 0x40, 0x44, 0x48, 0x4C.
Depends on how to connect CODE1 and CODE2 pin, see datasheet.

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

Maximum I2C clock = 100 KHz.


## Interface

```cpp
#include "PT2258.h"
```

### Constructor

- **PT2258(TwoWire \*wire = &Wire)** optional select I2C bus.
- **bool begin()** checks if device is visible on the I2C bus.
Sets all volume to 79.
- **bool isConnected()** Checks if device address can be found on I2C bus.
- **uint8_t getAddress()** Returns the fixed address 0x94 (148).


### Volume

volume = 0 (silent)..79 (full), volume scale is reverse of attenuation.

- **int setVolumeAll(uint8_t volume)** set all channels to same volume.
- **int setVolume(uint8_t channel, uint8_t volume)** set a single channel to volume.
- **int getVolume(uint8_t channel)** returns cached volume..
- **int mute(bool on)** mute or unmute all. 
Does not affect cached volume.


### Attenuation

attn = 0 (full)..79 (silent), note no sign is used.

- **int setAttenuationAll(uint8_t attn)** set all channels to same attenuation.
- **int setAttenuation(uint8_t channel, uint8_t attn)** set a single channel to attenuation.
- **int getAttenuation(uint8_t channel)** returns cached attenuation..


### Error / debug

- **int getLastError()** returns last low level I2C error.


## Future

#### Must

- improve documentation
- get hardware to test

#### Should

- improve error handling
- check address

#### Could

- add examples
- add unit tests (if possible)
- fix magic numbers (of registers)

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


