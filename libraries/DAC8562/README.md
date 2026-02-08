
[![Arduino CI](https://github.com/RobTillaart/DAC8562/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DAC8562/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DAC8562/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DAC8562/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DAC8562/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DAC8562.svg)](https://github.com/RobTillaart/DAC8562/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DAC8562/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DAC8562.svg?maxAge=3600)](https://github.com/RobTillaart/DAC8562/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DAC8562.svg)](https://registry.platformio.org/libraries/robtillaart/DAC8562)


# DAC8562

Arduino library for DAC8562 SPI 16 bit dual channel DAC.


## Description

**Experimental**

The DAC8562 is a SPI based 16 bit DAC with two channels.

This library is based upon the DAC8560 16 bit single channel DAC.

The library is "work in progress" and supports the basic DAC functions.
More functionality can be added in the future on request.

The library supports also the following devices as derived classes.
These are all dual channel.

|  device   |  bits  |   max   |  Power On Reset  |  Notes  |
|:---------:|:------:|:-------:|:----------------:|:-------:|
|  DAC7562  |   12   |   4095  |       zero       |
|  DAC7563  |   12   |   4095  |     midscale     |
|  DAC8162  |   14   |  16383  |       zero       |
|  DAC8163  |   14   |  16383  |     midscale     |
|  DAC8562  |   16   |  65535  |       zero       |
|  DAC8563  |   16   |  65535  |     midscale     |


This library is not tested with hardware yet, so use with care.

As always, feedback is welcome!


### Related

- https://github.com/RobTillaart/DAC8550 1 channel, 16 bit
- https://github.com/RobTillaart/DAC8551 1 channel, 16 bit
- https://github.com/RobTillaart/DAC8552 2 channel, 16 bit
- https://github.com/RobTillaart/DAC8554 4 channel, 16 bit
- https://github.com/RobTillaart/DAC8560 1 channel, 16 bit
- https://github.com/RobTillaart/DAC8562 2 channel, 16 bit et al.
- https://github.com/RobTillaart/MCP_DAC 1, 2 channel, 8,10,12 bit
- https://github.com/RobTillaart/AD5620 (12 bit DAC)
- https://github.com/RobTillaart/AD5680 (18 bit DAC)
- https://github.com/RobTillaart/MAX520 I2C, 4, 8 channel, 8 bit
- https://github.com/RobTillaart/MCP4725 I2C, 1 channel, 12 bit


## Interface

```cpp
#include "DAC8562.h"
```

### Core

- **DAC8562(uint8_t select, SPIClassRP2040 \* spi = &SPI, uint8_t LDAC = 255, uint8_t CLR = 255)** Constructor HW SPI RP2040.
- **DAC8562(uint8_t select, SPIClass \* spi = &SPI, uint8_t LDAC = 255, uint8_t CLR = 255)** Constructor HW SPI other.
- **DAC8562(uint8_t select, uint8_t spiData, uint8_t spiClock, uint8_t LDAC = 255, uint8_t CLR = 255)** Constructor SW SPI.
- **void begin()** initializes all pins to default state. 
Sets the cached values to either midpoint or zero. 

Other derived classes have similar constructors.


### SetValue

- **void setValue(uint16_t value)** set the value of both channels to 0 - 65535
- **void setValue(uint8_t channel, uint16_t value)** set the value of the channel to 0 - 65535
- **uint16_t getValue(uint8_t channel)** returns the last value written to channel.
This is returned from cache!
- **uint16_t getMaxValue()** returns the maximum value that can be set.


### Power down

See datasheet for details.

- **void setPowerDownMode(uint8_t powerDownMode)** sets power down mode. 0 - 3.
- **uint8_t getPowerDownMode()** returns last written mode.

| Power down mode            | Value |
|:---------------------------|:-----:|
| DAC8562_POWERDOWN_NORMAL   |   0   |
| DAC8562_POWERDOWN_1K       |   1   |
| DAC8562_POWERDOWN_100K     |   2   |
| DAC8562_POWERDOWN_HIGH_IMP |   3   |


### Internal Reference

See datasheet 7.3.5 Enable/Disable Internal Reference, P21. TODO CHECK

The DAC8562 has an internal reference voltage of 2.5 volt.
The internal reference is default enabled.
One can use this or use an external reference via **Vref** pin.

Unknown if the voltage of the internal Vref can be measured
on the **Vref** pin.

- **void enableInternalReference()** idem.
- **void disableInternalReference()** idem.


### Hardware SPI

To be used only if one needs a specific speed.

- **void setSPIspeed(uint32_t speed)** set SPI transfer rate.
- **uint32_t getSPIspeed()** returns SPI transfer rate.
- **bool usesHWSPI()** returns true if HW SPI is used.


## Future

#### Must

- improve documentation
- keep in sync with DAC8551 if possible.
- test with hardware
  - test basic DAC usage.
  - test internal reference
  - test powerDown

#### Should

- make functional complete => table 12 / 13
  - generic function to set big mask
- should begin get a parameter(value) to initialize the DAC?
- 8.4.6 LDAC Functionality - it must be connected to GND
permanently or asserted and held low before sending commands to the device.

#### Could

- support CLR  (?) how to know the reset value for getValue()?
- extend unit tests

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

