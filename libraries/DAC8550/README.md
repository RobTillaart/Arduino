
[![Arduino CI](https://github.com/RobTillaart/DAC8550/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DAC8550/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DAC8550/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DAC8550/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DAC8550/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DAC8550.svg)](https://github.com/RobTillaart/DAC8550/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DAC8550/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DAC8550.svg?maxAge=3600)](https://github.com/RobTillaart/DAC8550/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DAC8550.svg)](https://registry.platformio.org/libraries/robtillaart/DAC8550)


# DAC8550

Arduino library for DAC8550 SPI Digital Analog Convertor.


## Description

**Experimental**

The DAC8550 is a SPI based 16 bit DAC with one channel.

The library supports both hardware SPI as software SPI (bit banging).

**WARNING** this library is not tested with real hardware yet.
It is derived from the DAC8551 library.


### 0.3.0 Breaking change

Version 0.3.0 introduced a breaking change to improve handling the SPI dependency.
The user has to call **SPI.begin()** or equivalent before calling **DAC.begin()**.
Optionally the user can provide parameters to the **SPI.begin(...)**

### 0.2.0 Breaking change

The version 0.2.0 has breaking changes in the interface. 
The essence is removal of ESP32 specific code from the library. 
This makes it possible to support the ESP32-S3 and other processors in the future. 
Also it makes the library a bit simpler to maintain.

Note order of parameters changed.

### Related

- https://github.com/RobTillaart/DAC8550 1 channel, 16 bit
- https://github.com/RobTillaart/DAC8551 1 channel, 16 bit
- https://github.com/RobTillaart/DAC8552 2 channel, 16 bit
- https://github.com/RobTillaart/DAC8554 4 channel, 16 bit
- https://github.com/RobTillaart/DAC8560 1 channel, 16 bit
- https://github.com/RobTillaart/DAC8562 2 channel, 16 bit et al.
- https://github.com/RobTillaart/MCP_DAC 1, 2 channel, 8,10,12 bit
- https://github.com/RobTillaart/AD5620  (12 bit DAC)
- https://github.com/RobTillaart/AD5680  (18 bit DAC)
- https://github.com/RobTillaart/MAX520 I2C, 4, 8 channel, 8 bit
- https://github.com/RobTillaart/MCP4725 I2C, 1 channel, 12 bit


## Interface

```cpp
#include "DAC8550"
```

### Constructor

- **DAC8550(uint8_t select, SPIClassRP2040 \* spi = &SPI)** Constructor for hardware SPI, RP2040.
- **DAC8550(uint8_t select, SPIClass \* spi = &SPI)** Constructor for hardware SPI, other.
- **DAC8550(uint8_t select, uint8_t spiData, uint8_t spiClock)** Constructor for the software SPI.
- **void begin()** initializes library internals.

### Write DAC

- **void setValue(uint16_t value)** set the value of the channel to 0 - 65535
- **uint16_t getValue()** returns the last value written.

### Hardware SPI

To be used only if one needs a specific speed.

- **void setSPIspeed(uint32_t speed)** set SPI transfer rate.
- **uint32_t getSPIspeed()** returns SPI transfer rate.
- **bool usesHWSPI()** returns true if HW SPI is used.

### Power down

check datasheet for details.

- **void setPowerDown(uint8_t powerDownMode)** sets power down mode. 0 - 3.
- **uint8_t getPowerDownMode()** returns last written mode.

| Power down mode            | Value |
|:---------------------------|:-----:|
| DAC8550_POWERDOWN_NORMAL   |   0   |
| DAC8550_POWERDOWN_1K       |   1   |
| DAC8550_POWERDOWN_100K     |   2   |
| DAC8550_POWERDOWN_HIGH_IMP |   3   |


## Operation

See examples


## Future

#### Must

- improve documentation

#### Should

- testing with real hardware

#### Could

- improve code incl readability
  - spiData => spiDataOut

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


