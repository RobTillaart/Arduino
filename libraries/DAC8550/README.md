
[![Arduino CI](https://github.com/RobTillaart/DAC8551/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DAC8550/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DAC8550/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DAC8550/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DAC8550/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DAC8551/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DAC8551.svg?maxAge=3600)](https://github.com/RobTillaart/DAC8551/releases)


# DAC8550 - experimental

Arduino library for DAC8550 SPI Digital Analog Convertor


## Description

The DAC8550 is a SPI based 16 bit DAC with one channel.

**WARNING** this library is not tested with real hardware yet.
It is derived from the DAC8551 library.


## Interface


### Core

- **DAC8550(uint8_t slaveSelect)** Constructor for hardware SPI, the slaveSelect pin needs to be defined.
- **DAC8550(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect)** Constructor for the software SPI
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

- **void setGPIOpins(uint8_t clk, uint8_t miso, uint8_t mosi, uint8_t select)** overrule GPIO pins of ESP32 for hardware SPI. needs to be called 
AFTER the **begin()** function.


### Power down

check datasheet for details.

- **void setPowerDown(uint8_t powerDownMode)** sets power down mode. 0 - 3.
- **uint8_t getPowerDownMode()** returns last written mode.


| Power down mode         | Value |
|:------------------------|:-----:|
| DAC8550_POWERDOWN_NORMAL   | 0 |
| DAC8550_POWERDOWN_1K       | 1 |
| DAC8550_POWERDOWN_100K     | 2 |
| DAC8550_POWERDOWN_HIGH_IMP | 3 |



## Future

- testing with real hardware


## Operation

See examples

