
[![Arduino CI](https://github.com/RobTillaart/DAC8554/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DAC8554/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DAC8554/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DAC8554/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DAC8554/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DAC8554/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DAC8554.svg?maxAge=3600)](https://github.com/RobTillaart/DAC8554/releases)

# DAC8554

Arduino library for DAC8554 SPI Digital Analog Convertor.


## Description

The DAC8554 is a SPI based 16 bit DAC with four channels.

**Warning** This library is not tested extensively


## Interface

### Core

- **DAC8554(uint8_t slaveSelect, uint8_t address = 0)** Constructor for hardware SPI,
since 0.2.0 the slaveSelect pin needs to be defined.
- **DAC8554(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect, uint8_t address = 0)** 
Constructor for the software SPI
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

- testing

