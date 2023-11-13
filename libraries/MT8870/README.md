
[![Arduino CI](https://github.com/RobTillaart/MT8870/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MT8870/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MT8870/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MT8870/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MT8870/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MT8870.svg)](https://github.com/RobTillaart/MT8870/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MT8870/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MT8870.svg?maxAge=3600)](https://github.com/RobTillaart/MT8870/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MT8870.svg)](https://registry.platformio.org/libraries/robtillaart/MT8870)


# MT8870

Arduino library for MT8870 DTMF decoder (breakout).


## Description

This library reads the signals of the MT8870 chip. 
If data is available one can read it raw or as text.

DTMF = Dual Tones Multiple Frequency.
These are the tones you hear when you press buttons on your phone. 

DTMF tones, uses one from A..D and one from E..H.

|  Name  |  Frequency  |
|:------:|------------:|
|   A    |    697 Hz   |
|   B    |    770 Hz   |
|   C    |    852 Hz   |
|   D    |    941 Hz   |
|   E    |   1209 Hz   |
|   F    |   1336 Hz   |
|   G    |   1477 Hz   |
|   H    |   1633 Hz   |


## Interface

```cpp
#include "MT8870.h"
```

- **MT8870()** constructor
- **void begin(uint8_t STQ, uint8_t Q1, uint8_t Q2, uint8_t Q3, uint8_t Q4)** defines which pins to use. 
Technically it is possible to have readout multiple decoders
with one MT8870 object by calling **begin()** with other pins.
  - **STQ**    = data available signal
  - **Q1..Q4** = data pins.
  - Calling begin resets the **lastRead** char
- **bool available()** returns true if there is a DMTF signal 
- **char read()** reads the character available. Returns 255 if no signal available.
- **uint8_t readRaw()** returns 0 .. 15 or 255 if no signal is available.
- **uint8_t lastRaw()** returns the last code read 0 .. 15 or 255 if no signal available.
Note this is a cached value from a readRaw / read call.
- **uint32_t lastTimeRead()** returns the timestamp of last **read()** or **readRaw()**. 


## Operations

See examples.


## Future

#### Must

- improve documentation
  - keypad matrix, which key generates which tones

#### Should

- test setup
- add examples
  - DMTF with a PCF8574
  - DMTF as secret key
  - DMTF with less keys (less pins)
  - DMTF over interrupt triggered by STQ line

#### Could

- buffer like Serial? (how to fill? interrupt? example sketch?)
  - read part of stream interface?
- DMTF tone generation?  
  - MCP_DAC
  - PWM + HW?

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

