
[![Arduino CI](https://github.com/RobTillaart/M61538FP/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/M61538FP/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/M61538FP/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/M61538FP/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/M61538FP/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/M61538FP.svg)](https://github.com/RobTillaart/M61538FP/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/M61538FP/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/M61538FP.svg?maxAge=3600)](https://github.com/RobTillaart/M61538FP/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/M61538FP.svg)](https://registry.platformio.org/libraries/robtillaart/M61538FP)


# M61538FP

Arduino library for M61538FP 6 channel audio volume processor.


## Description

**Experimental**

This library is to use the M61538FP 6 channel audio volume processor from an Arduino.

The M61538FP is a 6-Channel volume IC specially designed for Home Theater Systems. 
The library provides setting volume in pairs separate 6-Channel Translator, which can directly mix
traditional stereo channel to simulate a 6-Channel audio output.

6 channel = front left and right, centre, subwoofer and rear left and right.

Instead of rear the term surround is used too.

Some data, check datasheet for remarks.

|  feature         |  value  |
|:-----------------|:--------|
|  Supply voltage  | dual or single.
|  dual voltage    |  ±7V => Check datasheet
|  single voltage  |  10V => Check datasheet
|  Channels        |  6
|  Volume          |  0 .. 95 dB (1 dB steps)
|  Low Noise       |  0.85 μVrms
|  Low Distortion  |  0.0012 %  (0.3Vrms, 1 kHz)

The library is not tested with hardware yet.

Feedback as always is welcome.


### Performance

Performance sketch output (UNO R3) with default pulse delay of 4.

```
M61538FP_LIB_VERSION: 0.1.0

SET ALL:	911.02
SET PAIR:	303.74
SET SINGLE:	304.63
GET SINGLE:	0.50

Done...
```

Tweaking performance can be done by changing line ```#define PULSE_DELAY 4```.
Datasheet states 3.2 µs as default, so set to 4 as default.
For boards with a slow digitalWrite() the delay can even be zero.
Use at own risk.


### Related

Datasheet
- Datasheet Rev.1.0, Mar.23.2004

Audio
- https://github.com/RobTillaart/PT2257 I2C 2 channel volume controller
- https://github.com/RobTillaart/PT2314 I2C 4 channel audio processor
- https://github.com/RobTillaart/PT2323 I2C audio processor / selector
- https://github.com/RobTillaart/M61538FP 6 channel volume processor


## Interface

```cpp
#include "M61538FP.h"
```

### Constructor

- **M61538FP(uint8_t dataPin, uint8_t clockPin)**
- **void begin()** initializes IO pins 




### Set volume

The volume can be set as attenuation from 0 (full open) to 96 (silent).
Values above 96 are clipped.

Pairs (IC can only set in pairs)

- **void setVolumeFrontLeftRight(uint16_t left, uint16_t right)**
- **void setVolumeRearLeftRight(uint16_t left, uint16_t right)**
- **void setVolumeCenterWoofer(uint16_t center, uint16_t woofer)**

Wrappers

- **void setVolumeAll(left, right, center, woofer, rearLeft, rearRight)** idem.
- **void muteAll()**

Using cached volume 
- **void setVolumeFrontLeft(uint16_t vol)**
- **void setVolumeFrontRight(uint16_t vol)**
- **void setVolumeCenter(uint16_t vol)**
- **void setVolumeWoofer(uint16_t vol)**
- **void setVolumeRearLeft(uint16_t vol)**
- **void setVolumeRearRight(uint16_t vol)**

### Get volume per channel

Returns volume from cache.

- **uint8_t getVolumeFrontLeft()**
- **uint8_t getVolumeFrontRight()**
- **uint8_t getVolumeCenter()**
- **uint8_t getVolumeWoofer()**
- **uint8_t getVolumeRearLeft()**
- **uint8_t getVolumeRearRight()**

## Future

#### Must

- improve documentation
- get hardware to test

#### Should

- improve error handling
- handle power up time.

#### Could

- add examples
- add unit tests if possible.
- add unmuteAll (do not cache the zero value)

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


