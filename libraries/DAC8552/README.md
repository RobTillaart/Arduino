
[![Arduino CI](https://github.com/RobTillaart/DAC8552/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DAC8552/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DAC8552.svg?maxAge=3600)](https://github.com/RobTillaart/DAC8552/releases)


# DAC8552

Arduino library for DAC8552 SPI Digital Analog Convertor


## Description

The DAC8552 is a SPI based 16 bit DAC with two channels.

**Warning** This library is not tested extensively


## Interface

### Core

- **DAC8552(uint8_t slaveSelect)** Constructor for hardware SPI,
since 0.2.0 the slaveSelect pin needs to be defined.
- **DAC8552(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect)** Constructor for the software SPI
- **void begin()** initializes all pins to default state
- **void bufferValue(uint8_t channel, uint16_t value)**
- **void setValue(uint8_t channel, uint16_t value)** set the value of the chosen channel to 0 - 65535
- **uint16_t getValue(uint8_t channel)**returns the last value written.


### Power down

Check datasheet for details.

- **void bufferPowerDown(uint8_t channel, uint8_t powerDownMode)** ets power down mode. 0 - 3, 
but waits until (TODO CHECK DATASHEET)
- **void setPowerDown(uint8_t channel, uint8_t powerDownMode)** sets power down mode. 0 - 3.
- **uint8_t getPowerDownMode(uint8_t channel)** returns last written mode.

| Power down mode         | Value |
|:------------------------|:-----:|
| DAC8552_POWERDOWN_NORMAL   | 0 |
| DAC8552_POWERDOWN_1K       | 1 |
| DAC8552_POWERDOWN_100K     | 2 |
| DAC8552_POWERDOWN_HIGH_IMP | 3 |


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


## TODO

more testing
