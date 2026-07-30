
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

_This library is work in progress. 
The API might be stripped to ATTENUATION ONLY in the future. 
The reason is that the getters for volume do not return the values set. 
This is due to using the attenuation in the cache which has a smaller range.
Furthermore the mapping of volume and attenuation is not linear.
Finally as integer values are used in the cache, rounding effects the getters.
For 0.1.x versions both API's will be kept._

**Experimental**

This library is to use the M61538FP 6 channel audio volume processor from an Arduino.

The M61538FP is a 6-Channel volume IC specially designed for Home Theater Systems et al.
The low level protocol of the IC uses pairs of attenuation data and has no means to
read back the set values.
The library solves this by caching the attenuation per channel, which allows to add
functions to set individual channels (by reusing the cached value).

The 6 channel are named as follows
- front left and right,
- center and subwoofer
- rear left and rear right. (a.k.a. surround left / right).

The library has essential 2 API's:
- Attenuation from 0 (full open) to 96 (silent) in steps of 1 dB
- Volume from 0% (silent) to 100% (full open) in steps of 1%.

The volume API uses a logarithmic scale (changed in 0.1.2) and wraps around the
attenuation API.

Note: Instead of rear the term surround (sometimes abbrevitated to S) is used in the datasheet.

Some data, check datasheet for remarks.

|  feature          |  value  |
|:------------------|:--------|
|  Supply voltage   | dual or single.
|  dual voltage     |  ±7V => Check datasheet
|  single voltage   |  10V => Check datasheet
|  Channels         |  6
|  Attenuation min  |  0 dB  == full open
|  Attenuation max  |  96 dB == silent
|  Low Noise        |  0.85 μVrms
|  Low Distortion   |  0.0012 %  (0.3Vrms, 1 kHz)

Note the library uses 0..96 dB instead of 0..-96dB 

Feedback as always is welcome.


### Tested

The library 0.1.0 is tested and confirmed to work with hardware.
Thanks to newarudinuser (Arduino forum).


### Performance

Indicative numbers of **M61538FP_performance.ino** (UNO R3).
Other boards may give different numbers so do your own tests
when performance is important.

```
M61538FP_LIB_VERSION: 0.1.2

SET ALL VOL:	914.17
SET PAIR VOL:	305.87
SET SINGLE VOL:	305.75
GET SINGLE VOL:	25.07

MUTE ALL:	912.47

SET ALL ATTN:	912.48
SET PAIR ATTN:	305.18
SET SINGLE ATTN:	305.25
GET SINGLE ATTN:	0.51

Done...
```

Tweaking performance can be done by changing line ```#define PULSE_DELAY 4```.
Datasheet states 3.2 µs as default, so it is set to 4 as default.
For boards with a slow digitalWrite() the delay can be lower.
Use at own risk.


### Related

Datasheet
- Datasheet Rev.1.0, Mar.23.2004

Audio
- https://github.com/RobTillaart/PT2257 I2C 2 channel volume controller
- https://github.com/RobTillaart/PT2258 I2C 6 channel volume controller
- https://github.com/RobTillaart/PT2314 I2C 4 channel audio processor
- https://github.com/RobTillaart/PT2323 I2C audio processor / selector
- https://github.com/RobTillaart/M61538FP 6 channel volume processor

Other
- https://github.com/RobTillaart/HC4052 (multiplexer for more inputs)



## Volume Interface

The volume can be set from 0 (silent) to 100 (full open).
Values above 100 are constrained to 100.
One can think of percentage.

```cpp
#include "M61538FP.h"
```

### Constructor

- **M61538FP(uint8_t dataPin, uint8_t clockPin)**
- **void begin()** initializes IO pins

### Set volume

Pairs interface as low level protocol can only set in pairs.

- **void setVolumeFrontLeftRight(uint16_t left, uint16_t right)**
- **void setVolumeRearLeftRight(uint16_t left, uint16_t right)**
- **void setVolumeCenterWoofer(uint16_t center, uint16_t woofer)**

### Volume wrappers

- **void setVolumeAll(left, right, center, woofer, rearLeft, rearRight)** idem.
One call to set them all, not simultaneously
- **void muteAll()** set all channels to silent.

### Set volume per channel

Using cache to set the "pair channel".

- **void setVolumeFrontLeft(uint16_t volume)** idem.
- **void setVolumeFrontRight(uint16_t volume)** idem.
- **void setVolumeCenter(uint16_t volume)** idem.
- **void setVolumeWoofer(uint16_t volume)** idem.
- **void setVolumeRearLeft(uint16_t volume)** idem.
- **void setVolumeRearRight(uint16_t volume)** idem.

### Get volume per channel

Returns volume from cache converted from attenuation.
As the storage is integer and the scale logarithmic this is not
as accurate as one would like. Additional cache of volume values
could solve this. Alternative is to remove this part of the API.

- **uint8_t getVolumeFrontLeft()**
- **uint8_t getVolumeFrontRight()**
- **uint8_t getVolumeCenter()**
- **uint8_t getVolumeWoofer()**
- **uint8_t getVolumeRearLeft()**
- **uint8_t getVolumeRearRight()**

----

## Attenuation Interface

The attenuation can be set from 96 (silent) to 0 (full open).
Values above 96 are constrained to 96.
Note the minus sign is not used (datasheet specs silent as -96)

Constructor and include statement are the same as above.

### Set attenuation

Pairs interface as low level protocol can only set in pairs.

- **void setAttnFrontLeftRight(uint16_t left, uint16_t right)**
- **void setAttnRearLeftRight(uint16_t left, uint16_t right)**
- **void setAttnCenterWoofer(uint16_t center, uint16_t woofer)**

### Attenuation wrappers

- **void setAttnAll(left, right, center, woofer, rearLeft, rearRight)** idem.
One call to set them all, not simultaneously

### Set attenuation per channel

Using cached attenuation to set the "pair channel".

- **void setAttnFrontLeft(uint16_t attn)** idem.
- **void setAttnFrontRight(uint16_t attn)** idem.
- **void setAttnCenter(uint16_t attn)** idem.
- **void setAttnWoofer(uint16_t attn)** idem.
- **void setAttnRearLeft(uint16_t attn)** idem.
- **void setAttnRearRight(uint16_t attn)** idem.

### Get attenuation per channel

Returns attenuation from cache.

- **uint8_t getAttnFrontLeft()**
- **uint8_t getAttnFrontRight()**
- **uint8_t getAttnCenter()**
- **uint8_t getAttnWoofer()**
- **uint8_t getAttnRearLeft()**
- **uint8_t getAttnRearRight()**


## Future

#### Must

- strip and split the API of the class ???
  - base class ATTN only
  - wrapper class for volume?
  - for now the volume part has some quirks (getters).
- improve documentation
- get hardware to test

#### Should


#### Could

- add unmuteAll
  - do not cache the zero value
  - cache the mute flag - bool isMuted()?
- add examples
- add unit tests if possible.
  - attn API can be done (getters setters)
  - volume API has quirks.
- investigate latch options
  - update all at once
  - make the latch a parameter of sendData()
  - ==> more functions need the "bool latch = true" parameter?
  - latch flag to set?

#### Wont

- investigate Power on Reset (page 6 datasheet)
  - effect on cached values!
  - hard to detect as there is no read back from device.
- investigate balance() function.
  - extra math layer / weight per channel
  - 3 pairs of balance() or more
  -

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


