
[![Arduino CI](https://github.com/RobTillaart/AD5684/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AD5684/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AD5684/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AD5684/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AD5684/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AD5684.svg)](https://github.com/RobTillaart/AD5684/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD5684/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD5684.svg?maxAge=3600)](https://github.com/RobTillaart/AD5684/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AD5684.svg)](https://registry.platformio.org/libraries/robtillaart/AD5684)


# AD5684

Arduino library for AD5684/5/6 4 channel SPI-DAC (12/14/16 bit).


## Description

**Experimental** 

The AD5684 is a 4 channel 12 bit DAC that can be controlled over SPI.
The library also supports the AD5685 (14 bit) and the D5686 (16 bit).

Warning: the library is not tested with hardware yet, so use with care.

TO ELABORATE.

Feedback as always is welcome.

### Compatibles

Overview of related devices, number of bits, setValue range and indicative LSB

|  device  |  bits  |  range     |  % step size  |   LSB @ 5V  |  notes  |
|:--------:|:------:|:----------:|:-------------:|:-----------:|:-------:|
|  AD5684  |   12   |  0..4096   |     0.025     |  1.221 mV   |
|  AD5685  |   14   |  0..16383  |     0.0065    |  0.3053 mV  |
|  AD5686  |   16   |  0..65535  |     0.0017    |  0.0763 mV  |


### Related

- https://github.com/RobTillaart/AD5620 single channel, 12 + 14 bit
- https://github.com/RobTillaart/AD5660 single channel, 16 bit
- https://github.com/RobTillaart/AD5680 single channel, 18 bit
- https://github.com/RobTillaart/AD56x8 multi channel
- https://github.com/RobTillaart/AD568X single channel lower resolution
- https://github.com/RobTillaart/AD568X 4 channel 12, 14, 16 bit
- https://github.com/RobTillaart/MCP_DAC SPI interface


## Interface

```cpp
#include "AD5684.h"
```

### Base class

- **AD5684(uint8_t slaveSelect, SPIClassRP2040 \* mySPI = &SPI)** constructor hardware SPI (RP2040 specific).
Sets internal value to zero.
- **AD5684(uint8_t slaveSelect, SPIClass \* mySPI = &SPI)** constructor hardware SPI.
Sets internal value to zero.
- **AD5684(uint8_t slaveSelect, uint8_t spiData, uint8_t spiClock)** constructor software SPI.
Sets the software SPI pins.
Sets internal value to zero.
- **void begin()** initializes the SPI and sets internal state.
- **uint8_t getType()** returns resolution in bits (12/14/16)


### LDAC

See datasheet

- **void setLDACPin(uint8_t ldac)** configure LDAC pin.
- **bool triggerLDAC()** return false if pin not set.


### Set DAC

Channels is 0..3 to select the DAC.

- **bool setValue(uint8_t channel, uint16_t value)** set the value 
to the output channel immediately, effectively a prepare + update in one call.
Returns false if the value is out of range.
Channel must be 0..3
- **bool setAll(uint16_t value)** set the value to all channels immediately,
effectively a prepare + update in one call.
Returns false if the value is out of range.
Typical to set all to zero or midrange value.
- **uint32_t getValue(uint8_t channel)** returns set or prepared value from cache.
At power up the AD5684 will be reset to 0 (== 0 volt).
- **uint32_t getMaxValue()** returns 262143 for AD5684.
- **bool setPercentage(uint8_t channel, float percentage)** sets the output
 as a percentage 0..100%.
If percentage is out of range, it is **not** set and the function returns false.
- **float getPercentage(uint8_t channel)** returns percentage, wrapper around **getValue(uint8_t channel)**.
Might return a slightly different value than **setPercentage()** due to
rounding math.
At power up the function will return 0 as default value.


### prepare & update

prep & update separately, allows to update all channels simultaneously (see datasheet).

- **bool prepareValue(uint8_t channel, uint16_t value)**
- **bool updateAll()** update all channels.

Note: prepareValue() affects the cache of the values.


### Misc

- **void softwareReset()**
- **bool setPowerDownMode(uint8_t mode)**


|  mode                  |  value  |
|:----------------------:|:-------:|
|  AD5684_PWR_NORMAL     |   0x00  |
|  AD5684_PWR_1K         |   0x01  |
|  AD5684_PWR_100K       |   0x02  |
|  AD5684_PWR_TRI_STATE  |   0x03  |


### SPI

Adjust the performance of the SPI port.

- **void setSPIspeed(uint32_t speed)** sets SPI clock in **Hz**,
please read datasheet of the ADC first to get optimal speed.
- **uint32_t getSPIspeed()** gets current speed in **Hz**.
- **bool usesHWSPI()** returns true if HW SPI is used.


## Performance

TODO

Measurements with AD5684_demo.ino - performance of **setValue()** is the
most important. The numbers are rounded and indicative, other boards might
produce different numbers.

|  version  |  board  |  clock    |  SPI  |  calls / sec  |  Notes  |
|:---------:|:-------:|:---------:|:-----:|:-------------:|:--------|
|   0.1.0   |  UNO    |   16 MHz  |  HW   |    53500      |
|   0.1.0   |  UNO    |   16 MHz  |  SW   |     2800      |
|   0.1.0   |  ESP32  |  240 MHz  |  HW   |               |
|   0.1.0   |  ESP32  |  240 MHz  |  SW   |               |


1. ESP32 HW is equal performant for HSPI and VSPI.
   Unknown why HW SPI is 20% slower than SW SPI (transaction overhead?)

50000 - 100000 calls per second means that a 1 KHz wave can be
constructed with 50-100 values per period (max).

Please share your performance data, open an issue to report.


## Future

#### Must

- improve documentation a lot
- get hardware, 
- test the library in detail

#### Should

- add examples
- add performance tests
- add generic access to registers.
- add **setPowerDownMode(channel, mode)**
  - needs PDM cache per channel?
- add **updateChannel(uint8_t channel)**
  - needs PREP cache per channel?

#### Could



#### Wont

- set all to certain value - solved by setAll().
  - setZero(), setMidRange(), setMax()

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

