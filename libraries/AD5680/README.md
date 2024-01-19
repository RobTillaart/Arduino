
[![Arduino CI](https://github.com/RobTillaart/AD5680/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AD5680/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AD5680/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AD5680/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AD5680/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AD5680.svg)](https://github.com/RobTillaart/AD5680/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD5680/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD5680.svg?maxAge=3600)](https://github.com/RobTillaart/AD5680/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AD5680.svg)](https://registry.platformio.org/libraries/robtillaart/AD5680)


# AD5680

Arduino library for the AD5680 series digital analog convertor (18 bit).


## Description

**Experimental**

The AD5680 is a 18 bit DAC on paper but in fact it is a 16 bit DAC.
To get the 18 bits a 2 bit duty cycle is used to implement the last two bits.
This means that the output voltage will be fluctuating unless the two
least significant bits are 0 (zero). To dampen this fluctuation the datasheet
advises to add a LOW pass filter after the output.

Feedback, issues, improvements are welcome. 
Please file an issue on GitHub.


#### 0.3.0 Breaking change

Version 0.3.0 introduced a breaking change to improve handling the SPI dependency.
The user has to call **SPI.begin()** or equivalent before calling **AD.begin()**.
Optionally the user can provide parameters to the **SPI.begin(...)**


#### 0.2.0 breaking change

The version 0.2.0 has breaking changes in the interface. 
The essence is removal of ESP32 specific code from the library. 
This makes it possible to support the ESP32-S3 and other processors in the future. 
Also it makes the library a bit simpler to maintain.

Note the order of the parameters of the software SPI constructor has changed in 0.2.0.


#### Related

- https://github.com/RobTillaart/AD56x8 (multi channel)
- https://github.com/RobTillaart/AD568X (single channel lower resolution)
- https://github.com/RobTillaart/MCP_DAC (SPI interface)


## Interface

```cpp
#include "AD5680.h"
```

### Base class

- **AD5680(uint8_t slaveSelect, SPIClassRP2040 \* mySPI = &SPI)** constructor hardware SPI (RP2040 specific). 
Sets internal value to zero.
- **AD5680(uint8_t slaveSelect, SPIClass \* mySPI = &SPI)** constructor hardware SPI. 
Sets internal value to zero.
- **AD5680(uint8_t slaveSelect, uint8_t spiData, uint8_t spiClock)** constructor software SPI.
Sets the software SPI pins.
Sets internal value to zero.
- **void begin()** initializes the SPI and sets internal state.
- **uint8_t getType()** returns 18 (for now).


### Set DAC

- **bool setValue(uint32_t value)** set value to the output immediately, 
effectively a prepare + update in one call.
Returns false if value out of range.
- **uint32_t getValue()** returns set value 0..262143 (from cache).
At power up the AD5680 will be reset to 0 (== 0 volt).
- **bool setPercentage(float percentage)** sets the output as a percentage 0..100.
If percentage is out of range, it is not set and the function returns false.
- **float getPercentage()** returns percentage, wrapper around **getValue()**.
Might return a slightly different value than **setPercentage()** due to 
rounding errors.


#### SPI 

- **void setSPIspeed(uint32_t speed)** sets SPI clock in **Hz**,
please read datasheet of the ADC first to get optimal speed.
- **uint32_t getSPIspeed()** gets current speed in **Hz**.
- **bool usesHWSPI()** returns true if HW SPI is used.


## Performance

Measurements with AD5680_demo.ino - setValue() most important.
(numbers are rounded).

|  version  |  board  |  clock    |  SPI  |  samples / second  |  Notes  |
|:---------:|:-------:}:---------:|:-----:}:------------------:|:--------|
|   0.1.1   |  UNO    |   16 MHz  |  HW   |    53500           |
|   0.1.1   |  UNO    |   16 MHz  |  SW   |     2800           |
|   0.1.1   |  ESP32  |  240 MHz  |  HW   |    91000           |  1
|   0.1.1   |  ESP32  |  240 MHz  |  SW   |   111000           |


1. ESP32 HW is equal performant for HSPI and VSPI. 
   Unknown why HW SPI is 20% slower than SW SPI (transaction overhead?)

50000 - 100000 samples per second means that a 1 KHz wave can be 
constructed with 50-100 values per period.


## Future

#### Must

- improve documentation
- get test hardware
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

