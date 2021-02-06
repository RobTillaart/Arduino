
[![Arduino CI](https://github.com/RobTillaart/DAC8551/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DAC8551/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DAC8551.svg?maxAge=3600)](https://github.com/RobTillaart/DAC8551/releases)

# DAC8551

Arduino library for DAC8501 DAC8531, DAC8550, DAC8551 SPI Digital Analog Convertor


## Description

The DAC8551 is a SPI based 16 bit DAC with one channel.

The DAC8501, DAC8531 and DAC8550 are drop in compatible 
They all have classed derived 1 to 1 from DAC8551.

**Warning** this library is not tested extensively


## Interface

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


### Power down

check datasheet for details.

- **void setPowerDown(uint8_t powerDownMode)** sets power down mode. 0 - 3.
- **uint8_t getPowerDownMode()** returns last written mode.

| Power down mode         | Value |
|:------------------------|:-----:|
| DAC8551_POWERDOWN_NORMAL   | 0 |
| DAC8551_POWERDOWN_1K       | 1 |
| DAC8551_POWERDOWN_100K     | 2 |
| DAC8551_POWERDOWN_HIGH_IMP | 3 |


DAC8501, DAC8531 and DAC8550 uses the same constants.


## Future

- more testing
- investigate differences between 8551 and 8550.


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

