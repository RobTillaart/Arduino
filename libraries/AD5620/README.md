
[![Arduino CI](https://github.com/RobTillaart/AD5620/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AD5620/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AD5620/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AD5620/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AD5620/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AD5620.svg)](https://github.com/RobTillaart/AD5620/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD5620/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD5620.svg?maxAge=3600)](https://github.com/RobTillaart/AD5620/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AD5620.svg)](https://registry.platformio.org/libraries/robtillaart/AD5620)


# AD5620

Arduino library for the AD5620 series digital analog convertor (12 bit).


## Description

**Experimental** 

The AD5620 is a 12 bit DAC, which is to be controlled by SPI.
This library supports both hardware as software SPI.

The library is not tested extensively so use with care.

The library also implements support for the AD5640, a 14 bit DAC.


Feedback, issues, improvements are welcome. 
Please file an issue on GitHub.


### Related

- https://github.com/RobTillaart/AD5620 (single channel, 12 bit)
- https://github.com/RobTillaart/AD5680 (single channel, 18 bit)
- https://github.com/RobTillaart/AD56x8 (multi channel)
- https://github.com/RobTillaart/AD568X (single channel lower resolution)
- https://github.com/RobTillaart/MCP_DAC (SPI interface)


## Interface

```cpp
#include "AD5620.h"
```

### Base class

The AD5640 has identical constructors.

- **AD5620(uint8_t slaveSelect, SPIClassRP2040 \* mySPI = &SPI)** constructor hardware SPI (RP2040 specific). 
Sets internal value to zero.
- **AD5620(uint8_t slaveSelect, SPIClass \* mySPI = &SPI)** constructor hardware SPI. 
Sets internal value to zero.
- **AD5620(uint8_t slaveSelect, uint8_t spiData, uint8_t spiClock)** constructor software SPI.
Sets the software SPI pins.
Sets internal value to zero.
- **void begin()** initializes the SPI and sets internal state.
- **uint8_t getType()** returns 12 for AD5620.


### Set DAC

- **bool setValue(uint16_t value)** set value to the output immediately, 
effectively a prepare + update in one call.
Returns false if value out of range.
- **uint16_t getValue()** returns set value 0..262143 (from cache).
At power up the AD5620 will be reset to 0 (== 0 volt).
- **uint16_t getMaxValue()** returns 4095 for AD5620.
- **bool setPercentage(float percentage)** sets the output as a percentage 0..100.
If percentage is out of range, it is not set and the function returns false.
- **float getPercentage()** returns percentage, wrapper around **getValue()**.
Might return a slightly different value than **setPercentage()** due to 
rounding math.
At power up the function will return 0 as default value.


SetValue range and indicative LSB

|  device  |  range     |  LSB @ 5V  |
|:--------:|:----------:|:----------:|
|  AD5620  |   0..4095  |  1.221 mV  |
|  AD5640  |  0..16383  |  0.3053 mV |


### Power down

See datasheet P19 for details.

- **bool setPowerDownMode(uint8_t mode)** returns false if mode is out of range.
- **uint8_t getPowerDownMode()** returns set power down mode, default 0.


|  mode  |  description            |
|:------:|:------------------------|
|   0    |  normal mode (default)  |
|   1    |  1 Kohm to GND          |
|   2    |  100 Kohm to GND        |
|   3    |  Threestate             |


### SPI

Adjust the performance of the SPI port.

- **void setSPIspeed(uint32_t speed)** sets SPI clock in **Hz**,
please read datasheet of the ADC first to get optimal speed.
- **uint32_t getSPIspeed()** gets current speed in **Hz**.
- **bool usesHWSPI()** returns true if HW SPI is used.

Datasheet max frequency. Overclocking not tested.

|  Voltage  |  Max Speed  |
|:---------:|:-----------:|
|   2.7 V   |   20 MHz    |
|   3.5 V   |   20 MHz    |
|           |             |
|   3.6 V   |   30 MHz    |
|   5.5 V   |   30 MHz    |


## Performance

Measurements with AD5620_demo.ino - setValue() most important.
(numbers are rounded and indicative, other boards might differ).

|  version  |  board  |  clock    |  SPI  |  calls / sec  |  Notes  |
|:---------:|:-------:}:---------:|:-----:}:--------- ---:|:--------|
|   0.1.0   |  UNO    |   16 MHz  |  HW   |    70900      |  max SPI speed
|   0.1.0   |  UNO    |   16 MHz  |  SW   |     5289      |
|   0.1.0   |  ESP32  |  240 MHz  |  HW   |               |  1
|   0.1.0   |  ESP32  |  240 MHz  |  SW   |               |


1. ESP32 HW is equal performant for HSPI and VSPI. 
   Unknown why HW SPI is 20% slower than SW SPI (transaction overhead?)

70000 calls per second means that a 1 KHz wave can be 
constructed with 70 values per period (max).


## Future

#### Must

- improve documentation
- get hardware
- test the library

#### Should

- add examples

#### Could



#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

