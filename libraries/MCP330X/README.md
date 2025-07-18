
[![Arduino CI](https://github.com/RobTillaart/MCP330X/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MCP330X/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MCP330X/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MCP330X/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MCP330X/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MCP330X.svg)](https://github.com/RobTillaart/MCP330X/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MCP330X/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MCP330X.svg?maxAge=3600)](https://github.com/RobTillaart/MCP330X/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MCP330X.svg)](https://registry.platformio.org/libraries/robtillaart/MCP330X)


# MCP330X

Arduino library for MCP3302 and MCP3304 13-Bit Differential ADC, SPI


## Description

**Experimental**

This library reads the channels of the MCP3302 and MCP3304 ADC convertors.

The devices have 4 or 8 channels, 13 bit and communicates with SPI.
The library supports both hardware SPI and software SPI.
The devices are meant for 5V operation.


|  type     |  bits  |  SPS   |  channels  |  pairs  |  notes  |
|:----------|:------:|:------:|:----------:|:-------:|:--------|
|  MCP3302  |  1+12  |  100k  |      4     |    2    |
|  MCP3304  |  1+12  |  100k  |      8     |    4    |

One bit is sign bit, 12 bit is magnitude (-4096..4095).

Read datasheet for all details.

The MCP3302/04-B is slightly more accurate than the MCP3302/04-C version.

The code of the library is based upon MCP_ADC library which is quite similar.
Nevertheless not all functionality of that library is implemented.

Feedback as always is welcome.


### 0.2.0 breaking change

In 0.2.0 the Single/Differential flag is fixed after testing with hardware.
Pre 0.2.0 versions are therefore obsolete.


### Differential channel table

| Channel | diff IN+ | diff IN- | 3302 | 3304 |
|:-------:|:--------:|:--------:|:----:|:----:|
|   0     |    0     |    1     |  V   |  V   |
|   1     |    1     |    0     |  V   |  V   |
|   2     |    2     |    3     |  V   |  V   |
|   3     |    3     |    2     |  V   |  V   |
|   4     |    4     |    5     |      |  V   |
|   5     |    5     |    4     |      |  V   |
|   6     |    6     |    7     |      |  V   |
|   7     |    7     |    6     |      |  V   |

The library does not support other pairs in differential mode (yet).
ONe can do this by make two **read()** calls.


### Performance

See - MCP3302_performance.ino


Indicative numbers Arduino UNO, reading all channels / pairs (4 or 8).

MCP3304 is 2x as slow as it has 2x as much channels.


|  version  |  function  |  proto  |  clock  |  MCP3302  |  MCP3304  |
|:---------:|:----------:|:-------:|:-------:|:---------:|:---------:|
|   0.1.0   |  read      |  HWSPI  |  1 MHz  |    216    |     428   |
|   0.1.0   |  diffRead  |  HWSPI  |  1 MHz  |    200    |     404   |
|   0.1.0   |  read      |  HWSPI  |  8 MHz  |    136    |      -    |
|   0.1.0   |  diffRead  |  HWSPI  |  8 MHz  |    112    |      -    |
|   0.1.0   |  read      |  SWSPI  |         |   1892    |    3804   |
|   0.1.0   |  diffRead  |  SWSPI  |         |   1836    |    3752   |


Indicative numbers Arduino ESP32, reading all channels / pairs (4 or 8).


|  version  |  function  |  proto  |  clock  |  MCP3302  |  MCP3304  |
|:---------:|:----------:|:-------:|:-------:|:---------:|:---------:|
|   0.1.0   |  read      |  HWSPI  |  1 MHz  |    182    |    304    |
|   0.1.0   |  diffRead  |  HWSPI  |  1 MHz  |    154    |    304    |
|   0.1.0   |  read      |  HWSPI  |  8 MHz  |     54    |     -     |
|   0.1.0   |  diffRead  |  HWSPI  |  8 MHz  |     52    |     -     |
|   0.1.0   |  read      |  SWSPI  |         |     56    |    107    |
|   0.1.0   |  diffRead  |  SWSPI  |         |     55    |    108    |


TODO: verify max SPI clock frequency the device works with.


### Related

- https://gammon.com.au/adc  tutorial about ADC's (UNO specific)
- https://github.com/RobTillaart/ADS1x15  (12 & 16 bit ADC, I2C, slow)
- https://github.com/RobTillaart/MCP330X  this library
- https://github.com/RobTillaart/PCF8591  (8 bit ADC + 1 bit DAC)
- https://github.com/RobTillaart/MCP_ADC  SPI based ADC
- https://github.com/RobTillaart/MCP_DAC  SPI based DAC


## Interface

```cpp
#include "MCP330X.h"
```

### Constructors

- **MCP330X(SPIClassRP2040 \* mySPI = &SPI)** hardware constructor RP2040
- **MCP330X(SPIClass \* mySPI = &SPI)** hardware constructor other
- **MCP330X(uint8_t dataIn, uint8_t dataOut, uint8_t clock)**

The derived classes have both constructors with same parameters.
- **MCP3302(...)** constructor 1+12 bit ADC 4 channel.
- **MCP3304(...)** constructor 1+12 bit ADC 8 channel.

### Base

- **void begin(uint8_t select)** set select pin. Initialises the internals.
- **uint8_t channels()** returns the number of channels (4 or 8)
- **int16_t maxValue()** returns 4095, the maxReading of the ADC.

### Read

- **int16_t read(uint8_t channel)** reads the value of a single channel.
channel = 0..3 or 0..7.
The value returned is 0..4095.
- **int16_t differentialRead(uint8_t pair)** reads differential between two channels.
pair = 0..3 or 0..7
The value returned is -4096..4095.
Check datasheet for details. See table above.

### SPI

- **void setSPIspeed(uint32_t speed)** sets SPI clock in **Hz**, please read datasheet
of the ADC first to get optimal speed.
- **uint32_t getSPIspeed()** gets current speed in **Hz**.
- **bool usesHWSPI()** returns true if hardware SPI is used.

### Debug

- **uint32_t count()** returns number of channels reads since start.


## Future

#### Must

- improve documentation
- get hardware to test

#### Should

- verify max SPI clock frequency the device works with.
- add examples

#### Could

- check interface to extend functionality.
- int16_t differentialRead(chan1, chan2) for all pairs
- float voltage(channel) interface as 5V fixed (+ set 5.000 Vref.)
  would add float lib (footprint).
- improve performance SWSPI see figure 6.2 -> 20 bit iso 24 (16%)
  more complex, first test the lib as is.
- diffRead() short for differentialRead()?

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

