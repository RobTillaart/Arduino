
[![Arduino CI](https://github.com/RobTillaart/ADC081S/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/ADC081S/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/ADC081S/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/ADC081S/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/ADC081S/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/ADC081S.svg)](https://github.com/RobTillaart/ADC081S/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/ADC081S/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/ADC081S.svg?maxAge=3600)](https://github.com/RobTillaart/ADC081S/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/ADC081S.svg)](https://registry.platformio.org/libraries/robtillaart/ADC081S)


# ADC081S

Arduino library for ADC081S 8 bit ADC (SPI).


## Description

This library reads the ADC ports of the ADC081S ADC convertor.

Feedback is as always welcome. 


#### Related

- https://gammon.com.au/adc  tutorial about ADC's (UNO specific)
- https://github.com/RobTillaart/MCP_ADC
- https://github.com/RobTillaart/ADS1x15  (12 & 16 bit ADC, I2C, slow)
- https://github.com/RobTillaart/PCF8591  (8 bit ADC + 1 bit DAC)
- https://github.com/RobTillaart/MCP_DAC


## Interface

```cpp
#include "ADC081S.h"
```

#### Constructors

- **ADC081S(SPIClassRP2040 \* mySPI = &SPI)** hardware constructor RP2040
- **ADC081S(SPIClass \* mySPI = &SPI)** hardware constructor other
- **ADC081S(uint8_t dataOut, uint8_t clock)**
- **void begin(uint8_t select)** set select pin.
- **int16_t maxValue()** returns maxReading of ADC, => 256


#### Base

- **uint16_t read()** reads the value of a single channel.
- **void setSPIspeed(uint32_t speed)** sets SPI clock in **Hz**, please read datasheet
of the ADC first to get optimal speed.
- **uint32_t getSPIspeed()** gets current speed in **Hz**.


### Debug

- **bool usesHWSPI()** returns true if hardware SPI is used.
- **uint32_t count()** returns number of reads since start.


## Future

#### Must

- improve documentation
- improve all
- get hardware to test

#### Should

- add shutDown() + wakeUp()  // select between normal and shutdown mode.
-

#### Could


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

