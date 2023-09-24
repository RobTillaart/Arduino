
[![Arduino CI](https://github.com/RobTillaart/PT2314/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PT2314/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PT2314/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PT2314/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PT2314/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/PT2314.svg)](https://github.com/RobTillaart/PT2314/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PT2314/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PT2314.svg?maxAge=3600)](https://github.com/RobTillaart/PT2314/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/PT2314.svg)](https://registry.platformio.org/libraries/robtillaart/PT2314)


# PT2314

Arduino library for PT2314 i2C 4 channel audio processor.


## Description

The PT2314 library is experimental as it is not tested with hardware.

The PT2314 is a audio processor that can select from four stereo
inputs, and provides one stereo output.
Attributes to control are volume, gain, attenuation, bass, treble,
mute and loudness.
The library should also work with the PT7314, a separate constructor 
exist for it.

A separate derived class is created for the PT7313, an compatible 
audio processor with only three stereo inputs and two stereo outputs.
It is used in automotive to control front and back speakers.

|  processor  |  inputs  |  outputs  |  datasheet        |
|:-----------:|:--------:|:---------:|:-----------------:|
|    PT2314   |    4     |    1      |  V1.4 July, 2005  |
|    PT7314   |    4     |    1      |  V1.0 Jan,  2010  |
|    PT7313   |    3     |    2      |  V1.0 feb,  2010  |

Feedback as always, is welcome.

The library is based upon Datasheet: PT2314 V1.4 July, 2005


#### I2C

|  processor  |  MAX KHz |  tested  |
|:-----------:|:--------:|:--------:|
|    PT2314   |   100    |    N     |
|    PT7314   |   400    |    N     |
|    PT7313   |   400    |    N     |


Note: Datasheet PT7314 states that the device needs at least 50 ms 
to wake up before it can process I2C commands. So one might need
to give it some time to get started.


## Interface PT2314 PT7314

```cpp
#include "PT2314.h"
```

#### Constructors

- **PT2314(TwoWire \*wire = &Wire)** constructor, optional set Wire interface.
- **PT7314(TwoWire \*wire = &Wire)** constructor, optional set Wire interface.
- **bool begin(int sda, int scl)** for ESP32 et al.
- **bool begin()** other platforms.
- **bool isConnected()** device (0x44) can be seen on I2C bus.

#### Channel

- **void setChannel(uint8_t channel = 0)** Select the input channel 0..3.
- **uint8_t getChannel()** return selected input channel.

#### Volume

- **void setMute(bool on = true)** mute all output channels.
- **bool getMute()** get current mute state.
- **void setLoudness(bool on = true)** set loudness on.
- **bool getLoudness()** get current loudness state.
- **void setVolume(uint8_t volume = 0)** set the volume between 0..63.
- **uint8_t getVolume()** get current volume.

#### Bass Treble

- **void setBass(int8_t bass = 0)** bass can be set to -14..14 dB,
will be rounded to even numbers only. So 15 levels in total.
- **int8_t getBass()** get current bass level.
- **void setTreble(int8_t treble = 0)** treble can be set to -14..14 dB,
will be rounded to even numbers only. So 15 levels in total.
- **int8_t getTreble()** get current treble level.

#### Gain

- **void setGain(uint8_t gain = 0)**  Gain can be 0..3. 
CHeck datasheet for mapping.
- **uint8_t getGain()**

|  Gain  |   dB   |
|:------:|:------:|
|    0   |  11.25 |
|    1   |   7.50 |
|    2   |   3.75 |
|    3   |   0.00 |


#### Attenuation

- **void setAttnLeft(uint8_t value = 31)** set the left attenuation from 0..31.
- **uint8_t getAttnLeft()** get current left attenuation level.
- **void setAttnRight(uint8_t value = 31)** set the right attenuation from 0..31.
- **uint8_t getAttnRight()** get current right attenuation level.
- **void setAttn(uint8_t attnLeft, uint8_t attnRight)** set both in one call.
Convenience function.

Formula attenuation:
```cpp
Attn = value * -1.25;  //  dB  0..-37.50,  31 ==> MUTE.
```

## Interface PT7313

```cpp
#include "PT2314.h"
```

Additional constructor:
- **PT7313(TwoWire \*wire = &Wire)** constructor.

- **void setMute(bool on)** idem, four channel version.
- **void setChannel(uint8_t channel = 0)** idem, 0..2.
  
Additional attenuation:
- **void setAttnLeftBack(uint8_t value = 31)** idem, 0..31.
- **uint8_t getAttnLeftBack()** get current level.
- **void setAttnRightBack(uint8_t value = 31)** idem, 0..31
- **uint8_t getAttnRightBack()** get current level.
- **void setAttnLeftFront(uint8_t value = 31)** idem, 0..31
- **uint8_t getAttnLeftFront()** get current level.
- **void setAttnRightFront(uint8_t value = 31)** idem, 0..31
- **uint8_t getAttnRightFront()** get current level.


## Future

#### Must

- test with hardware
- improve documentation

#### Should

- investigate **setAttn(value)** function for all channels.
  - better also for the 7313
  - 0.2.0 ==> remove the setAttn(left, right) ?
- add more examples.
- check parameters range:  0..63 => -63..0?
  - some are in dB others not.

#### Could

- replace magic numbers with defines.
  - PT2413_MAX_ATTN  31   etc.
- extend unit test
- add **getType()** 7313  or 13 / 14  (16 or 8 bit)
- error handling

#### Wont (unless on request)


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

