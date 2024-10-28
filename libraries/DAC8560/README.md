
[![Arduino CI](https://github.com/RobTillaart/DAC8560/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DAC8560/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DAC8560/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DAC8560/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DAC8560/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DAC8560.svg)](https://github.com/RobTillaart/DAC8560/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DAC8560/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DAC8560.svg?maxAge=3600)](https://github.com/RobTillaart/DAC8560/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DAC8560.svg)](https://registry.platformio.org/libraries/robtillaart/DAC8560)


# DAC8560

Arduino library for DAC8560 SPI Digital Analog Convertor (16 bit).


## Description

**Experimental**

The DAC8560 is a SPI based 16 bit DAC with one channel.

This library is not tested yet, so use with care.


#### Related

- https://github.com/RobTillaart/DAC8550
- https://github.com/RobTillaart/DAC8561
- https://github.com/RobTillaart/DAC8552
- https://github.com/RobTillaart/DAC8554
- https://github.com/RobTillaart/DAC8560
- https://github.com/RobTillaart/MCP_DAC
- https://github.com/RobTillaart/AD5620  (12 bit DAC)
- https://github.com/RobTillaart/AD5680  (18 bit DAC)


## Interface

```cpp
#include "DAC8560.h"
```

### Core

- **DAC8560(uint8_t select, SPIClassRP2040 \* spi = &SPI)** Constructor HW SPI RP2040.
- **DAC8560(uint8_t select, SPIClass \* spi = &SPI)** Constructor HW SPI other.
- **DAC8560(uint8_t select, uint8_t spiData, uint8_t spiClock)** Constructor SW SPI.
- **void begin()** initializes all pins to default state
- **void setValue(uint16_t value)** set the value of the channel to 0 - 65535
- **uint16_t getValue()** returns the last value written.


### Hardware SPI

To be used only if one needs a specific speed.

- **void setSPIspeed(uint32_t speed)** set SPI transfer rate.
- **uint32_t getSPIspeed()** returns SPI transfer rate.
- **bool usesHWSPI()** returns true if HW SPI is used.


### Power down

See datasheet for details.

- **void setPowerDownMode(uint8_t powerDownMode)** sets power down mode. 0 - 3.
- **uint8_t getPowerDownMode()** returns last written mode.

| Power down mode            | Value |
|:---------------------------|:-----:|
| DAC8560_POWERDOWN_NORMAL   |   0   |
| DAC8560_POWERDOWN_1K       |   1   |
| DAC8560_POWERDOWN_100K     |   2   |
| DAC8560_POWERDOWN_HIGH_IMP |   3   |


### Internal Reference

See datasheet 7.3.5 Enable/Disable Internal Reference, P21.

The DAC8560 has an internal reference voltage of 2.5 volt.
The internal reference is default enabled.
One can use this or use an external reference via **Vref** pin.

Unknown if the voltage of the internal Vref can be measured
on the **Vref** pin.

- **void enableInternalReference()** idem.
- **void disableInternalReference()** idem.


## Future

#### Must

- improve documentation
- keep in sync with DAC8551 if possible.
- test with hardware
  - test basic DAC usage.
  - test internal reference
  - test powerDown

#### Should


#### Could


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

