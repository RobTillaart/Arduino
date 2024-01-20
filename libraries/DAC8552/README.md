
[![Arduino CI](https://github.com/RobTillaart/DAC8552/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DAC8552/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DAC8552/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DAC8552/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DAC8552/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DAC8552.svg)](https://github.com/RobTillaart/DAC8552/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DAC8552/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DAC8552.svg?maxAge=3600)](https://github.com/RobTillaart/DAC8552/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DAC8552.svg)](https://registry.platformio.org/libraries/robtillaart/DAC8552)


# DAC8552

Arduino library for DAC8552 SPI Digital Analog Convertor.


## Description

The DAC8552 is a SPI based 16 bit DAC with two channels.

**Warning** This library is not tested extensively.



#### 0.5.0 Breaking change

Version 0.5.0 introduced a breaking change to improve handling the SPI dependency.
The user has to call **SPI.begin()** or equivalent before calling **DAC.begin()**.
Optionally the user can provide parameters to the **SPI.begin(...)**


#### 0.4.0 Breaking change

Bugfix channel select bit, invalidates all pre 0.4.0 versions


#### 0.3.0 Breaking change

The version 0.3.0 has breaking changes in the interface. 
The essence is removal of ESP32 specific code from the library. 
This makes it possible to support the ESP32-S3 and other processors in the future. 
Also it makes the library a bit simpler to maintain.

Note order of parameters changed.


#### Related

- https://github.com/RobTillaart/DAC8550
- https://github.com/RobTillaart/DAC8551
- https://github.com/RobTillaart/DAC8552
- https://github.com/RobTillaart/DAC8554
- https://github.com/RobTillaart/MCP_DAC
- https://github.com/RobTillaart/AD5680  (18 bit DAC)


## Interface

```cpp
#include "DAC8552.h"
```

### Core

- **DAC8552(uint8_t select, SPIClassRP2040 \* spi = &SPI)** Constructor HW SPI RP2040.
- **DAC8552(uint8_t select, SPIClass \* spi = &SPI)** Constructor HW SPI other.
- **DAC8552(uint8_t select, uint8_t spiData, uint8_t spiClock)** Constructor SW SPI.
- **DAC8532(...)** idem constructors for DAC8532.
- **void begin()** initializes all pins to default state
- **void bufferValue(uint8_t channel, uint16_t value)**
- **void setValue(uint8_t channel, uint16_t value)** set the value of the chosen channel to 0 - 65535
- **uint16_t getValue(uint8_t channel)**returns the last value written.


### Hardware SPI

To be used only if one needs a specific speed.

- **void setSPIspeed(uint32_t speed)** set SPI transfer rate.
- **uint32_t getSPIspeed()** returns SPI transfer rate.
- **bool usesHWSPI()** returns true if HW SPI is used.


### Power down

Check datasheet for details.

- **void bufferPowerDown(uint8_t channel, uint8_t powerDownMode)** ets power down mode. 0 - 3, 
but waits until (TODO CHECK DATASHEET)
- **void setPowerDown(uint8_t channel, uint8_t powerDownMode)** sets power down mode. 0 - 3.
- **uint8_t getPowerDownMode(uint8_t channel)** returns last written mode.

| Power down mode            | Value |
|:---------------------------|:-----:|
| DAC8552_POWERDOWN_NORMAL   |   0   |
| DAC8552_POWERDOWN_1K       |   1   |
| DAC8552_POWERDOWN_100K     |   2   |
| DAC8552_POWERDOWN_HIGH_IMP |   3   |



## Operation

See examples

**demo_hw_spi.ino**
- write a sawtooth to channel A followed by a sinus 
- uses HW SPI

**demo_sw_spi.ino**
- write a sawtooth to channel A followed by a sinus 
- uses SW SPI

**demo_same_time_write.ino**
- writes two square waves that trigger at the same time

**demo_sequential_write.ino**
- writes two square waves sequentially (slight time difference)

**demo_powerdown.ino**
- idem


## Future

#### Must

- improve documentation
- testing with hardware


#### Should

#### Could

- performance measurements


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

