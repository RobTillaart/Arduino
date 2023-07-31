
[![Arduino CI](https://github.com/RobTillaart/PT2314/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![JSON check](https://github.com/RobTillaart/PT2314/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PT2314/actions/workflows/jsoncheck.yml)
[![Arduino-lint](https://github.com/RobTillaart/PT2314/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PT2314/actions/workflows/arduino-lint.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PT2314/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PT2314.svg?maxAge=3600)](https://github.com/RobTillaart/PT2314/releases)


# PT2314

Arduino library for PT2314 i2C 4 channel audio processor.

## Description

The PT2314 library is experimental as it is not tested with hardware.
The library should also work with the PT7314, a separate constructor 
exist for it. 

Feedback is welcome.

The library is based upon Datasheet: PT2314 V1.4 July, 2005


#### I2C

According to the datasheet:
- PT2314 only work on 100 KHz.
- PT7314 can support 400 KHz.
- check if higher speeds work?

Datasheet PT7314 states that the device needs 50 ms to wake up 
before it can process I2C commands.
The datasheet of the PT2314 does not mention such timeout.


## Interface

```cpp
#include "PT2314.h"
```

#### Constructors

- **PT2314(TwoWire \*wire = &Wire)** constructor.
- **PT7314(TwoWire \*wire = &Wire)** constructor.
- **bool begin(int sda, int scl)** for ESP32 et al.
- **bool begin()** other
- **bool isConnected()** device address can be seen on I2C bus.

#### Channel

- **void setChannel(uint8_t channel = 0)**  0..3
- **uint8_t getChannel()**

#### Volume

- **void    setMute(bool on = true)**
- **bool    getMute()**
- **void    setLoudness(bool on = true)**
- **bool    getLoudness()**
- **void    setVolume(uint8_t volume = 0)** 0..63
- **uint8_t getVolume()**

#### Bass Treble

- **void    setBass(int8_t bass = 0)** -14..14 dB
- **int8_t  getBass()**
- **void    setTreble(int8_t treble = 0)** -14..14 dB
- **int8_t  getTreble()**

#### Gain

- **void    setGain(uint8_t gain = 0)**  0..3
- **uint8_t getGain()**

#### Attenuation

- **void    setAttnLeft(uint8_t value = 31)**  0..31
- **uint8_t getAttnLeft()**
- **void    setAttnRight(uint8_t value = 31)**  0..31
- **uint8_t getAttnRight()**
- **void    setAttn(uint8_t attnLeft, uint8_t attnRight)**

## Future

#### Must

- improve documentation
- test with hardware

#### Should

- error handling
- add more examples.
- check parameters range (0..63 => -63..0?
  - some are in dB others not.

#### Could

- replace magic numbers with defines.
- extend unit test

#### Wont (unless on request)

