
[![Arduino CI](https://github.com/RobTillaart/DAC8554/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DAC8554/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DAC8554/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DAC8554/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DAC8554/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DAC8554.svg)](https://github.com/RobTillaart/DAC8554/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DAC8554/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DAC8554.svg?maxAge=3600)](https://github.com/RobTillaart/DAC8554/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DAC8554.svg)](https://registry.platformio.org/libraries/robtillaart/DAC8554)


# DAC8554

Arduino library for DAC8554 SPI Digital Analog Convertor.


## Description

The DAC8554 is a SPI based 16 bit DAC with four channels.

**Warning** This library is not tested extensively.


#### 0.4.0 Breaking change

Version 0.4.0 introduced a breaking change to improve handling the SPI dependency.
The user has to call **SPI.begin()** or equivalent before calling **DAC.begin()**.
Optionally the user can provide parameters to the **SPI.begin(...)**


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
#include "DAC8554.h"
```

### Core

- **DAC8554(uint8_t select, SPIClassRP2040 \* spi = &SPI)** Constructor HW SPI RP2040.
- **DAC8554(uint8_t select, SPIClass \* spi = &SPI)** Constructor HW SPI other.
- **DAC8554(uint8_t select, uint8_t spiData, uint8_t spiClock)** Constructor SW SPI.
- **DAC8534(...)** idem constructors for DAC8534.
- **void begin()** initializes all pins to default state
- **void setValue(uint8_t channel, uint16_t value)** set the value of the channel to 0 - 65535
- **void setSingleValue(uint8_t channel, uint16_t value)** writes the value to the channel but 
does not affect buffered ones. TODO - elaborate.
- **uint16_t getValue(uint8_t channel)** returns the last value written.


### Hardware SPI

To be used only if one needs a specific speed.

- **void setSPIspeed(uint32_t speed)** set SPI transfer rate.
- **uint32_t getSPIspeed()** returns SPI transfer rate.
- **bool usesHWSPI()** returns true if HW SPI is used.


### Power down

Check datasheet for details.

- **void setPowerDown(uint8_t powerDownMode)** sets power down mode. 0 - 3.
- **uint8_t getPowerDownMode()** returns last written mode.
- **void setSinglePowerDown(uint8_t channel, uint8_t powerDownMode)** does not affect other channels.

| Power down mode             | Value |
|:----------------------------|:-----:|
| DAC8554_POWERDOWN_NORMAL    |  0x00 |
| DAC8554_POWERDOWN_1K        |  0x40 |
| DAC8554_POWERDOWN_100K      |  0x80 |
| DAC8554_POWERDOWN_HIGH_IMP  |  0xC0 |


### Broadcast

- **void bufferValue(uint8_t channel, uint16_t value)** prepare a new value for a channel. 
- **void broadcastBuffer()** write all buffers to all(up to 4) 8554's channel's.
- **void broadcastValue(uint16_t value)** write value to all(up to 4) 8554's channel's.
- **void broadcastPowerDown(uint8_t powerDownMode)** write powerDownMode to all 8554's channel's.


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
- add channels?

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,
