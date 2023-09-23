
[![Arduino CI](https://github.com/RobTillaart/DAC8551/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DAC8551/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DAC8551/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DAC8551/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DAC8551/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DAC8551.svg)](https://github.com/RobTillaart/DAC8551/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DAC8551/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DAC8551.svg?maxAge=3600)](https://github.com/RobTillaart/DAC8551/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DAC8551.svg)](https://registry.platformio.org/libraries/robtillaart/DAC8551)


# DAC8551

Arduino library for DAC8501 DAC8531, DAC8550, DAC8551 SPI Digital Analog Convertor.


## Description

The DAC8551 is a SPI based 16 bit DAC with one channel.

The DAC8501, DAC8531 and DAC8550 are drop in compatible.
They all have classes derived 1 to 1 from DAC8551.

**Warning** this library is not tested extensively.


#### Related

- https://github.com/RobTillaart/AD5680  (18 bit DAC)


## Interface

```cpp
#include "DAC8551.h"
```

### Core

- **DAC8501(uint8_t slaveSelect)** Constructor for DAC8501 with hardware SPI,
- **DAC8531(uint8_t slaveSelect)** Constructor for DAC8531 with hardware SPI,
- **DAC8550(uint8_t slaveSelect)** Constructor for DAC8550 with hardware SPI,
- **DAC8551(uint8_t slaveSelect)** Constructor for DAC8551 with hardware SPI,
since 0.2.0 the slaveSelect pin needs to be defined.
- **DAC8501(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect)** Constructor for the software SPI
- **DAC8531(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect)** Constructor for the software SPI
- **DAC8550(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect)** Constructor for the software SPI
- **DAC8551(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect)** Constructor for the software SPI
- **void begin()** initializes all pins to default state
- **void setValue(uint16_t value)** set the value of the channel to 0 - 65535
- **uint16_t getValue()** returns the last value written.


### Hardware SPI

To be used only if one needs a specific speed.

- **void setSPIspeed(uint32_t speed)** set SPI transfer rate.
- **uint32_t getSPIspeed()** returns SPI transfer rate.
- **bool usesHWSPI()** returns true if HW SPI is used.


### ESP32 specific

- **void selectHSPI()** in case hardware SPI, the ESP32 has two options HSPI and VSPI.
- **void selectVSPI()** see above.
- **bool usesHSPI()** returns true if HSPI is used.
- **bool usesVSPI()** returns true if VSPI is used.

The **selectVSPI()** or the **selectHSPI()** needs to be called 
BEFORE the **begin()** function.


#### experimental

- **void setGPIOpins(uint8_t clk, uint8_t miso, uint8_t mosi, uint8_t select)** 
overrule GPIO pins of ESP32 for hardware SPI. 
Needs to be called AFTER the **begin()** function.


### Power down

check datasheet for details.

- **void setPowerDown(uint8_t powerDownMode)** sets power down mode. 0 - 3.
- **uint8_t getPowerDownMode()** returns last written mode.

| Power down mode            | Value |
|:---------------------------|:-----:|
| DAC8551_POWERDOWN_NORMAL   |   0   |
| DAC8551_POWERDOWN_1K       |   1   |
| DAC8551_POWERDOWN_100K     |   2   |
| DAC8551_POWERDOWN_HIGH_IMP |   3   |


Note: DAC8501, DAC8531 and DAC8550 uses the same constants.


## Operation

See examples

**demo_hw_spi.ino**
- write a sawtooth to channel A followed by a sinus 
- uses HW SPI

**demo_sw_spi.ino**
- write a sawtooth to channel A followed by a sinus 
- uses SW SPI

**demo_powerdown.ino**
- idem


## Future

#### Must

- improve documentation


#### Should 

- testing (DAC8531 is verified, see example)
- verify replacement chips


#### Could


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

